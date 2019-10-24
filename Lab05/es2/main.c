#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int *nr, int *nc);
void separa(int **mat, int nr, int nc, int **b, int **n);
void free2dR(int **mat, int nr);

int main() {
    int **mat;
    int *b, *n, nr, nc, k;
    
    mat = malloc2dR(&nr, &nc);
    
    separa(mat, nr, nc, &b, &n);
    
    for(int i=0; i<13; i++)         //stampa dei due vettori rispettivamente bianchi e neri            
        printf("%d ", b[i]);
    
    printf("\n");
    
    for(int i=0; i<12; i++)
         printf("%d ", n[i]);
    
    free(b);            //liberazione della memoria allocata
    free(n);
    free2dR(mat,nr);
    return 0;
}

int **malloc2dR(int *nr, int *nc){    //allocazione della matrice scacchiera
    int **m;
    FILE *fp;
    
    fp = fopen("file.txt","r");
    if(fp==NULL){
        printf("Errore file.\n");
        exit(1);
    }
    
    fscanf(fp,"%d %d", nr, nc);
    m = (int **)malloc((*nr)*sizeof(int *));      //allocazione del vettore di puntatori di lunghezza numero_righe
    for(int i=0; i<*nr; i++){
        m[i] = (int *)malloc((*nc)*sizeof(int));   //allocazione delle righe
    }
    
    for(int i=0; i<*nr; i++){                   //caricamento della matrice
        for(int j=0; j<*nc; j++){
            fscanf(fp,"%d", &m[i][j]);
        }
    }
    
    fclose(fp);
    return m;           //ritorno del punatore al main
}

void separa(int **mat, int nr, int nc, int **b, int **n){
    int k=0 ,i,j,start=0;
    int sc=0, rc = 0, s1=0, s2=0;
    k = ((nr*nc)/2);
    if((nr*nc)%2==0){                           //calcolo delle dimensioni dei vettori per le padine nere e bianche
        *b = (int *)malloc(k*sizeof(int));      //allocazione dei due vettori
        *n = (int *)malloc(k*sizeof(int));
        for(i=0; i<nr; i++){
            if(i%2==0){                 
                sc=0;
                rc=1;
            }
            else{
                sc=1;
                rc=0;
            }
            for(j=0; j<nc-1; j+=2){
                (*b)[start] = mat[i][j+sc];
                (*n)[start] = mat[i][j+rc];
                start++;
            }
        }
    }
    else{
        *b = (int *)malloc((k+1)*sizeof(int));     //allocazione dei due vettori nel caso l'area della scacchiera non sia pari
        *n = (int *)malloc(k*sizeof(int));
        for(i=0; i<nr; i++){
            for(j=0; j<nc; j++){
                if((j+i)%2==0){
                    (*b)[s1]=mat[i][j];
                    s1++;
                }
                else{
                    (*n)[s2]=mat[i][j];
                    s2++;
                }
            }
        }
        
    }
}

void free2dR(int **mat, int nr){    //liberazione della memoria allocata per la matrice
    for(int i=0; i<nr; i++){
        free(mat[i]);
    }
    free(mat);
}