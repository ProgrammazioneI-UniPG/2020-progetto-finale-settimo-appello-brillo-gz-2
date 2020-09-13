#ifndef GAMELIB_H
#define GAMELIB_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

//permette di giocare e di gestire le dinamiche del gioco
void gioca();
//permnette la creazione, la modifica e la cancellazione di cunicoli
void crea_cunicoli();
//permette di uscire dal gioco e di deallocare il percorso scorrendo la lista dalla testa alla coda
void termina_gioco();

enum tipo_imprevisto {
     nessun_imprevisto,
     crollo,
     baco
                     }; //chiusura enum imprevisti
enum quantita_melassa {
     nessuna=0,
     poca=1,
     molta=3
                      };//fine enum melassa
enum tipo_caverna{
     normale,
     speciale, //aggiunge 1 unità melassa
     accidentata, //toglie 1 unità melassa
     uscita //permette di uscire dal cunicolo
                 };//fine enum tipo caverna

//descrive la singola caverna
enum direzione{
  dir_caverna_sinistra,
  dir_caverna_avanti,
  dir_caverna_destra
                };

struct caverna {
      enum tipo_imprevisto imprevisto;
      enum quantita_melassa melassa_presente;
      enum tipo_caverna tipologia_caverna;
      enum direzione direzione_caverna;// metterla a puntatore a struct caverna?
      struct caverna *caverna_successiva, *caverna_sinistra, *caverna_avanti, *caverna_destra;
                };//fine struct caverna

struct scavatrice{
       struct caverna *posizione_attuale, *prima_caverna, *ultima_caverna;
       unsigned short int serbatoio_melassa [16];
                  };//fine struct scavatrice

enum serbatoi_scavatrice{
energia,
raccolta
                        };

#endif
