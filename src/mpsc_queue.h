#ifndef MMCSO_MPSC_QUEUE_H_INCLUDED
#define MMCSO_MPSC_QUEUE_H_INCLUDED

#include <array>
#include <atomic>
#include <iostream>
#include <new>

#include <unistd.h>

#include "offload.h"

#define eprintf(...)
// #define eprintf(...) printf(__VA_ARGS__)

// Queue may only have a single consumer

// use std::hardware_destructive_interference_size instead of CLSIZE

namespace mmcso
{
    // using Element = OffloadCommand &;

    template <size_t Capacity>
    class MPSCQueue
    {
    public:
        // Enqueue an item using inplace construction. Blocks if queue is full.
        void enqueue(OffloadCommand &&command)
        {
            // unsigned integer overflow is well-defined so we can use FAI instead of CAS
            size_t my_tail   = tail_idx_.fetch_add(1u, std::memory_order_relaxed) & mask_;
            size_t next_tail = (my_tail + 1) & mask_;

            eprintf("[pid=%d] next_tail: %zu\n", (int)getpid(), next_tail);

            // wait until queue is not full
            while (next_tail == head_idx_.load(std::memory_order_acquire)) {
                /* spin */
                eprintf("[pid=%d] queue full\n", (int)getpid());
            }

            // wait until slot can be written to
            while (readable_[my_tail].load(std::memory_order_acquire)) /* TODO: memory order */ {
                /* spin */
                eprintf("[pid=%d] slot %zu not writeable\n", (int)getpid(), my_tail);
            }

            eprintf("[pid=%d] writing to: %zu\n", (int)getpid(), my_tail);

            cmd_pool_[my_tail] = std::move(command);

            // mark slot as readable
            readable_[my_tail].store(true, std::memory_order_release);
        }

        // Dequeue an item by returning a pointer. Returns nullptr if queue is empty.
        OffloadCommand *dequeue()
        {
            size_t current_head = head_idx_.load(std::memory_order_relaxed);

            if (current_head == (tail_idx_.load(std::memory_order_acquire) & mask_)) {
                // Queue is empty
                // return false;
                eprintf("[pid=%d] queue empty\n", (int)getpid());
                return nullptr;
            }

            // wait until slot can be read
            while (!readable_[current_head].load(std::memory_order_acquire)) /* TODO: memory order */ {
                /* spin */
                eprintf("[pid=%d] slot %zu not readable\n", (int)getpid(), current_head);
            }

            head_idx_.store((current_head + 1) & mask_, std::memory_order_release);

            eprintf("[pid=%d] reading from: %zu\n", (int)getpid(), current_head);

            // don't mark slot as writeable yet!

            return &cmd_pool_[current_head];
        }

        void release_command(OffloadCommand *oc)
        {
            size_t index = oc - &cmd_pool_[0];
            // mark slot as writeable
            readable_[index].store(false, std::memory_order_release);
        }

    private:
        alignas(CLSIZE) std::atomic<std::size_t> tail_idx_{0u};
        alignas(CLSIZE) std::atomic<std::size_t> head_idx_{0u};

        alignas(CLSIZE) std::array<OffloadCommand, Capacity>   cmd_pool_{};
        alignas(CLSIZE) std::array<std::atomic_bool, Capacity> readable_{}; // TODO: better put this in OffloadCommand ?!

        static constexpr std::size_t capacity_{Capacity};
        static constexpr std::size_t mask_{Capacity - 1};

        static constexpr bool is_pow_2(size_t val) { return val > 0 && (val & (val - 1)) == 0; }
        static_assert(is_pow_2(Capacity), "MPSCQueue capacity must be power of 2");
    };
} // namespace mmcso

#endif /* MMCSO_MPSC_QUEUE_H_INCLUDED */
