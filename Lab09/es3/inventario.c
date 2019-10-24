#include "inventario.h"

inv_t *alloca_inventario(int n){
    inv_t *tmp;
    
    tmp=(inv_t *)malloc(n*sizeof(inv_t));
    if(tmp==NULL){
        printf("Errore allocazione inventario.\n");
        exit(1);
    }
    
    return tmp;
}

void leggi_oggetti(FILE *fp, inv_t *invent, int n){
    for(int i=0; i<n; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", invent[i].nome, invent[i].tipo, &invent[i].stat.hp, &invent[i].stat.mp, &invent[i].stat.atk, &invent[i].stat.def, &invent[i].stat.mag, &invent[i].stat.spr);
    }
}

int sel_obj_vettInv(inv_t *inv, int n, char *oggetto){
    int i;
    
    for(i=0; strcmp(inv[i].nome, oggetto) && i<n; i++);
    
    if(i==n){
        printf("Errore - Oggetto non presente nell' inventario\n");
        return -1;
    }
    return i;
}

int check_oggetto(int i, char *oggetto, inv_t *inv){
    if(!strcmp(inv[i].nome), oggetto){
        return 1;
    }
    return 0;
}

void print_tool(inv_t inv){
    printf(" %s\n", inv.nome);
}

int _hp(int i, inv_t *inv){
    return inv[i].stat.hp;
}

int _mp(int i, inv_t *inv){
    return inv[i].stat.mp;
}

int _atk(int i, inv_t *inv){
    return inv[i].stat.atk;
}

int _def(int i, inv_t *inv){
    return inv[i].stat.def;
}

int _mag(int i, inv_t *inv){
    return inv[i].stat.mag;
}

int _spr(int i, inv_t *inv){
    return inv[i].stat.spr;
}

void libera_inv(inv_t *inv){
    free(inv);
}