#include <stdio.h>
#include <stdlib.h>

#define N 50
#define dim 5

typedef struct{
    int nr;
    int nc;
}Numero;

Numero carica(int mat[N][N]);
void zero(int v[dim]);
void controlla(Numero num, int mappa[N][N], int base[], int altezza[], int area[],int r, int c, int j,int i);

int main() {
    Numero num;
    int mappa[N][N];
    int i=0,j=0;
    int base[dim];
    int altezza[dim];
    int area[dim];

    zero(base); zero(altezza); zero(area);

    num = carica(mappa);

    for(i=0;i<num.nr;i++){
        for(j=0;j<num.nc;j++){
            if(mappa[i][j]==1){
                if(i==0 || i==num.nr-1 ||j==0 || j==num.nc-1  ) {
                    controlla(num, mappa, base, altezza, area, i, j, j, i);
                }
                else if(mappa[i][j-1]==0 && mappa[i-1][j]==0)  controlla(num, mappa, base, altezza, area, i, j, j, i);
            }
        }
    }

    printf("Msx Base: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d\n",base[0], base[1], base[2], base[3], base[4]);
    printf("Msx Area: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d\n",area[0], area[1], area[2], area[3], area[4]);
    printf("Msx Altezza: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d",altezza[0], altezza[1], altezza[2], altezza[3], altezza[4]);
    return 0;
}

Numero carica(int mat[N][N]){
    int i=0, j=0;
    Numero numero;
    FILE *fp;
    fp = fopen("mappa.txt","r");
    if(fp==NULL){
        printf("ERRORE APERTURA mappa.txt");
        exit(1);
    }
    fscanf(fp,"%d%d",&numero.nr,&numero.nc);
    for(i=0; i<numero.nr;i++){
        for(j=0; j<numero.nc;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);
    return numero;
}

void zero(int v[dim]){
    int i=0;
    for(i=0; i<dim;i++){
        v[i]=0;
    }
}

void controlla(Numero num, int mappa[N][N], int base[], int altezza[], int area[],int r, int c, int j,int i){
    int count_r=0, count_c=0;
    while(mappa[r][c]==1 && c<num.nc){
        c++;
        count_c++;
    }
    c=j;
    while(mappa[r][c]==1 && r<num.nr){
        r++;
        count_r++;
    }
    if(count_c>base[2]){
        base[0]=i;
        base[1]=j;
        base[2]=count_c;
        base[3]=count_r;
        base[4]=count_c*count_r;
    }
    if(count_r>altezza[3]){
        altezza[0]=i;
        altezza[1]=j;
        altezza[2]=count_c;
        altezza[3]=count_r;
        altezza[4]=count_c*count_r;
    }
    if(count_r*count_c>area[4]){
        area[0]=i;
        area[1]=j;
        area[2]=count_c;
        area[3]=count_r;
        area[4]=count_c*count_r;
    }
}