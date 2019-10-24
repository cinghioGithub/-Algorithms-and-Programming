#include <stdio.h>
#include <stdlib.h>

#define N 20

void capolista(int mat[N][N], int nr, int nc){
    int index=0, max=0,sum=0;
    for(int i=0;i<nc;i++){
        index =0;
        max=0;
        sum=0;
        for(int j=0;j<nr;j++){
            sum=0;
            for(int k=0;k<i+1;k++){
                sum+=mat[j][k];
            }
            if(sum>max){
                max = sum;
                index=j;
            }
        }
        printf("%d",index);

    }
}

int main() {
    int mat[N][N];
    int i=0,j=0;
    FILE *fp;
    char c=' ';
    int nc=0, nr=0;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            mat[i][j]=0;
        }
    }

    i=0;j=0;

    fp = fopen("C:\\Users\\Cinghio\\Desktop\\PoliTo\\Algoritmi e programmazione\\Esercitazioni\\Lab01\\es1\\campionato.txt","r");
    if (fp==NULL){
        printf("ERRORE APERTURA FILE");
        exit(1);
    }

    while(!feof(fp) && i<N ){
        c=' ';
        j=0;
        while(!feof(fp) && j<N && c!='\r' ){
            fscanf(fp,"%d",&mat[i][j]);
            fscanf(fp,"%c",&c);
            j++;
        }
        i++;
    }

    //j--;i--;

    nr=i;nc=j;

    capolista(mat,i,j);

    /*int index=0, max=0,sum=0;
    for(int i=0;i<nc;i++){
        index =0;
        max=0;
        sum=0;
        for(int j=0;j<nr;j++){
            sum=0;
            for(int k=0;k<i+1;k++){
                sum+=mat[j][k];
            }
            if(sum>max){
                max = sum;
                index=j;
            }
        }
        printf("%d",index);

    }*/

    return 0;
}