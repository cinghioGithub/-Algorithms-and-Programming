#ifndef _PERSONAGGIO
#define _PERSONAGGIO

#include "inventario.h"
#include "equipArray.h"
#include <stdlib.h>

typedef struct statistiche_p{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_p;

typedef struct pg{
    char nome[MAX];
    char codice[N];
    char classe[MAX];
    tabEquipment tabEquip;
    stat_p stat;
}caratteristiche;

void leggi_caratteristiche(FILE *fp, caratteristiche *pg_t, int *n);
void carica_caratt_pg(caratteristiche *pg_t);
void Init_vett_equip(caratteristiche *pg_t);
void alloca_equip(caratteristiche pg_t);
int check_equip(caratteristiche p);
int selezione_equip(caratteristiche p);
void assegna_obj(caratteristiche *p, int ind_eq, int ind_obj);
int rimozione_oggetto(caratteristiche *p, char *oggetto, inv_t *inv);
int confronta_codice(caratteristiche p, char *cod);
void print_personaggio(caratteristiche pg_t, inv_t *inv);
void calcola_stat(caratteristiche pg_t, inv_t *inv);
void libera_equip(caratteristiche pg_t);

#endif 