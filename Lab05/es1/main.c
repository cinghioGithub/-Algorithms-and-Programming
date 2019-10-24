#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 255

typedef struct {        //struttura dati per il salvataggio delle canzoni di ogni amico
    int n;
    char **song;
}amico;

void leggi_file(char ***sol, amico **val, int *num);
void combinazioni(int start, char **sol, amico *val, int n, int *count);
void free_mem(amico *val, char **sol, int n);

int main() {
    char **sol;
    amico *val;
    int start=0;
    int n, count=0;
    
    leggi_file(&sol, &val, &n);
    
    combinazioni(start, sol, val, n, &count);
    
    printf("\nNumero playlist: %d\n", count);
    
    free_mem(val, sol, n);
    
    return 0;
}

void leggi_file(char ***sol, amico **val, int *num){
    FILE *fp;
    int n=0;
    char **solp;
    amico *valp;
    
    fp=fopen("brani.txt", "r");
    if(fp==NULL){
        printf("Errore file.\n");
    }
    
    fscanf(fp,"%d", num);
    n = *num;
    solp=(char **)malloc(n*sizeof(char*));      //allocazione del vettore soluzione
    valp=(amico *)malloc(n*sizeof(amico));      //allocazione del vettore di tipo amico per il salvataggio delle canzoni
    
    for(int i=0; i<n; i++){
        fscanf(fp,"%d", &valp[i].n);
        valp[i].song=(char **)malloc(valp[i].n*sizeof(char *));   //allocazine del vettore di stringhe per ogni amico
        solp[i]=(char *)malloc(N*sizeof(char));
        for(int j=0; j<valp[i].n; j++){
            valp[i].song[j]=(char *)malloc(N*sizeof(char));      //allocazione delle singole stringhe
            fscanf(fp,"%s",valp[i].song[j]);
        }
    }
    
    *val = valp; *sol = solp;       //assegnazione dei punatori per il riutilizzo delle strutture dati nel main
    
    fclose(fp);
}

void combinazioni(int start, char **sol, amico *val, int n, int *count){   //calcolo delle playlist (principio di moltiplicazione)
    int i=0, j=0, k=0;
    
    if(start==n){
        (*count)++;       //conteggio delle playlist
        printf("\n");
        for(k=0; k<n; k++){
            printf("%s\n",sol[k]);
        }
        return;
    }
    
    for(j=0; j<val[start].n; j++){
        strcpy(sol[j],val[start].song[j]);
        combinazioni(start+1, sol, val, n, count);
    }
}

void free_mem(amico *val, char **sol, int n){    //liberazione della memoria allocata precedentemente
    for(int i=0; i<n; i++){
        free(sol[i]);
        for(int j=0; j<val[i].n; j++){
            free(val[i].song[j]);
        }
        free(val[i].song);
    }
    free(val);
    free(sol);
}