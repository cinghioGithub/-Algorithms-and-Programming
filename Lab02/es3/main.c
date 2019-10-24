#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_S 25
#define MAX_l 200
#define N 20
#define MAX_C 5

int main() {
    char sequenze[N][MAX_C];
    FILE *fp;
    char parola[MAX_S];
    char line[MAX_l];
    int ns, pos=0, i=0, j=0, flag=0,count=0, occor=0;
    int len_line, len_parola, len_sequenza;

    fp = fopen("sequenze.txt", "r");
    if(fp==NULL){
        printf("ERRORE APERTURA file sequenze.txt");
        exit(1);
    }
    fscanf(fp,"%d", &ns);
    for(int i=0; i<ns; i++){                                 /*caricamento delle sequenze*/
        fscanf(fp,"%s", &sequenze[i]);
    }
    fclose(fp);

    j=0;
    for(int k=0; k<ns; k++) {                               /*scorrimento di tutte le sequenze*/
        occor=0;
        pos=0;
        len_sequenza=strlen(sequenze[k]);
        fp = fopen("testo.txt" ,"r");
        if(fp==NULL){
            printf("ERRORE APERTURA file");
            exit(1);
        }

        while (fgets(line, MAX_l, fp)!=NULL){              /*lettura riga per riga del file*/
            len_line=strlen(line);
            i=0;
            j=0;

            while(i<len_line) {                             /*controllo di corrispondeze per la sequenza corrente sulla riga letta*/
                while(!isalnum(line[i]) && i<len_line){
                    i++;
                }
                if(i>=len_line) break;                      /*uscita non strutturata nel caso si arrivi a fine riga, per evitare che conti una parola in più*/
                j=0;
                while (isalnum(line[i]) && i < len_line) {
                    parola[j] = line[i];
                    j++;
                    i++;
                }
                parola[j]='\0';
                len_parola = strlen(parola);
                pos++;                                       /*contatore parole*/
                flag = 0;
                for (int y = 0; y <= len_parola - len_sequenza && flag == 0; y++) {        /*selezione del carattere della riga da cui cominciare il confronto della sequenza*/
                    count = 0;
                    for (int l = 0; l < len_sequenza; l++) {                               /*confronto della sequenza sulla porzione di riga selezionata*/
                        if (tolower(parola[l + y]) == tolower(sequenze[k][l])) count++;
                    }
                    if (count == len_sequenza) {
                        occor++;
                        if(occor==1) {
                            printf("La sequenza %s e' contenuta in %s (parola in posizione %d nel testo)", sequenze[k], parola, pos);
                        }
                        else printf(", %s (parola in posizione %d nel testo)", parola, pos);
                        flag = 1;
                    }
                }
            }
        }
        if (occor!=0) printf("\n");
    }
    return 0;
}