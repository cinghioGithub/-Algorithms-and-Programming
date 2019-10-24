#include <stdio.h>
#include <stdlib.h>

#define N 50

void leggiMatrice(int *nr, int *nc, int mat[N][N]);
int riconosciRegione(int mappa[N][N], int *b, int *h,int *r, int *c, int nr, int nc);

int main() {
    int nr, nc;
    int mappa[N][N];
    int b=0, h=0;

    int y=0, k=0;

    leggiMatrice(&nr, &nc, mappa);

    for(y=0; y<nr; y++) {
        for (k = 0; k < nc; k++) {
            if (riconosciRegione(mappa, &b, &h, &y, &k, nr, nc)) {
                printf("Rettangolo trovato: (%d,%d), con base= %d e altezza= %d\n", y, k, b, h);
            }
        }
    }

    return 0;
}

void leggiMatrice(int *nr, int *nc, int mat[N][N]){
    int i=0, j=0;
    FILE *fp;
    fp = fopen("mappa.txt","r");
    if(fp==NULL){
        printf("ERRORE APERTURA mappa.txt");
        exit(1);
    }
    fscanf(fp,"%d%d",nr,nc);
    for(i=0; i<*nr;i++){
        for(j=0; j<*nc;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);
}

int riconosciRegione(int mappa[N][N], int *b, int *h,int *r, int *c, int nr, int nc){
    int i=0, j=0;
    *b=0; *h=0;
    if (mappa[*r][*c] == 1 && ((*r) == 0 || mappa[(*r) - 1][*c] == 0) && ((*c) == 0 || mappa[*r][(*c) - 1] == 0)) {
                i = *c;
                while (mappa[*r][i] == 1 && i < nc) {
                    i++;
                    (*b)++;
                }
                j = *r;
                while (mappa[j][*c] == 1 && j < nr) {
                    j++;
                    (*h)++;
                }
                return 1;
            }
    return 0;
}