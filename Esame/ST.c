#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

struct st{
    char **mat;
    int dim;
};

ST ST_init(int n){
    ST st;
    st = (ST)malloc(sizeof(*st));
    if(st == NULL)
        exit(1);
    st->mat = (char **)malloc(n*sizeof(char *));
    if(st->mat==NULL)
        exit(1);
    for(int i=0; i<n; i++)
        st->mat[i] = NULL;
    
    st->dim = 0;
    return st;
}

int ST_insert(ST st, char *str){
    int i=0;
    
    for (i=0; i<st->dim; i++){              //rimozione della j dichiarata nel for e uso della i
        if(!strcmp(str, st->mat[i]))
            return i;
    }
    st->mat[i] = strdup(str);
    st->dim++;
    return i;
}

int ST_string_to_ind(ST st, char *str){
    int i;
    for(i=0; i<st->dim; i++){
        if(!strcmp(str, st->mat[i]))
            return i;
    }
    return -1;
}

char *ST_ind_to_string(ST st, int i){
    return st->mat[i];
}

void libera_ST(ST st){
    for(int i=0; i<st->dim; i++)
        free(st->mat[i]);
    free(st->mat);
    free(st);
}

//correzione
int ST_size(ST st){
    return st->dim;
}