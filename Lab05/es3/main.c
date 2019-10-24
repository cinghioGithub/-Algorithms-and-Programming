#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30
#define N_C 9

typedef enum {
    r_print, r_data, r_codice, r_partenza, r_capolinea, r_ricerca, r_help, r_fine, r_leggi
}command_e;

struct Bus{
    char code[N];
    char start[N];
    char finish[N];
    char date[N];
    char o_start[N];
    char o_finish[N];
    int late;
} ;

void carica(int *n, char *file, struct Bus **pulman,struct Bus ***busd,struct Bus ***busco,struct Bus ***busp,struct Bus ***busca);
void print(struct Bus *bus, int n, char *nome);
command_e controllo (char str[], char tab[N_C][N]);
void data(int n, struct Bus **busp, int cod, int *flag);
struct Bus *ricerca_dic(struct Bus **busp, int i, int f, char *staz);
struct Bus *ricerca_lin(struct Bus **busp, int n, char *staz);
void print_menu(char tab[][N]);

int main() {
    struct Bus *pulman;
    struct Bus *support;
    struct Bus **bus_data, **bus_cod, **bus_par, **bus_cap;
    char tab[N_C][N] = {"print","data","codice","partenza","capolinea","ricerca", "help", "fine", "leggi"};
    int n, cod, flag, esci=1;
    char command[N], nome[N], line[N];

    carica(&n, "log.txt", &pulman, &bus_data, &bus_cod, &bus_par, &bus_cap);
    for(int i=0; i<n; i++) {
        bus_data[i] = &pulman[i];
        bus_cod[i] = &pulman[i];
        bus_par[i] = &pulman[i];
        bus_cap[i] = &pulman[i];
    }

    do {
        printf("Inserire comando (help per menu): ");
        fgets(line, N, stdin);
        sscanf(line,"%s %s", command, nome);

        cod = controllo(command, tab);

        switch (cod) {
            case r_print:
                print(pulman, n, nome);
                break;
            case r_leggi:
                free(pulman);           //liberazione della memoria allocata per la riallocazione e il caricamento da file
                free(bus_data);
                free(bus_cod);
                free(bus_par);
                free(bus_cap);
                carica(&n, nome, &pulman, &bus_data, &bus_cod, &bus_par, &bus_cap);
                for(int i=0; i<n; i++) {            //riassegnazione dei puntatori ai vari vettori per gli ordinamenti
                    bus_data[i] = &pulman[i];
                    bus_cod[i] = &pulman[i];
                    bus_par[i] = &pulman[i];
                    bus_cap[i] = &pulman[i];
                }
                break;
            case r_data:
                data(n, bus_data, cod, &flag);
                break;
            case r_codice:
                data(n, bus_cod, cod, &flag);
                break;
            case r_partenza:
                data(n, bus_par, cod, &flag);
                break;
            case r_capolinea:
                data(n, bus_cap, cod, &flag);
                break;
            case r_ricerca:
                if (flag == 3) {
                    support = ricerca_dic(bus_par, 0, n - 1, nome);
                    if(support!=NULL)
                        printf("%s\n", support->code);
                    else
                        printf("%s - Non trovato\n", nome);
                }
                else {
                    support = ricerca_lin(bus_par, n, nome);
                    if(support!=NULL)
                        printf("%s\n", support->code);
                    else
                        printf("%s - Non trovato\n", nome);
                }
                break;
            case r_help:
                print_menu(tab);
                break;
            case r_fine:
                esci=0;
                break;
            default:
                printf(" %s - Comando non esistente.\n", command);
                break;
        }
    }while(esci);

    free(pulman);
    free(bus_data);
    free(bus_cod);
    free(bus_par);
    free(bus_cap);
    
    return 0;
}

void carica(int *n, char *file, struct Bus **pulman,struct Bus ***busd,struct Bus ***busco,struct Bus ***busp,struct Bus ***busca){
    FILE *fp;    
    fp = fopen(file,"r");
    if(fp == NULL){
        printf("ERRORE APERTURA file.\n");
        return;
    }
    fscanf(fp,"%d",n);
    (*pulman)=(struct Bus *)malloc((*n)*sizeof(struct Bus));    //allocazione del vettore di strutture Bus e dei vari vettori di punatori per gli ordinamnti
    (*busd) = (struct Bus **)malloc((*n)*sizeof(struct Bus *));
    (*busco) = (struct Bus **)malloc((*n)*sizeof(struct Bus *));
    (*busp) = (struct Bus **)malloc((*n)*sizeof(struct Bus *));
    (*busca) = (struct Bus **)malloc((*n)*sizeof(struct Bus *));
    for(int j=0; j<*n; j++){
        fscanf(fp,"%s %s %s %s %s %s %d",(*pulman)[j].code,(*pulman)[j].start,(*pulman)[j].finish,(*pulman)[j].date,(*pulman)[j].o_start,(*pulman)[j].o_finish,&(*pulman)[j].late);
    }
    fclose(fp);
}

void print(struct Bus *bus, int n, char *nome){
    FILE *fp;
    if(nome[0]!='\0'){
        if(strcmp(nome,"no")){
            fp = fopen(nome,"w");
            if(fp == NULL){
                printf("Errore nome file.\n");
                return;
            }
        }
        else{
            fp = stdout;
        }
        for(int j=0; j<n; j++){
            fprintf(fp,"%s %s %s %s %s %s %d\n",bus[j].code,bus[j].start,bus[j].finish,bus[j].date,bus[j].o_start,bus[j].o_finish,bus[j].late);
        }
        if(fp!=stdout)
            fclose(fp);
    }
    else{
        printf("Errore. Nome file non trovato.\n");
    }
}

void print_menu(char tab[][N]){
    for(int i=0; i<N_C; i++){
        printf("-%s: ", tab[i]);
        switch(i){
            case r_print:
                printf("[nome file] per stampare su fine, altrimenti [no]\n");
                break;
            case r_data:
                printf("ordinamento per data\n");
                break;
            case r_codice:
                printf("ordinamento per codice tratta\n");
                break;
            case r_partenza:
                printf("ordinamento per stazione di partenza\n");
                break;
            case r_capolinea:
                printf("ordinamento per stazione di capolinea\n");
                break;
            case r_ricerca:
                printf("(ricerca [nome stazione]) -> ricerca per stazione di partenza\n");
                break;
            case r_fine:
                printf("Termina esecuzione\n");
                break;
            case r_help:
                printf("Stampa lista comandi\n");
                break;
            case r_leggi:
                printf("(leggi [nome file]) -> carica i dati da un nuovo file\n");
                break;
            default:
                break;
        }
    }
}

command_e controllo (char str[], char tab[N_C][N]){
    command_e cmd = -1;
    for(int i=0; i<N_C; i++){
        if(!strcmp(str,tab[i])) {
            cmd = i;
            break;
        }
    }
    return cmd;
}

void data(int n, struct Bus **busp, int cod, int *flag) {
    struct Bus *sup;
    for(int i=0; i<n-1; i++){
        for(int j=0; j<(n-1)-i; j++){
            switch(cod) {
                case 1:
                    *flag=1;
                    if (strcmp(busp[j]->date, busp[j+1]->date) > 0) {
                        sup = busp[j];
                        busp[j] = busp[j+1];
                        busp[j+1] = sup;
                    }
                    else if(!strcmp(busp[j]->date, busp[j+1]->date)){
                        if(strcmp(busp[j]->o_start, busp[j+1]->o_start) > 0){
                            sup = busp[j];
                            busp[j] = busp[j+1];
                            busp[j+1] = sup;
                        }
                    }
                    break;
                case 2:
                    *flag=2;
                    if (strcmp(busp[j]->code, busp[j + 1]->code) > 0) {
                        sup = busp[j];
                        busp[j] = busp[j + 1];
                        busp[j + 1] = sup;
                    }
                    break;
                case 3:
                    *flag=3;
                    if (strcmp(busp[j]->start, busp[j + 1]->start) > 0) {
                        sup = busp[j];
                        busp[j] = busp[j + 1];
                        busp[j + 1] = sup;
                    }
                    break;
                case 4:
                    *flag=4;
                    if (strcmp(busp[j]->finish, busp[j + 1]->finish) > 0) {
                        sup = busp[j];
                        busp[j] = busp[j + 1];
                        busp[j + 1] = sup;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

struct Bus *ricerca_lin(struct Bus **busp, int n, char *staz){
    for(int i=0; i<n; i++){
        if(strstr(busp[i]->start, staz)!=NULL)
            return busp[i];
    }
    return NULL;
}

struct Bus *ricerca_dic(struct Bus **busp, int i, int f, char *staz){
    int k = (i+f)/2;
    if(i>f) return NULL;

    if(strstr(busp[k]->start,staz)!=NULL)
        return busp[k];
    if(strcmp(busp[k]->start,staz)<0)
        return ricerca_dic(busp,k+1,f,staz);
    return ricerca_dic(busp,i,k-1,staz);
}