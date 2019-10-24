#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200
#define MAX 30

typedef struct {
    char cod[N];
    char word[N];
} Dizionario;

int carica_dizionario(Dizionario diz[],FILE *fp){
    int n=0,i=0;
    fp = fopen("C:\\Users\\Cinghio\\Desktop\\PoliTo\\Algoritmi e programmazione\\Esercitazioni\\Lab01\\es2\\dizionario.txt","r");
    fscanf(fp,"%d",&n);
    for(i=0; i<n;i++){
        fscanf(fp,"%s %s",&diz[i].cod,&diz[i].word);
    }
    fclose(fp);
    return n;
}

int main() {
    FILE *fp_in;
    FILE *fp_out;
    char parola[N];
    char acapo;
    int n=0,i=0,count=0,k=0,j=0,l=0,m=0;
    int len_parola=0,len_word=0,flag=0,check=0;
    Dizionario dizionario[MAX];

    n = carica_dizionario(dizionario,fp_in); //carica il dizionario nel vettore di struct

    fp_in = fopen("C:\\Users\\Cinghio\\Desktop\\PoliTo\\Algoritmi e programmazione\\Esercitazioni\\Lab01\\es2\\sorgente.txt","r");
    fp_out=fopen("C:\\Users\\Cinghio\\Desktop\\PoliTo\\Algoritmi e programmazione\\Esercitazioni\\Lab01\\es2\\ricodificato.txt","w");
    while(fscanf(fp_in,"%s",&parola)==1){  //legge una parola
        fscanf(fp_in,"%c",&acapo);
        len_parola=strlen(parola);
        i=0;
        flag=0;
        while(i<n && flag==0){  //controllo tutte le parole del dizionario finchè non trovo una corrispondenza
            len_word=strlen(dizionario[i].word);
            if(len_parola>=len_word) {
                for (j = 0; j <= len_parola - len_word; j++) {   //setto il carratere di inizio (di _parola_) per i confronto
                    l = j;
                    count = 0;
                    check=0;
                    for (k = 0; k < len_word && check==0; k++) {      //controllo che i carratteri da j a len_word di parola corrisponadano a quelli di dizionario[i].word
                        if (parola[l] == dizionario[i].word[k]) count++;
                        else check=1;
                        l++;
                    }
                    if (count == len_word) {
                        flag = 1;
                        for (m = 0; m < j; m++) {
                            fprintf(fp_out, "%c", parola[m]);
                        }
                        fprintf(fp_out, "%s", dizionario[i].cod);
                        for (m = j+len_word; m < len_parola; m++) {
                            fprintf(fp_out, "%c", parola[m]);
                        }
                    }

                }
            }
            i++;
        }
        if (flag==0) fprintf(fp_out,"%s",parola);
        if (acapo=='\r' || acapo=='\n') fprintf(fp_out, "\n");
        else fprintf(fp_out," ");
    }
    fclose(fp_out);
    fclose(fp_in);
    return 0;
}