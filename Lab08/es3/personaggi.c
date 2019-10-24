#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "personaggi.h"

void alloca_head(tabPg_t **h){
    (*h) = (tabPg_t *)malloc(sizeof(tabPg_t));
    (*h)->nPg=0;
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

void libera_nodo(link nodo){
    free(nodo->pg_t.tabEquip->vettEq);
    free(nodo->pg_t.tabEquip);
    free(nodo);
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
            (tmp->next)=NULL;
            x->next = tmp;
            head->tailPg=tmp;
            x = x->next;
        }
    }
    
    fclose(fp);
    return head;
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
                //x->next=NULL;
            }
            libera_nodo(x);
            break;
        }
        p=x;
        x=x->next;
    }
    return head;
}

void agg_rim_oggetto(command_t cmd, tabPg_t *head, tabInv *inventario){
    char codice[MAX], oggetto[MAX];
    link x=head->headPg;
    int i, j;
    
    if(head->headPg==NULL){                     //controllo che la lista non sia vuota
        printf("Errore - lista vuota.\n");
        return;
    }
    
    printf("Inserire codice personaggio e nome oggetto: ");
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
        for(j=0; strcmp(inventario->vettInv[j].nome, oggetto) && j<inventario->nInv; j++);      //selezionde dell'oggetto da caricare nell'inventario
        
        if(j==inventario->nInv){
            printf("Errore - Oggetto non presente nell' inventario\n");
            return;
        }
        
        x->pg_t.tabEquip->vettEq[i] = &(inventario->vettInv[j]);            //assegnazione dell'oggetto all'inventario del personaggio
        x->pg_t.tabEquip->inUso++;
        
        //printf("%s\n", x->pg_t.tabEquip->vettEq[i]->nome );
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
        x->pg_t.tabEquip->inUso--;
        
/*
        for(int k=0; x->pg_t.tabEquip->vettEq[k]!=NULL; k++)
            printf("%s\n", x->pg_t.tabEquip->vettEq[k]->nome );
*/
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
    
    printf("%s %s %d %d %d %d %d %d\n", x->pg_t.codice, x->pg_t.nome, hp, mp, def, mag, spr);
}

link ricerca_pg(tabPg_t *head){
    link x;
    char cod[MAX];
    
    if(head->headPg==NULL){
        printf("Errore - lista vuota.\n");
        exit(1);
    }
    
    printf("Inerisci il codice personaggio: ");
    scanf("%s", cod);
    
    for(x=head->headPg; x!=NULL; x=x->next){
        if(!strcmp(x->pg_t.codice, cod))
            break;
    }
   
    return x;
}

void stampa_personaggio(tabPg_t *head){
    link x;
    int i=0;
    char cod[MAX];
    
    if(head->headPg==NULL){
        printf("Errore - lista vuota.\n");
        exit(1);
    }
    
    printf("Inserire il codice personaggio: ");
    scanf("%s", cod);
    
    for(x=head->headPg; x!=NULL; x=x->next){
        if(!strcmp(x->pg_t.codice, cod))
            break;
    }
    
    if(x!=NULL){
        printf("Personaggio:\n %s %s %s %d %d %d %d %d %d\n", x->pg_t.codice, x->pg_t.nome, x->pg_t.classe, x->pg_t.stat.hp, x->pg_t.stat.mp, x->pg_t.stat.atk, x->pg_t.stat.def, x->pg_t.stat.mag, x->pg_t.stat.spr);
        if(x->pg_t.tabEquip->inUso!=0){
            printf("Inventario:\n");
            for(i=0; i<x->pg_t.tabEquip->inUso; i++)
                printf(" %s\n", x->pg_t.tabEquip->vettEq[i]->nome);
        }
        else{
            printf("Inventario di %s vuoto.\n", x->pg_t.nome);
        }
    }
    else{
        printf("Personaggio non trovato.\n");
    }
}

void libera_lista(tabPg_t *head){
    int i;
    link x, tmp;
    x=head->headPg;
    for(i=0; i<head->nPg; i++){
        tmp=x;
        x=x->next;
        libera_equipment(tmp->pg_t.tabEquip->vettEq);
        libera_nodo(tmp);
    }
    free(head);
}