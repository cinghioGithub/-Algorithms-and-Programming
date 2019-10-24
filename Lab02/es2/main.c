#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30
#define MAX 1000
#define N_C 6

//struct
typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
}command_e;

typedef struct{
    char code[N];
    char start[N];
    char finish[N];
    char date[N];
    char o_start[N];
    char o_finish[N];
    int late;
} Bus ;

//funzioni
command_e controllo (char str[],char tab[N_C][N]);
void date(Bus bus[],int n, command_e cmd, char line[]);
void partenza(Bus bus[], int n,char line[]);
void capolinea(Bus bus[], int n,char line[]);
void ritardo(Bus bus[], int n,char line[]);

//main
int main() {
    FILE *fp;
    command_e cmd;
    Bus pulman[MAX];
    int fine=1;
    char tab[N_C][N] = {"date","partenza","capolinea","ritardo","ritardo_tot","fine"};
    char line[N];
    char command[N];
    int n=0;

    fp = fopen("log.txt","r");
    if(fp == NULL){
        printf("ERRORE APERTURA log.txt");
        exit(1);
    }
    fscanf(fp,"%d",&n);
    for(int j=0; j<n; j++){
        fscanf(fp,"%s %s %s %s %s %s %d",pulman[j].code,pulman[j].start,pulman[j].finish,pulman[j].date,pulman[j].o_start,pulman[j].o_finish,&pulman[j].late);
    }
    fclose(fp);
    do {
        printf("Inserire comando: ");
        gets(line);
        sscanf(line,"%s", command);
        cmd = controllo(command,tab);

        switch (cmd) {
            case r_date:
                date(pulman, n, cmd, line);
                break;
            case r_partenza:
                partenza(pulman, n, line);
                break;
            case r_capolinea:
                capolinea(pulman, n, line);
                break;
            case r_ritardo:
                date(pulman, n, cmd, line);
                break;
            case r_ritardo_tot:
                ritardo(pulman, n, line);
                break;
            case r_fine:
                printf("Fine programma");
                fine =0;
                break;
            case -1:
                printf("Comando non eistente\n");
                break;
            default:
                break;
        }
    } while(fine);
    return 0;
}

//funzioni
command_e controllo (char str[], char tab[N_C][N]){
    command_e cmd = -1;
    for(int i=0; i<N_C; i++){
        if(!strcmp(str,tab[i])) cmd = i;
    }
    return cmd;
}

void date(Bus bus[],int n,command_e cmd, char line[]){
    int day1, month1, year1;
    int day2, month2, year2;
    int day, month, year;
    int i;
    char buff[N];

    sscanf(line,"%s %d/%d/%d %d/%d/%d",buff,&year1, &month1, &day1,&year2, &month2, &day2);
    for(i=0;i<n; i++){
        sscanf(bus[i].date, "%d/%d/%d", &year, &month, &day);
        if(year<year2 && year>year1) {
            if (cmd == 3 && bus[i].late != 0)
                printf("%s %s %s %s %s %s %d\n", bus[i].code, bus[i].start, bus[i].finish, bus[i].date, bus[i].o_start, bus[i].o_finish, bus[i].late);
            else
                printf("%s %s %s %s %s %s %d\n", bus[i].code, bus[i].start, bus[i].finish, bus[i].date, bus[i].o_start, bus[i].o_finish, bus[i].late);
        }
        else{
            if (month < month2 && month > month1) {
                if (cmd == 3 && bus[i].late != 0)
                    printf("%s %s %s %s %s %s %d\n", bus[i].code, bus[i].start, bus[i].finish, bus[i].date, bus[i].o_start, bus[i].o_finish, bus[i].late);
                else
                    printf("%s %s %s %s %s %s %d\n", bus[i].code, bus[i].start, bus[i].finish, bus[i].date, bus[i].o_start, bus[i].o_finish, bus[i].late);
            }
            else{
                if (day <= day2 && day >= day1) {
                    if (cmd == 3 && bus[i].late != 0)
                        printf("%s %s %s %s %s %s %d\n", bus[i].code, bus[i].start, bus[i].finish, bus[i].date, bus[i].o_start, bus[i].o_finish, bus[i].late);
                    else
                        printf("%s %s %s %s %s %s %d\n", bus[i].code, bus[i].start, bus[i].finish, bus[i].date, bus[i].o_start, bus[i].o_finish, bus[i].late);
                }
            }
        }

    }
}

void partenza(Bus bus[], int n,char line[]){
    int i;
    char fermata[N];
    char buf[N];
    sscanf(line,"%s %s", buf, fermata);
    for(i=0; i<n; i++){
        if(!strcmp(fermata,bus[i].start ))
            printf("%s %s %s %s %s %s %d\n",bus[i].code,bus[i].start,bus[i].finish,bus[i].date,bus[i].o_start,bus[i].o_finish,bus[i].late);
    }
}

void capolinea(Bus bus[], int n, char line[]){
    int i;
    char fermata[N];
    char buf[N];
    sscanf(line,"%s %s", buf, fermata);
    for(i=0; i<n; i++){
        if(!strcmp(fermata,bus[i].finish ))
            printf("%s %s %s %s %s %s %d\n",bus[i].code,bus[i].start,bus[i].finish,bus[i].date,bus[i].o_start,bus[i].o_finish,bus[i].late);
    }
}

void ritardo(Bus bus[], int n, char line[]){
    int i, c=0;
    char code [N];
    char buf[N];
    sscanf(line,"%s %s", buf, code);
    for(i=0; i<n; i++){
        if(!strcmp(bus[i].code, code)) c+= bus[i].late;
    }
    printf("Ritardo totale per la tratta %s : %d ", code, c);
}