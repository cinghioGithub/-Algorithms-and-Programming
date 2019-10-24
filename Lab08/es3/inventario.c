#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inventario.h"

void carica_oggetti(inv_t **invent, tabInv **inventario){
    FILE *fp;
    int i, num_inv;
    
    fp = fopen("inventario.txt", "r");
    if(fp==NULL){
        printf("Errore apertura inventario.txt\n");
        exit(1);
    }
    
    fscanf(fp, "%d", &num_inv);
    (*inventario)=(tabInv *)malloc(sizeof(tabInv));
    (*invent)=(inv_t *)malloc(num_inv*sizeof(inv_t));
    if((*invent)==NULL){
        printf("Errore allocazione inventario.\n");
        exit(1);
    }
    
    for(i=0; i<num_inv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", (*invent)[i].nome, (*invent)[i].tipo, &(*invent)[i].stat.hp, &(*invent)[i].stat.mp, &(*invent)[i].stat.atk, &(*invent)[i].stat.def, &(*invent)[i].stat.mag, &(*invent)[i].stat.spr);
    }
    
    (*inventario)->nInv=num_inv;
    (*inventario)->vettInv=(*invent);
    fclose(fp);
}

void ricerca_oggetto(tabInv *tab){
    char name[MAX];
    int i;
    if(tab->nInv==0){
        printf("Inventario vuoto.\n");
    }
    else{
        printf("Inserire nome oggetto: ");
        scanf("%s", name);
        
        for(i=0; i<tab->nInv; i++){
            if(!strcmp(tab->vettInv[i].nome, name)){
                break;
            }
        }
        if(i==tab->nInv){
            printf("Oggetto non presente nell'inventario.\n");
        }
        else{
            printf("Oggetto trovato, tipo: %s\n", tab->vettInv[i].tipo);
        }
    }
    
}

void stampa_oggetto(tabInv *tab){
    char name[MAX];
    int i;
    if(tab->nInv==0){
        printf("Inventario vuoto.\n");
    }
    else{
        printf("Inserire nome oggetto: ");
        scanf("%s", name);
        
        for(i=0; i<tab->nInv; i++){
            if(!strcmp(tab->vettInv[i].nome, name)){
                break;
            }
        }
        if(i==tab->nInv){
            printf("Oggetto non presente nell'inventario.\n");
        }
        else{
            printf("Oggetto trovato:\n %s %s %d %d %d %d %d %d\n", tab->vettInv[i].nome, tab->vettInv[i].tipo, tab->vettInv[i].stat.hp, tab->vettInv[i].stat.mp, tab->vettInv[i].stat.atk, tab->vettInv[i].stat.def, tab->vettInv[i].stat.mag, tab->vettInv[i].stat.spr);
        }
    }
}

void libera_inventario(tabInv *tab){
    libera_equipment(tab->vettInv);
    free(tab);
}

void libera_equipment(inv_t *p){
    free(p);
}