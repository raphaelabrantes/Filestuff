#include "metafile.h"

void addnode(char new_name[] ,metadata * metainfo,  char * hash){
    filenode * new_node = (filenode *) calloc(sizeof(filenode *), 1);
    new_node->filename = new_name;
    new_node->hash = (char *) hash;
    if(metainfo->start == NULL){
        metainfo->start = new_node;
        return;
    }
    filenode * aux = metainfo->start;
    while (aux->next != NULL){
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
    fprintf(metafile, "%"PRIu64"\n",metainfo->size);
    fprintf(metafile, "%"PRIu64"\n", metainfo->nfiles);
    for(uint64_t i = 0; i <= metainfo->nfiles; i++){
        fprintf(metafile, "%s\n%s\n",getnodefile(i, metainfo->start), getnodehash(i, metainfo->start));
    }
    fclose(metafile);
}
void readmetaf(metadata* metainfo){
    FILE * metafile = fopen("meta.inf", "r");
    char buff [50];
    char * filename, *hash;
    fgets(buff, 50, metafile);
    metainfo->size = strtoull(buff,&filename, 10);
    memset(buff,0,strlen(buff));
    fgets(buff, 50, metafile);
    metainfo->nfiles = strtoull(buff, &filename, 10);
    for(uint64_t i = 0; i <= metainfo->nfiles; i++){
        filename = (char *) calloc(sizeof(char ), 50);
        hash = (char *) calloc(sizeof(char ), 34);
        fgets(filename, 50, metafile);
        fgets(hash, 34, metafile);
        filename[strcspn(filename, "\n")] = 0;
        hash[strcspn(hash, "\n")] = 0;
        addnode(filename, metainfo, hash);
    }
    fclose(metafile);
}

unsigned char * createhash(const char * buffer, uint64_t size){
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned char * md_value = (unsigned char *) calloc(sizeof(char *), EVP_MAX_MD_SIZE);
    const EVP_MD *md = EVP_get_digestbyname("md5");
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, buffer, size);
    EVP_DigestFinal_ex(mdctx, md_value, NULL);
    EVP_MD_CTX_free(mdctx);
    return md_value;
}

char * makehexhash(unsigned char * hash){
    char add[3];
    char * hexhash = (char *) calloc(sizeof(char *), HASHSIZE);
    for(int i=0; i < HASHSIZE; i++){
        sprintf(add, "%02x" ,hash[i]);
        strcat(hexhash, add);
    }
    return hexhash;
}
