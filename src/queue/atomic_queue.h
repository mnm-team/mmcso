#ifndef MMCSO_ATOMIC_QUEUE_H_INCLUDED
#define MMCSO_ATOMIC_QUEUE_H_INCLUDED

#include "atomic_queue/atomic_queue.h"
#include "offload.h"

namespace mmcso
{
    template <size_t QueueSize>
    class AtomicQueue
    {
    public:
        void            enqueue(OffloadCommand &&elem) { q_.push(new OffloadCommand{std::move(elem)}); }
        OffloadCommand *dequeue()
        {
            OffloadCommand *value;
            if (q_.try_pop(value)) {
                return value;
            }
            return nullptr;
        }

        void release_command(OffloadCommand *oc) { delete oc; }

    private:
        atomic_queue::AtomicQueue<OffloadCommand *, QueueSize> q_;
    };
} // namespace mmcso

#endif /* MMCSO_ATOMIC_QUEUE_H_INCLUDED */
