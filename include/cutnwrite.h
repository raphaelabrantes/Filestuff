#ifndef FILESTUFF_CUTNWRITE_H
#define FILESTUFF_CUTNWRITE_H
#include "metafile.h"
#define CUTSIZE 256000

void readcutf(char filename[], metadata * metainfo);
char * createfilename(char oldfilename[], uint64_t cut, metadata * metainfo);
uint64_t writefile( const char fbuffer[], uint64_t cutsmade, char * filename, uint64_t until, metadata * metainfo);


#endif //FILESTUFF_CUTNWRITE_H