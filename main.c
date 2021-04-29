#include <stdlib.h>
#include "include/cutnwrite.h"
#include "include/metafile.h"

#define CUTSIZE 256000



int main() {
    metadata * metainfo = (metadata *) calloc(sizeof(metadata *), 1);
    readcutf("new.jpg", metainfo);
    writemetaf(metainfo);
    metadata * metainfo2 = (metadata *) calloc(sizeof(metadata *), 1);
    readmetaf(metainfo2);
    return 0;
}
