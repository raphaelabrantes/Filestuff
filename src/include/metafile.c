#include "metafile.h"

void addnode(char new_name[] ,metadata * metainfo,  char * hash){
    filenode * new_node = (filenode *) calloc(1, sizeof(filenode *));
    new_node->filename = new_name;
    new_node->hash = hash;
    if(!metainfo->start){
        metainfo->start = new_node;
        return;
    }
    filenode * aux = metainfo->start;
    while (aux->next){
        aux = aux->next;
    }
    aux->next = new_node;
}

filenode * getnode(uint64_t index, filenode * node){
    for(uint64_t i = 0; i < index; i++){
        node = node->next;
    }
    return node;
}

char * getnodefile(uint64_t index, filenode * node){
    return getnode(index, node)->filename;
}

char * getnodehash(uint64_t index, filenode * node){
    return getnode(index, node)->hash;
}

void writemetaf(metadata * metainfo){
    FILE * metafile = fopen("meta.inf", "w");
    if(!metafile)exit(1);
    fprintf(metafile, "%"PRIu64"\n",metainfo->size);
    fprintf(metafile, "%"PRIu64"\n", metainfo->nfiles);
    for(uint64_t i = 0; i <= metainfo->nfiles; i++){
        fprintf(metafile, "%s\n%s\n",getnodefile(i, metainfo->start), getnodehash(i, metainfo->start));
    }
    fclose(metafile);
}
void readmetaf(metadata* metainfo){
    char buff [MAXSIZE];
    char * filename;
    char * hash;
    FILE * metafile = fopen("meta.inf", "r");
    if(!metafile)exit(1);
    fgets(buff, MAXSIZE, metafile);
    metainfo->size = strtoull(buff,&filename, 10);
    memset(buff,0, MAXSIZE);
    fgets(buff, MAXSIZE, metafile);
    metainfo->nfiles = strtoull(buff, &filename, 10);
    for(uint64_t i = 0; i <= metainfo->nfiles; i++){
        filename = (char *) calloc(FILE_NAME_S, sizeof(char ));
        hash = (char *) calloc(HEX_HASH_S, sizeof(char ));
        fgets(filename, FILE_NAME_S, metafile);
        fgets(hash, HEX_HASH_S, metafile);
        filename[strcspn(filename, "\n")] = 0;
        hash[strcspn(hash, "\n")] = 0;
        addnode(filename, metainfo, hash);
    }
    fclose(metafile);
}

unsigned char * createhash(const char * buffer, uint64_t size){
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned char * md_value = (unsigned char *) calloc(EVP_MAX_MD_SIZE, sizeof(char *));
    const EVP_MD *md = EVP_get_digestbyname("md5");
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, buffer, size);
    EVP_DigestFinal_ex(mdctx, md_value, NULL);
    EVP_MD_CTX_free(mdctx);
    return md_value;
}

char * makehexhash(const unsigned char * hash){
    char add[3];
    char * hexhash = (char *) calloc(HASHSIZE, sizeof(char *));
    for(int i=0; i < HASHSIZE; i++){
        sprintf(add, "%02x" ,hash[i]);
        strcat(hexhash, add);
    }
    return hexhash;
}

void freenodes(metadata * metainfo){
    for(int64_t size = (int64_t) metainfo->nfiles; size >= 0; size--){
        filenode * oldnode = getnode(size, metainfo->start);
        free(oldnode->hash);
        free(oldnode->filename);
        free(oldnode);
    }
    free(metainfo);
}