#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabella.h"

struct tabella{
    char **tab;
    int n_v;
};

Tab tabella_init(int n){
    Tab t;
    
    t = (Tab)malloc(sizeof(*t));            //allocazione della struttura tabella
    if(t==NULL){
        printf("Errore allocazione tabella di simboli.\n");
        exit(-1);
    }
    
    t->n_v=0;
    t->tab = (char **)malloc(n*sizeof(char *));        //allocazionde del vettore di stringhe
    
    for(int i=0; i<n; i++)
        t->tab[i]=NULL;
    
    return t;
}

int ins_tab(Tab t, char *name, int *num){
    int i;
    int flag=1;
    
    for(i=0; i<t->n_v && flag==1; i++){             //controllo che name non sia già presente nella tabella di simboli
        if(!strcmp(t->tab[i], name)){
            flag = 0;
            break;
        }
    }
    
    if(flag){                       //quando name non c'è nella tabella lo aggiungo
        t->tab[i] = strdup(name);
        t->n_v++;
        (*num)++;
    }
    
    return i;           //restituzione dell'indice di name
}

char *ind_to_string(Tab t, int ind){
    return t->tab[ind];
}

int string_to_ind(Tab t, char *name){
    int i;
    
    for(i=0; i<t->n_v; i++){
        if(!strcmp(name, t->tab[i]))
            return i;
    }
    
    return -1;
}

void sort_vertici(int *v, Tab t, int n){           //ordinamento dei verici in ordine alfabetico (utilizzo di une vettore di indici)
    int i, j, tmp;
    
    for(i=0; i<n; i++){            //selection sort sui vertici
        for(j=i+1; j<n; j++){
            if(strcmp(t->tab[v[i]], t->tab[v[j]])>0){
                tmp=v[i];
                v[i]=v[j];
                v[j]=tmp;
            }
        }
    }
}

void print_tabella(Tab t){              //funzione di stampa della tabella
    int i;
    
    for(i=0; i<t->n_v; i++){
        printf("%d %s\n", i, t->tab[i]);
    }
}