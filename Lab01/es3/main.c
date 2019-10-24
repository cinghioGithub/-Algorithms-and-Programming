#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

int destra_giu(int mat[MAX][MAX],int indice,int posizioni,int nr,int nc,char selettore[10]){
    int i=0,j=0;
    int sup=0;
    for(i=0;i<posizioni;i++){
        if(!strcmp(selettore,"riga")){
            sup=mat[indice][nc-1];
            for(j=nr-1;j>0;j--){
                mat[indice][j]=mat[indice][j-1];
            }
            mat[indice][0]=sup;
        }
        if(!strcmp(selettore,"colonna")){
            sup=mat[nr-1][indice];
            for(j=nc-1;j>0;j--){
                mat[j][indice]=mat[j-1][indice];
            }
            mat[0][indice]=sup;
        }
    }
    return mat;
}

int sinistra_su(int mat[MAX][MAX],int indice,int posizioni,int nr,int nc,char selettore[10]){
    int i=0,j=0;
    int sup=0;
    for(i=0;i<posizioni;i++){
        if(!strcmp(selettore,"riga")){
            sup=mat[indice][0];
            for(j=0;j<nc-1;j++){
                mat[indice][j]=mat[indice][j+1];
            }
            mat[indice][nc-1]=sup;
        }
        if(!strcmp(selettore,"colonna")){
            sup=mat[0][indice];
            for(j=0;j<nr-1;j++){
                mat[j][indice]=mat[j+1][indice];
            }
            mat[nr-1][indice]=sup;
        }
    }
    return mat;
}

int main() {
    int mat[MAX][MAX];
    char selettore[10];
    int indice;
    char direzione[10];
    int posizioni;
    int nr, nc;

    FILE *fp;
    fp = fopen("C:\\Users\\Cinghio\\Desktop\\PoliTo\\Algoritmi e programmazione\\Esercitazioni\\Lab01\\es3\\matrice.txt","r");
    fscanf(fp,"%d %d",&nr,&nc);
    for(int i=0; i<nr; i++){
        for(int j=0; j<nc;j++) {
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);

    printf("Ins <selettore> <indice> <direzione> <posizioni>: ");
    scanf("%s %d %s %d",&selettore,&indice,&direzione,&posizioni);

    if(!strcmp(selettore,"riga")){
        if(!strcmp(direzione,"destra")){
            destra_giu(mat,indice,posizioni,nr,nc,selettore);
        }
        else{
            sinistra_su(mat,indice,posizioni,nr,nc,selettore);
        }
    }
    else{
        if(!strcmp(direzione,"giu")){
            destra_giu(mat,indice,posizioni,nr,nc,selettore);
        }
        else{
            sinistra_su(mat,indice,posizioni,nr,nc,selettore);
        }
    }

    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}