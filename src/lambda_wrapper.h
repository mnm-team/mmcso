#pragma once

namespace mmcso
{
    template <auto F, bool R, class... Ts>
    struct lambda_wrapper {
        explicit constexpr lambda_wrapper(Ts &&...args) : lambda_{make_lambda(std::move(args)...)} {}

        /* TODO: implement default constructor to avoid std::monostate */
        constexpr lambda_wrapper(lambda_wrapper &&other) : lambda_{std::move(other.lambda_)} {}
        lambda_wrapper(const lambda_wrapper &other) = delete;

        constexpr lambda_wrapper &operator=(lambda_wrapper &&other)
        {
            // using in-place construction via move constructor
            new (this) lambda_wrapper(std::move(other));
            return *this;
        }
        lambda_wrapper &operator=(const lambda_wrapper &other) = delete;

        static constexpr auto make_lambda(Ts &&...args)
        {
            return [=](MPI_Request *r) {
                if constexpr (R)
                    return F(std::move(args)..., r);
                else
                    return F(std::move(args)...);
            };
        }
        // auto operator()(MPI_Request *r) const noexcept { return std::move(lambda_)(r); }
        auto operator()(MPI_Request *r) const noexcept { return lambda_(r); }

        // auto operator()(MPI_Request *r) { return lambda_(r); }

        decltype(make_lambda(Ts{}...)) lambda_;
    };

    // deduction guide
    template <auto F, bool R, class... Ts>
    auto make_lambda_wrapper(Ts &&...args)
    {
        return mmcso::lambda_wrapper<F, R, Ts...>(std::move(args)...);
    }
} // namespace mmcso
