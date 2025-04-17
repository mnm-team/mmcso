#pragma once

// #include "hash_request_manager.h"
// #include "atomic_queue_rigtorp.h"
// #include "locked_queue.h"

#include "array_request_manager.h"
#include "offload.h"
#include "wait_strategy.h"

#define QUEUE_SIZE        256
#define REQUEST_POOL_SIZE 1024

#define USE_MPSCQUEUE 1

#if USE_MPSCQUEUE
#    include "queue/mpsc_queue.h"
using OE = mmcso::OffloadEngine<mmcso::MPSCQueue<mmcso::OffloadCommand, QUEUE_SIZE>, mmcso::ArrayRequestManager<REQUEST_POOL_SIZE>>;
#else
#    include "queue/atomic_queue.h"
using OE = mmcso::OffloadEngine<mmcso::AtomicQueue<QUEUE_SIZE>, mmcso::ArrayRequestManager<REQUEST_POOL_SIZE>>;
//
#endif

extern OE &oe;
