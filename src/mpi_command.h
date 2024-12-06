#pragma once

#include "variant_type.h"
#include "lambda_wrapper.h"

#include <functional>
#include <utility>
#include <variant>

#include <mpi.h>

namespace mmcso
{
    template <std::size_t IDX = 0u, auto F, bool R>
    constexpr auto make_mpi_callable(auto &&...args) noexcept
    {
        // in_place_index is required for conversion to variant
        // return variant_type{std::in_place_index<IDX>, make_lambda_wrapper<std::decay_t(func), R>(std::move(args)...)};
        return variant_type{std::in_place_index<IDX>, make_lambda_wrapper<F, R>(std::move(args)...)};
    }
} // namespace mmcso
