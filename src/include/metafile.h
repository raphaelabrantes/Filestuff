#ifndef FILESTUFF_METAFILE_H
#define FILESTUFF_METAFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <dirent.h>
#include <openssl/evp.h>
#define HASHSIZE 16
#define MAXSIZE 12
#define FILE_NAME_S 50
#define HEX_HASH_S 34
#define CUTSIZE 256000


typedef struct filenodes{
    struct filenodes * next;
    char * hash;
    char * filename;

} filenode;

typedef struct metadatas{
    uint64_t size;
    uint64_t nfiles;
    filenode * start;
} metadata;

filenode * getnode(uint64_t index, filenode * node);
void freenodes(metadata * metainfo);
void addnode(char new_name[] ,metadata * metainfo, char * hash);
void writemetaf(metadata * metainfo);
void readmetaf(metadata* metainfo);
char * getnodefile(uint64_t index, filenode * node);
char * getnodehash(uint64_t index, filenode * node);
unsigned char * createhash(const char * buffer, uint64_t size);
char * makehexhash(const unsigned char * hash);

#endif //FILESTUFF_METAFILE_H
