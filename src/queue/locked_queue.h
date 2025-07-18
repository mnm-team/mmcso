#ifndef MMCSO_LOCKED_QUEUE_H_INCLUDED
#define MMCSO_LOCKED_QUEUE_H_INCLUDED

#include <mutex>
#include <queue>

#include "offload.h"

namespace mmcso
{
    class LockedQueue
    {
    public:
        void enqueue(OffloadCommand &&elem)
        {
            std::lock_guard<std::mutex> lock{mtx_};
            q_.push(new OffloadCommand(std::move(elem)));
        }

        OffloadCommand *dequeue()
        {
            OffloadCommand *value;

            std::lock_guard<std::mutex> lock{mtx_};
            if (q_.empty()) {
                return nullptr;
            }
            value = q_.front();
            q_.pop();

            return value;
        }

        void release_command(OffloadCommand *oc) { delete oc; }

    private:
        std::queue<OffloadCommand *> q_;
        std::mutex                   mtx_;
    };
} // namespace mmcso

#endif /* MMCSO_LOCKED_QUEUE_H_INCLUDED */
