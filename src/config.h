#pragma once

// #include "hash_request_manager.h"
// #include "atomic_queue_rigtorp.h"
// #include "locked_queue.h"

#include "array_request_manager.h"
#include "offload.h"
#include "wait_strategy.h"

#define QUEUE_SIZE        256
#define REQUEST_POOL_SIZE 1024

#define USE_MPSC_QUEUE    1
#define USE_ATOMIC_QUEUE  0

using WAIT_STRATEGY = mmcso::SpinWait;
// using WAIT_STRATEGY = mmcso::AtomicWait;

using REQUEST_MANAGER_TYPE = mmcso::ArrayRequestManager<REQUEST_POOL_SIZE, WAIT_STRATEGY>;

#if USE_MPSC_QUEUE
#    include "queue/mpsc_queue.h"
using QUEUE_TYPE = mmcso::MPSCQueue<mmcso::OffloadCommand, QUEUE_SIZE>;
#elif USE_ATOMIC_QUEUE
#    include "queue/atomic_queue.h"
using QUEUE_TYPE = mmcso::AtomicQueue<QUEUE_SIZE>;
#else
#    include "queue/locked_queue.h"
using QUEUE_TYPE = mmcso::LockedQueue;
#endif

using OE = mmcso::OffloadEngine<QUEUE_TYPE, REQUEST_MANAGER_TYPE>;

extern OE &oe;
