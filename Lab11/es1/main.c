#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titoli.h"

#define N_C 8
#define MAX_C 30

typedef enum {
    c_carica, c_ricerca_titolo, c_ric_titolo_data, c_max_min_tot, c_max_min_intervallo, c_bilancia, c_help, c_fine
}Cmd;

Cmd cmd_manager(char *tab[], char *c);
void print_menu(char *tab[]);

int main() {
    char *tab[N_C] = {"carica", "ricerca_titolo", "ricerca_data", "max_min_tot", "max_min_int", "bilancia", "help", "fine"};
    char command[30];
    int flag=1;
    Cmd cmd;
    L_titoli head = NULL;
    
    head = init(head);

    do{
    printf("Inserire comando [help - lista comandi]: ");
    scanf("%s", command);
    
    cmd = cmd_manager(tab, command);
    
    switch(cmd){
        case c_carica:
            carica_lista_titoli(head);
            break;
        case c_ricerca_titolo:
            ricerca_titolo(head);
            break;
        case c_ric_titolo_data:
            ricerca_quotazione(head);
            break;
        case c_max_min_tot:
            max_min_titolo(head);
            break;
        case c_max_min_intervallo:
            max_min_intervallo(head);
            break;
        case c_bilancia:
            bilancia(head);
            break;
        case c_help:
            print_menu(tab);
            break;
        case c_fine:
            flag=0;
			libera_lista(head);
            break;
        default:
            printf("%s - comando non esistente.\n", command);
            break;
    }
    
    }while(flag);
    
    return 0;
}

Cmd cmd_manager(char *tab[], char *c){
    int i;
    for(i=0; i<N_C; i++){
        if(!strcmp(tab[i], c))
            return i;
    }
    return -1;
}

void print_menu(char *tab[]){
    int i=0;
    for(i=0; i<N_C; i++){
        printf("-%s: ", tab[i]);
        switch(i){
        case c_carica:
            printf("carica un file di titoli e le relative transazioni.\n");
            break;
        case c_ricerca_titolo:
            printf("Ricerca un titolo .\n");
            break;
        case c_ric_titolo_data:
            printf("Ricerca la quotazione di un titolo in una data.\n");
            break;
        case c_max_min_tot:
            printf("Stampa la quotazione max e min di un titolo.\n");
            break;
        case c_max_min_intervallo:
            printf("Stampa la quotazione max e min di un titolo in un intervallo di date.\n");
            break;
        case c_bilancia:
            printf("Bilancia l'albero delle quotazioni di un titolo.\n");
            break;
        case c_help:
            printf("Stamoa elenco comandi.\n");
            break;
        case c_fine:
            printf("Termina l'esecuzione.\n");
            break;
        default:
            break;
    }
    }
}