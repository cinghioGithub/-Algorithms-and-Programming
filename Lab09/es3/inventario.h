#ifndef _INEVANTARIO
#define _INEVANTARIO

#include <stdlib.h>
#include <stdio.h>

#define MAX 50
#define N 7

typedef struct statistiche{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat;

typedef struct inv{
    char nome[MAX];
    char tipo[MAX];
    stat stat;
}inv_t;

inv_t *alloca_inventario(int n);
void leggi_oggetti(FILE *fp, inv_t *invent, int n);
int sel_obj_vettInv(inv_t *inv, int n, char *oggetto);
int check_oggetto(int i, char *oggetto, inv_t *inv);
void print_tool(inv_t inv);
int _hp(int i, inv_t *inv);
int _mp(int i, inv_t *inv);
int _atk(int i, inv_t *inv);
int _def(int i, inv_t *inv);
int _mag(int i, inv_t *inv);
int _spr(int i, inv_t *inv);
void libera_inv(inv_t *inv);

#endif 

