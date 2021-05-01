#include "mergefiles.h"

void mergefiles(metadata * metainfo){
    uint64_t size;
    FILE * f = fopen("merge.jpg", "wb");
    for(uint64_t i=0; i <= metainfo->nfiles; i++){
        char * fbuffer;
        filenode * node = getnode(i, metainfo->start);
        FILE *cutfile = fopen(node->filename, "rb");
        if(cutfile==NULL) exit(1);
        size = getfilesz(cutfile);
        fbuffer = (char *) calloc(size, sizeof(char));
        fread(fbuffer, 1, size, cutfile);
        fclose(cutfile);
        if(strcmp(node->hash, makehexhash(createhash(fbuffer, size))) == 0){
            printf("node %" PRIu64" hash %s bate\n", i, node->hash);
            fwrite(fbuffer, 1, size, f);
        }
        else {
            printf("node %" PRIu64" hash %s nao bate\n", i, node->hash);
            exit(2);
        }
        free(fbuffer);
    }
    fclose(f);
}
