#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"
#include "personaggi.h"

#define N_C 13

typedef enum {
    c_carica_lista, c_carica_oggetti, c_nuovo_perso, c_aggiungi, c_rimuovi, c_cancella, c_statistiche, c_help, c_ricerca, c_stampa, c_ricerca_o, c_stampa_o, fine
}command_t;

void menu(char *tab[]);
command_t gestione_cmd(char *cmd, char *tab[]);

int main() {
    char *tab_cmd[N_C]={"lista", "inventario","nuovo", "aggiungi", "rimuovi","cancella","statistiche", "help","ricerca","stampa","ricerca_o", "stampa_o", "fine"};
    command_t cmd;
    char command[MAX];
    int flag=1;
    tabPg_t *head;
    inv_t *invent;
    tabInv *inventario;
    link x;
    
    alloca_head(&head);    
    
    do{
        printf("Inserisci comando (help - per lista comandi): ");
        scanf("%s", command);
        
        cmd = gestione_cmd(command, tab_cmd);
        
        switch(cmd){
            case c_carica_lista:
                head = carica_lista(head);
                break;
            case c_carica_oggetti:
                carica_oggetti(&invent, &inventario);
                break;
            case c_nuovo_perso:
                head = nuovo_personaggio(head);
                break;
            case c_aggiungi:
                agg_rim_oggetto(cmd, head, inventario);
                break;
            case c_rimuovi:
                agg_rim_oggetto(cmd, head, inventario);
                break;
            case c_cancella:
                head=elimina_personaggio(head); 
                break;
            case c_statistiche:
                statistiche(head);
                break;
            case c_help:
                menu(tab_cmd);
                break;
            case c_ricerca:
                x = ricerca_pg(head);
                printf("PG: %s\n", x!=NULL? x->pg_t.nome:"Non presente");
                break;
            case c_stampa:
                stampa_personaggio(head);
                break; 
            case c_ricerca_o:
                ricerca_oggetto(inventario);
                break;
            case c_stampa_o:
                stampa_oggetto(inventario);
                break;
            case fine:
                flag=0;
                break;
            case -1:
                printf("Errore - comando non esistente.\n");
                break;
            default:
                break;
        }
    }while(flag);
    
    libera_lista(head);
    libera_inventario(inventario);
    
    return 0;
}

command_t gestione_cmd(char *cmd,  char *tab[] ){
    int i;
    command_t c=-1;
    for(i=0; i<N_C; i++){
        if(!strcmp(cmd, tab[i])){
            c = i;
            break;
        }
    }
    return c;
}

void menu(char *tab[]){
    int i=0;
    for(i=0; i<N_C; i++){
        switch(i){
            case c_carica_lista:
                printf("%s -> Carica la lista da file.\n", tab[i]);
                break;
            case c_carica_oggetti:
                printf("%s -> Carica l'inventario da file.\n", tab[i]);
                break;
            case c_nuovo_perso:
                printf("%s -> Permette di aggiungere un nuovo personaggio alla lista.\n", tab[i]);
                break;
            case c_aggiungi:
                printf("%s -> Aggiunge un oggetto dell'inventario ad un personaggio.\n", tab[i]);
                break;
            case c_rimuovi:
                printf("%s -> Rimuove un oggetto dall'inventario di un personaggio.\n", tab[i]);
                break;
            case c_cancella:
                printf("%s -> Cancella un personaggio dalla lista.\n", tab[i]);
                break;
            case c_statistiche:
                printf("%s -> Stampa le statistiche di un personaggio [codice] [nome] [classe] [hp] [mp] [atk] [def] [mag] [spr].\n", tab[i]);
                break;
            case c_help:
                printf("%s -> Stampa il menù dei comandi.\n", tab[i]);
                break;
            case fine:
                printf("%s -> Termina il programma.\n", tab[i]);
                break;
            default:
                break;
        }
    }
}