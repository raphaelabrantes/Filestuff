#ifndef FILESTUFF_METAFILE_H
#define FILESTUFF_METAFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <dirent.h>


typedef struct filenodes{
    struct filenodes * next;
    char * filename;

} filenode;

typedef struct metadatas{
    uint64_t size;
    uint64_t nfiles;
    filenode * start;
} metadata;


void addnode(char new_name[] ,metadata * metainfo);
void writemetaf(metadata * metainfo);
void readmetaf(metadata* metainfo);
char * getnodefile(uint64_t index, filenode * node);
#endif //FILESTUFF_METAFILE_H
