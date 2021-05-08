#ifndef FILESTUFF_CUTNWRITE_H
#define FILESTUFF_CUTNWRITE_H
#include "metafile.h"

void readcutf(char filename[], metadata * metainfo);
char * createfilename(const char * oldfilename, uint64_t cut);
uint64_t getfilesz(FILE * file);
uint64_t writefile( const char fbuffer[], uint64_t cutsmade, const char * filename, uint64_t until, metadata * metainfo);


#endif //FILESTUFF_CUTNWRITE_H