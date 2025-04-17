#pragma once

#include <functional> // std::invoke
#include <utility>    // std::move, std::swap

#include "mpi.h"

template <std::size_t Size, std::size_t Align = 8ul>
class MpiCommand
{
public:
    struct MpiCommandConcept {
        virtual ~MpiCommandConcept() = default;

        virtual int do_invoke(MPI_Request *) const = 0;

        // no copy allowed
        // virtual void clone(MpiCommandConcept *memory) const = 0;

        virtual void move(MpiCommandConcept *memory) const = 0;
    };

    template <class MpiCommandT>
    struct MpiCommandModel : MpiCommandConcept {
        MpiCommandModel(MpiCommandT &&command) : command_{std::move(command)} {}

        MpiCommandT command_;

        // no copy allowed
        // void clone(MpiCommandConcept *memory) const override { ::new (memory) MpiCommandModel(*this); }

        void move(MpiCommandConcept *memory) const override { ::new (memory) MpiCommandModel(std::move(*this)); }

        int do_invoke(MPI_Request *request) const override
        {
            // std::printf("command model size=%zu\n", sizeof(MpiCommandT));
            return std::invoke(command_, request);
        }
    };

    friend int invoke(MpiCommand const &command, MPI_Request *request) { return command.pimpl()->do_invoke(request); }

    MpiCommandConcept *pimpl() noexcept { return reinterpret_cast<MpiCommandConcept *>(buffer_.data()); }

    const MpiCommandConcept *pimpl() const noexcept
    {
        return reinterpret_cast<const MpiCommandConcept *>(buffer_.data());
    }

    alignas(Align) std::array<std::byte, Size> buffer_;

    /* ctors */
    MpiCommand() = default;

    template <class MpiCommandT>
    MpiCommand(MpiCommandT &&command)
    {
        using M = MpiCommandModel<MpiCommandT>;
        static_assert(sizeof(M) <= Size);
        static_assert(alignof(M) <= Align);
        ::new (pimpl()) M(std::move(command)); // eventually std::construct_at()
    }

    // MpiCommand(MpiCommand const &other) { other.pimpl()->clone(pimpl()); }

    MpiCommand(MpiCommand const &other) = delete;
    MpiCommand(MpiCommand &&other) { other.pimpl()->move(pimpl()); }

    /* assignment ops */
    MpiCommand &operator=(MpiCommand const &other) = delete;

#if NEED_COPY_ASSIGNMENT
    MpiCommand &operator=(MpiCommand const &other)
    {
        MpiCommand copy(other);
        buffer_.swap(copy.buffer_);
        return *this;
    }
#endif

    MpiCommand &operator=(MpiCommand &&other)
    {
        MpiCommand tmp(std::move(other));
        buffer_.swap(tmp.buffer_);
        return *this;
    }
};
