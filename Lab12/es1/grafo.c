#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "ST.h"

struct grafo{
    int **mat;
    int V, E;
    ST st;
    Edge *edge;
};

Grafo init(Grafo g){
    g = (Grafo)malloc(sizeof(*g));
    if(g==NULL){
        printf("Errore allocazione grafo.\n");
        exit(-1);
    }
    
    g->mat = NULL;
    g->edge = NULL;
    g->E = 0;
    g->V = 0;
    
    return g;
}

void free_grafo(Grafo g){
    int i;
    
    for(i=0; i<g->V; i++)
        free(g->mat[i]);
    free(g->mat);
    
    libera_ST(g->st);
    
    free(g->edge);
    free(g);
}

void carica_grafo(Grafo g){
    FILE *fp;
    int i, w, n;
    char str[MAX], str1[MAX];
    
    fp = fopen("grafo.txt", "r");
    if(fp == NULL){
        printf("Errore apertura file.\n");
        exit(-1);
    }
    
    fscanf(fp, "%d", &n);
    
    for(i=0; i<n; i++){
        fscanf(fp, "%s", str);
    }
    while(fscanf(fp, "%s %s %d", str, str1, &w)>0){
        g->E++;
    }
    fclose(fp);
    
    fp = fopen("grafo.txt", "r");
    if(fp == NULL){
        printf("Errore apertura file.\n");
        exit(-1);
    }
    g->V = n;
    g->edge = (Edge *)malloc(g->E*sizeof(Edge));
    g->mat = (int **)malloc(n*sizeof(int *));
    for(int i=0; i<n; i++){
        g->mat[i] = (int *)calloc(n, sizeof(int));
    }
    g->st = setNull();
    
    fscanf(fp, "%d", &n);
    for(i=0; i<n; i++){
        fscanf(fp, "%s", str);
        g->st = st_insert(g->st, str, i);
    }
    
    for(i=0; i<g->E; i++){
        fscanf(fp, "%s %s %d", str, str1, &w);
        g->mat[string_to_ind(g->st, str)][string_to_ind(g->st, str1)] = w;
        g->edge[i].a = string_to_ind(g->st, str);
        g->edge[i].b = string_to_ind(g->st, str1);
        g->edge[i].w = w;
    }
    fclose(fp);
}

static void DFS(int **mat, int V, int v, int *pre, int *post, int *time, int *res){
    int i;
    
    if(pre[v]==0){
        (*time)++;
        pre[v] = (*time);
        for(i=0; i<V; i++){
            if(mat[v][i]!=0){
                if(pre[i]!=0 && post[i] == 0){
                    (*res) = 0;
                    return;
                }
                DFS(mat, V, i, pre, post, time, res);  
                if((*res)==0){
                    return;
                }
            }
        }
        (*time)++;
        post[v] = (*time);
    }
}

static int check_sol(Grafo g, Edge *sol, int n, int **mat){
    int i, j;
    int *pre, *post, time=0, res = 1;
    
    pre = calloc(g->V, sizeof(int));
    post = calloc(g->V, sizeof(int));
    for(i=0; i<n; i++){                         //aggiornamento della matrice utilizzando la soluzione appena trovata
        mat[sol[i].a][sol[i].b] = 0;
    }
    
    for(j=0; j<g->V; j++){
        if(pre[j]==0){
            DFS(mat, g->V, j, pre, post, &time, &res);
        }
    }
    free(pre);
    free(post);
    
    for(i=0; i<n; i++){
        mat[sol[i].a][sol[i].b] = g->mat[sol[i].a][sol[i].b];       //ripristino della matrice test
    }
    
    if(res){
        return 1;
    }
    return 0;
}

static void power_setR(int **mat, Grafo g, Edge *sol, int pos, int start, int n, int tot, Edge ***vet, int *dim, int *ind, int *flag){
    int i;
    
    if(pos>=n){
        if(check_sol(g, sol, n, mat)){
            (*flag)=n;
            if((*dim)<=(*ind)){                                         //salvataggio della soluzione valida
                (*vet) = realloc((*vet), 2*(*dim)*sizeof(Edge *));
                (*dim) = 2*(*dim);
                for(int j=(*ind); j<(*dim); j++)
                    (*vet)[j] = malloc(tot*sizeof(Edge));
            }
            for(int j=0; j<n; j++){
                (*vet)[(*ind)][j] = sol[j];
            }
            (*ind)++;
        }
        return;
    }
    
    for(i=start; i<tot; i++){
        sol[pos] = g->edge[i];
        power_setR(mat, g, sol, pos+1, start+1, n, tot, vet, dim, ind, flag);
    }
}

void power_set(Grafo g){
    Edge *sol, **vet;
    int i, j, **mat, dim=1, ind=0, flag = INT_MAX;
    int max=0, w_temp=0, indice; 
    
    vet = malloc(sizeof(Edge));                                     //allocazione strttura dati per il salvataggio delle soluzioni
    vet[0] = malloc(g->E*sizeof(Edge));
    
    mat = (int **)malloc(g->V*sizeof(int *));
    for(i=0; i<g->V; i++){
        mat[i] = (int *)calloc(g->V, sizeof(int));
        for(int j=0; j<g->V; j++){
            mat[i][j] = g->mat[i][j];
        }
    }
    
    for(i=0; i<g->E; i++){
        if(i>flag){
            break;
        }
        sol = (Edge *)malloc(i*sizeof(Edge));
        power_setR(mat, g, sol, 0, 0, i, g->E, &vet, &dim, &ind, &flag); 
        free(sol);
    }
    
    for(i=0; i<g->V; i++){
        free(mat[i]);
    }
    free(mat);
    
    //calcolo dell'insieme a peso massimo e costruzione del DAG
    for(i=0; i<ind; i++){
        w_temp = 0;
        for(j=0; j<flag; j++){
            w_temp += vet[i][j].w;
        }
        if(w_temp>max){
            max = w_temp;
            indice = i;
        }
    }
    
    for(i=0; i<flag; i++){                  //costruzione del DAG
        g->mat[vet[indice][i].a][vet[indice][i].b] = 0;
    }
    
    //free
    for(i=0; i<dim; i++)
        free(vet[i]);
    free(vet);
}

void max_dist(Grafo g){
    int *pre, *post, i, j, time, res;
    int *d, *sol, v, y, ind, start ,max, vertice;
    int flag1 = 1, flag2 = 1;
    
    pre = (int *)calloc(g->V, sizeof(int));
    post = (int *)calloc(g->V, sizeof(int));
    sol = (int *)calloc(g->V, sizeof(int));
    d = (int *)calloc(g->V, sizeof(int));
    
    for(i=0; i<g->V; i++){          //DFS con partenza da ogni vertice
        time = 0;
        start = i;
        for(int k=0; k<g->V; k++){          //azzeramento dei vettori per ogni DFS
            pre[k] = 0;
            post[k] = 0;
            sol[k] = 0;
            d[k] = 0;
        }
        for(j=0; j<g->V; j++){   //DFS
            if(pre[start]==0){
                DFS(g->mat, g->V, start, pre, post, &time, &res);
            }
            start = (start + 1) % g->V;
        }
        for(y=0; y<g->V; y++){              //ordinamento topologico
            max = 0;
            ind = y;
            for(v=0; v<g->V; v++){
                if(post[v]>max){
                    max = post[v];
                    ind = v;
                }
            }
            sol[y] = ind;
            post[ind] = 0;
        }
        
        for(v=0; v<g->V; v++){              //selezione del vertice da cui volgio calcolare le distanze massime
            if(sol[v]==i){
                vertice = v;
                break;
            }
        }
        
        for(v=vertice; v<g->V; v++){
            for(y=0; y<g->V; y++){
                if(g->mat[sol[v]][y]!=0){
                    if(d[y]<d[sol[v]] + g->mat[sol[v]][y]){
                        d[y] = d[sol[v]]+g->mat[sol[v]][y];
                    }
                }
            }
        }
        printf("Distanza massime di %s: \n", ind_to_string(g->st, i, &flag1));
        flag1 = 1;
        for(v=0; v<g->V; v++){
            printf("-%s: %d\n", ind_to_string(g->st, v, &flag1), d[v]);
            flag1 = 1;
            flag2 = 1;
        }
    }
	
    free(sol);
    free(pre);
    free(post);
    free(d);
}

void print_grafo(Grafo g){
    int flag1 = 1, flag2 = 1;
    
    for(int i=0; i<g->V; i++){
        for(int j=0; j<g->V; j++){
            if(g->mat[i][j]){
                printf("%s %s\n", ind_to_string(g->st, i, &flag1), ind_to_string(g->st, j, &flag2));
                flag1 = 1;
                flag2 = 1;
            }
        }
    }
}