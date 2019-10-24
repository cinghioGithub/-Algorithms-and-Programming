#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "Tabella.h"

#define MAX 31

struct node {
    int v;
    int wt;
    link next;
};

struct grafo{
    int V;
    int E;
    int **adj;
    Tab tab;
    link *ladj;
};

Grafo grafo_init(){
    Grafo g;
    
    g = (Grafo)malloc(sizeof(*g));              //allocazione della struttura grafo
    if(g==NULL){
        printf("Errore allocazione grafo.\n");
        exit(-1);
    }
    g->V=0;
    g->E=0;
    g->ladj=NULL;
    
    return g;
}

link new_node(){
    link m;
    
    m = (link)malloc(sizeof(*m));
    
    return m;
}

void free_lista(link *ladj, int n){
    int i;
    link x, tmp;
    
    for(i=0; i<n; i++){
        x=ladj[i]->next;
        while(x!=NULL){
            tmp=x;
            x=x->next;
            free(tmp);
        }
    }
    
    free(ladj);
}

int **adj_init(int v){
    int i;
    int **mat;
    
    mat = (int **)malloc((2*v)*sizeof(int *));          //allocazione della matrice delle adiacenze
    
    for(i=0; i<2*v; i++){
        mat[i] = (int *)calloc(2*v, sizeof(int));
    }
    return mat;
}

void carica_grafo(Grafo g){
    FILE *fp;
    char el1[MAX], net1[MAX], el2[MAX], net2[MAX];
    int flusso;
    int ind1, ind2, n_a=0;
    
    fp = fopen("grafo.txt", "r");
    if(fp==NULL){
        printf("Errore apertura file.\n");
        exit(-1);
    }
    
    while(fscanf(fp, "%s %s %s %s %d", el1, net1, el2, net2, &flusso)==5){    //prima lettura del file per il conteggio degli archi
        n_a++; 
    }
    fclose(fp);
    
    g->E = n_a;                 //numero di archi
    g->adj = adj_init(n_a);             //inizializzazione della metrice delle adiacenze
    g->tab = tabella_init(n_a);         //inizializzazione della tabella di simboli
    
    fp = fopen("grafo.txt", "r");
    if(fp==NULL){
        printf("Errore apertura file.\n");
        exit(-1);
    }
    
    while(fscanf(fp, "%s %s %s %s %d", el1, net1, el2, net2, &flusso)==5){    //seconda lettura del file per il caricamento del grafo
        ind1 = ins_tab(g->tab, el1, &g->V);
        ind2 = ins_tab(g->tab, el2, &g->V);
        g->adj[ind1][ind2] = flusso;
        g->adj[ind2][ind1] = flusso;
    }
    
    fclose(fp);
}

void print_grafo(Grafo g){
    int i, j;
    
    for(i=0; i<g->V; i++){
        for(j=i; j<g->V; j++){
            if((g->adj[i][j])!=0){
                printf("%s %s\n", ind_to_string(g->tab, i), ind_to_string(g->tab, j));
            }
        }
    }
}

void genera_lista(Grafo g){
    int i, j, c=0;
    link tmp;
    
    g->ladj = (link *)malloc(g->V*sizeof(link));    //allocazione vettore di liste
    for(i=0; i<g->V; i++){                          //allocazione dei nodi sentinella
        g->ladj[i]=malloc(sizeof(*(g->ladj[i])));
        g->ladj[i]->v = -1;
        g->ladj[i]->wt = -1;
        g->ladj[i]->next = NULL;
    }
    
    for(i=0; i<g->V; i++){              //scansione della matrice delle adiacenze
        for(j=0; j<g->V; j++){
            if(g->adj[i][j]!=0){
                for(tmp = g->ladj[i]; tmp->next!=NULL; tmp = tmp->next);        //selezione dell'ultimo nodo della lista del vertice slezionato (i)
                tmp->next = new_node();
                tmp->next->v = j;
                tmp->next->wt = g->adj[i][j];
                tmp->next->next = NULL;
            }
        }        
    }
}

void print_elenco(Grafo g){
    int *v, i, j, *sup;
    int n, pos=0;
    
    v = (int *)malloc(g->V*sizeof(int));    //allocazione del vettore di indici (per ordinamento dei vertici)
    sup = (int *)malloc(g->V*sizeof(int));  //allocazionde del vettore per memorizzare i vertici adiacenti a quello selezionato
    
    for(i=0; i<g->V; i++)         //inizializzazione del vettore di indici
        v[i]=i;
    
    sort_vertici(v, g->tab, g->V);        //ordinamento dei vertici
    
    for(i=0; i<g->V; i++){
        pos=0;
        printf("%s:\n", ind_to_string(g->tab, v[i]));      //stampa del vertice selezionato
        for(j=0; j<g->V; j++){
            if(g->adj[v[i]][j]!=0){
                sup[pos]=j;
                pos++;
            }
        }
        sort_vertici(sup, g->tab, pos);
        
        for(j=0; j<pos; j++){                       //stampa dei vertici adiacenti a quello selezionato
            printf("\t%s\n", ind_to_string(g->tab, sup[j]));
        }
    }
}

void adiacenti(Grafo g){
    int v1, v2, v3;
    char n1[MAX], n2[MAX], n3[MAX];
    
    printf("Inserire tre vertici [v1 v2 v3]: ");
    scanf("%s %s %s", n1, n2, n3);
    
    v1 = string_to_ind(g->tab, n1);             //ricerca dell'indice corrispondente ad ogni vertice inserito
    v2 = string_to_ind(g->tab, n2);
    v3 = string_to_ind(g->tab, n3);
    
    if(v1==-1 || v2==-1 || v3==-1){                 //controllo che i nomi inseriti siano corretti
        printf("Errore - nomi vertici non esistenti.\n");
        return;
    }
    
    if(g->adj[v1][v2]!=0 && g->adj[v2][v3]!=0 && g->adj[v3][v1]!=0){      //verifica di adiacenze con la matrice
        printf("vero\n");
    }
    else{
        printf("falso\n");
    }
}

void adiacenti_lista(Grafo g){      //verifica delle adiacenze con la lista
    int v1, v2, v3;
    int flag1=0, flag2=0, flag3=0;
    link x;
    char n1[MAX], n2[MAX], n3[MAX];
    
    printf("Inserire tre vertici [v1 v2 v3]: ");
    scanf("%s %s %s", n1, n2, n3);
    
    v1 = string_to_ind(g->tab, n1);             //ricerca dell'indice corrispondente ad ogni vertice inserito
    v2 = string_to_ind(g->tab, n2);
    v3 = string_to_ind(g->tab, n3);
    
    if(v1==-1 || v2==-1 || v3==-1){             //controllo che i nomi inseriti siano corretti
        printf("Errore - nomi vertici non esistenti.\n");
        return;
    }
    
    for(x=g->ladj[v1]; x!=NULL; x=x->next){
        if(x->v==v2){
            flag1=1;
        }
    }
    
    for(x=g->ladj[v2]; x!=NULL; x=x->next){
        if(x->v==v3){
            flag2=1;
        }
    }
    
    for(x=g->ladj[v3]; x!=NULL; x=x->next){
        if(x->v==v1){
            flag3=1;
        }
    }
    
    if(flag1 && flag2 && flag3){
        printf("vero\n");
    }
    else{
        printf("falso\n");
    }
}

void free_grafo(Grafo g){
    int i;
    
    for(i=0; i<g->V; i++){
        free(g->adj[i]);
    }
    free(g->adj);
    
    if(g->ladj!=NULL){
        free_lista(g->ladj, g->V);
    }
    
    free(g);
}

void print_tabella_G(Grafo g){
    print_tabella(g->tab);
}