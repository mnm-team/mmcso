#include <vector>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <mpi.h>
#include <omp.h>

#ifndef _GNU_SOURCE
#    define _GNU_SOURCE
#endif /* _GNU_SOURCE */
#include <unistd.h>

struct alignas(CLSIZE) measurement {
    double post_time{0.0};
    double wait_time{0.0};
    double comp_time{0.0};
    double comm_time{0.0};
};

#if USE_MEMORY_INTENSIVE_WORK
#define ARRAY_SIZE 500000000 // 500MB
thread_local char *a{nullptr};
thread_local char *b{nullptr};

static void do_work(int work)
{
    work = 10 * work;
    thread_local static int i{0};
    if (i + work > ARRAY_SIZE) {
        i = 0;
    }
    memcpy(a + i, b + i, work);
    i += work;
}
#else
static void do_work(int work)
{
    struct timespec ts{};
    ts.tv_sec  = 0;
    ts.tv_nsec = work;
    nanosleep(&ts, NULL);
}
#endif

int main(int argc, char *argv[])
{
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    int rank;
    int num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (provided != MPI_THREAD_MULTIPLE) {
        if (rank == 0) {
            fprintf(stderr, "Provided thread support level below MPI_THREAD_MULTIPLE. Abort...\n");
        }
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    const char *csv_file_default = "bench.csv";

    int   nthreads = omp_get_max_threads();
    int   work     = 0;
    int   msg_size = 1;
    int   rep      = 20000;
    char *csv_file = (char *)csv_file_default;
    bool intel_async{false};

    int opt;
    while ((opt = getopt(argc, argv, "m:r:f:w:a")) != -1) {
        switch (opt) {
        case 'a':
            intel_async = true;
            break;
        case 'm':
            msg_size = atoi(optarg);
            break;
        case 'f':
            csv_file = optarg;
            break;
        case 'r':
            rep = atoi(optarg);
            break;
        case 'w':
            work = atoi(optarg);
            break;
        default: /* '?' */
                 // usage:
            fprintf(stderr, "Usage: %s [-m message size] [-w work] [-r repetitions] [-f csv file]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    MPI_Info info;
    MPI_Info_create(&info);
    MPI_Info_set(info, "mpi_assert_no_any_tag", "true");
    MPI_Info_set(info, "mpi_assert_no_any_source", "true");
    MPI_Info_set(info, "mpi_assert_exact_length", "true");
    MPI_Info_set(info, "mpi_assert_allow_overtaking", "true");
    if(intel_async) {
        MPI_Info_set(info, "thread_id", "0"); // for using 1 Intel async progress thread
        // see:
        // https://www.intel.com/content/www/us/en/docs/mpi-library/developer-guide-linux/2021-16/async-progress-sample-c.html
    }
    MPI_Comm_set_info(MPI_COMM_WORLD, info);
    MPI_Info_free(&info);

    std::vector<measurement> m(nthreads);
    std::vector<MPI_Comm>    communicators(nthreads);

    for (int i = 0; i < nthreads; ++i) {
        if (MPI_Comm_dup(MPI_COMM_WORLD, &communicators[i]) != MPI_SUCCESS) {
            fprintf(stderr, "MPI_Comm_dup\n");
        }
    }

    FILE *csv_out = fopen(csv_file, "a");
    if (!csv_out) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // rank 0 <-> rank 1 <-> ... <-> rank N-1 <-> rank 0
    int rank_send = (rank + 1) % num_procs;
    int rank_recv = (rank + num_procs - 1) % num_procs;

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        size_t num_pages  = ((msg_size * sizeof(int) + PAGESIZE - 1) / PAGESIZE);
        size_t alloc_size = num_pages * PAGESIZE;

        int *sendbuf = (int *)aligned_alloc(PAGESIZE, alloc_size);
        int *recvbuf = (int *)aligned_alloc(PAGESIZE, alloc_size);
        if (!sendbuf || !recvbuf) {
            perror("aligned_alloc");
            exit(EXIT_FAILURE);
        }

#if USE_MEMORY_INTENSIVE_WORK
        num_pages  = ((ARRAY_SIZE + PAGESIZE - 1) / PAGESIZE);
        alloc_size = num_pages * PAGESIZE;

        a = (char *)aligned_alloc(PAGESIZE, alloc_size);
        b = (char *)aligned_alloc(PAGESIZE, alloc_size);
        if (!a || !b) {
            perror("aligned_alloc");
            exit(EXIT_FAILURE);
        }
        memset(a, 0x0, alloc_size);
        memset(b, 0x0, alloc_size);
#endif

        for (int i = 0; i < msg_size; ++i) {
            sendbuf[i] = thread_id + i;
        }

#pragma omp barrier

        for (int i = 0; i < rep; ++i) {

            MPI_Status  status_s, status_r;
            MPI_Request request_s, request_r;

            double time_start = omp_get_wtime();
            double total_time = time_start;
            double time_end;

            MPI_Irecv(recvbuf, msg_size, MPI_INT, rank_recv, thread_id, communicators[thread_id], &request_r);
            MPI_Isend(sendbuf, msg_size, MPI_INT, rank_send, thread_id, communicators[thread_id], &request_s);

            time_end = omp_get_wtime();

            m[thread_id].post_time += time_end - time_start;

            time_start = time_end;
            if (work) {
                do_work(work);
            }
            time_end = omp_get_wtime();

            m[thread_id].comp_time += time_end - time_start;

            time_start = time_end;

            MPI_Wait(&request_s, &status_s);
            MPI_Wait(&request_r, &status_r);

            time_end = omp_get_wtime();

            m[thread_id].wait_time += time_end - time_start;
            m[thread_id].comm_time += time_end - total_time;

#pragma omp barrier

#if !defined(NDEBUG)
            int count;
            MPI_Get_count(&status_r, MPI_INT, &count);
            assert(status_r.MPI_SOURCE == rank_recv);
            assert(status_r.MPI_TAG == thread_id);
            assert(count == msg_size);
            for (int i = 0; i < msg_size; ++i) {
                assert(recvbuf[i] == thread_id + i);
                recvbuf[i] = -1;
            }
#endif

#pragma omp barrier
        }
        free(sendbuf);
        free(recvbuf);

#if USE_MEMORY_INTENSIVE_WORK
        free(a);
        free(b);
#endif
    } // parallel region end

    // MPI_Barrier(MPI_COMM_WORLD);

    double post_time = 0.0;
    double wait_time = 0.0;
    double comp_time = 0.0;
    double comm_time = 0.0;

    for (int i = 0; i < nthreads; ++i) {
        post_time += m[i].post_time;
        wait_time += m[i].wait_time;
        comp_time += m[i].comp_time;
        comm_time += m[i].comm_time;
    }

    printf("[rank %d] post time (avg. per thread and iter): %fus\n", rank, 1.0e6 * post_time / nthreads / rep);
    printf("[rank %d] wait time (avg. per thread and iter): %fus\n", rank, 1.0e6 * wait_time / nthreads / rep);
    printf("[rank %d] comp time (avg. per thread and iter): %fus\n", rank, 1.0e6 * comp_time / nthreads / rep);
    printf("[rank %d] comm time (avg. per thread and iter): %fus\n", rank, 1.0e6 * comm_time / nthreads / rep);
    printf("[rank %d] overlap: %.2lf%%\n", rank, 100. * comp_time / comm_time);
    fflush(stdout);

    for (int i = 0; i < nthreads; ++i) {
        fprintf(csv_out,
                "%d,%d,%d,%d,%d,%zu,%f,%f,%f,%f\n",
                rank,
                nthreads,
                i,
                rep,
                work,
                msg_size * sizeof(int),
                m[i].post_time,
                m[i].wait_time,
                m[i].comp_time,
                m[i].comm_time);
    }
    fflush(csv_out);
    fclose(csv_out);

    MPI_Finalize();
    return 0;
}
