#include <stdlib.h>
#include <curl/curl.h>
#include "include/cutnwrite.h"
#include "include/metafile.h"
#include "include/mergefiles.h"
#include "include/trackers.h"
#include "libs/cJSON.h"

void makemate();
void makecurl();

int main() {
    makemate();
    makecurl();
    return 0;
}

void makecurl(){
    CURL *curl = curl_easy_init();
    tracker_info trinfo;
    trinfo.amountSeeders = trinfo.amountTrackers = 0;
    trinfo.seeders = NULL;
    trinfo.trackers = NULL;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &trinfo);
        curl_easy_perform(curl);
    }
    for(list * aux = trinfo.seeders; aux ; aux = aux->next){
        printf("%s\n", aux->value);
    }
    for(list * aux1 = trinfo.trackers; aux1 ; aux1 = aux1->next){
        printf("%s\n", aux1->value);
    }
}

void makemate(){
    metadata * metainfo = (metadata *) calloc(sizeof(metadata *), 1);
    readcutf("new.jpg", metainfo);
    writemetaf(metainfo);
    metadata * metainfo2 = (metadata *) calloc(sizeof(metadata *), 1);
    readmetaf(metainfo2);
    mergefiles(metainfo2);
}