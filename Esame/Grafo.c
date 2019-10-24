#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "ST.h"

struct grafo{
    int **madj;
    int V, E;
    ST st;
};

void carica_Grafo(Grafo g, char *nome){
    FILE *fp;
    int i, ind1, ind2;
    char id1[21], id2[21];     //errore nella dichiarazione
    
    fp = fopen(nome, "r");
    if(fp == NULL)
        exit(1);
    while(fscanf(fp, "%s %s", id1, id2)>0){
        g->E++;
    }
    fclose(fp);
  
    g->st = ST_init(g->E);
    
    //codice corretto (mancante nel compito)
    fp = fopen(nome, "r");
    if(fp == NULL)
        exit(1);
    while(fscanf(fp, "%s %s", id1, id2)>0){
        ind1 = ST_insert(g->st, id1);
        ind2 = ST_insert(g->st, id2);
    }
    
    g->V = ST_size(g->st);
    
    g->madj = (int **)malloc(g->V*sizeof(int *));
    if(g->madj == NULL)
        exit(1);
    for(i=0; i<g->V; i++){
        g->madj[i] = (int *)malloc(g->V*sizeof(int));
        if(g->madj[i]==NULL)
            exit(1);
    }
    
    //codice corretto
    fp = fopen(nome, "r");
    if(fp == NULL)
        exit(1);
    while(fscanf(fp, "%s %s", id1, id2)>0){
        ind1 = ST_string_to_ind(g->st, id1);
        ind2 = ST_string_to_ind(g->st, id2);
        g->madj[ind1][ind2] = 1;
    }
    fclose(fp);

    /*
    fp = fopen(nome, "r");
    if(fp == NULL)
        exit(1);
    while(fscanf(fp, "%s %s", id1, id2)>0){
        ind1 = ST_insert(g->st, id1);
        ind2 = ST_insert(g->st, id2);
        g->madj[ind1][ind2] = 1;
    }
    fclose(fp);
    */
}

Grafo Init(){
    Grafo g = (Grafo)malloc(sizeof(*g));
    if(g==NULL)
        exit(-1);
    
    g->V = 0;
    g->E = 0;
    g->st = NULL;
    g->madj = NULL;
    return g;
}

static int Test_Kernel_A(Grafo g, int n, int *v){    //spostata sopra la funzione Test_Kernel
    int i, j;
    
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            if(i!=j){
                if(g->madj[v[i]][v[j]])
                    return 0;
            }
        }
    }
    
    //codice corretto  (mancante nel compito)
    int flag = 1, c = 0;
    for(i=0; i<g->V; i++){
        c = 0;
        flag = 1;
        for(int j=0; j<n; j++){
            if(i==v[j])
                flag = 0;
        }
        if(flag){
            for(int j=0; j<n; j++){
                if(g->madj[v[j]][i])
                    c++;
            }
            if(c==0)
                return 0;
        }
    }
    
    return 1;
}

void Test_Kernel(Grafo g, char *nome){
    FILE *fp;
    int *v, ind, n=0;    //aggiunto inizializzazione di n, asterisco a v
    char s[21];
    
    fp = fopen(nome, "r");
    
    //codice corretto
    while(fscanf(fp, "%s", s)>0){
        n++;
    }

    /*
    while(fscanf(fp, "%d", &ind)>0){
        n++;
    }
    fclose(fp);
    */
    
    fp = fopen(nome, "r");
    v = (int *)malloc(n*sizeof(int));
    for(int j=0; j<n; j++){
        fscanf(fp, "%s", s);
        v[j] = ST_string_to_ind(g->st, s);
    }
    
    if(Test_Kernel_A(g, n, v))
        printf("L'elenco forma un kernel di g\n");
    else
        printf("L'elenco non forma un kernel di g\n");
    
}

static void powerset_R(int *sol, int pos, int start, int *flag, int n, Grafo g){       //spostata sopra la funzione Max_Kernel
    int i;
    
    if(pos>=n){
        if(Test_Kernel_A(g, n, sol)){
            (*flag) = 1;
        }
        return;
    }
    
    if((*flag)==0){
        for(i=start; i<g->V; i++){
            if((*flag)==0){   //correzione
                sol[pos] = i;
                powerset_R(sol, pos+1, i+1, flag, n, g);    //aggiunta );
            }
        }
    }
}

static void print_sol(int *v, char *str, int n, Grafo g){    //spostata sopra la funzione Max_Kernel
    FILE *fp;
    int i;
    fp = fopen(str, "w");
    if(fp == NULL)
        exit(1);
    for(i=0; i<n; i++){
        fprintf(fp, "%s\n", ST_ind_to_string(g->st, v[i]));
    }
    fclose(fp);
}

int *Max_Kernel(Grafo g, char *str){
    int *sol, i, flag=0, *tmp;
    
    for(i=g->V; i>=0; i--){
        if(flag){
            tmp = malloc((i+1)*sizeof(int));
            for(int j=0; j<i+1; j++)
                tmp[j] = sol[j];
            break;
        }
        if(i!=g->V)
            free(sol);
        sol = (int *)malloc(i*sizeof(int));
        if(sol == NULL)
            exit(1);
        powerset_R(sol, 0, 0, &flag, i, g);
    }
    free(sol);
    print_sol(tmp, str, i+1, g);
    return tmp;
}

void libera_Grafo(Grafo g){
    int i;
    for(i=0; i<g->V; i++)
        free(g->madj[i]);
    free(g->madj);
    libera_ST(g->st);
    free(g);
}

static void cammini_sempliciR(Grafo g, int *k, int v, int *mark, int k_dim, int /***/dim /*correzione*/, int l, int *maxl, int *bdim ){              //spostata sopra la funzione cammini_semplici
    int i, j;    //aggiunta la dichiarazione di i e j
    
    //codice corretto
    l++;
    for(j=0; j<k_dim; j++){
        if(v == k[j])
            dim++;
    }
    for(i=0; i<g->V; i++){
        if(g->madj[v][i]){
            if(mark[i]==0){
                mark[i] = 1;
                cammini_sempliciR(g, k, i, mark, k_dim, dim, l, maxl, bdim);
                mark[i] = 0;
            }
        }
    }
    if(dim>(*bdim)){
        (*bdim)=dim;
        (*maxl)=l;
    }
    
    /*
    for(i=0; i<g->V; i++){
        if(mark[i]==0){
            for(j=0; j<k_dim; j++){
                if(i==k[j]){
                    (*dim)++;
                }
            }
            cammini_sempliciR(g, k, i, mark, k_dim, dim);
        }
    }
    */
}

void cammini_semplici(Grafo g, int *k){
    int b_dim = 0, dim, *mark;           //aggiunta la dichiarazione di mark
    int k_dim = sizeof(k)/sizeof(int);
    int maxl=0;     //correzione
    
    mark = calloc(g->V, sizeof(int));
    
    //codice corretto
    for(int i=0; i<g->V; i++){
        cammini_sempliciR(g, k, i, mark, k_dim, 0, 0, &maxl, &b_dim);
        for(int j=0; j<g->V; j++)
            mark[j] = 0;
    }
    printf("Cammino semplice con più vertici nel kernel è lungo %d\n", maxl);
    
    /*
    for(int i=0; i<g->V; i++){
        cammini_sempliciR(g, k, i, mark, k_dim, &dim);      //aggiunto il passaggio di k_dim
        if(dim>b_dim)
            b_dim = dim;
        for(int j=0; j<g->V; j++)
            mark[j] = 0;
    }
    printf("Cammino semplice con più vertici nel kernel è lungo %d\n", b_dim);
    */
    free(mark);
}