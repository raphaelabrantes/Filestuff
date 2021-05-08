//
// Created by godofall on 07/05/2021.
//

#include "trackers.h"
#include "../libs/cJSON.h"

list * add_to_list(const char * value, list * old){
    list * new = (list *) calloc(1, sizeof(list *));
    new->value = value;
    new->next = old;
    return new;
}

size_t writefunc(void *prt, size_t size, size_t nmemb, tracker_info * trinfo){
    const cJSON * seed = NULL;
    const cJSON * track = NULL;
    const cJSON * reply = cJSON_Parse(prt);
    const cJSON * seeders = cJSON_GetObjectItemCaseSensitive(reply, "seeders");
    const cJSON * trackers = cJSON_GetObjectItemCaseSensitive(reply, "trackers");
    cJSON_ArrayForEach(seed, seeders){
        trinfo->seeders = add_to_list(seed->valuestring, trinfo->seeders);
        trinfo->amountSeeders+=1;
    }
    cJSON_ArrayForEach(track, trackers){
        trinfo->trackers = add_to_list(track->valuestring, trinfo->trackers);
        trinfo->amountTrackers +=1;
    }
    return size * nmemb;
}
