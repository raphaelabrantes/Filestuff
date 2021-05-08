#include "cutnwrite.h"

void readcutf(char filename[], metadata * metainfo){
    uint64_t ogfilesz;
    uint64_t cuts;
    uint64_t cutsmade;
    uint64_t wrote = 0;

    FILE *file = fopen(filename, "rb");
    if(file==NULL) exit(1);
    ogfilesz = getfilesz(file);
    cuts = ogfilesz/ CUTSIZE;
    char * fbuffer = (char *) calloc(ogfilesz, sizeof(char));
    fread(fbuffer, 1, ogfilesz, file);
    fclose(file);

    metainfo->size = ogfilesz;

    for(cutsmade = 0; cutsmade < cuts; cutsmade++) {
        wrote += writefile(fbuffer,cutsmade, filename, CUTSIZE, metainfo);
    }
    if(wrote != ogfilesz){
        wrote += writefile(fbuffer, cutsmade,filename, ogfilesz - wrote, metainfo);
    }
    free(fbuffer);
    metainfo->nfiles = cutsmade;
    printf("size %" PRIu64 "\n", ogfilesz);
    printf("wrote %" PRIu64 "\n", wrote);
    printf("cuts: %" PRIu64 "\n",cuts);
}


char * createfilename(const char * oldfilename, uint64_t  cut){
    char cutname[27];
    char * new_name;
    char trans [] = "cuts/";
    snprintf(cutname, 27, ".cut-%" PRIu64 ".rtf", cut);
    new_name = (char *)calloc(strlen(oldfilename) + strlen(cutname) + 1, sizeof(char));
    strcpy(new_name, trans);
    strcat(new_name, oldfilename);
    strcat(new_name, cutname);
    return new_name;

}

uint64_t getfilesz(FILE * file){
    uint64_t size;
    fseek(file, 0L, SEEK_END);
    size= ftell(file);
    rewind(file);
    return size;
}

uint64_t writefile(const char fbuffer[], uint64_t cutsmade, const char * filename, uint64_t until, metadata * metainfo){
    char * newbuff = (char *) calloc(until, sizeof(char));
    char * hash;
    for(uint64_t i =0; i < until; i++){
        newbuff[i] = fbuffer[(cutsmade * CUTSIZE) + i];
    }
    char * name = createfilename(filename, cutsmade);
    FILE * newfile = fopen(name, "wb");
    if(newfile == NULL) exit(-1);
    uint64_t wrote = fwrite(newbuff, 1, until, newfile);
    fclose(newfile);
    hash = makehexhash(createhash(newbuff, wrote));
    addnode(name, metainfo, hash);
    free(newbuff);
    return wrote;
}
