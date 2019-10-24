#include "personaggio.h"

void leggi_caratteristiche(FILE *fp, caratteristiche *pg_t, int *n){
    char nome[MAX], codice[MAX], classe[MAX];
    int hp, mp, atk, def, mag, spr;
    
    fscanf(fp, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr);
    (*n)++;
    strcpy(pg_t->nome, nome);
    strcpy(pg_t->codice, codice);
    strcpy(pg_t->classe, classe);
    pg_t->stat.hp=hp;
    pg_t->stat.mp=mp;
    pg_t->stat.atk=atk;
    pg_t->stat.def=def;
    pg_t->stat.mag=mag;
    pg_t->stat.spr=spr;
}

void carica_caratt_pg(caratteristiche *pg_t){
    printf("Inserire dati nuovo personaggio\n\n");
    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>: ");
    scanf("%s %s %s %d %d %d %d %d %d", pg_t->codice, pg_t->nome, pg_t->classe, &(pg_t->stat.hp), &(pg_t->stat.mp), &(pg_t->stat.atk), &(pg_t->stat.def), &(pg_t->stat.mag), &(pg_t->stat.spr));
}

void Init_vett_equip(caratteristiche *pg_t){
    void Init_vettEq(pg->tabEquip);
}

void alloca_equip(caratteristiche pg_t){
    alloca_tabEquip(&(pg_t.tabEquip));
}

int check_equip(caratteristiche p){
    return check_full_equip(p.tabEquip);
}

int selezione_equip(caratteristiche p){
    return sleziona_cella_equip(p.tabEquip);
}

void assegna_obj(caratteristiche *p, int ind_eq, int ind_obj){
    assegna_obj_inv(p->tabEquip, ind_eq, ind_obj);
}

int rimozione_oggetto(caratteristiche *p, char *oggetto, inv_t *inv){
    return rimozione_oggetto_equipe(p->tabEquip, oggetto, inv);
}

int confronta_codice(caratteristiche p, char *cod){
    if(!strcmp(p.codice, cod)){
        return 1;
    }
    return 0;
}

void print_personaggio(caratteristiche pg_t, inv_t *inv){
    printf("Personaggio:\n %s %s %s %d %d %d %d %d %d\n", pg_t.codice, pg_t.nome, pg_t.classe, pg_t.stat.hp, pg_t.stat.mp, pg_t.stat.atk, pg_t.stat.def, pg_t.stat.mag, pg_t.stat.spr);
    print_equipe(pg_t.tabEquip, inv);
}

void calcola_stat(caratteristiche pg_t, inv_t *inv){
    int i, hp, mp, atk, def, mag, spr;
    
    hp=pg_t.stat.hp;
    mp=pg_t.stat.mp;
    atk=pg_t.stat.atk;
    def=pg_t.stat.def;
    mag=pg_t.stat.mag;
    spr=pg_t.stat.spr;
    
    calcola_statistiche(&hp, &mp, &atk, &def, &mag, spr, pg_t.tabEquip);
    if(hp<1)
        hp=1;
    if(mp<1)
        mp=1;
    if(atk<1)
        atk=1;
    if(def<1)
        def=1;
    if(def<1) 
        def=1;
    if(spr<1)
        spr=1;
    
    printf("%s %s %d %d %d %d %d %d\n", pg_t.codice, pg_t.nome, hp, mp, atk, def, mag, spr);

    
}

void libera_equip(caratteristiche pg_t){
    libera_equipment(pg_t.tabEquip);
}