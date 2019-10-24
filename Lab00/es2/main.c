#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 20

int conta(char S[], int n){
    int i=0,j=0;
    int count=0,c=0;
    for(i=0;i<N-n;i++){
        c=0;
        for(j=i;j<n+i;j++){
            if(S[j]=='a' || S[j]=='e' || S[j]=='i' || S[j]=='o' || S[j]=='u' || S[j]=='A' || S[j]=='E' || S[j]=='I' || S[j]=='O' || S[j]=='U') c++;
        }
        if(c==2)count++;
    }
    return count;
}

int main() {
    FILE *fp;
    char file[N];
    char S[N*2];
    int n=0,i=0,l=0;

    printf("Inserire il nome del file: ");
    scanf("%s",&S);

    printf("Inserire la lunghezza della sottostringa: ");
    scanf("%d",&l);

    fp = fopen(S,"r");

    if(fp==NULL) {
        printf("ERRORE");
        system("PAUSE");
        exit(1);
    }

    fscanf(fp,"%d",&n);
    /*if (!feof(fp)){
        printf("ERRORE: FILE VUOTO");
        system("PAUSE");
        exit(1);
    }*/

    for(i=0;i<n;i++){
        fscanf(fp,"%s",&file);
        printf("%d\n",conta(file,l));
    }
    fclose(fp);
    system("PAUSE");
    return 0;
}
