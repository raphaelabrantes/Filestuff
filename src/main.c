#include <stdlib.h>
#include "include/cutnwrite.h"
#include "include/metafile.h"
#include "include/mergefiles.h"



int main() {
    metadata * metainfo = (metadata *) calloc(sizeof(metadata *), 1);
    readcutf("new.jpg", metainfo);
    writemetaf(metainfo);
    metadata * metainfo2 = (metadata *) calloc(sizeof(metadata *), 1);
    readmetaf(metainfo2);
    mergefiles(metainfo2);
    return 0;
}
