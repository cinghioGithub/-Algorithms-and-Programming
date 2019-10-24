#include <stdio.h>
#include <stdlib.h>

#define nr 7
#define nc 30

int main() {
    int mat[nr][nc];
    FILE *fp;
    int i, j;
    int c_in, c_out, tmp, c_swap, sup;

    fp = fopen("sort.txt", "r");
    if(fp==NULL){
        printf("ERRORE");
        exit(1);
    }
    fscanf(fp,"%d",&i);
    for(i=0; i<nr;i++){
        fscanf(fp,"%d",&j);
        for(j=0; j<nc; j++){
            fscanf(fp,"%d", &mat[i][j]);
        }
    }
    fclose(fp);

    for(int y=0; y<nr; y++){
        //selection sort
        for(i=0; i<nc-1; i++){
            c_out++;
            for(j=i+1; j<nc; j++){
                c_in++;
                if(mat[y][i]>mat[y][j]){
                    c_swap++;
                    tmp=mat[y][i];
                    mat[y][i]=mat[y][j];
                    mat[y][j]=tmp;
                }
            }
        }

        printf("SELECTION SORT\nnumero cicli esterni: %d\nnumero cicli interni: %d\nnumero cicli totali: %d\nnumero scambi: %d\n",c_out,c_in,c_out*c_in,c_swap);
        c_in=0; c_out=0; c_swap=0;

        //insertion sort
        for(i=0; i<nc-1; i++){
            c_out++;
            j=i-1;
            sup = mat[y][i];
            while(sup<mat[y][j] && j>=0){
                c_in++;
                mat[y][j+1]= mat[y][j];
                j--;
            }
            mat[y][j+1]=sup;
        }
        printf("INSERTIO SORT\nnumero cicli esterni: %d\nnumero cicli interni: %d\nnumero cicli totali: %d\nnumero scambi: %d\n",c_out,c_in,c_out*c_in,c_swap);
        c_in=0; c_out=0; c_swap=0;
    }


    return 0;
}