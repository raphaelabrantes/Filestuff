#include "metafile.h"

void addnode(char new_name[] ,metadata * metainfo){
    filenode * new_node = (filenode *) calloc(sizeof(filenode *), 1);
    new_node->filename = new_name;
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

char * getnodefile(uint64_t index, filenode * node){
    for(uint64_t i = 0; i < index; i++){
        node = node->next;
    }
    return node->filename;
}

void writemetaf(metadata * metainfo){
    FILE * metafile = fopen("meta.inf", "w");
    fprintf(metafile, "%"PRIu64"\n",metainfo->size);
    fprintf(metafile, "%"PRIu64"\n", metainfo->nfiles);
    for(uint64_t i = 0; i <= metainfo->nfiles; i++){
        fprintf(metafile, "%s\n",getnodefile(i, metainfo->start));
    }
    fclose(metafile);
}
void readmetaf(metadata* metainfo){
    FILE * metafile = fopen("meta.inf", "r");
    char buff [50];
    char * clean;
    fgets(buff, 50, metafile);
    metainfo->size = strtoull(buff,&clean, 10);
    memset(buff,0,strlen(buff));
    fgets(buff, 50, metafile);
    metainfo->nfiles = strtoull(buff, &clean, 10);
    for(uint64_t i = 0; i <= metainfo->nfiles; i++){
        clean = (char *) calloc(sizeof(char ), 50);
        fgets(clean, 50, metafile);
        clean[strcspn(clean, "\n")] = 0;
        addnode(clean, metainfo);
    }
    fclose(metafile);
}