//
// Created by godofall on 07/05/2021.
//

#ifndef FILESTUFF_TRACKERS_H
#define FILESTUFF_TRACKERS_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    struct list * next;
    const char * value;
}list;

typedef struct tracker_info{
    list * trackers;
    list * seeders;
    uint32_t amountTrackers;
    uint32_t amountSeeders;
} tracker_info;

size_t writefunc(void *ptr, size_t size, size_t nmemb, tracker_info * x);
list * add_to_list(const char * value, list * old);
#endif //FILESTUFF_TRACKERS_H
