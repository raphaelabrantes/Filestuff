#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#define CUTSIZE 256000


char * readcutf(char filename[]);
uint64_t   readwrite(FILE * oldfile,char filename[], uint64_t   start, uint64_t   end,  uint64_t final);
char * createfilename(char oldfilename[], uint64_t   cut);

int main() {
    char * c = readcutf("fotoo.png");
    printf("%s", c);
    return 0;
}


char * readcutf(char filename[]){
    uint64_t   ogfilesz, cuts, cutsmade, left = 0;
    FILE *file = fopen(filename, "rb");
    if(file==NULL) exit(1);
    fseek(file, 0L, SEEK_END);
    ogfilesz= ftell(file);
    cuts = ogfilesz/ CUTSIZE;
    rewind(file);

    printf("size %" PRIu64 "\n", ogfilesz);
    printf("cuts: %" PRIu64 "\n",cuts);

    for(cutsmade = 0; cutsmade < cuts; cutsmade++){
        char * newnamef = createfilename(filename, cutsmade);
        uint64_t  start, end;
        start = (cutsmade  * CUTSIZE) + 1 ;
        end = cutsmade + 1 * CUTSIZE;
        left += readwrite(file, newnamef, start, end, CUTSIZE);
    }
    if(left != ogfilesz){
        char * newnamef = createfilename(filename, cutsmade);
        left += readwrite(file, newnamef, (cutsmade * CUTSIZE) + 1 , ogfilesz, ogfilesz - left);
    }
    printf("WROTE: %" PRIu64 "" , left);
    fclose(file);
}


uint64_t   readwrite(FILE * oldfile, char filename[], uint64_t   start, uint64_t   end, uint64_t final){
    char cutbuff[CUTSIZE];
    FILE *newfile = fopen(filename, "wb");
    fread(cutbuff, start , end , oldfile);
    uint64_t  sizewrote = fwrite(cutbuff, 1, final, newfile);
    fclose(newfile);
    return sizewrote;

}

char * createfilename(char oldfilename[], uint64_t  cut){
    char cutname[27],  * new_name;
    snprintf(cutname, 27, ".cut-%" PRIu64 ".rtf", cut);
    new_name = (char *)calloc(strlen(oldfilename) + strlen(cutname) + 1, sizeof(char));
    strcat(new_name, oldfilename);
    strcat(new_name, cutname);
    return new_name;

}