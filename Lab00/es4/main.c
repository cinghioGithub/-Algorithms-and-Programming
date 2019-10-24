#include <stdio.h>
#include <stdlib.h>

#define N 20

int main() {
    int mat[N][N];
    int max_m[N][N];
    int max=0,pr=0,pc=0,sum=0;
    int nr=0,nc=0,n=0,i=0,j=0,k=0,y=0;
    FILE *fp;

    printf("Inserire un numero: ");
    scanf("%d",&n);

    fp = fopen("C:\\Users\\Cinghio\\Desktop\\PoliTo\\Algoritmi e programmazione\\Esercitazioni\\Lab00\\es4\\file.txt","r");

    fscanf(fp,"%d %d", &nr,&nc);

    for(i=0; i<nr;i++){
        for(j=0; j<nc;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }

    for(i=0; i<nr-n;i++){
        sum=0;
        for(j=0;j<nc-n;j++){
            sum=0;
            for(k=i;k<n+i;k++){
                for(y=j; y<n+j;y++){
                    printf("%d ",mat[k][y]);
                    sum+=mat[k][y];
                }
                printf("\n");
            }
            printf("somma: %d\n",sum);
            if(sum>max){
                max=sum;
                pr=k-n;
                pc=y-n;
            }
        }
        printf("\n");
    }

    printf("***********************************************************\n");

    for(i=pr; i<pr+n;i++){
        for(j=pc; j<pc+n;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}