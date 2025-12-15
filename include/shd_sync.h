#ifndef SHD_SYNC_H
#define SHD_SYNC_H

#include "pico/sync.h"

extern semaphore_t init_comp;
extern volatile bool payload_finished;

#endif