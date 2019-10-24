#ifndef _PERSONAGGI
#define _PERSONAGGI
#include "inventario.h"

#define MAX 50
#define N 7

typedef struct statistiche{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct equip{
    int inUso;
    inv_t *vettEq[N_INV];
}tabEquipment;

typedef struct pg{
    char nome[MAX];
    char codice[N];
    char classe[MAX];
    tabEquipment *tabEquip;
    stat_t stat;
}caratteristiche;

typedef struct nodo nodo_pg, *link;

typedef struct nodo {
    caratteristiche pg_t;
    link next;
}nodo_pg;

typedef struct node{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

void alloca_head(tabPg_t **h);
link new_node();
void libera_nodo(link nodo);
tabPg_t *nuovo_personaggio(tabPg_t *head);
tabPg_t *carica_lista(tabPg_t *head);
tabPg_t *elimina_personaggio(tabPg_t *head);
void agg_rim_oggetto(command_t cmd, tabPg_t *head, tabInv *inventario);
void statistiche(tabPg_t *head);
link ricerca_pg(tabPg_t *head);
void stampa_personaggio(tabPg_t *head);
void libera_lista(tabPg_t *head);

#endif

