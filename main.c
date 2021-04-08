#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamelib.h"

#define GOOD 0
#define ERROR 1
#define EMPTY 2
#define TOOSHORT 3
#define TOOLONG 4

int debug_on = 0;


// la funzione prende una stringa di 3 byte in input
int get_line(char* inputStr) {
    int chr, check;

    if (fgets (inputStr, 3, stdin) == NULL){
      return EMPTY;
    }
    // controllo che almeno 1 carattere sia stato inserito in input
    int len = strlen(inputStr);
    if (len < 2){
      return TOOSHORT;
    }
    // controllo a fine linea se trovo \n
    if (inputStr[len - 1] != '\n') {
        check = 0;

        // flush
        while (((chr = getchar()) != '\n') && (chr != EOF))
            check = 1;

        if (check==1){
          return TOOLONG;
        }
        else
          return GOOD;
    }
    // termino l'array
    inputStr[len - 1] = '\0';
    return GOOD;
}


int get_int(int* choice){
  char choiceStr[2];
  int result = get_line(choiceStr);
  if (result != GOOD)
    return result;
  char* strInit;
  *choice = strtol(choiceStr, &strInit, 10);
  return GOOD;
}



static void menu_main(){
  printf("Cosa vuoi fare?\n");
  printf("1) Imposta il gioco\n");
  printf("2) Gioca\n");
  printf("3) Esci\n");
}


int main(int argc, char** argv){

  char* name = "anonimo";
  if (argc > 1){
    name = argv[1];
  }

  time_t t;
  srand((unsigned) time(&t));

  int choice = 0;
  int game_set = 0;
  int game_active = 0;
  int exit = 0;
  do{
    menu_main();
    while (get_int(&choice) != GOOD || choice < 0 || choice > 3){
      printf("Input non consentito, inserisci un numero tra 1 e 3\n");
      menu_main();
    }
    switch (choice) {
      case 0:
        if (debug_on == 0){
          debug_on = 1;
          printf("\033[0;34mDebug attivato\033[0m\n");
        }
        else {
          debug_on = 0;
          printf("\033[0;34mDebug disattivato\033[0m\n");
        }
        break;
      case 1:
        if (game_set == 1)
          deallocate_memory();
        game_set = imposta_gioco();
        break;
      case 2:
        if (game_active == 1){
          deallocate_memory();
          game_set = 0;
        }
        if (game_set != 1){
          printf("Per giocare devi prima impostare il gioco\n");
          break;
        }
        gioca();
        game_active = 1;
        break;
      case 3:
        if (game_set == 1)
          deallocate_memory();
        printf("%s left the chat\n", name);
        exit = 1;
        break;
      }
  } while(exit != 1);

  return GOOD;
}
