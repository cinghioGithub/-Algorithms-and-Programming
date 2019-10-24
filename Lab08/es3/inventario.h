#ifndef _INVENTARIO
#define _INVENTARIO

#define N_INV 8

#ifndef MAX
#define MAX 50
#endif

typedef struct statistiche_inv{
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

typedef struct tab_inv{
    int nInv;
    inv_t *vettInv;
}tabInv;

void carica_oggetti(inv_t **invent,tabInv **inventario);
void ricerca_oggetto(tabInv *tab);
void stampa_oggetto(tabInv *tab);
void libera_inventario(tabInv *tab);
void libera_equipment(inv_t *p);

#endif

