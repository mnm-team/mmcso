#pragma once

#include "array_request_manager.h"
// #include "hash_request_manager.h"

// #include "atomic_queue_rigtorp.h"
// #include "locked_queue.h"

#include "offload.h"

#define QUEUE_SIZE        64
#define REQUEST_POOL_SIZE 64

#define USE_MPSCQUEUE 1

#if USE_MPSCQUEUE
#    include "queue/mpsc_queue.h"
#    define NEW_OR_FWD
using OE = mmcso::OffloadEngine<mmcso::MPSCQueue<mmcso::OffloadCommand, QUEUE_SIZE>, mmcso::ArrayRequestManager<REQUEST_POOL_SIZE>>;
#else
#    include "queue/atomic_queue.h"
#    define NEW_OR_FWD new
using OE = mmcso::OffloadEngine<mmcso::AtomicQueue<QUEUE_SIZE>, mmcso::ArrayRequestManager<REQUEST_POOL_SIZE>>;
//
#endif

extern OE &oe;
