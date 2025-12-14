#include <utility> // std::move

#include "config.h"
#include "mpi_command.h"

#include <mpi.h>

using mmcso::OffloadCommand;
using mmcso::make_mpi_callable;

extern "C" {

int MPI_Allgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iallgather(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iallgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iallgather, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Allgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iallgatherv(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(displs), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iallgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iallgatherv, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(displs), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Allreduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iallreduce(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iallreduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iallreduce, true>(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Alltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ialltoall(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ialltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ialltoall, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Alltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ialltoallv(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ialltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ialltoallv, true>(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Alltoallw(const void * sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ialltoallw(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtypes), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtypes), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ialltoallw(const void * sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ialltoallw, true>(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtypes), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtypes), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Barrier(MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ibarrier(std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ibarrier(MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ibarrier, true>(std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Bcast(void * buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ibcast(std::move(buffer), std::move(count), std::move(datatype), std::move(root), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Bsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ibsend(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ibcast(void * buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ibcast, true>(std::move(buffer), std::move(count), std::move(datatype), std::move(root), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Comm_dup(MPI_Comm comm, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    MPI_Comm_idup(std::move(comm), std::move(newcomm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Comm_idup(MPI_Comm comm, MPI_Comm * newcomm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_idup, true>(std::move(comm), std::move(newcomm)), request});
    return MPI_SUCCESS;
}

int MPI_Exscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iexscan(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iexscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iexscan, true>(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iread_at(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iread_at_all(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iwrite_at(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iwrite_at_all(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iread_at, true>(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iwrite_at, true>(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iread_at_all, true>(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iwrite_at_all, true>(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_read(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iread(std::move(fh), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_read_all(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iread_all(std::move(fh), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_write(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iwrite(std::move(fh), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_write_all(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iwrite_all(std::move(fh), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_iread(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iread, true>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iwrite(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iwrite, true>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iread_all(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iread_all, true>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iwrite_all(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iwrite_all, true>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_read_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iread_shared(std::move(fh), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_write_shared(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_File_iwrite_shared(std::move(fh), std::move(buf), std::move(count), std::move(datatype), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_File_iread_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iread_shared, true>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_File_iwrite_shared(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_iwrite_shared, true>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), request});
    return MPI_SUCCESS;
}

int MPI_Gather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Igather(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(root), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Igather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Igather, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(root), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Gatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Igatherv(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(displs), std::move(recvtype), std::move(root), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Igatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Igatherv, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(displs), std::move(recvtype), std::move(root), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Ibsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ibsend, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Improbe(int source, int tag, MPI_Comm comm, int * flag, MPI_Message * message, MPI_Status * status)
{
    MPI_Request request_local = MPI_REQUEST_NULL; // TODO
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Improbe, false>(std::move(source), std::move(tag), std::move(comm), std::move(flag), std::move(message), std::move(status)), &request_local});
    return MPI_SUCCESS;
}

int MPI_Imrecv(void * buf, int count, MPI_Datatype type, MPI_Message * message, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Imrecv, true>(std::move(buf), std::move(count), std::move(type), std::move(message)), request});
    return MPI_SUCCESS;
}

int MPI_Iprobe(int source, int tag, MPI_Comm comm, int * flag, MPI_Status * status)
{
    MPI_Request request_local = MPI_REQUEST_NULL; // TODO
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iprobe, false>(std::move(source), std::move(tag), std::move(comm), std::move(flag), std::move(status)), &request_local});
    return MPI_SUCCESS;
}

int MPI_Irecv(void * buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Irecv, true>(std::move(buf), std::move(count), std::move(datatype), std::move(source), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Irsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Irsend, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Isend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Isend, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Issend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Issend, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Mrecv(void * buf, int count, MPI_Datatype type, MPI_Message * message, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_Imrecv(std::move(buf), std::move(count), std::move(type), std::move(message), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Neighbor_allgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ineighbor_allgather(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ineighbor_allgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ineighbor_allgather, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Neighbor_allgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ineighbor_allgatherv(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(displs), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ineighbor_allgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ineighbor_allgatherv, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(displs), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Neighbor_alltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ineighbor_alltoall(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ineighbor_alltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ineighbor_alltoall, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Neighbor_alltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ineighbor_alltoallv(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtype), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ineighbor_alltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void * recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ineighbor_alltoallv, true>(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtype), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtype), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Neighbor_alltoallw(const void * sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ineighbor_alltoallw(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtypes), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtypes), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ineighbor_alltoallw(const void * sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ineighbor_alltoallw, true>(std::move(sendbuf), std::move(sendcounts), std::move(sdispls), std::move(sendtypes), std::move(recvbuf), std::move(recvcounts), std::move(rdispls), std::move(recvtypes), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Recv(void * buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status * status)
{
    MPI_Request request_local;
    MPI_Irecv(std::move(buf), std::move(count), std::move(datatype), std::move(source), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, status); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Reduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ireduce(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(root), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ireduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ireduce, true>(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(root), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Reduce_scatter(const void * sendbuf, void * recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ireduce_scatter(std::move(sendbuf), std::move(recvbuf), std::move(recvcounts), std::move(datatype), std::move(op), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ireduce_scatter(const void * sendbuf, void * recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ireduce_scatter, true>(std::move(sendbuf), std::move(recvbuf), std::move(recvcounts), std::move(datatype), std::move(op), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Reduce_scatter_block(const void * sendbuf, void * recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Ireduce_scatter_block(std::move(sendbuf), std::move(recvbuf), std::move(recvcount), std::move(datatype), std::move(op), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ireduce_scatter_block(const void * sendbuf, void * recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ireduce_scatter_block, true>(std::move(sendbuf), std::move(recvbuf), std::move(recvcount), std::move(datatype), std::move(op), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Rsend(const void * ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Irsend(std::move(ibuf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Scan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iscan(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iscan, true>(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Scatter(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iscatter(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(root), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iscatter(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iscatter, true>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(root), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Scatterv(const void * sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iscatterv(std::move(sendbuf), std::move(sendcounts), std::move(displs), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(root), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Iscatterv(const void * sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iscatterv, true>(std::move(sendbuf), std::move(sendcounts), std::move(displs), std::move(sendtype), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(root), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Send(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Isend(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Ssend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Issend(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

} /* extern "C" */

