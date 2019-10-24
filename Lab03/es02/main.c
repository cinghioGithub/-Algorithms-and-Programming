#include <stdio.h>
#include <ctype.h>
#define MAX 128

void stampaCodifica (void *p, int size, int bigEndian);
void checkBigendian (int *flag);
void stampa(int v[], int e, int m, int size, int bigE);

int main() {
    float af;
    double ad;
    long double ald;
    int bigEndian=1;

    checkBigendian(&bigEndian);

    printf("Le dimensioni delle vasiabili af, ad e ald sono:\n");
    printf("\na) af: %d byte, %d bit\n",sizeof(float), sizeof(float)*8);
    printf("b) ad: %d byte, %d bit\n",sizeof(double), sizeof(double)*8);
    printf("c) ald: %d byte, %d bit\n",sizeof(long double), sizeof(long double)*8);

    printf("\nInserire un numero: ");
    scanf("%Lf", &ald);
    af = (float)ald; ad = (double)ald;

    printf("\n-Codifca float: \n");
    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    printf("\n-Codifca double: \n");
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    printf("\n-Codifca long double: \n");
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);

    return 0;
}

void checkBigendian (int *flag){
    int check=1;
    char *p;
    p=(char *)&check;                 //cast da puntatore a intero a puntatore a char per poter leggere un byte alla volta
    if(*p==1) {
        printf("La codifica utilizzata e' LITTLE ENDIAN\n");            //controllo se in primo byte contiene il LSB
        *flag = 0;
    }
    else printf("La codifica utilizzata e' BIG ENDIAN\n");
}

void stampa(int v[], int e, int m, int size, int bigE){          //la funzione serve per stampare il vettore in base alla codifica utilizzata
    if(bigE){
        printf("Il bit di sengo  vale: %d\n", v[0]);
        printf("L' esponente vale: ");
        for (int i = 1; i <= e; i++) {
            printf("%d", v[i]);
        }
        printf("\n");

        printf("La mantissa vale: ");
        for (int i = e+1; i < size*8; i++) {
            printf("%d", v[i]);
        }
        printf("\n");
    }
    else{
        printf("Il bit di sengo  vale: %d\n", v[size*8-1]);
        printf("L' esponente vale: ");
        for (int i = size*8-2; i >= m; i--) {
            printf("%d", v[i]);
        }
        printf("\n");

        printf("La mantissa vale: ");
        for (int i = m-1; i >= 0; i--) {
            printf("%d", v[i]);
        }
        printf("\n");
    }

}

void stampaCodifica (void *p, int size, int bigEndian){
    unsigned char *c;
    int v[MAX];
    int num=0, j=0, q=0, count=0;
    c = p;
    if (size==16) size=10;                      //il long double lo alloca su 16 byte ma ne occupa effetivamente 10
    for(int i=0; i<size; i++){
        num = c[i];                             //salvo la codifica del carattere in una variabile intera per poi convertirlo in binario
        /*while(num==0){
            for(int k=0; k<8; k++){             //nel caso il numero letto si uno zero, inserisco nel vettore un byte di zeri
                v[j]=0;
                j++;
            }
            i++;

            num = c[i];
        }*/
        q = num;
        count=0;
        while(q!=0){                            //converto in numero letto in binario
            v[j] = q % 2;
            q = q / 2;
            j++;
            count++;
        }
        if(count<8){                            //controllo che il numero appena convertito sia su 8 bit, altrimenti aggiungo zeri prima del
            for(int k=0; k<8-count; k++){       //MSB in modo da arrivare a 8 bit
                v[j]=0;
                j++;
            }
        }
    }
    /*if(j<size*8){
        for(int y=j; y<size*8; y++){
            v[y]=0;
        }
    }*/

    switch(size) {                                              //stampa delle codifiche del float, double e long double
        case 4:
            stampa(v, 8, 23, size, bigEndian);
            break;
        case 8:
            stampa(v, 11, 52, size, bigEndian);
            break;
        case 10:
            stampa(v, 16, 63, size, bigEndian);
            break;
        default:
            break;
    }


}