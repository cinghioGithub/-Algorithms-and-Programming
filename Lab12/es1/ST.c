#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

struct st {
    char *str;
    ST l;
    ST r;
    int ind;
};

ST setNull(){
    return NULL;
}

ST st_new_node(char *str, int ind){
    ST st;
    
    st = (ST)malloc(sizeof(*st));
    if(st == NULL){
        printf("Errore allocazione nodo.\n");
        exit(-1);
    }
    
    st->l = NULL;
    st->r = NULL;
    st->str = strdup(str);
    st->ind = ind;
    
    return st;
}

ST st_insert(ST st, char *str, int ind){
    if(st == NULL){
        return st_new_node(str, ind);
    }
    if(strcmp(str, st->str)>0){
        st->r = st_insert(st->r, str, ind);
    }
    if(strcmp(str, st->str)<0){
        st->l = st_insert(st->l, str, ind);
    }
    
    return st;
}

void libera_ST(ST st){
    if(st == NULL){
        return;
    }
    libera_ST(st->l);
    libera_ST(st->r);
    free(st->str);
    free(st);
}

int string_to_ind(ST st, char *str){
    if(!strcmp(st->str, str)){
        return st->ind;
    }
    if(strcmp(str, st->str)>0){
        return string_to_ind(st->r, str);
    }
    if(strcmp(str, st->str)<0){
        return string_to_ind(st->l, str);
    }
}

char *ind_to_string(ST st, int ind, int *flag){
    char *i;
    
    if(st == NULL){
        return NULL;
    }
    if(st->ind == ind){
        (*flag) = 0;
        return st->str;
    }
    
    i = ind_to_string(st->l, ind, flag);
    if(*flag){
        i = ind_to_string(st->r, ind, flag);
    }
    return i;
}

void print_st(ST st){
    if(st == NULL)
        return;
    
    print_st(st->l);
    printf("%s\n", st->str);
    print_st(st->r);
}