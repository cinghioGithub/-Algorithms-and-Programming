#include <stdio.h>
#include <stdlib.h>

typedef struct {       //struttura dati per gli archi
    int a;
    int b;
} arco;

void carica(FILE *fp, int *n, int *e, arco **v, int **sol);
void powerset(int n, int *sol, int start, int pos, int num, int arc, arco *vet);
int check(arco *v, int *sol, int n, int num);

int main() {
    FILE *fp;
    int n=0, e=0, i=0, start=0;
    arco *v;
    int *sol;
    
    carica(fp, &n, &e, &v, &sol);                              //carica della struttura dati per gli archi
    
    for(i=1; i<=n; i++){                                        //calcolo del powerset con combinazioni da 1 a n elementi
        powerset(i, sol, 0, 0, n, e, v);
    }
    
    free(sol);
    free(v);
    
    return 0;
}

void carica(FILE *fp, int *n, int *e, arco **v, int **sol){    //caicamento del file in una struttura dati di tipo arco
    fp = fopen("grafo.txt", "r");
    if(fp==NULL){
        printf("Erroere file.\n");
        exit(1);
    }
    
    fscanf(fp, "%d %d", n, e);
    (*sol)=(int *)malloc((*n)*sizeof(int));                //allocazione del vettore delle soluzioni
    (*v)=(arco *)malloc((*e)*sizeof(arco));                 //allocazione della struttura dati per gli archi del grafo
    for(int i=0; i<(*e); i++){
        fscanf(fp,"%d %d", &((*v)[i].a), &((*v)[i].b));
    }
    
    fclose(fp);
}

void powerset(int n, int *sol, int start, int pos, int num, int arc, arco *vet){    //calcolo del powerset attraverso le combinazioni semplici
    int i=0;
    if(pos>=n){
        if(check(vet, sol, n, arc)){
            printf("{");
            for(int j=0; j<n; j++){
                printf("%d%s", sol[j], j==(n-1)? "":",");    
            }
            printf("}\n");
            return;
        }
        return;
    }
    
    for(i=start; i<num; i++){
        sol[pos]=i;
        powerset(n, sol, i+1, pos+1, num, arc, vet);
    }
}

int check(arco *v, int *sol, int n, int num){                //funzione che controlla se la soluzione trovata e' valida
    int count=0;
    for(int i=0; i<num; i++){
        for(int j=0; j<n; j++){
            if(v[i].a == sol[j] || v[i].b == sol[j]){
                count++;
                break;
            }
        }
    }
    if(count==num)
        return 1;
    return 0;
}