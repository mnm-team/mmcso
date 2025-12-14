#include <utility> // std::move

#include "config.h"
#include "mpi_command.h"

#include <mpi.h>

using mmcso::OffloadCommand;
using mmcso::make_mpi_callable;

extern "C" {

int MPI_Abort(MPI_Comm comm, int errorcode)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Abort, false>(std::move(comm), std::move(errorcode)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Accumulate(const void * origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Accumulate, false>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(op), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


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

int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void * baseptr)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Alloc_mem, false>(std::move(size), std::move(info), std::move(baseptr)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Bsend_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Bsend_init, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Buffer_attach(void * buffer, int size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Buffer_attach, false>(std::move(buffer), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Buffer_detach(void * buffer, int * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Buffer_detach, false>(std::move(buffer), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cancel(MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cancel, true>(), request});
    return MPI_SUCCESS;
}

int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_coords, false>(std::move(comm), std::move(rank), std::move(maxdims), std::move(coords)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cart_create(MPI_Comm old_comm, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm * comm_cart)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_create, false>(std::move(old_comm), std::move(ndims), std::move(dims), std::move(periods), std::move(reorder), std::move(comm_cart)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_get, false>(std::move(comm), std::move(maxdims), std::move(dims), std::move(periods), std::move(coords)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int * newrank)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_map, false>(std::move(comm), std::move(ndims), std::move(dims), std::move(periods), std::move(newrank)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cart_rank(MPI_Comm comm, const int coords[], int * rank)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_rank, false>(std::move(comm), std::move(coords), std::move(rank)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int * rank_source, int * rank_dest)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_shift, false>(std::move(comm), std::move(direction), std::move(disp), std::move(rank_source), std::move(rank_dest)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm * new_comm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cart_sub, false>(std::move(comm), std::move(remain_dims), std::move(new_comm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Cartdim_get(MPI_Comm comm, int * ndims)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Cartdim_get, false>(std::move(comm), std::move(ndims)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Close_port(const char * port_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Close_port, false>(std::move(port_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_accept(const char * port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_accept, false>(std::move(port_name), std::move(info), std::move(root), std::move(comm), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_call_errhandler, false>(std::move(comm), std::move(errorcode)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int * result)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_compare, false>(std::move(comm1), std::move(comm2), std::move(result)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_connect(const char * port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_connect, false>(std::move(port_name), std::move(info), std::move(root), std::move(comm), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function * function, MPI_Errhandler * errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_create_errhandler, false>(std::move(function), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function * comm_copy_attr_fn, MPI_Comm_delete_attr_function * comm_delete_attr_fn, int * comm_keyval, void * extra_state)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_create_keyval, false>(std::move(comm_copy_attr_fn), std::move(comm_delete_attr_fn), std::move(comm_keyval), std::move(extra_state)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_create_group, false>(std::move(comm), std::move(group), std::move(tag), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_create, false>(std::move(comm), std::move(group), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_delete_attr, false>(std::move(comm), std::move(comm_keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_disconnect(MPI_Comm * comm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_disconnect, false>(std::move(comm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_dup_with_info, false>(std::move(comm), std::move(info), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_free_keyval(int * comm_keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_free_keyval, false>(std::move(comm_keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_free(MPI_Comm * comm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_free, false>(std::move(comm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void * attribute_val, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_get_attr, false>(std::move(comm), std::move(comm_keyval), std::move(attribute_val), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Dist_graph_create(MPI_Comm comm_old, int n, const int nodes[], const int degrees[], const int targets[], const int weights[], MPI_Info info, int reorder, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Dist_graph_create, false>(std::move(comm_old), std::move(n), std::move(nodes), std::move(degrees), std::move(targets), std::move(weights), std::move(info), std::move(reorder), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm * comm_dist_graph)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Dist_graph_create_adjacent, false>(std::move(comm_old), std::move(indegree), std::move(sources), std::move(sourceweights), std::move(outdegree), std::move(destinations), std::move(destweights), std::move(info), std::move(reorder), std::move(comm_dist_graph)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Dist_graph_neighbors, false>(std::move(comm), std::move(maxindegree), std::move(sources), std::move(sourceweights), std::move(maxoutdegree), std::move(destinations), std::move(destweights)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Dist_graph_neighbors_count(MPI_Comm comm, int * inneighbors, int * outneighbors, int * weighted)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Dist_graph_neighbors_count, false>(std::move(comm), std::move(inneighbors), std::move(outneighbors), std::move(weighted)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler * erhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_get_errhandler, false>(std::move(comm), std::move(erhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_get_info(MPI_Comm comm, MPI_Info * info_used)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_get_info, false>(std::move(comm), std::move(info_used)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_get_name(MPI_Comm comm, char * comm_name, int * resultlen)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_get_name, false>(std::move(comm), std::move(comm_name), std::move(resultlen)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_get_parent(MPI_Comm * parent)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_get_parent, false>(std::move(parent)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_group(MPI_Comm comm, MPI_Group * group)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_group, false>(std::move(comm), std::move(group)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_join(int fd, MPI_Comm * intercomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_join, false>(std::move(fd), std::move(intercomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_rank(MPI_Comm comm, int * rank)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_rank, false>(std::move(comm), std::move(rank)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group * group)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_remote_group, false>(std::move(comm), std::move(group)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_remote_size(MPI_Comm comm, int * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_remote_size, false>(std::move(comm), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void * attribute_val)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_set_attr, false>(std::move(comm), std::move(comm_keyval), std::move(attribute_val)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_set_errhandler, false>(std::move(comm), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_set_info, false>(std::move(comm), std::move(info)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_set_name(MPI_Comm comm, const char * comm_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_set_name, false>(std::move(comm), std::move(comm_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_size(MPI_Comm comm, int * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_size, false>(std::move(comm), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_spawn(const char * command, char * argv[], int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm * intercomm, int array_of_errcodes[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_spawn, false>(std::move(command), std::move(argv), std::move(maxprocs), std::move(info), std::move(root), std::move(comm), std::move(intercomm), std::move(array_of_errcodes)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_spawn_multiple(int count, char * array_of_commands[], char ** array_of_argv[], const int array_of_maxprocs[], const MPI_Info array_of_info[], int root, MPI_Comm comm, MPI_Comm * intercomm, int array_of_errcodes[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_spawn_multiple, false>(std::move(count), std::move(array_of_commands), std::move(array_of_argv), std::move(array_of_maxprocs), std::move(array_of_info), std::move(root), std::move(comm), std::move(intercomm), std::move(array_of_errcodes)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_split, false>(std::move(comm), std::move(color), std::move(key), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm * newcomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_split_type, false>(std::move(comm), std::move(split_type), std::move(key), std::move(info), std::move(newcomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Comm_test_inter(MPI_Comm comm, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Comm_test_inter, false>(std::move(comm), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Compare_and_swap(const void * origin_addr, const void * compare_addr, void * result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Compare_and_swap, false>(std::move(origin_addr), std::move(compare_addr), std::move(result_addr), std::move(datatype), std::move(target_rank), std::move(target_disp), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Dims_create(int nnodes, int ndims, int dims[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Dims_create, false>(std::move(nnodes), std::move(ndims), std::move(dims)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Exscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Iexscan(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Fetch_and_op(const void * origin_addr, void * result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Fetch_and_op, false>(std::move(origin_addr), std::move(result_addr), std::move(datatype), std::move(target_rank), std::move(target_disp), std::move(op), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Iexscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Iexscan, true>(std::move(sendbuf), std::move(recvbuf), std::move(count), std::move(datatype), std::move(op), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_File_call_errhandler(MPI_File fh, int errorcode)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_call_errhandler, false>(std::move(fh), std::move(errorcode)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_create_errhandler(MPI_File_errhandler_function * function, MPI_Errhandler * errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_create_errhandler, false>(std::move(function), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_set_errhandler, false>(std::move(file), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_errhandler(MPI_File file, MPI_Errhandler * errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_errhandler, false>(std::move(file), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_open(MPI_Comm comm, const char * filename, int amode, MPI_Info info, MPI_File * fh)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_open, false>(std::move(comm), std::move(filename), std::move(amode), std::move(info), std::move(fh)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_close(MPI_File * fh)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_close, false>(std::move(fh)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_delete(const char * filename, MPI_Info info)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_delete, false>(std::move(filename), std::move(info)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_set_size(MPI_File fh, MPI_Offset size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_set_size, false>(std::move(fh), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_preallocate(MPI_File fh, MPI_Offset size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_preallocate, false>(std::move(fh), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_size(MPI_File fh, MPI_Offset * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_size, false>(std::move(fh), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_group(MPI_File fh, MPI_Group * group)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_group, false>(std::move(fh), std::move(group)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_amode(MPI_File fh, int * amode)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_amode, false>(std::move(fh), std::move(amode)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_set_info(MPI_File fh, MPI_Info info)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_set_info, false>(std::move(fh), std::move(info)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_info(MPI_File fh, MPI_Info * info_used)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_info, false>(std::move(fh), std::move(info_used)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char * datarep, MPI_Info info)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_set_view, false>(std::move(fh), std::move(disp), std::move(etype), std::move(filetype), std::move(datarep), std::move(info)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_view(MPI_File fh, MPI_Offset * disp, MPI_Datatype * etype, MPI_Datatype * filetype, char * datarep)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_view, false>(std::move(fh), std::move(disp), std::move(etype), std::move(filetype), std::move(datarep)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_seek, false>(std::move(fh), std::move(offset), std::move(whence)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_position(MPI_File fh, MPI_Offset * offset)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_position, false>(std::move(fh), std::move(offset)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset * disp)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_byte_offset, false>(std::move(fh), std::move(offset), std::move(disp)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_File_read_ordered(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_ordered, false>(std::move(fh), std::move(buf), std::move(count), std::move(datatype), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_ordered(MPI_File fh, const void * buf, int count, MPI_Datatype datatype, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_ordered, false>(std::move(fh), std::move(buf), std::move(count), std::move(datatype), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_seek_shared, false>(std::move(fh), std::move(offset), std::move(whence)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_position_shared(MPI_File fh, MPI_Offset * offset)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_position_shared, false>(std::move(fh), std::move(offset)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_at_all_begin, false>(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_read_at_all_end(MPI_File fh, void * buf, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_at_all_end, false>(std::move(fh), std::move(buf), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void * buf, int count, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_at_all_begin, false>(std::move(fh), std::move(offset), std::move(buf), std::move(count), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_at_all_end(MPI_File fh, const void * buf, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_at_all_end, false>(std::move(fh), std::move(buf), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_read_all_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_all_begin, false>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_read_all_end(MPI_File fh, void * buf, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_all_end, false>(std::move(fh), std::move(buf), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_all_begin(MPI_File fh, const void * buf, int count, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_all_begin, false>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_all_end(MPI_File fh, const void * buf, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_all_end, false>(std::move(fh), std::move(buf), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_read_ordered_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_ordered_begin, false>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_read_ordered_end(MPI_File fh, void * buf, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_read_ordered_end, false>(std::move(fh), std::move(buf), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_ordered_begin(MPI_File fh, const void * buf, int count, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_ordered_begin, false>(std::move(fh), std::move(buf), std::move(count), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_write_ordered_end(MPI_File fh, const void * buf, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_write_ordered_end, false>(std::move(fh), std::move(buf), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint * extent)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_type_extent, false>(std::move(fh), std::move(datatype), std::move(extent)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_set_atomicity(MPI_File fh, int flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_set_atomicity, false>(std::move(fh), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_get_atomicity(MPI_File fh, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_get_atomicity, false>(std::move(fh), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_File_sync(MPI_File fh)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_File_sync, false>(std::move(fh)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Free_mem(void * base)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Free_mem, false>(std::move(base)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Get_address(const void * location, MPI_Aint * address)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get_address, false>(std::move(location), std::move(address)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Get_count(const MPI_Status * status, MPI_Datatype datatype, int * count)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get_count, false>(std::move(status), std::move(datatype), std::move(count)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Get_elements(const MPI_Status * status, MPI_Datatype datatype, int * count)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get_elements, false>(std::move(status), std::move(datatype), std::move(count)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Get_elements_x(const MPI_Status * status, MPI_Datatype datatype, MPI_Count * count)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get_elements_x, false>(std::move(status), std::move(datatype), std::move(count)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Get(void * origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get, false>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Get_accumulate(const void * origin_addr, int origin_count, MPI_Datatype origin_datatype, void * result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get_accumulate, false>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(result_addr), std::move(result_count), std::move(result_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(op), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Get_processor_name(char * name, int * resultlen)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Get_processor_name, false>(std::move(name), std::move(resultlen)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm * comm_graph)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Graph_create, false>(std::move(comm_old), std::move(nnodes), std::move(index), std::move(edges), std::move(reorder), std::move(comm_graph)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Graph_get, false>(std::move(comm), std::move(maxindex), std::move(maxedges), std::move(index), std::move(edges)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int * newrank)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Graph_map, false>(std::move(comm), std::move(nnodes), std::move(index), std::move(edges), std::move(newrank)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int * nneighbors)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Graph_neighbors_count, false>(std::move(comm), std::move(rank), std::move(nneighbors)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Graph_neighbors, false>(std::move(comm), std::move(rank), std::move(maxneighbors), std::move(neighbors)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Graphdims_get(MPI_Comm comm, int * nnodes, int * nedges)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Graphdims_get, false>(std::move(comm), std::move(nnodes), std::move(nedges)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Grequest_complete(MPI_Request request)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Grequest_complete, false>(std::move(request)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Grequest_start(MPI_Grequest_query_function * query_fn, MPI_Grequest_free_function * free_fn, MPI_Grequest_cancel_function * cancel_fn, void * extra_state, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Grequest_start, true>(std::move(query_fn), std::move(free_fn), std::move(cancel_fn), std::move(extra_state)), request});
    return MPI_SUCCESS;
}

int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int * result)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_compare, false>(std::move(group1), std::move(group2), std::move(result)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_difference, false>(std::move(group1), std::move(group2), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_excl, false>(std::move(group), std::move(n), std::move(ranks), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_free(MPI_Group * group)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_free, false>(std::move(group)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_incl, false>(std::move(group), std::move(n), std::move(ranks), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_intersection, false>(std::move(group1), std::move(group2), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_range_excl, false>(std::move(group), std::move(n), std::move(ranges), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_range_incl, false>(std::move(group), std::move(n), std::move(ranges), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_rank(MPI_Group group, int * rank)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_rank, false>(std::move(group), std::move(rank)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_size(MPI_Group group, int * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_size, false>(std::move(group), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_translate_ranks, false>(std::move(group1), std::move(n), std::move(ranks1), std::move(group2), std::move(ranks2)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group * newgroup)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Group_union, false>(std::move(group1), std::move(group2), std::move(newgroup)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Info_get(MPI_Info info, const char * key, int valuelen, char * value, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Info_get, false>(std::move(info), std::move(key), std::move(valuelen), std::move(value), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Info_get_valuelen(MPI_Info info, const char * key, int * valuelen, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Info_get_valuelen, false>(std::move(info), std::move(key), std::move(valuelen), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm * newintercomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Intercomm_create, false>(std::move(local_comm), std::move(local_leader), std::move(bridge_comm), std::move(remote_leader), std::move(tag), std::move(newintercomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm * newintercomm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Intercomm_merge, false>(std::move(intercomm), std::move(high), std::move(newintercomm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Lookup_name(const char * service_name, MPI_Info info, char * port_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Lookup_name, false>(std::move(service_name), std::move(info), std::move(port_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Op_commutative(MPI_Op op, int * commute)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Op_commutative, false>(std::move(op), std::move(commute)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Op_create(MPI_User_function * function, int commute, MPI_Op * op)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Op_create, false>(std::move(function), std::move(commute), std::move(op)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Open_port(MPI_Info info, char * port_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Open_port, false>(std::move(info), std::move(port_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Op_free(MPI_Op * op)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Op_free, false>(std::move(op)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Pack_external(const char datarep[], const void * inbuf, int incount, MPI_Datatype datatype, void * outbuf, MPI_Aint outsize, MPI_Aint * position)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Pack_external, false>(std::move(datarep), std::move(inbuf), std::move(incount), std::move(datatype), std::move(outbuf), std::move(outsize), std::move(position)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Pack_external_size, false>(std::move(datarep), std::move(incount), std::move(datatype), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Pack(const void * inbuf, int incount, MPI_Datatype datatype, void * outbuf, int outsize, int * position, MPI_Comm comm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Pack, false>(std::move(inbuf), std::move(incount), std::move(datatype), std::move(outbuf), std::move(outsize), std::move(position), std::move(comm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Pack_size, false>(std::move(incount), std::move(datatype), std::move(comm), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Publish_name(const char * service_name, MPI_Info info, const char * port_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Publish_name, false>(std::move(service_name), std::move(info), std::move(port_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Put(const void * origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Put, false>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Raccumulate(const void * origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Raccumulate, true>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(op), std::move(win)), request});
    return MPI_SUCCESS;
}

int MPI_Recv_init(void * buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Recv_init, true>(std::move(buf), std::move(count), std::move(datatype), std::move(source), std::move(tag), std::move(comm)), request});
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

int MPI_Reduce_local(const void * inbuf, void * inoutbuf, int count, MPI_Datatype datatype, MPI_Op op)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Reduce_local, false>(std::move(inbuf), std::move(inoutbuf), std::move(count), std::move(datatype), std::move(op)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
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

int MPI_Register_datarep(const char * datarep, MPI_Datarep_conversion_function * read_conversion_fn, MPI_Datarep_conversion_function * write_conversion_fn, MPI_Datarep_extent_function * dtype_file_extent_fn, void * extra_state)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Register_datarep, false>(std::move(datarep), std::move(read_conversion_fn), std::move(write_conversion_fn), std::move(dtype_file_extent_fn), std::move(extra_state)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Request_free(MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Request_free, true>(), request});
    return MPI_SUCCESS;
}

int MPI_Request_get_status(MPI_Request request, int * flag, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Request_get_status, false>(std::move(request), std::move(flag), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Rget(void * origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Rget, true>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(win)), request});
    return MPI_SUCCESS;
}

int MPI_Rget_accumulate(const void * origin_addr, int origin_count, MPI_Datatype origin_datatype, void * result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Rget_accumulate, true>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(result_addr), std::move(result_count), std::move(result_datatype), std::move(target_rank), std::move(target_disp), std::move(target_count), std::move(target_datatype), std::move(op), std::move(win)), request});
    return MPI_SUCCESS;
}

int MPI_Rput(const void * origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_cout, MPI_Datatype target_datatype, MPI_Win win, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Rput, true>(std::move(origin_addr), std::move(origin_count), std::move(origin_datatype), std::move(target_rank), std::move(target_disp), std::move(target_cout), std::move(target_datatype), std::move(win)), request});
    return MPI_SUCCESS;
}

int MPI_Rsend(const void * ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Irsend(std::move(ibuf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Rsend_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Rsend_init, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
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

int MPI_Send_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Send_init, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Send(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Isend(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Sendrecv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void * recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Sendrecv, false>(std::move(sendbuf), std::move(sendcount), std::move(sendtype), std::move(dest), std::move(sendtag), std::move(recvbuf), std::move(recvcount), std::move(recvtype), std::move(source), std::move(recvtag), std::move(comm), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Sendrecv_replace(void * buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Sendrecv_replace, false>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(sendtag), std::move(source), std::move(recvtag), std::move(comm), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Ssend_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Ssend_init, true>(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm)), request});
    return MPI_SUCCESS;
}

int MPI_Ssend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    MPI_Request request_local;
    MPI_Issend(std::move(buf), std::move(count), std::move(datatype), std::move(dest), std::move(tag), std::move(comm), &request_local);
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}

int MPI_Start(MPI_Request * request)
{
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Start, true>(), request});
    return MPI_SUCCESS;
}

int MPI_Status_set_cancelled(MPI_Status * status, int flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Status_set_cancelled, false>(std::move(status), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Status_set_elements(MPI_Status * status, MPI_Datatype datatype, int count)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Status_set_elements, false>(std::move(status), std::move(datatype), std::move(count)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Status_set_elements_x(MPI_Status * status, MPI_Datatype datatype, MPI_Count count)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Status_set_elements_x, false>(std::move(status), std::move(datatype), std::move(count)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Topo_test(MPI_Comm comm, int * status)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Topo_test, false>(std::move(comm), std::move(status)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_commit(MPI_Datatype * type)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_commit, false>(std::move(type)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_contiguous, false>(std::move(count), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_darray(int size, int rank, int ndims, const int gsize_array[], const int distrib_array[], const int darg_array[], const int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_darray, false>(std::move(size), std::move(rank), std::move(ndims), std::move(gsize_array), std::move(distrib_array), std::move(darg_array), std::move(psize_array), std::move(order), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_f90_complex(int p, int r, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_f90_complex, false>(std::move(p), std::move(r), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_f90_integer(int r, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_f90_integer, false>(std::move(r), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_f90_real(int p, int r, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_f90_real, false>(std::move(p), std::move(r), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_hindexed_block, false>(std::move(count), std::move(blocklength), std::move(array_of_displacements), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_hindexed, false>(std::move(count), std::move(array_of_blocklengths), std::move(array_of_displacements), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_hvector, false>(std::move(count), std::move(blocklength), std::move(stride), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_keyval(MPI_Type_copy_attr_function * type_copy_attr_fn, MPI_Type_delete_attr_function * type_delete_attr_fn, int * type_keyval, void * extra_state)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_keyval, false>(std::move(type_copy_attr_fn), std::move(type_delete_attr_fn), std::move(type_keyval), std::move(extra_state)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_indexed_block, false>(std::move(count), std::move(blocklength), std::move(array_of_displacements), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_struct(int count, const int array_of_block_lengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_struct, false>(std::move(count), std::move(array_of_block_lengths), std::move(array_of_displacements), std::move(array_of_types), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_subarray(int ndims, const int size_array[], const int subsize_array[], const int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_subarray, false>(std::move(ndims), std::move(size_array), std::move(subsize_array), std::move(start_array), std::move(order), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_create_resized, false>(std::move(oldtype), std::move(lb), std::move(extent), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_delete_attr(MPI_Datatype type, int type_keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_delete_attr, false>(std::move(type), std::move(type_keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_dup(MPI_Datatype type, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_dup, false>(std::move(type), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_free(MPI_Datatype * type)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_free, false>(std::move(type)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_free_keyval(int * type_keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_free_keyval, false>(std::move(type_keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_attr(MPI_Datatype type, int type_keyval, void * attribute_val, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_attr, false>(std::move(type), std::move(type_keyval), std::move(attribute_val), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[])
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_contents, false>(std::move(mtype), std::move(max_integers), std::move(max_addresses), std::move(max_datatypes), std::move(array_of_integers), std::move(array_of_addresses), std::move(array_of_datatypes)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_envelope(MPI_Datatype type, int * num_integers, int * num_addresses, int * num_datatypes, int * combiner)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_envelope, false>(std::move(type), std::move(num_integers), std::move(num_addresses), std::move(num_datatypes), std::move(combiner)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_extent(MPI_Datatype type, MPI_Aint * lb, MPI_Aint * extent)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_extent, false>(std::move(type), std::move(lb), std::move(extent)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_extent_x(MPI_Datatype type, MPI_Count * lb, MPI_Count * extent)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_extent_x, false>(std::move(type), std::move(lb), std::move(extent)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_name(MPI_Datatype type, char * type_name, int * resultlen)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_name, false>(std::move(type), std::move(type_name), std::move(resultlen)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint * true_lb, MPI_Aint * true_extent)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_true_extent, false>(std::move(datatype), std::move(true_lb), std::move(true_extent)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count * true_lb, MPI_Count * true_extent)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_get_true_extent_x, false>(std::move(datatype), std::move(true_lb), std::move(true_extent)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_indexed, false>(std::move(count), std::move(array_of_blocklengths), std::move(array_of_displacements), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_match_size(int typeclass, int size, MPI_Datatype * type)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_match_size, false>(std::move(typeclass), std::move(size), std::move(type)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_set_attr(MPI_Datatype type, int type_keyval, void * attr_val)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_set_attr, false>(std::move(type), std::move(type_keyval), std::move(attr_val)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_set_name(MPI_Datatype type, const char * type_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_set_name, false>(std::move(type), std::move(type_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_size(MPI_Datatype type, int * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_size, false>(std::move(type), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_size_x(MPI_Datatype type, MPI_Count * size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_size_x, false>(std::move(type), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype * newtype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Type_vector, false>(std::move(count), std::move(blocklength), std::move(stride), std::move(oldtype), std::move(newtype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Unpack(const void * inbuf, int insize, int * position, void * outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Unpack, false>(std::move(inbuf), std::move(insize), std::move(position), std::move(outbuf), std::move(outcount), std::move(datatype), std::move(comm)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Unpublish_name(const char * service_name, MPI_Info info, const char * port_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Unpublish_name, false>(std::move(service_name), std::move(info), std::move(port_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Unpack_external(const char datarep[], const void * inbuf, MPI_Aint insize, MPI_Aint * position, void * outbuf, int outcount, MPI_Datatype datatype)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Unpack_external, false>(std::move(datarep), std::move(inbuf), std::move(insize), std::move(position), std::move(outbuf), std::move(outcount), std::move(datatype)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void * baseptr, MPI_Win * win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_allocate, false>(std::move(size), std::move(disp_unit), std::move(info), std::move(comm), std::move(baseptr), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void * baseptr, MPI_Win * win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_allocate_shared, false>(std::move(size), std::move(disp_unit), std::move(info), std::move(comm), std::move(baseptr), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_attach(MPI_Win win, void * base, MPI_Aint size)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_attach, false>(std::move(win), std::move(base), std::move(size)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_call_errhandler(MPI_Win win, int errorcode)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_call_errhandler, false>(std::move(win), std::move(errorcode)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_complete(MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_complete, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_create(void * base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win * win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_create, false>(std::move(base), std::move(size), std::move(disp_unit), std::move(info), std::move(comm), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win * win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_create_dynamic, false>(std::move(info), std::move(comm), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_create_errhandler(MPI_Win_errhandler_function * function, MPI_Errhandler * errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_create_errhandler, false>(std::move(function), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_create_keyval(MPI_Win_copy_attr_function * win_copy_attr_fn, MPI_Win_delete_attr_function * win_delete_attr_fn, int * win_keyval, void * extra_state)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_create_keyval, false>(std::move(win_copy_attr_fn), std::move(win_delete_attr_fn), std::move(win_keyval), std::move(extra_state)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_delete_attr(MPI_Win win, int win_keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_delete_attr, false>(std::move(win), std::move(win_keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_detach(MPI_Win win, const void * base)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_detach, false>(std::move(win), std::move(base)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_fence(int assert, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_fence, false>(std::move(assert), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_flush(int rank, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_flush, false>(std::move(rank), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_flush_all(MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_flush_all, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_flush_local(int rank, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_flush_local, false>(std::move(rank), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_flush_local_all(MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_flush_local_all, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_free(MPI_Win * win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_free, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_free_keyval(int * win_keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_free_keyval, false>(std::move(win_keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_get_attr(MPI_Win win, int win_keyval, void * attribute_val, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_get_attr, false>(std::move(win), std::move(win_keyval), std::move(attribute_val), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler * errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_get_errhandler, false>(std::move(win), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_get_group(MPI_Win win, MPI_Group * group)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_get_group, false>(std::move(win), std::move(group)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_get_info(MPI_Win win, MPI_Info * info_used)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_get_info, false>(std::move(win), std::move(info_used)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_get_name(MPI_Win win, char * win_name, int * resultlen)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_get_name, false>(std::move(win), std::move(win_name), std::move(resultlen)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_lock, false>(std::move(lock_type), std::move(rank), std::move(assert), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_lock_all(int assert, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_lock_all, false>(std::move(assert), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_post(MPI_Group group, int assert, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_post, false>(std::move(group), std::move(assert), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_set_attr(MPI_Win win, int win_keyval, void * attribute_val)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_set_attr, false>(std::move(win), std::move(win_keyval), std::move(attribute_val)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_set_errhandler, false>(std::move(win), std::move(errhandler)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_set_info(MPI_Win win, MPI_Info info)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_set_info, false>(std::move(win), std::move(info)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_set_name(MPI_Win win, const char * win_name)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_set_name, false>(std::move(win), std::move(win_name)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint * size, int * disp_unit, void * baseptr)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_shared_query, false>(std::move(win), std::move(rank), std::move(size), std::move(disp_unit), std::move(baseptr)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_start(MPI_Group group, int assert, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_start, false>(std::move(group), std::move(assert), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_sync(MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_sync, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_test(MPI_Win win, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_test, false>(std::move(win), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_unlock(int rank, MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_unlock, false>(std::move(rank), std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_unlock_all(MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_unlock_all, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Win_wait(MPI_Win win)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Win_wait, false>(std::move(win)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


double MPI_Wtick()
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Wtick, false>(), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


double MPI_Wtime()
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Wtime, false>(), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Attr_delete(MPI_Comm comm, int keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Attr_delete, false>(std::move(comm), std::move(keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Attr_get(MPI_Comm comm, int keyval, void * attribute_val, int * flag)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Attr_get, false>(std::move(comm), std::move(keyval), std::move(attribute_val), std::move(flag)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Attr_put(MPI_Comm comm, int keyval, void * attribute_val)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Attr_put, false>(std::move(comm), std::move(keyval), std::move(attribute_val)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Keyval_create(MPI_Copy_function * copy_fn, MPI_Delete_function * delete_fn, int * keyval, void * extra_state)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Keyval_create, false>(std::move(copy_fn), std::move(delete_fn), std::move(keyval), std::move(extra_state)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


int MPI_Keyval_free(int * keyval)
{
    MPI_Request request_local;
    oe.post(OffloadCommand{make_mpi_callable<PMPI_Keyval_free, false>(std::move(keyval)), &request_local, true});
    MPI_Wait(&request_local, MPI_STATUS_IGNORE); // NOLINT: suppress warning 'no matching nonblocking call'
    return MPI_SUCCESS;
}


} /* extern "C" */

