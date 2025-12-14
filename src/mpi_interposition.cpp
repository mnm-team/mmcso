#include <functional>
#include <future>

#include <mpi.h>

#include "config.h"

/* static */ OE &oe = OE::instance();

extern "C" {

int MPI_Init_thread(int *argc, char ***argv, [[maybe_unused]] int required, int *provided)
{
    // future required because offload engine initializes MPI
    std::promise<int> provided_promise;
    std::future<int>  provided_future = provided_promise.get_future();

    oe.start(argc, argv, std::move(provided_promise));

    // MPI is guaranteed initialized (eventually by offloading thread) after get()
    *provided = provided_future.get();

    if (*provided == MPI_THREAD_SINGLE) {
        MPI_Abort(MPI_COMM_WORLD, 0);
    }

    if ((*provided == MPI_THREAD_SERIALIZED || *provided == MPI_THREAD_FUNNELED) && oe.num_threads == 1) {
        // using one offloading thread behaves as-if provided was MPI_THREAD_MULTIPLE
        *provided = MPI_THREAD_MULTIPLE;
    }

    return MPI_SUCCESS;
}

int MPI_Init(int *argc, char ***argv)
{
    /** TODO: use offloading when MPI_Init is called ? */
    int provided;
    return MPI_Init_thread(argc, argv, MPI_THREAD_SERIALIZED, &provided);
}

int MPI_Finalize()
{
    oe.stop(); /** TODO: fix race condition, according to thread sanitizer */
    PMPI_Finalize();
    return MPI_SUCCESS;
}

#if REQUIRED
int MPI_Query_thread(int *provided);
#endif

/***********************************************
 * MPI wait / test
 ***********************************************/

int MPI_Wait(MPI_Request *request, MPI_Status *status)
{
    /** TODO: handle this case:
     * One is allowed to call MPI_Wait with a null or inactive request argument.
     * In this case the operation returns immediately with empty status.
     *
    if(*request == MPI_REQUEST_NULL) {
        // set empty status
        *status = ?
        return MPI_SUCCESS;
    }
    */

    oe.wait(request, status);
    return MPI_SUCCESS;
}

int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status *array_of_statuses)
{
    for (int i = 0; i < count; ++i) {
        MPI_Status *status = (array_of_statuses == MPI_STATUSES_IGNORE) ? MPI_STATUS_IGNORE : &array_of_statuses[i];
        MPI_Wait(&array_of_requests[i], status);
        /* spin */
    }
    return MPI_SUCCESS;
}

/*
A call to MPI_Waitany can be used to wait for the completion of one out of several requests.

       The  array_of_requests list may contain null or inactive handles. If the list contains no active handles (list
has length zero or all entries are null or inactive), then the call returns immediately with index = MPI_UNDEFINED, and
an empty status.

       The execution of MPI_Waitany(count, array_of_requests, index, status) has the same effect as the execution of
MPI_Wait(&array_of_requests[i], status), where i is the value returned by index  (unless the value of index is
MPI_UNDEFINED). MPI_Waitany with an array containing one active entry is equivalent to MPI_Wait.

       If your application does not need to examine the status field, you can save resources by using the predefined
constant MPI_STATUS_IGNORE as a special value for the status argument.
*/
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status)
{
    if (count == 0) {
        *index = MPI_UNDEFINED;
        // TODO: set status to empty status
        // *status = ?;
        return MPI_SUCCESS;
    }
    // TODO: check whether the list contains any active handles

    while (1) {
        for (int i = 0; i < count; ++i) {
            int flag;
            MPI_Test(&array_of_requests[i], &flag, status);
            if (flag) {
                *index = i;
                return MPI_SUCCESS;
            }
        }
        /* TODO: exponential backoff?? */
    }
    return MPI_SUCCESS;
}

/*
Waits  until at least one of the operations associated with active handles in the list have completed. Returns in
outcount the number of requests from the list array_of_requests that have completed. Returns in the first outcount
locations of the array array_of_indices the indices of these operations (index within the array array_of_requests; the
array is indexed from 0 in C and from 1  in  Fortran).  Returns in the first outcount locations of the array
array_of_status the status for these completed operations. If a request that completed was allocated by a nonblocking
communication call, then it is deallocated, and the associated handle is set to MPI_REQUEST_NULL.

       If the list contains no active handles, then the call returns immediately with outcount = MPI_UNDEFINED.

       When one or more of the communications completed by MPI_Waitsome fails, then it is desirable to return specific
information on each communication. The arguments outcount, array_of_indices,  and  array_of_statuses  will be adjusted
to indicate completion of all communications that have succeeded or failed. The call will return the error code
MPI_ERR_IN_STATUS and the error field of each status returned will be set to indicate success or to indicate the
specific error that occurred. The call will return MPI_SUCCESS if no request resulted in an error, and will return
another error  code  if it failed for other reasons (such as invalid arguments). In such cases, it will not update the
error fields of the statuses.

If  your  application  does  not  need  to examine the array_of_statuses field, you can save resources by using
the predefined constant MPI_STATUSES_IGNORE can be used as a special value for the array_of_statuses argument.
*/
int MPI_Waitsome(
    int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[])
{
    if (incount == 0) {
        *outcount = MPI_UNDEFINED;
        // TODO: set status to empty status
        // *status = ?;
        return MPI_SUCCESS;
    }
    // TODO: check whether the list contains any active handles

    int completed = 0;
    while (completed < 1) {
        for (int i = 0; i < incount; ++i) {
            int         flag;
            MPI_Status *status = (array_of_statuses == MPI_STATUSES_IGNORE) ? MPI_STATUS_IGNORE : &array_of_statuses[i];
            MPI_Test(&array_of_requests[i], &flag, status);
            if (flag) {
                array_of_indices[completed] = i;
                ++completed;
            }
        }
        /* TODO: exponential backoff?? */
    }
    *outcount = completed;
    return MPI_SUCCESS;
}

int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status)
{
    /** TODO: handle this case:
     * One is allowed to call MPI_Test with a null or inactive request argument.
     * In such a case the operation returns with flag = true and empty status.
     */
    *flag = oe.test(request, status);
    return MPI_SUCCESS;
}

/*
       Returns  flag  = true if all communications associated with active handles in the array have completed (this
   includes the case where no handle in the list is active). In this case, each status entry that corresponds to an
   active handle request is set to the status of the corresponding communication; if the request was allocated by a
   nonblocking communication call then it is deallocated, and the handle is set to MPI_REQUEST_NULL. Each status entry
   that corresponds to a null or inactive handle is set to empty.

       Otherwise, flag = false is returned, no request is modified and the values of the status entries are undefined.
   This is a local operation.

       If  your  application  does  not  need  to examine the array_of_statuses field, you can save resources by using
   the predefined constant MPI_STATUSES_IGNORE can be used as a special value for the array_of_statuses argument.

       Errors that occurred during the execution of MPI_Testall are handled in the same manner as errors in MPI_Waitall.
*/
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[])
{
    /**
     * TODO: this implementation potentially modifies requests and statuses
     */
    for (int i = 0; i < count; ++i) {
        int         local_flag;
        MPI_Status *status = (array_of_statuses == MPI_STATUSES_IGNORE) ? MPI_STATUS_IGNORE : &array_of_statuses[i];
        MPI_Test(&array_of_requests[i], &local_flag, status);
        if (!local_flag) {
            *flag = false;
            return MPI_SUCCESS;
        }
    }
    *flag = true;
    return MPI_SUCCESS;
}

/*
       MPI_Testany tests for completion of either one or none of the operations associated with active handles. In the
   former case, it returns flag = true, returns in index the index of this request in the array, and returns in status
   the status of that operation; if the request was allocated by a nonblocking communication call then the request is
   deallocated and the handle is set to MPI_REQUEST_NULL. (The array is indexed from 0 in C, and from 1 in Fortran.) In
   the latter case (no operation completed), it returns flag = false, returns a value of MPI_UNDEFINED in index, and
   status is undefined.

       The array may contain null or inactive handles. If the array contains no active handles then the call returns
   immediately with flag = true, index = MPI_UNDEFINED, and an empty status.

       If  the  array  of requests contains active handles then the execution of MPI_Testany(count, array_of_requests,
   index, status) has the same effect as the execution of MPI_Test(&array_of_requests[i], flag, status), for
   i=0,1,...,count-1, in some arbitrary order, until one call returns flag = true, or all fail. In the former case,
   index is set to the last value of i, and in the latter case, it is set to MPI_UNDEFINED. MPI_Testany with an array
   containing one active entry is equivalent to MPI_Test.

       If your application does not need to examine the status field, you can save resources by using the predefined
   constant MPI_STATUS_IGNORE as a special value for the status argument.
*/
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status)
{
    if (count == 0) {
        *index = MPI_UNDEFINED;
        *flag  = true;
        // TODO: set status to empty status
        // *status = ?;
        return MPI_SUCCESS;
    }

    for (int i = 0; i < count; ++i) {
        int local_flag;
        MPI_Test(&array_of_requests[i], &local_flag, status);
        if (local_flag) {
            *index = i;
            *flag  = true;
            return MPI_SUCCESS;
        }
    }

    *index = MPI_UNDEFINED;
    *flag  = false;
    return MPI_SUCCESS;
}

/*
Behaves like MPI_Waitsome, except that it returns immediately.

       Returns  in outcount the number of requests from the list array_of_requests that have completed. Returns in the
first outcount locations of the array array_of_indices the indices of these operations (index within the array
array_of_requests; the array is indexed from 0 in C and from 1 in Fortran). Returns in the first outcount locations of
the array array_of_status the  status  for  these  completed operations. If a request that completed was allocated by
a nonblocking communication call, then it is deallocated, and the associated handle is set to MPI_REQUEST_NULL.

       If no operation has completed it returns outcount = 0. If there is no active handle in the list, it returns
outcount = MPI_UNDEFINED.

       MPI_Testsome  is  a  local  operation,  which returns immediately, whereas MPI_Waitsome blocks until a
communication completes, if it was passed a list that contains at least one active handle. Both calls fulfill a fairness
requirement: If a request for a receive repeatedly appears in a list of requests passed to MPI_Waitsome or MPI_Testsome,
and a matching send has been posted,  then  the  receive will eventually succeed unless the send is satisfied by
another receive; send requests also fulfill this fairness requirement.

       Errors that occur during the execution of MPI_Testsome are handled as for MPI_Waitsome.

       If  your  application  does  not  need  to examine the array_of_statuses field, you can save resources by using
the predefined constant MPI_STATUSES_IGNORE can be used as a special value for the array_of_statuses argument.
*/
int MPI_Testsome(
    int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[])
{
    if (incount == 0) {
        *outcount = MPI_UNDEFINED;
        // TODO: set status to empty status
        // *status = ?;
        return MPI_SUCCESS;
    }
    // TODO: check whether the list contains any active handles

    int completed = 0;
    for (int i = 0; i < incount; ++i) {
        int         flag;
        MPI_Status *status = (array_of_statuses == MPI_STATUSES_IGNORE) ? MPI_STATUS_IGNORE : &array_of_statuses[i];
        MPI_Test(&array_of_requests[i], &flag, status);
        if (flag) {
            array_of_indices[completed] = i;
            ++completed;
        }
    }
    *outcount = completed;
    return MPI_SUCCESS;
}

int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status)
{
    int flag;
    do {
        MPI_Iprobe(source, tag, comm, &flag, status);
        /* TODO: exponential backoff?? */
    } while (!flag);
    return MPI_SUCCESS;
}

int MPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status)
{
    int flag;
    do {
        MPI_Improbe(source, tag, comm, &flag, message, status);
        /* TODO: exponential backoff?? */
    } while (!flag);
    return MPI_SUCCESS;
}

int MPI_Startall(int count, MPI_Request array_of_requests[])
{
    for (int i = 0; i < count; ++i) {
        MPI_Start(&array_of_requests[i]);
    }
    return MPI_SUCCESS;
}

#if MMCSO_OFFLOAD_NOT_IMPLEMENTED_YET
int MPI_Test_cancelled(const MPI_Status *status, int *flag);
#endif

#if MMCSO_OFFLOAD_NOT_IMPLEMENTED_YET
int MPI_Abort(MPI_Comm comm, int errorcode);

int MPI_Add_error_class(int *errorclass);
int MPI_Add_error_code(int errorclass, int *errorcode);
int MPI_Add_error_string(int errorcode, const char *string);

int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr);

int MPI_Buffer_attach(void *buffer, int size);
int MPI_Buffer_detach(void *buffer, int *size);

int MPI_Errhandler_free(MPI_Errhandler *errhandler);
int MPI_Error_class(int errorcode, int *errorclass);
int MPI_Error_string(int errorcode, char *string, int *resultlen);

int MPI_Close_port(const char *port_name);

int MPI_Finalize(void);
int MPI_Finalized(int *flag);
int MPI_Free_mem(void *base);

int MPI_Get_address(const void *location, MPI_Aint *address);

int MPI_Get_library_version(char *version, int *resultlen);
int MPI_Get_processor_name(char *name, int *resultlen);
int MPI_Get_version(int *version, int *subversion);

int MPI_Initialized(int *flag);

int MPI_Intercomm_create(
    MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm);
int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm);

int MPI_Is_thread_main(int *flag);
int MPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name);

int MPI_Op_commutative(MPI_Op op, int *commute);
int MPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op);
int MPI_Open_port(MPI_Info info, char *port_name);

int MPI_Op_free(MPI_Op *op);
int MPI_Pack_external(const char   datarep[],
                      const void  *inbuf,
                      int          incount,
                      MPI_Datatype datatype,
                      void        *outbuf,
                      MPI_Aint     outsize,
                      MPI_Aint    *position);
int MPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size);
int MPI_Pack(
    const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm);
int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size);
int MPI_Pcontrol(const int level, ...);
int MPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name);

int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op);

int MPI_Register_datarep(const char                      *datarep,
                         MPI_Datarep_conversion_function *read_conversion_fn,
                         MPI_Datarep_conversion_function *write_conversion_fn,
                         MPI_Datarep_extent_function     *dtype_file_extent_fn,
                         void                            *extra_state);

int MPI_Unpack(
    const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm);
int MPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name);
int MPI_Unpack_external(const char   datarep[],
                        const void  *inbuf,
                        MPI_Aint     insize,
                        MPI_Aint    *position,
                        void        *outbuf,
                        int          outcount,
                        MPI_Datatype datatype);

double MPI_Wtick(void);
double MPI_Wtime(void);

#endif /* MMCSO_OFFLOAD_NOT_IMPLEMENTED_YET */

} /* extern "C" */

// #include "mpi_fortran_wrappers.h"
