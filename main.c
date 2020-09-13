
#include <stdlib.h>
#include <stdio.h>
#include "gamelib.h"
int main(void) {
  system("clear");
//opzione = considera la scelta dell'utente
// mappa = esistenza percorso 1 esiste, 0 non esiste,
//modifica mappa= se esiste un percorso l'utente sceglie se modificarlo o crearne uno nuovo
    unsigned short int opzione=0, scelta_modifica_cunicolo =0, cunicolo_a=0, cunicolo_h=0;
//breve introduzione

    system("clear");
    //printf("\033[1;32m");
    printf("Le due famiglie Arvais e Hartornen si contendono da anni il possesso della melassa sul pianeta Sabbie \n");
    printf("fronteggiando ogni giorno temibili pericoli come crolli improvvisi, enormi bachi del deserto e la spudorata concorrenza della famiglia avversaria. \n");
    printf("Sostieni una delle due fazioni in questa sfida!!! \n");
    sleep(5);
//pulizia schermo
  system ("clear");
//presentazione menu
    do {

      printf(" Digitare:\n");
      printf(" 1 per creare cunicoli \n");
      printf(" 2 per giocare \n");
      printf(" 3 per uscire \n");
      printf(" fa la tua scelta!!! \n");

    //controllo dell'input nel menu

    while (scanf("%hu", &opzione)  !=1 || opzione>3 ||opzione <1) {
      printf(" opzione non corretta, inserisci un numero tra 1 e 3.\n");
      sleep(2);
    while (getchar() !='\n');
                                                                   }
switch(opzione) {
  case 1: //utente crea un cunicolo
        if(cunicolo_a==1 && cunicolo_h==1) {//se esistono già dei percorsi
          printf(" Esistono già dei percorsi, premi 1 per modificarli o 2 per rimpiazzarli \n");

          while (scanf("%hu", &scelta_modifica_cunicolo) !=1 || scelta_modifica_cunicolo >2 || scelta_modifica_cunicolo <1) {
            printf(" La scelta non è corretta, immetti 1 o 2 \n");
            sleep(2);
        while (getchar() !='\n');

                                                            }//chiusura while nell'if

        if (scelta_modifica_cunicolo==1) { //l'utente sceglie di modificare il percorso preesistente
          system("clear");
          crea_cunicoli ();
                               }
          else {
            if (scelta_modifica_cunicolo==2) { //l'utente decide di creare un nuovo cunicolo
              system("clear");
              termina_gioco ();//azzera i cunicoli
              crea_cunicoli ();
                                  } //chiusura if
                } //chiusura else
                          } //chiusura if mappa
            else {
              system("clear");
              crea_cunicoli ();
              cunicolo_a=1;
              cunicolo_h=1; //ora esiste un cunicolo

                 }//chiusura else
         break;


       case 2: //utente sceglie di giocare
             gioca();
             cunicolo_h=0;
             cunicolo_a=0; //viene liberata la memoria occupata dal cunicolo
        break;


         case 3:
              system("clear");
              termina_gioco();
              break;
              default:
              break;

             }  //chiusura switch
           }//chiusura do
           while (opzione!=3); // chiusura  ripetizione "mostra menu"

             } //main chiuso
