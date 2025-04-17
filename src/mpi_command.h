#pragma once

#include "type_erasure.h"

// 120 bytes storage for argument values of MPI function
using MPICommand = MpiCommand<120ul>;

#include <functional>
#include <utility>

#include <mpi.h>

namespace mmcso
{
    template <std::size_t IDX = 0u, auto Function, bool HasRequest>
    constexpr auto make_mpi_callable(auto &&...args) noexcept
    {
        return MPICommand([=](MPI_Request *r) {
            if constexpr (HasRequest)
                return Function(std::move(args)..., std::move(r));
            else
                return Function(std::move(args)...);
        });
    }
} // namespace mmcso
