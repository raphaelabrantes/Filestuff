#include "cutnwrite.h"

void readcutf(char filename[], metadata * metainfo){
    uint64_t  ogfilesz, cuts, cutsmade, wrote =0;

    FILE *file = fopen(filename, "rb");
    if(file==NULL) exit(1);
    fseek(file, 0L, SEEK_END);
    ogfilesz= ftell(file);
    rewind(file);
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
    metainfo->nfiles = cutsmade;
    printf("size %" PRIu64 "\n", ogfilesz);
    printf("wrote %" PRIu64 "\n", wrote);
    printf("cuts: %" PRIu64 "\n",cuts);
}


char * createfilename(char oldfilename[], uint64_t  cut, metadata * metainfo){
    char cutname[27],  * new_name, trans [] = "here/";
    snprintf(cutname, 27, ".cut-%" PRIu64 ".rtf", cut);
    new_name = (char *)calloc(strlen(oldfilename) + strlen(cutname) + 1, sizeof(char));
    strcat(new_name, trans);
    strcat(new_name, oldfilename);
    strcat(new_name, cutname);
    addnode(new_name, metainfo);
    return new_name;

}

uint64_t writefile(const char fbuffer[], uint64_t cutsmade, char * filename, uint64_t until, metadata * metainfo){
    char * newbuff = (char *) calloc(until, sizeof(char));
    for(uint64_t i =0; i < until; i++){
        newbuff[i] = fbuffer[(cutsmade * CUTSIZE) + i];
    }
    char * name = createfilename(filename, cutsmade, metainfo);
    FILE * newfile = fopen(name, "wb");
    uint64_t wrote = fwrite(newbuff, 1, until, newfile);
    fclose(newfile);
    free(newbuff);
    return wrote;
}
