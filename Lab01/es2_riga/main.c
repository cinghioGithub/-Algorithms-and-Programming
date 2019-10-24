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
    fp = fopen("dizionario.txt","r");
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
    int n=0,i=0,count=0,k=0,j=0,l=0,m=0,start=0;
    int len_parola=0,len_word=0,check=0,flag=0;
    Dizionario dizionario[MAX];

    n = carica_dizionario(dizionario,fp_in); //carica il dizionario nel vettore di struct

    fp_in = fopen("sorgente.txt","r");
    fp_out=fopen("ricodificato.txt","w");
    while(fgets(parola,N,fp_in)!=NULL){  //legge una riga
        len_parola=strlen(parola);
        i=0;
        start=0;
        m=0;
            for (j = start; j < len_parola ; j++) {
                flag=0;
                for (k = 0; k < n && flag==0; k++) {
                    if (parola[j] == dizionario[k].word[0]){
                        len_word=strlen(dizionario[k].word);
                        count=0;
                        for(l=0;l<len_word;l++){
                            if(parola[j+l]==dizionario[k].word[l]) count++;
                        }
                        if (count == len_word) flag=1;
                    }
                }
                if (flag) {
                    for (m = start; m < j; m++) {
                        fprintf(fp_out, "%c", parola[m]);
                    }
                    fprintf(fp_out, "%s", dizionario[k-1].cod);
                    for (m = j+len_word; parola[m]!=' ' && m<len_parola; m++) {
                        fprintf(fp_out, "%c", parola[m]);
                    }
                    start=m;
                    j=m;
                }

            }

    }
    fclose(fp_out);
    fclose(fp_in);
    return 0;
}