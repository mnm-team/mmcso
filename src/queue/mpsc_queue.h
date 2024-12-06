#ifndef MMCSO_MPSC_QUEUE_H_INCLUDED
#define MMCSO_MPSC_QUEUE_H_INCLUDED

#include <array>
#include <atomic>
#include <new>

// constexpr size_t CLSIZE = std::hardware_destructive_interference_size;

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

    template <class T, size_t Capacity>
    class MPSCQueue
    {
    public:
        struct alignas(CLSIZE) TAligned {
            TAligned(T &&t) : t_{std::move(t)} {}
            TAligned() = default;
            T t_;
        };
        // MPSCQueue() { std::cout << "Command Queue Size: " << sizeof(variant_type) <<
        // '\n'; }

        // Enqueue an item using inplace construction. Blocks if queue is full.
        void enqueue(T &&command)
        {
            // unsigned integer overflow is well-defined so we can use FAI instead of CAS
            // Returns the value immediately preceding the effects of this function
            size_t current_tail = tail_idx_.fetch_add(1u, std::memory_order_relaxed);

            // reload head to check whether queue is still full
            while ((current_tail - head_idx_.load(std::memory_order_acquire)) >= Capacity)
                [[unlikely]] {

                /* spin */
            }

            size_t my_tail = current_tail & mask_;

            cmd_pool_[my_tail] = std::move(command);

            // mark slot as readable
            readable_[my_tail].store(true, std::memory_order_release);
        }

        // Dequeue an item by returning a pointer.
        // Returns nullptr if queue is empty.
        T *dequeue()
        {
            size_t current_head = head_idx_.load(std::memory_order_relaxed);

            if (current_head == tail_idx_.load(std::memory_order_relaxed)) {
                /* queue is empty */
                return nullptr;
            }

            size_t head = current_head & mask_;

            // wait until slot can be read
            // (is currently being written to by another thread)
            while (!readable_[head].load(std::memory_order_acquire)) [[unlikely]] {
                /* spin */
            }

            // don't mark slot as writeable yet!
            // do it when reading is complete (avoids copy due to return by value)

            return &cmd_pool_[head].t_;
        }

        void release_command(T *oc)
        {
            size_t index = (TAligned *)oc - &cmd_pool_[0];
            // mark slot as writeable
            readable_[index].store(false, std::memory_order_relaxed);
            head_idx_.fetch_add(1u, std::memory_order_release);
        }

    private:
        alignas(CLSIZE) std::atomic<std::size_t> tail_idx_{0u};
        alignas(CLSIZE) std::atomic<std::size_t> head_idx_{0u};

        std::array<TAligned, Capacity> cmd_pool_{};
        alignas(CLSIZE) std::array<std::atomic_bool, Capacity> readable_{};

        static constexpr std::size_t mask_{Capacity - 1};

        static constexpr bool is_pow_2(size_t val)
        {
            return val > 0u && (val & (val - 1u)) == 0u;
        }
        static_assert(is_pow_2(Capacity), "MPSCQueue capacity must be power of 2");
    };
} // namespace mmcso

#endif /* MMCSO_MPSC_QUEUE_H_INCLUDED */
