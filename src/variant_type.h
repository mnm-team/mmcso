#pragma once

#include <mpi.h>

#include <functional> // bind_front
#include <variant>    // variant
#include "lambda_wrapper.h"

namespace mmcso {

    using T1 = decltype(mmcso::make_lambda_wrapper<PMPI_Iallgather, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T2 = decltype(mmcso::make_lambda_wrapper<PMPI_Iallgatherv, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T3 = decltype(mmcso::make_lambda_wrapper<PMPI_Iallreduce, true>(std::decay_t<const void *>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Op>{}, std::decay_t<MPI_Comm>{}));
    using T4 = decltype(mmcso::make_lambda_wrapper<PMPI_Ialltoall, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T5 = decltype(mmcso::make_lambda_wrapper<PMPI_Ialltoallv, true>(std::decay_t<const void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T6 = decltype(mmcso::make_lambda_wrapper<PMPI_Ialltoallw, true>(std::decay_t<const void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<const MPI_Datatype[]>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<const MPI_Datatype[]>{}, std::decay_t<MPI_Comm>{}));
    using T7 = decltype(mmcso::make_lambda_wrapper<PMPI_Ibarrier, true>(std::decay_t<MPI_Comm>{}));
    using T8 = decltype(mmcso::make_lambda_wrapper<PMPI_Ibcast, true>(std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T9 = decltype(mmcso::make_lambda_wrapper<PMPI_Comm_idup, true>(std::decay_t<MPI_Comm>{}, std::decay_t<MPI_Comm *>{}));
    using T10 = decltype(mmcso::make_lambda_wrapper<PMPI_Iexscan, true>(std::decay_t<const void *>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Op>{}, std::decay_t<MPI_Comm>{}));
    using T11 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iread_at, true>(std::decay_t<MPI_File>{}, std::decay_t<MPI_Offset>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T12 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iwrite_at, true>(std::decay_t<MPI_File>{}, std::decay_t<MPI_Offset>{}, std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T13 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iread_at_all, true>(std::decay_t<MPI_File>{}, std::decay_t<MPI_Offset>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T14 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iwrite_at_all, true>(std::decay_t<MPI_File>{}, std::decay_t<MPI_Offset>{}, std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T15 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iread, true>(std::decay_t<MPI_File>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T16 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iwrite, true>(std::decay_t<MPI_File>{}, std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T17 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iread_all, true>(std::decay_t<MPI_File>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T18 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iwrite_all, true>(std::decay_t<MPI_File>{}, std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T19 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iread_shared, true>(std::decay_t<MPI_File>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T20 = decltype(mmcso::make_lambda_wrapper<PMPI_File_iwrite_shared, true>(std::decay_t<MPI_File>{}, std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}));
    using T21 = decltype(mmcso::make_lambda_wrapper<PMPI_Igather, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T22 = decltype(mmcso::make_lambda_wrapper<PMPI_Igatherv, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T23 = decltype(mmcso::make_lambda_wrapper<PMPI_Ibsend, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T24 = decltype(mmcso::make_lambda_wrapper<PMPI_Improbe, false>(std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}, std::decay_t<int *>{}, std::decay_t<MPI_Message *>{}, std::decay_t<MPI_Status *>{}));
    using T25 = decltype(mmcso::make_lambda_wrapper<PMPI_Imrecv, true>(std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Message *>{}));
    using T26 = decltype(mmcso::make_lambda_wrapper<PMPI_Iprobe, false>(std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}, std::decay_t<int *>{}, std::decay_t<MPI_Status *>{}));
    using T27 = decltype(mmcso::make_lambda_wrapper<PMPI_Irecv, true>(std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T28 = decltype(mmcso::make_lambda_wrapper<PMPI_Irsend, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T29 = decltype(mmcso::make_lambda_wrapper<PMPI_Isend, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T30 = decltype(mmcso::make_lambda_wrapper<PMPI_Issend, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T31 = decltype(mmcso::make_lambda_wrapper<PMPI_Ineighbor_allgather, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T32 = decltype(mmcso::make_lambda_wrapper<PMPI_Ineighbor_allgatherv, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T33 = decltype(mmcso::make_lambda_wrapper<PMPI_Ineighbor_alltoall, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T34 = decltype(mmcso::make_lambda_wrapper<PMPI_Ineighbor_alltoallv, true>(std::decay_t<const void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Comm>{}));
    using T35 = decltype(mmcso::make_lambda_wrapper<PMPI_Ineighbor_alltoallw, true>(std::decay_t<const void *>{}, std::decay_t<const int[]>{}, std::decay_t<const MPI_Aint[]>{}, std::decay_t<const MPI_Datatype[]>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<const MPI_Aint[]>{}, std::decay_t<const MPI_Datatype[]>{}, std::decay_t<MPI_Comm>{}));
    using T36 = decltype(mmcso::make_lambda_wrapper<PMPI_Ireduce, true>(std::decay_t<const void *>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Op>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T37 = decltype(mmcso::make_lambda_wrapper<PMPI_Ireduce_scatter, true>(std::decay_t<const void *>{}, std::decay_t<void *>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Op>{}, std::decay_t<MPI_Comm>{}));
    using T38 = decltype(mmcso::make_lambda_wrapper<PMPI_Ireduce_scatter_block, true>(std::decay_t<const void *>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Op>{}, std::decay_t<MPI_Comm>{}));
    using T39 = decltype(mmcso::make_lambda_wrapper<PMPI_Iscan, true>(std::decay_t<const void *>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<MPI_Op>{}, std::decay_t<MPI_Comm>{}));
    using T40 = decltype(mmcso::make_lambda_wrapper<PMPI_Iscatter, true>(std::decay_t<const void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
    using T41 = decltype(mmcso::make_lambda_wrapper<PMPI_Iscatterv, true>(std::decay_t<const void *>{}, std::decay_t<const int[]>{}, std::decay_t<const int[]>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<void *>{}, std::decay_t<int>{}, std::decay_t<MPI_Datatype>{}, std::decay_t<int>{}, std::decay_t<MPI_Comm>{}));
using variant_type = std::variant<std::monostate,
T1,
T2,
T3,
T4,
T5,
T6,
T7,
T8,
T9,
T10,
T11,
T12,
T13,
T14,
T15,
T16,
T17,
T18,
T19,
T20,
T21,
T22,
T23,
T24,
T25,
T26,
T27,
T28,
T29,
T30,
T31,
T32,
T33,
T34,
T35,
T36,
T37,
T38,
T39,
T40,
T41
>;
static_assert(std::variant_size_v<variant_type> == 42);
static_assert(std::is_same_v<T1, std::variant_alternative_t<1, variant_type>>);
static_assert(std::is_same_v<T2, std::variant_alternative_t<2, variant_type>>);
static_assert(std::is_same_v<T3, std::variant_alternative_t<3, variant_type>>);
static_assert(std::is_same_v<T4, std::variant_alternative_t<4, variant_type>>);
static_assert(std::is_same_v<T5, std::variant_alternative_t<5, variant_type>>);
static_assert(std::is_same_v<T6, std::variant_alternative_t<6, variant_type>>);
static_assert(std::is_same_v<T7, std::variant_alternative_t<7, variant_type>>);
static_assert(std::is_same_v<T8, std::variant_alternative_t<8, variant_type>>);
static_assert(std::is_same_v<T9, std::variant_alternative_t<9, variant_type>>);
static_assert(std::is_same_v<T10, std::variant_alternative_t<10, variant_type>>);
static_assert(std::is_same_v<T11, std::variant_alternative_t<11, variant_type>>);
static_assert(std::is_same_v<T12, std::variant_alternative_t<12, variant_type>>);
static_assert(std::is_same_v<T13, std::variant_alternative_t<13, variant_type>>);
static_assert(std::is_same_v<T14, std::variant_alternative_t<14, variant_type>>);
static_assert(std::is_same_v<T15, std::variant_alternative_t<15, variant_type>>);
static_assert(std::is_same_v<T16, std::variant_alternative_t<16, variant_type>>);
static_assert(std::is_same_v<T17, std::variant_alternative_t<17, variant_type>>);
static_assert(std::is_same_v<T18, std::variant_alternative_t<18, variant_type>>);
static_assert(std::is_same_v<T19, std::variant_alternative_t<19, variant_type>>);
static_assert(std::is_same_v<T20, std::variant_alternative_t<20, variant_type>>);
static_assert(std::is_same_v<T21, std::variant_alternative_t<21, variant_type>>);
static_assert(std::is_same_v<T22, std::variant_alternative_t<22, variant_type>>);
static_assert(std::is_same_v<T23, std::variant_alternative_t<23, variant_type>>);
static_assert(std::is_same_v<T24, std::variant_alternative_t<24, variant_type>>);
static_assert(std::is_same_v<T25, std::variant_alternative_t<25, variant_type>>);
static_assert(std::is_same_v<T26, std::variant_alternative_t<26, variant_type>>);
static_assert(std::is_same_v<T27, std::variant_alternative_t<27, variant_type>>);
static_assert(std::is_same_v<T28, std::variant_alternative_t<28, variant_type>>);
static_assert(std::is_same_v<T29, std::variant_alternative_t<29, variant_type>>);
static_assert(std::is_same_v<T30, std::variant_alternative_t<30, variant_type>>);
static_assert(std::is_same_v<T31, std::variant_alternative_t<31, variant_type>>);
static_assert(std::is_same_v<T32, std::variant_alternative_t<32, variant_type>>);
static_assert(std::is_same_v<T33, std::variant_alternative_t<33, variant_type>>);
static_assert(std::is_same_v<T34, std::variant_alternative_t<34, variant_type>>);
static_assert(std::is_same_v<T35, std::variant_alternative_t<35, variant_type>>);
static_assert(std::is_same_v<T36, std::variant_alternative_t<36, variant_type>>);
static_assert(std::is_same_v<T37, std::variant_alternative_t<37, variant_type>>);
static_assert(std::is_same_v<T38, std::variant_alternative_t<38, variant_type>>);
static_assert(std::is_same_v<T39, std::variant_alternative_t<39, variant_type>>);
static_assert(std::is_same_v<T40, std::variant_alternative_t<40, variant_type>>);
static_assert(std::is_same_v<T41, std::variant_alternative_t<41, variant_type>>);

} // namespace mmcso

