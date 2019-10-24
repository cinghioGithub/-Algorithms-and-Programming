#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define N 7
#define N_C 9
#define STAT 6
#define N_INV 8

typedef enum {
    c_carica_lista, c_carica_oggetti, c_nuovo_perso, c_aggiungi, c_rimuovi, c_cancella, c_statistiche,c_help,  fine
}command_t;

typedef struct statistiche{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct inv{
    char nome[MAX];
    char tipo[MAX];
    stat_t stat;
}inv_t;

typedef struct equip{
    int inUso;
    inv_t *vettEq[N_INV];
}tabEquipment;

typedef struct tab_inv{
    int nInv;
    inv_t *vettInv;
}tabInv;

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
};

typedef struct node{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

//funzioni
tabPg_t *carica_lista(tabPg_t *head);
void carica_oggetti(inv_t **invent,int *num_inv);
tabPg_t *nuovo_personaggio(tabPg_t *head);
tabPg_t *elimina_personaggio(tabPg_t *head);
void agg_rim_oggetto(command_t cmd, tabPg_t *head, tabInv inventario);
void libera_nodo(link nodo);
void statistiche(tabPg_t *head);
void menu(char *tab[]);
command_t gestione_cmd(char *cmd, char *tab[]);
link new_node();
void my_free(tabPg_t *head, tabInv inventario);

//main
int main() {
    char *tab_cmd[N_C]={"lista", "inventario","nuovo", "aggiungi", "rimuovi","cancella","statistiche", "help","fine"};
    tabPg_t *head;
    link x;
    inv_t *invent;
    tabInv inventario;
    int num_inv, flag=1;
    char command[MAX];
    command_t cmd;
    
    head = (tabPg_t *)malloc(sizeof(tabPg_t));
    head->nPg=0;   
    
    do{
        printf("Inserisci comando (help - per lista comandi): ");
        scanf("%s", command);
        
        cmd = gestione_cmd(command, tab_cmd);
        
        switch(cmd){
            case c_carica_lista:
                head = carica_lista(head);
                break;
            case c_carica_oggetti:
                carica_oggetti(&invent, &num_inv);
                inventario.vettInv=invent;
                inventario.nInv=num_inv;
                break;
            case c_nuovo_perso:
                head = nuovo_personaggio(head);
                break;
            case c_aggiungi:
                agg_rim_oggetto(cmd, head, inventario);
                break;
            case c_rimuovi:
                agg_rim_oggetto(cmd, head, inventario);
                break;
            case c_cancella:
                head=elimina_personaggio(head);   
                break;
            case c_statistiche:
                statistiche(head);
                break;
            case c_help:
                menu(tab_cmd);
                break;
            case fine:
                flag=0;
                break;
            case -1:
                printf("Errore - comando non esistente.\n");
                break;
            default:
                break;
        }
    }while(flag);
    
    my_free(head, inventario);    
    
    return 0;
}

command_t gestione_cmd(char *cmd,  char *tab[] ){
    int i;
    command_t c=-1;
    for(i=0; i<N_C; i++){
        if(!strcmp(cmd, tab[i])){
            c = i;
            break;
        }
    }
    return c;
}

link new_node(){
    link node;
    node = (link)malloc(sizeof(nodo_pg));
    node->pg_t.tabEquip = (tabEquipment *)malloc(sizeof(tabEquipment));
    if(node==NULL){
        printf("Allocazione node fallita.\n");
        exit(1);
    }
    node->pg_t.tabEquip->inUso=0;
    return node;
}

tabPg_t *carica_lista(tabPg_t *head){
    FILE *fp;
    link tmp, x;
    char nome[MAX], codice[MAX], classe[MAX];
    int hp, mp, atk, def, mag, spr;
    
    fp=fopen("pg.txt", "r");
    if(fp==NULL){
        printf("Errore apertura pg.txt\n");
        exit(1);
    }
    
    x = head->headPg;
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", codice, nome, classe, &hp, &mp, &atk, &def, &mag, &spr)>0){
        (head->nPg)++;
        tmp = new_node();
        strcpy(tmp->pg_t.nome, nome);
        strcpy(tmp->pg_t.codice, codice);
        strcpy(tmp->pg_t.classe, classe);
        tmp->pg_t.stat.hp=hp;
        tmp->pg_t.stat.mp=mp;
        tmp->pg_t.stat.atk=atk;
        tmp->pg_t.stat.def=def;
        tmp->pg_t.stat.mag=mag;
        tmp->pg_t.stat.spr=spr;
        
        if((head->nPg)==1){    //gestisco il caricamento del primo nodo
            head->headPg=tmp;
            x=tmp;
        }
        else{
            x->next = tmp;
            head->tailPg=tmp;
            (tmp->next)=NULL;
            x = x->next;
        }
    }
    
    fclose(fp);
    return head;
}

void carica_oggetti(inv_t **invent,int *num_inv){
    FILE *fp;
    int i;
    
    fp = fopen("inventario.txt", "r");
    if(fp==NULL){
        printf("Errore apertura inventario.txt\n");
        exit(1);
    }
    
    fscanf(fp, "%d", num_inv);
    (*invent)=(inv_t *)malloc((*num_inv)*sizeof(inv_t));
    if((*invent)==NULL){
        printf("Errore allocazione inventario.\n");
        exit(1);
    }
    
    for(i=0; i<(*num_inv); i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", (*invent)[i].nome, (*invent)[i].tipo, &(*invent)[i].stat.hp, &(*invent)[i].stat.mp, &(*invent)[i].stat.atk, &(*invent)[i].stat.def, &(*invent)[i].stat.mag, &(*invent)[i].stat.spr);
    }
    
    fclose(fp);
}

tabPg_t *nuovo_personaggio(tabPg_t *head){
    link tmp;
    tmp = new_node();
    
    printf("Inserire dati nuovo personaggio\n\n");
    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>: ");
    scanf("%s %s %s %d %d %d %d %d %d", tmp->pg_t.codice, tmp->pg_t.nome, tmp->pg_t.classe, &(tmp->pg_t.stat.hp), &(tmp->pg_t.stat.mp), &(tmp->pg_t.stat.atk), &(tmp->pg_t.stat.def), &(tmp->pg_t.stat.mag), &(tmp->pg_t.stat.spr));
    
    if(head->headPg==NULL){
        head->headPg=tmp;
    }
    else{
        head->tailPg->next = tmp;
        tmp->next=NULL;
        head->tailPg=tmp;
    }
    
    (head->nPg)++;
    return head;
}

void libera_nodo(link nodo){
    free(nodo->pg_t.tabEquip->vettEq);
    free(nodo->pg_t.tabEquip);
    free(nodo);
}

tabPg_t *elimina_personaggio(tabPg_t *head){
    link x=head->headPg, p=NULL;
    char cod[MAX];
    int i;
    if(x==NULL){
        printf("Errore - lista vuota.\n");
        return head;
    }
    
    printf("Inserire codice personaggio: ");
    scanf("%s", cod);
    
    for(i=0; i<head->nPg; i++){
        if(!strcmp(x->pg_t.codice, cod)){
            if(p==NULL){
                head->headPg=x->next;
            }
            else{
                p->next=x->next;
            }
            libera_nodo(x);
            break;
        }
        p=x;
        x=x->next;
    }
    return head;
}

void agg_rim_oggetto(command_t cmd, tabPg_t *head, tabInv inventario){
    char codice[MAX], oggetto[MAX];
    link x=head->headPg;
    int i, j;
    
    if(head->headPg==NULL){                     //controllo che la lista non sia vuota
        printf("Errore - lista vuota.\n");
        return;
    }
    
    printf("Inerire codice personaggio e nome oggetto: ");
    scanf("%s %s", codice, oggetto);
    
    for(i=0; i<head->nPg ; i++){
        if(!strcmp(x->pg_t.codice, codice)){
            break;
        }
        x=x->next;
    }
        
    if(i==head->nPg){
        printf("Errore - codice personaggio non trovato.\n");
        return;
    }
    if(x->pg_t.tabEquip->inUso==0){
        for(j=0; j<N_INV; j++){                         //inizializzazione dei puntatori a NULL
            x->pg_t.tabEquip->vettEq[j]=NULL;
        }
    }
    if(x->pg_t.tabEquip->inUso==N_INV){
        printf("Errore - inventario pieno.\n");
        return;
    }
    if(cmd==c_aggiungi){
        for(i=0; x->pg_t.tabEquip->vettEq[i]!=NULL; i++);    //selezione del primo puntatore diverso da NULL
        for(j=0; strcmp(inventario.vettInv[j].nome, oggetto) && j<inventario.nInv; j++);      //selezionde dell'oggetto da caricare nell'inventario
        
        if(j==inventario.nInv){
            printf("Errore - Oggetto non presente nell' inventario\n");
            return;
        }
        
        x->pg_t.tabEquip->vettEq[i] = &(inventario.vettInv[j]);            //assegnazione dell'oggetto all'inventario del personaggio
        x->pg_t.tabEquip->inUso++;
    }
    else{
        for(i=0; i<x->pg_t.tabEquip->inUso; i++){
            if(!strcmp(x->pg_t.tabEquip->vettEq[i]->nome, oggetto)){
                //printf("%s\n",x->pg_t.tabEquip->vettEq[i]->nome );
                break;
            }
        }
        if(i==x->pg_t.tabEquip->inUso){
            printf("Errore - oggetto non trovato nell'inventario del personaggio.\n");
            return;
        }
        i++;
        while(x->pg_t.tabEquip->vettEq[i]!=NULL){
            x->pg_t.tabEquip->vettEq[i-1]=x->pg_t.tabEquip->vettEq[i];      //copertura della cella in cui è stato eliminato l'oggetto
            i++;
        }
        x->pg_t.tabEquip->vettEq[i-1]=NULL;         //assegnazione di NULL all'ultimo elemento dell'inventario diventato un doppione del penultimo
    }
}

void statistiche(tabPg_t *head){
    link x=head->headPg;
    char cod[MAX];
    int i;
    int hp, mp, atk, def, mag, spr;
    
    if(x==NULL){
        printf("Errore - lista vuota.\n");
        return;
    }
    
    printf("Inserire codice personaggio: ");
    scanf("%s", cod);
    
    for(i=0; i<head->nPg ; i++){
        if(!strcmp(x->pg_t.codice, cod)){
            break;
        }
        x=x->next;
    }
    
    if(i==head->nPg){
        printf("Errore - personaggio non presente nella lista.\n");
        return;
    }
    
    for(i=0; i<x->pg_t.tabEquip->inUso; i++){
        hp=x->pg_t.stat.hp + x->pg_t.tabEquip->vettEq[i]->stat.hp;
        mp=x->pg_t.stat.mp + x->pg_t.tabEquip->vettEq[i]->stat.mp;
        atk=x->pg_t.stat.atk + x->pg_t.tabEquip->vettEq[i]->stat.atk;
        def=x->pg_t.stat.def + x->pg_t.tabEquip->vettEq[i]->stat.def;
        mag=x->pg_t.stat.mag + x->pg_t.tabEquip->vettEq[i]->stat.mag;
        spr=x->pg_t.stat.spr + x->pg_t.tabEquip->vettEq[i]->stat.spr;
    }
    
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
    
    printf("%s %s %d %d %d %d %d %d\n", x->pg_t.codice, x->pg_t.nome, hp, mp, atk, def, mag, spr);
}

void menu(char *tab[]){
    int i=0;
    for(i=0; i<N_C; i++){
        switch(i){
            case c_carica_lista:
                printf("%s -> Carica la lista da file.\n", tab[i]);
                break;
            case c_carica_oggetti:
                printf("%s -> Carica l'inventario da file.\n", tab[i]);
                break;
            case c_nuovo_perso:
                printf("%s -> Permette di aggiungere un nuovo personaggio alla lista.\n", tab[i]);
                break;
            case c_aggiungi:
                printf("%s -> Aggiunge un oggetto dell'inventario ad un personaggio.\n", tab[i]);
                break;
            case c_rimuovi:
                printf("%s -> Rimuove un oggetto dall'inventario di un personaggio.\n", tab[i]);
                break;
            case c_cancella:
                printf("%s -> Cancella un personaggio dalla lista.\n", tab[i]);
                break;
            case c_statistiche:
                printf("%s -> Stampa le statistiche di un personaggio [codice] [nome] [classe] [hp] [mp] [atk] [def] [mag] [spr].\n", tab[i]);
                break;
            case c_help:
                printf("%s -> Stampa il menù dei comandi.\n", tab[i]);
                break;
            case fine:
                printf("%s -> Termina il programma.\n", tab[i]);
                break;
            default:
                break;
        }
    }
}

void my_free(tabPg_t *head, tabInv inventario){
    int i;
    link tmp, x;
    x=head->headPg;
    for(i=0; i<head->nPg; i++){
        tmp=x;
        x=x->next;
        libera_nodo(tmp);
    }
    free(head);
    free(inventario.vettInv);
}