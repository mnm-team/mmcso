#pragma once

#include <atomic>

namespace mmcso
{
    struct SpinWait {
        static void wait(std::atomic_bool &done)
        {
            while (!done.load(std::memory_order_acquire)) {
                /* spin */
            }
        }
        static void notify(std::atomic_bool &done) { done.store(true, std::memory_order_release); }
    };

    struct AtomicWait {
        static void wait(std::atomic_bool &done) { done.wait(false, std::memory_order_acquire); }
        static void notify(std::atomic_bool &done)
        {
            done.store(true, std::memory_order_release);
            done.notify_one();
        }
    };
} // namespace mmcso