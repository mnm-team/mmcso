#ifndef MMCSO_MPSC_QUEUE_H_INCLUDED
#define MMCSO_MPSC_QUEUE_H_INCLUDED

#include <array>
#include <atomic>
#include <limits>
#include <new>

#include <cstddef> // offsetof
#include <cstdint> // int types

// Queue may only have a single consumer

namespace mmcso
{
    // queue empty:
    // [-------------------]
    //     head~^~tail
    //
    // queue full:
    // [XXXXXXXXXXXXXXXXXXX]
    //     tail~^^~head
    //
    // queue not empty/full (1)
    //
    // [--------XXXXXX-----]
    //     head~^    ^~tail
    //
    // queue not empty/full (2)
    //
    // [XXX-------------XXX]
    //    ^~tail   head~^
    //
    // def: we enqueue at tail and read from head

    using index_t = std::uint_fast32_t;
    static_assert(std::numeric_limits<index_t>::is_integer);
    static_assert(!std::numeric_limits<index_t>::is_signed);
    static_assert(std::numeric_limits<index_t>::is_modulo);

    template <class T, index_t Capacity>
    class MPSCQueue
    {
        // static constexpr size_t CLSIZE = std::hardware_destructive_interference_size;

    public:
        // Enqueue an item using inplace construction. Blocks if queue is full.
        void enqueue(T &&command)
        {
            // unsigned integer overflow is well-defined so we can use FAI instead of CAS
            // Returns the value immediately preceding the effects of this function
            index_t current_tail = tail_idx_.fetch_add(1u, std::memory_order_relaxed);

            // reload head to check whether queue is still full
            while (static_cast<index_t>(current_tail - head_idx_.load(std::memory_order_acquire)) >= Capacity)
                [[unlikely]] {
                /* spin */
            }

            index_t tail_slot = current_tail & mask_;

            // write to slot
            cmd_pool_[tail_slot].t_ = std::move(command);

            // mark slot as readable
            cmd_pool_[tail_slot].readable_.store(true, std::memory_order_release);
        }

        // Dequeue an item by returning a pointer.
        // Returns nullptr if queue is empty.
        T *dequeue()
        {
            current_head_ = head_idx_.load(std::memory_order_relaxed);

            if (current_head_ == tail_idx_.load(std::memory_order_relaxed)) {
                /* queue is empty */
                return nullptr;
            }

            index_t head_slot = current_head_ & mask_;

            // wait until slot can be read
            // (is currently being written to by another thread)
            while (!cmd_pool_[head_slot].readable_.load(std::memory_order_acquire)) [[unlikely]] {
                /* spin */
            }

            // don't mark slot as writeable yet!
            // do it when reading is complete (avoids copy due to return by value)

            return &cmd_pool_[head_slot].t_;
        }

        void release_command(T *oc)
        {
            size_t index = reinterpret_cast<QElement *>(oc) - &cmd_pool_[0];
            // mark slot as writeable, then advance head
            cmd_pool_[index].readable_.store(false, std::memory_order_relaxed);
            head_idx_.store(current_head_ + 1u, std::memory_order_release);
        }

    private:
        struct alignas(CLSIZE) QElement {
            QElement()                 = default;
            QElement(const QElement &) = delete;
            QElement(QElement &&)      = delete;

            QElement &operator=(const QElement &t) = delete;
            QElement &operator=(QElement &&t)      = delete;

            T                t_{};
            std::atomic_bool readable_{false};
        };
        static_assert(std::is_standard_layout_v<QElement>);
        static_assert(offsetof(QElement, QElement::t_) == 0);

        static constexpr index_t mask_{Capacity - 1u};
        index_t                  current_head_{0u};

        alignas(CLSIZE) std::atomic<index_t> tail_idx_{0u};
        alignas(CLSIZE) std::atomic<index_t> head_idx_{0u};

        std::array<QElement, Capacity> cmd_pool_{};

        static constexpr bool is_pow_2(index_t val) { return val > 0u && (val & (val - 1u)) == 0u; }
        static_assert(is_pow_2(Capacity), "MPSCQueue capacity must be power of 2");
    };
} // namespace mmcso

#endif /* MMCSO_MPSC_QUEUE_H_INCLUDED */
