
#include "gamelib.h"

//PROTOTIPI FUNZIONI


short int numero_turni=0;

void gioca();
unsigned short int cunicolo_a=0, cunicolo_h=0;
//variabili utilizzate per decretare vittoria
static short int vittoria_a = 0;
static short int vittoria_h = 0;

static unsigned short int ordinalita_arvais = 1;//tiene conto numero caverna posizione attuale nella tabella del turno
static unsigned short int ordinalita_hartornen = 1;

static void ins_caverna ();
short int inserimento_caverne = 0;// regola obbligatorietà 10 caverne, se = 0 devono essere inserite minimo 10 caverne
static short int caverne_cunicolo = 0;//numero totale caverne nel cunicolo
static short int numero_caverne=0;// numero di caverne inserite ad ogni aggiornamento
static void canc_caverna ();

static void stampa_cunicolo();

static void chiudi_cunicoli();

void crea_cunicoli();

//inizializzazione delle scavatrici all'inizio del gioco
static struct scavatrice arvais = {NULL,.serbatoio_melassa[raccolta]=0,.serbatoio_melassa[energia]=4};

static struct scavatrice hartornen = {NULL,.serbatoio_melassa[raccolta]=0,.serbatoio_melassa[energia]=4};

void termina_gioco();

static void reset();

static void turno_arvais();

static void turno_hartornen();

static void scontro_scavatrici();

static void avanza (struct scavatrice* giocatore);

static void abbatti (struct scavatrice* giocatore);

short int numero_abbatti_arvais = 0;
short int numero_abbatti_hartornen = 0;

static void reset_abbatti();

static void aggira (struct scavatrice* giocatore);

static void esci(); //solo se stato caverna=uscita, determina la vittoria in vase all'uscita o mneno delle famiglie
short int uscita_a= 0;// ponendo a 1 queste due variabili
short int uscita_h = 0;



static void melassa_trovata();

static void stato_imprevisto();

static void stato_caverna();


static enum quantita_melassa p_melassa_abbatti (int probabilita_melassa_abbatti);
static enum tipo_imprevisto p_imprevisto_abbatti (int probabilita_imprevisto_abbatti);
static enum tipo_caverna p_tipologia ( int probabilita_tipologia_abbatti);
static enum quantita_melassa p_melassa (int probabilita_melassa);
static enum tipo_imprevisto p_imprevisto (int probabilita_imprevisto);
static enum chiusura {si,no} chiusura=no;
static short int numero_abbatti=0;// preferibile dentro turno_arvais e turno_hartornen

static void reset(){ //resetta i dati del gioco per un'eventuale secodna partita
       arvais.serbatoio_melassa[raccolta]=0;
       arvais.serbatoio_melassa[energia]=4;
       hartornen.serbatoio_melassa[raccolta]=0;
       hartornen.serbatoio_melassa[energia]=4;
       vittoria_a=0;
       vittoria_h=0;
       ordinalita_arvais = 1;
       ordinalita_hartornen = 1;
       numero_turni=0;
       numero_abbatti=0;
       numero_abbatti_arvais = 0;
       numero_abbatti_hartornen = 0;
       uscita_a = 0;
       uscita_h = 0;

                  }
void termina_gioco () { // deallcola i cunicoli utilizzati per la partita precedente

 while (arvais.prima_caverna!= NULL){
   struct caverna *posizione = arvais.prima_caverna;
   if (posizione-> caverna_successiva!= NULL){


     while(posizione-> caverna_successiva!= NULL){
     free (posizione-> caverna_successiva);
     posizione-> caverna_successiva=NULL;
                                                }


   }
   else{
     free (arvais.prima_caverna);
     arvais.prima_caverna=NULL;

    }
                                     }

 while (hartornen.prima_caverna!= NULL){
struct caverna *posizione = hartornen.prima_caverna;
if (posizione-> caverna_successiva!= NULL){


while(posizione-> caverna_successiva!= NULL){
  free (posizione-> caverna_successiva);
 posizione-> caverna_successiva=NULL;
   }


  }
  else{
  free (hartornen.prima_caverna);
   hartornen.prima_caverna=NULL;

    }
   }





                    }//termina gioco



void crea_cunicoli(){ // permette inserimento,modifica e visualizzazione dei cunicoli nel menu iniziale di ogni famiglia
  system("clear");
  printf("\033[1;31m");
  printf("Tocca alla famiglia Arvais \n");
  short int scelta_arvais=0;




while(scelta_arvais !=5){
  printf("ARVAIS, CREATE IL VOSTRO CUNICOLO \n");
  printf("Premere:\n 1 per creare o modificare il cunicolo, \n 2 per cancellare l'ultima caverna, \n 3 per visualizzare il cunicolo, \n 4 per chiudere il cunicolo,\n ");
  if (chiusura==si){
  printf("5 per creare le caverne Hartornen \n");
                }
  scanf("%hu", &scelta_arvais);





  switch(scelta_arvais){
       case 1:

             ins_caverna(&arvais);
             inserimento_caverne +=1;

       break;
       case 2:
             canc_caverna(&arvais);

       break;
       case 3:
             stampa_cunicolo(&arvais);

       break;
       case 4:

             chiudi_cunicoli();

       break;
       case 5:
          if(arvais.prima_caverna == NULL){
           printf("\n\t\t\tPRIMA DI GIOCARE,COSTRUISCI LA MAPPA!\n");
           sleep(2);

           crea_cunicoli();
                                       }
            else if(chiusura==no){
              printf("non puoi giocare senza cunicolo \n");

              sleep(3);
              system("clear");
              crea_cunicoli();
            }
            cunicolo_a=1;
            system ("clear");
           break;
      default:
      printf("scelta non corretta \n");
      sleep(3);


      break;



  }//chiusura switch
}

chiusura = no;// permette di mostrare il comando 5 solo dopo aver chiuso il cunicolo
short int scelta_hartornen=0;
//do {



//} //chiusura do

while(scelta_hartornen !=5){
  printf("\033[1;33m");
    printf("Ora gli Hartornen\n");
    printf("CREA IL TUO CUNICOLO \n");
    printf("Premere:\n 1 per creare o modificare il cunicolo,\n 2 per cancellare l'ultima caverna,\n 3 per visualizzare il cunicolo,\n 4 per chiudere questo cunicolo,\n ");
  if (chiusura==si){// fa comparire il tasto 5 solo dopo aver chiusoi i cunicoli
    printf("5 per poter giocare \n");
                    }
    scanf("%hu", &scelta_hartornen);


  switch(scelta_hartornen){
         case 1:

              ins_caverna(&hartornen);
              inserimento_caverne +=1;

         break;
         case 2:
               canc_caverna(&hartornen);

         break;
         case 3:
               stampa_cunicolo(&hartornen);

         break;
         case 4:
               printf("\n");
               chiudi_cunicoli();

         break;
         case 5:
            if(hartornen.prima_caverna == NULL){
             printf("\n\t\t\tPRIMA DI GIOCARE,COSTRUISCI LA MAPPA!\n");
             sleep(2);
             system("clear");

             crea_cunicoli();
                                         }

             else if(chiusura==no){
               printf("non puoi giocare senza cunicolo \n");
               sleep(2);
               system("clear");

               crea_cunicoli();
             }
             cunicolo_h=1;

            break;
        default:
        printf("scelta non corretta \n");
        sleep(2);

        break;



  }//chiusura switch
}
system("clear");

}//chiusura crea_cunicoli



static void canc_caverna(struct scavatrice *giocatore){
  struct caverna* posizione_coda = NULL;
  posizione_coda=giocatore-> prima_caverna;
  if (giocatore-> prima_caverna==NULL){
    printf("Non ci sono ancora caverne \n");
    sleep(2);
    system("clear");
                          }
    else if (posizione_coda->caverna_successiva==NULL){
     printf("Non puoi cancellare la prima caverna \n");
                                                        }
               else {
                 caverne_cunicolo--;


          do {
            giocatore->ultima_caverna = posizione_coda;
               posizione_coda=posizione_coda->caverna_successiva;
          } while(posizione_coda->caverna_successiva !=NULL);

         free(posizione_coda);
         giocatore-> ultima_caverna-> caverna_successiva=NULL;
                  printf("\n\t\t  Ultima caverna cancellata \n");
                  sleep(3);
                  system("clear");
              }//chiusura else

                            }//canc_caverna


static enum quantita_melassa p_melassa (int probabilita_melassa){
  if (probabilita_melassa>=80) {
    return molta;
                                }
    else if (probabilita_melassa>50 && probabilita_melassa<=80) {
    return poca;
                                                                }
    else{
      return nessuna;
        }
                                                               }
   static enum tipo_imprevisto p_imprevisto (int probabilita_imprevisto){
if (probabilita_imprevisto>=85) {
 return baco;
 }
 else if (probabilita_imprevisto>50 && probabilita_imprevisto<=85) {
 return crollo;
                                                                   }
 else{
    return nessun_imprevisto;
    }
                                                                       }


static void ins_caverna(struct scavatrice *giocatore){
  time_t t;

  srand((unsigned) time(&t));

  int probabilita_melassa = 0;
  int probabilita_imprevisto = 0;


  struct caverna* nuova_caverna;
  if (inserimento_caverne < 1){
    printf("Quante caverne vuoi inserire? \n devi inserirne almeno 10 \n");
    scanf("%hu", &numero_caverne);
    while (numero_caverne<10) {
      printf("Devi inserire almeno 10 caverne \n");
      scanf("%hu", &numero_caverne);
      sleep(1);
      system("clear");
                              }//chiusura while
  }
  else {
    printf("Quante caverne vuoi inserire? \n");
    scanf("%hu", &numero_caverne);
    while (numero_caverne<1) {
      printf("Devi inserire almeno 1 caverna \n");
      scanf("%hu", &numero_caverne);
      sleep(1);
      system("clear");
                              }//chiusura while
  }

for (int i = 0; i < numero_caverne; i++) {
system("clear");
nuova_caverna = (struct caverna *) malloc(sizeof(struct caverna));
  printf("inserisci la direzione della caverna: 1 per sinistra, 2 per avanti, 3 per destra \n");

  while(scanf("%u", &nuova_caverna-> direzione_caverna)!=1 || nuova_caverna-> direzione_caverna <1 || nuova_caverna-> direzione_caverna >3){
    printf("scelta non corretta, reinserisci il valore \n");

    while (getchar() != '\n');
                                                                      }

if (nuova_caverna-> direzione_caverna == 1) {
  nuova_caverna->direzione_caverna = dir_caverna_sinistra;
  printf("la caverna sarà creata a sinistra \n");
                                             }
else if (nuova_caverna-> direzione_caverna == 2) {
  nuova_caverna-> direzione_caverna= dir_caverna_avanti;
  printf("la caverna sarà creata avanti \n");
}
else{
  nuova_caverna-> direzione_caverna= dir_caverna_destra;
  printf("la caverna sarà creata a destra \n");
}



probabilita_melassa = 1+(rand() %100);
probabilita_imprevisto = 1+(rand() %100);
printf("Scegli il tipo di caverna: 1 per normale, 2 speciale, 3 per accidentato \n");
while(scanf("%u", &nuova_caverna-> tipologia_caverna)!=1 || nuova_caverna-> tipologia_caverna <1 ||nuova_caverna-> tipologia_caverna >3 ){
  printf("scelta non corretta, reinserisci il valore \n");

  while (getchar() !='\n');
                                                                                                                               }// chiudo while
if (nuova_caverna-> tipologia_caverna==1) {

  printf("la caverna sarà di tipo normale \n");
    nuova_caverna-> tipologia_caverna=normale;}
    else if(nuova_caverna-> tipologia_caverna ==2 ){


    printf("la caverna sarà di tipo speciale \n");
    nuova_caverna-> tipologia_caverna=speciale;

  }
  else{

    printf("la caverna sarà di tipo accidentato \n");
    nuova_caverna->tipologia_caverna=accidentata;
      }



nuova_caverna-> melassa_presente = p_melassa(probabilita_melassa);

nuova_caverna-> imprevisto = p_imprevisto(probabilita_imprevisto);

nuova_caverna-> caverna_successiva = NULL;

  caverne_cunicolo++;
 if(giocatore-> prima_caverna == NULL ) {
    giocatore-> prima_caverna = nuova_caverna;
    giocatore-> ultima_caverna = giocatore-> prima_caverna;
    giocatore-> posizione_attuale = giocatore-> prima_caverna;
    //hartornen/arvais.posizione_attuale= giocatore-> prima_caverna;
                                        }//chiudo if
    else{
        giocatore-> ultima_caverna-> caverna_successiva = nuova_caverna;
        giocatore-> ultima_caverna = giocatore-> ultima_caverna-> caverna_successiva;
      }
}//for

printf("Ottimo, percorso aggiornato correttamente \n");
sleep(1);
system("clear");



}//chiudo ins caverna


static void stampa_cunicolo (struct scavatrice *giocatore){
int num_cav = 0; // tiene conto del numero della caverna stampata, ordinalità

  if (giocatore-> prima_caverna == NULL) {
    printf("non ci sono caverne \n");
    sleep(2);
                         }
  else {

 struct caverna* temp = giocatore-> prima_caverna;
system("clear");
printf("\t+-----------------------------------+\n");
printf("\t| NUMERO | DIREZIONE  |  TIPOLOGIA  |\n");
printf("\t+-----------------------------------+\n");
while (temp != NULL){

  num_cav ++;

  if (num_cav<10){// serve per migliorare aspetto tabella
    printf("\t|   %d    |" , num_cav);
                 }
  else {
    printf("\t|  %d    |" , num_cav);
       }
if (temp-> direzione_caverna== dir_caverna_sinistra) {

    printf(" A SINISTRA |");
  }
  else if(temp-> direzione_caverna== dir_caverna_avanti){

    printf("  IN AVANTI |");
  }
  else if (temp-> direzione_caverna== dir_caverna_destra){

      printf("  A DESTRA  |");

                                     }

  switch (temp-> tipologia_caverna) {
    case normale:
    printf("\t  NORMALE   |");
    break;
    case speciale:
    printf("\t  SPECIALE  |");
    break;
    case accidentata:
    printf("\tACCIDENTATA |");
    break;
    default:
    break;
                               }//switch
                               printf("\n");
printf("\t+-----------------------------------+\n");


temp = temp-> caverna_successiva;
}//while
}//else

printf("\n\n\n");



}//fine stampa_cunicolo


static void chiudi_cunicoli(){
  //if (numero_caverne<10) {
    if (caverne_cunicolo<10){
      printf("impossibile chiudere il cunicolo, ci sono meno di 10 caverne \n");
             }
else if (chiusura==si) {
  printf("cunicolo pronto per giocare,\n");
  sleep(2);
  system("clear");

     }
     else if(chiusura==no){
       printf("mappa chiusa correttamente\n");
       chiusura=si;
       printf("pronta per giocare \n");
       sleep(1);
       system("clear");
       caverne_cunicolo = 0;

     }

inserimento_caverne=0;

}//fine chiudi_cunicoli


 static void scontro_scavatrici(){ //+3% ogni turno

   int vincitore;
   int pos_scontro = numero_turni * 3;//ogni volta che si cambia giocatore si considera un turno
   time_t t;
   srand((unsigned) time(&t));
   int possibilita=(rand()%100);
   printf("Si odono degli strani rumori in lontananza... un baco? una scavatrice rivale? Forse sarebbe meglio non scoprirlo... \n");//magari dopo l if
   sleep(3);
   if (possibilita<=pos_scontro){
     vincitore=possibilita%2;//semplice meccanismo di vittoria basato sull'estrazione di un numero casuale e la sua parità/disparità
     printf("si palesa dinanzi a te la scavatrice avversaria, le due famiglie si scontrano... \n dopo una lunga battaglia.... \n ");
     sleep (2);
     if (vincitore==0){
       printf("vince la famiglia Arvais \n" );
       vittoria_a=1;
     }
     else {
       printf("la famiglia Hartornen ha distrutto la scavatrice Arvais \n");
       vittoria_h=1;
     }
                                }
    else{
      printf("... fiù!!!, tutto è andato per il meglio \n ");
    }

 }//fine scontro scavatrici

static void melassa_trovata(struct scavatrice *giocatore){
short int scelta_serbatoio;
//short int melassa_presente;// non utilizzato per ora
short int resto;// variabile utilizzata in caso si riempa il piccolo serbatoio di energia
switch (giocatore-> posizione_attuale-> melassa_presente) {
  case nessuna://nessuna
  printf("non hai trovato melassa in questa caverna \n");
  break;
  case poca://poca
  printf("hai trovato poca melassa, scegli dove metterla, 1 per carburante, 2 per incrementare quella raccolta \n");
  scanf("%hu" ,& scelta_serbatoio);
  while (scelta_serbatoio != 1 && scelta_serbatoio != 2) {
    printf("Scelta sbagliata, digita 1 per carburante oppure 2 per bottino \n");
    scanf("%hu" ,& scelta_serbatoio);
  }
  if (scelta_serbatoio==1 && giocatore->serbatoio_melassa[energia] < 4) {
    giocatore->serbatoio_melassa[energia] ++;
    printf("ora hai piu energia!! \n");
                                                                        }
  else if (scelta_serbatoio==1 && giocatore->serbatoio_melassa[energia] == 4){
    giocatore->serbatoio_melassa[raccolta] ++;
    printf("dato che il serbatoio energia è pieno e stato incrementato quello di raccolta \n");
                                                                        }
    else if  (scelta_serbatoio==2 && giocatore->serbatoio_melassa[raccolta] < 10){
      giocatore->serbatoio_melassa[raccolta]++;
      printf("serbatoio raccolta aumentato di 1 unita \n");
      //non ha molto senso controllare se il serbatoio di raccolta sia pieno o meno, è molto difficle lo sia e che , al contempo, si trovi molta melassa
                                                                                  }
  else{
    printf("vorresti diventare un allevatore di bachi e quindi lasci loro la melassa in eccesso \n");
  }
  break;

  case molta://molta
  printf("hai trovato molta melassa, scegli dove metterla, 1 per carburante, 2 per incrementare quella raccolta \n");
  scanf("%hu" ,& scelta_serbatoio);
  while (scelta_serbatoio != 1 && scelta_serbatoio != 2) {
    printf("Scelta sbagliata, digita 1 per carburante oppure 2 per bottino \n");
    scanf("%hu" ,& scelta_serbatoio);
  }
  if (scelta_serbatoio==1 && giocatore->serbatoio_melassa[energia]<=1) {
    giocatore->serbatoio_melassa[energia] +=3;
    printf("ora hai molta piu energia!! \n");
  }
  else if (scelta_serbatoio==1 && giocatore->serbatoio_melassa[energia]>1){

    resto = (giocatore->serbatoio_melassa[energia]+3) % 4;
    giocatore->serbatoio_melassa[energia] = 4;
    giocatore->serbatoio_melassa[raccolta] += resto;

    printf("dato che il serbatoio energia è pieno è stato incrementato quello di raccolta \n");
                                                                     }
    else if  (scelta_serbatoio==2 && giocatore->serbatoio_melassa[raccolta] <=7){
      giocatore->serbatoio_melassa[raccolta]+=3;
      printf("serbatoio di raccolta aumentato di 3 unita \n");
      //non ha troppo senso controllare se il serbatoio di raccolta sia pieno o meno
    }
    else if (scelta_serbatoio==2 && giocatore->serbatoio_melassa[raccolta] >7){
      printf("il serbatoio di raccolta trabocca \n");
      giocatore->serbatoio_melassa[raccolta]=10;


    }

  break;
  default:
  break;
}//switch
}//melassa trovata

static void stato_imprevisto(struct scavatrice* giocatore){
  switch (giocatore-> posizione_attuale-> imprevisto) {
    case nessun_imprevisto:
    printf("La caverna non sembra avere nulla di strano... \n");
    break;
    case crollo:
    printf("si sente uno strano baccano e la parete dinanzi a te crolla!!! \n");
    giocatore->serbatoio_melassa[energia]--;
    printf("Sei costretto ad utilizzare 1 unità di melassa per liberarti \n");
    break;
    case baco:
    printf("un viscido verme sguscia dalla parete laterale della caverna e assale la scavatrice svuotando completamente entrambi i serbatoi... \n");
// il baco prosciuga entrambi i serbatoi
    giocatore ->serbatoio_melassa[energia]=0;
    giocatore ->serbatoio_melassa[raccolta]=0;
    break;
    default:
    break;
                                                        }//switch


}//fine stato imprev

static void stato_caverna(struct scavatrice* giocatore){
  switch (giocatore-> posizione_attuale-> tipologia_caverna) {
    case normale:
    printf("tutto sembra calmo... \n");
    break;
    case accidentata:
    printf("la caverna va ripulita dalle macerie, per farlo la scavatrice consuma un'unità di energia \n");
    giocatore-> serbatoio_melassa[energia]--;
    break;
    case speciale:
    printf("le pareti della caverna hanno un colore diverso, è melassa, perché non aggiungerla al serbatoio energia ? \n");
    if (giocatore-> serbatoio_melassa[energia]<4){
      giocatore-> serbatoio_melassa[energia]++;   }
      else {
        printf("il serbatoio della scavatrice trabocca, verrà incrementato quello di raccolta\n");
        giocatore-> serbatoio_melassa[raccolta]++;
           }

    break;
    case uscita:
    printf("Si intravede uno spiraglio di luce... incredibile.... siamo arrivati all'uscita!!! \n");
    break;
    default:
    break;
                                                           }

                                                        }


void gioca(){
  int inizio=0;
  time_t t;
  srand((unsigned) time(&t));
  if(arvais.prima_caverna == NULL|| hartornen.prima_caverna == NULL ){
      printf("\033[1;31m");
      printf("\n\t  Nessun percorso presente, digita 1 per crearne uno \n");
      sleep(1);
      //printf("\033[0m");
      system("clear");
                                                                   }
  else {
      //system("clear");
          //gestisce i turni casuali
          inizio= 1 + (rand() % 100);
do{
         if (inizio<=50){


        esci();
            if (vittoria_a==1 && vittoria_h==0){
            printf("\033[1;31m");
             printf("Hanno vinto gli Arvais \n");
             sleep(5);
             system("clear");
             termina_gioco();
             reset();
             break;                                 }
      else if (vittoria_a==0 && vittoria_h==1){
        printf("\033[1;33m");
        printf(" Hanno vinto gli Hartornen \n");
        sleep(5);
        system("clear");
        termina_gioco();
        reset();
        break;
                                            }
         else if (vittoria_a==0 && vittoria_h==0){
             system("clear");
             printf("\033[1;31m");
             printf("la lotta continua... \n");
             printf("Turno Arvais \n");
             turno_arvais();
          printf("turno Arvais completo \n");
          sleep(2);
          system("clear");
          if (vittoria_a == 0 && vittoria_h ==0 && uscita_a==0){
          scontro_scavatrici();
          sleep(5);
          system("clear");   }
          if (vittoria_a == 0 && vittoria_h ==0){
          printf("\033[1;33m");
          printf("Turno Hartornen \n");
          turno_hartornen();
printf("turno Hartornen completo \n");
  sleep(2);
system("clear");
esci();                                                }
        if (vittoria_a == 0 && vittoria_h == 0 && uscita_a ==0 && uscita_h ==0){
          //basterebbe controllare solo la vittoria dato che si pone uguale a 1 con l'uscita
scontro_scavatrici();
sleep(5);
system("clear");

}
//}//chiusura if dentro l'if che controlla vittoria_a o h == 0
                                               }
                          }// chiusura if inizio 50
    else {
      //printf("Tocca agli Hartornen \n");
     esci();
      if (vittoria_a==1 && vittoria_h==0){
      printf("\033[1;31m");
      printf("Hanno vinto gli Arvais \n");
      sleep(6);
      system("clear");
      termina_gioco();
      reset();
      break;
                                           }

else if (vittoria_a==0 && vittoria_h==1){
 printf("\033[1;33m");
 printf(" Hanno vinto gli Hartornen \n");
 sleep(6);
 system("clear");
 termina_gioco();
 reset();
 break;

                                        }
if (vittoria_a==0 && vittoria_h==0){
system("clear");
printf("\033[1;33m");
printf("la lotta continua \n");
printf("Turno Hartornen \n");
turno_hartornen();
printf("turno Hartornen completo \n");
sleep(2);
system("clear");
if (vittoria_a==0 && vittoria_h==0 && uscita_h==0){
scontro_scavatrici();
sleep(5);
system("clear");
                                   }
  if (vittoria_a == 0 && vittoria_h ==0){
printf("\033[1;31m");
printf("turno Arvais\n");
turno_arvais();
printf("turno Arvais completo \n");
sleep(2);
system("clear");
esci();
                                        }
if (vittoria_a==0 && vittoria_h==0 && uscita_a ==0 && uscita_h == 0){
  //basterebbe controllare solo la vittoria dato che si pone = a 1 nella funzione esci
scontro_scavatrici();
                                       }//chiusura if dentro l'if che controlla vittoria_a o h == 0

                                    }

         }
       }//chiusura do
      while (1);

                  }
   }//chiusura gioca


//gestisce la possibilita crollo 25% su avanza
static enum tipo_imprevisto avanza_imprevisto(int probabilita_imprev_avanza){

  if (probabilita_imprev_avanza <= 25) {
    return crollo;
                         }
  else if (probabilita_imprev_avanza > 25 ) {
    return nessun_imprevisto;
      }
      else {
        return 0;// inserito per poter far terminare il controllo
      }

                                                                              }// imprevisto crollo avanza

static void avanza(struct scavatrice* giocatore){

int probabilita_imprev_avanza;

time_t t;

srand((unsigned) time(&t));
 //giocatore-> posizione_attuale-> caverna_successiva;

 giocatore-> serbatoio_melassa[energia]--;
 probabilita_imprev_avanza = 1+ (rand () %100);

 giocatore-> posizione_attuale-> imprevisto = avanza_imprevisto(probabilita_imprev_avanza);

// si è optato per tale scelta poiché reputato ingiusto utilizzare 3 unita di energia per muoversi di una caverna
// avendo 4 unità di energia reputate buone per la suspense del gioco

                                                 }//fine avanza


static void aggira (struct scavatrice* giocatore){
int probabilita_melassa = 0;
int probabilita_imprevisto = 0;
int probabilita_tipologia_abbatti = 0;

printf("\t Gli ingegneri stanno pensando quale sia l'angolazione migliore... \n");
sleep(2);
struct caverna *caverna_aggira = malloc (sizeof(struct caverna));

caverna_aggira = giocatore-> posizione_attuale;
probabilita_melassa = 1+(rand() % 100);
probabilita_imprevisto = 1+(rand() % 100);
probabilita_tipologia_abbatti = 1+(rand() % 100);
caverna_aggira-> melassa_presente = p_melassa(probabilita_melassa);
caverna_aggira-> imprevisto = p_imprevisto(probabilita_imprevisto);
caverna_aggira-> tipologia_caverna = p_tipologia( probabilita_tipologia_abbatti);// soluzione forzata ma efficace
giocatore-> serbatoio_melassa[energia] --;

printf("\t Angolazione perfetta trovata, varco aperto \n");

                                                  }//fine aggira

static void abbatti (struct scavatrice *giocatore) {
  // la scavatrice abbatendo si sposta nella nuova caverna, sia per motivi di giocabilità sia per logica
  // (per abbattere la scavatrice deve "irrompere" nella nuova caverna fisicamente, non ha senso che torni indietro)
  // al turno successivo, poi, ogni volta ,abbatti dealloca il cunicolo originale
  short int direzione=0;
  time_t t;

  srand((unsigned) time(&t));

  int probabilita_melassa_abbatti = 0;
  int probabilita_imprevisto_abbatti = 0;
  int probabilita_tipologia_abbatti = 0;

struct caverna *caverna_abbatti = malloc(sizeof(struct caverna));

printf("inserisci la direzione della caverna: 1 per sinistra, 2 per avanti, 3 per destra \n" );

  while(scanf("%hu", &direzione)!=1 || direzione <1 || direzione >3 ){
    printf("scelta non corretta, reinserisci il valore \n");
    while (getchar() != '\n');
                                                                    }
if (direzione==1) {

  printf("la caverna sarà creata a sinistra \n");
  caverna_abbatti-> direzione_caverna = dir_caverna_sinistra;
}
else if (direzione==1) {
  printf("la caverna sarà creata avanti \n");
  caverna_abbatti-> direzione_caverna = dir_caverna_avanti;

}
    else {
      printf("la caverna sarà creata a destra \n");
      caverna_abbatti-> direzione_caverna = dir_caverna_destra;
    }

    probabilita_melassa_abbatti= 1+(rand() %100);
    probabilita_imprevisto_abbatti = 1+(rand() %100);
    probabilita_tipologia_abbatti= 1+(rand() %100);

caverna_abbatti-> tipologia_caverna = p_tipologia(probabilita_tipologia_abbatti);

caverna_abbatti-> melassa_presente = p_melassa_abbatti(probabilita_melassa_abbatti);

caverna_abbatti-> imprevisto = p_imprevisto_abbatti(probabilita_imprevisto_abbatti);




caverna_abbatti = giocatore-> posizione_attuale-> caverna_successiva;
caverna_abbatti-> caverna_successiva = NULL;

giocatore-> serbatoio_melassa[energia]-=2;
//dato che si avanza e si abbatte contemporaneamente, senza pero rischiare di incorrere in un "crollo avanza"
//si è optato per togliere 2 unità di energia per rendere il tutto più giocabili


                                                  }



  static enum tipo_imprevisto p_imprevisto_abbatti (int probabilita_imprevisto_abbatti){
     if (probabilita_imprevisto_abbatti <=40) {
        return nessun_imprevisto;
                                               }
  else if (probabilita_imprevisto_abbatti>40 && probabilita_imprevisto_abbatti<=80) {
 return crollo;
                                        }
 else{
return baco;
     }
                                                                                         }

  static enum quantita_melassa p_melassa_abbatti (int probabilita_melassa_abbatti){
  if (probabilita_melassa_abbatti<=40) {
 return nessuna;
                                        }
  else if (probabilita_melassa_abbatti>40 && probabilita_melassa_abbatti<=80) {
  return poca;
                                                                                                                                                                                    }
  else{
      return molta;
    }
  }

static enum tipo_caverna p_tipologia ( int probabilita_tipologia_abbatti ){

int totale=100;
int esco=0;
int tetto_normale=0;
int caverna_uscita=0;

esco= 10 * numero_abbatti_arvais;
tetto_normale= ((totale-esco)-20)/2;
caverna_uscita=100-esco;

if(probabilita_tipologia_abbatti < tetto_normale) {
   return arvais.posizione_attuale-> tipologia_caverna =normale;
                                      }
else if (probabilita_tipologia_abbatti>= tetto_normale && probabilita_tipologia_abbatti <(2*tetto_normale)) {
  return arvais.posizione_attuale-> tipologia_caverna =speciale;
                                                                                     }
else if (probabilita_tipologia_abbatti>caverna_uscita){
  return arvais.posizione_attuale-> tipologia_caverna =uscita;
                                                      }
else {
return arvais.posizione_attuale-> tipologia_caverna =accidentata;
     }



//caso hartornen
totale=100;
esco=0;
tetto_normale=0;
caverna_uscita= 0;

     esco= 10 * numero_abbatti_hartornen;
     tetto_normale= ((totale-esco)-20)/2;
     caverna_uscita=100-esco;

     if(probabilita_tipologia_abbatti < tetto_normale) {
       return hartornen.posizione_attuale-> tipologia_caverna =normale;
                                           }
     else if (probabilita_tipologia_abbatti>= tetto_normale && probabilita_tipologia_abbatti <(2*tetto_normale)) {
       return hartornen.posizione_attuale-> tipologia_caverna =speciale;
                                                                                          }
     else if (probabilita_tipologia_abbatti>caverna_uscita){
       return hartornen.posizione_attuale-> tipologia_caverna =uscita;
                                                       }
     else {
       return hartornen.posizione_attuale-> tipologia_caverna =accidentata;
          }



                                                    }

static void reset_abbatti(struct scavatrice *giocatore){
  printf("La scavatrice sale di giri e si prepara ad abbattere...\n");
  sleep(3);
  struct caverna *posizione_coda=NULL;
  posizione_coda=giocatore-> posizione_attuale;




      while(posizione_coda-> caverna_successiva != NULL){
        giocatore-> ultima_caverna= posizione_coda;
        posizione_coda=posizione_coda-> caverna_successiva;

      free (posizione_coda);
      giocatore-> ultima_caverna -> caverna_successiva = NULL;
                                                        }
    printf("Missione riuscita \n");

                                                             }

//esci regola la possibilità di entrambe le scavatrici di uscire allo stesso turno
static void esci(){


    if (uscita_a == 1 && uscita_h == 0){
      vittoria_a= 1;
                                       }
   else if (uscita_a == 0 && uscita_h == 1){
     vittoria_h=1;
   }
   else if (uscita_a==1 && uscita_h ==1){
     if (arvais.serbatoio_melassa[raccolta] > hartornen.serbatoio_melassa[raccolta]){
       vittoria_a=1;
       printf("Nonostante siano usciti entrambi gli Arvais hanno più melassa e sopraffanno il nemico \n");
                                                                                     }
      else if (arvais.serbatoio_melassa[raccolta] < hartornen.serbatoio_melassa[raccolta]){
        vittoria_h=1;
        printf("Nonostante siano uscite entrambe le scavatrici gli Hartornen hanno più melassa e sopraffanno il nemico \n");
                                                                                           }
        else{
          printf("le scavatrici hanno la stessa quantità di melassa, le due famiglie sono infuriate e si scontrano alla luce del sole...\n");
       sleep(4);
       if(arvais.serbatoio_melassa[energia] > hartornen.serbatoio_melassa[energia]){
         vittoria_a=1;
         printf("gli Arvais hanno però più energia e riescono a vincere \n");
                                                                                     }
     else if(arvais.serbatoio_melassa[energia] < hartornen.serbatoio_melassa[energia] ){
       vittoria_h=1;
       printf("gli Hartornen hanno però più energia e riescono a spuntarla \n");
                                                                                        }
      else{

       vittoria_a=1;
     printf("riescono a vincere gli Arvais!!! \n"); // si è optato per questa scelta poichè è un caso rarissimo
               }
           }

                                         }
                           }// fine esci


static void turno_arvais(){



int scelta=0;
numero_turni ++;

printf("\033[1;31m");

printf("\n");
printf("\t+-----------+------------+--------------+------------+---------+----------+\n");
printf("\t|  FAMIGLIA |  POSIZIONE | TIPO CAVERNA | IMPREVISTO | ENERGIA | RACCOLTA |\n");
printf("\t+-----------+------------+--------------+------------+---------+----------+\n");
printf("\t|   ARVAIS  |");//FORSE UTILIZZO NUMERO CAVERNA CHE CON AGGIRA E AVANZA FA ++PER POSIZIONE

if(ordinalita_arvais <10){
  printf(" Caverna: %hu |" , ordinalita_arvais);
                             }
  else {
    printf(" Caverna: %hu|" , ordinalita_arvais);
       }
switch (arvais.posizione_attuale-> tipologia_caverna) {
  case normale:
  printf("   NORMALE    |");
  break;
  case speciale:
  printf("    SPECIALE  |");
  break;
  case accidentata:
  printf("  ACCIDENTATA |");
  break;
  case uscita:
  printf("     USCITA   |");
  break;
  default:
  break;
}//switch
switch(arvais.posizione_attuale-> imprevisto){
  case nessun_imprevisto:
  printf("  NESSUNO   |");
  break;
  case crollo:
  printf("   CROLLO   |");
  break;
  case baco:
  printf("    BACO    |");
  break;
  default:
  break;
                                                 }

printf(" %d unità |" , arvais.serbatoio_melassa[energia]);
if (arvais.serbatoio_melassa[raccolta] >9 ){
  printf (" %d unità |\n" , arvais.serbatoio_melassa[raccolta]);
                                           }
else {
  printf (" %d unità  |\n" , arvais.serbatoio_melassa[raccolta]);
     }//else
printf("\t+-----------+------------+--------------+------------+---------+----------+\n\n\n");

printf("alla ricerca di gioie e dolori...\n\n\n");
sleep(2);


stato_imprevisto(&arvais);
melassa_trovata(&arvais);
stato_caverna(&arvais);

if (arvais.serbatoio_melassa[energia] <= 0 || arvais.serbatoio_melassa[energia] >4 ) {
  printf("La scavatrice non può fare nulla, ha finito energia, dunque gli Arvais sono costretti a dichiarare la resa, vincono quindi gli hartornen!! \n");
  vittoria_h=1;
                                                       }

  else {
    if(arvais.posizione_attuale-> caverna_successiva != NULL && arvais.posizione_attuale-> imprevisto != crollo && arvais.posizione_attuale-> tipologia_caverna != uscita){
      printf("Premere:\t 1 per avanzare, \t 2 per abbattere. \n");
      while (scanf("%u" , &scelta )!= 1 || scelta <1 || scelta >2) {
        printf("per favore digita 1 o 2 \n");
        while (getchar ()!='\n');
                                                                    }
   switch (scelta) {
     case 1:
     avanza(&arvais);
     if(arvais.posizione_attuale-> imprevisto == crollo){
       printf("C'è stato un crollo, non puoi avanzare \n");
       sleep(3);
       printf("consumi energia per liberarti e avanzare\n");// se avessi dovuto aggiungere la funzione aggira avrei consumato 4 ENERGIA
       // poniamo caso -1 per accidentata, -1 per avanza, -1 per liberarsi e -1 per aggirare si perderebbe sempre
       // si è preferito lasciare il serbatoio energia di 4 unità per una maggiore "suspense" nella scelta dei serbatoi
       sleep(3);
       arvais.serbatoio_melassa[energia]--;//1 unita energia per liberarsi dalle macerie e la scavatrice avanza
       ordinalita_arvais++;
                                       }
      else {
        ordinalita_arvais++;
           }
     break;
     case 2:
     abbatti(&arvais);
     reset_abbatti(&arvais);
     numero_abbatti_arvais++;
     // numero_abbatti ++;//parametro a giocatore?
     break;
     default:
     break;
                 }

    }
    else if(arvais.posizione_attuale-> imprevisto == crollo){
      printf ("C'è stato un crollo, puoi solo aggirare, premi 1 per farlo \n");
      while (scanf("%u" , &scelta )!= 1 || scelta <1 || scelta >1) {

          printf("digita 1 \n");

          while (getchar() !='\n');
                                          }
      aggira(&arvais);
      ordinalita_arvais ++;
                                                             }//else if

else if(arvais.posizione_attuale-> caverna_successiva == NULL){
  printf("non ci sono più caverne disponibili è necessario abbattere, premi 1 per farlo \n");
  while (scanf("%u" , &scelta )!= 1 || scelta <1 || scelta >1) {
    printf("per favore digita 1 \n");
    while (getchar ()!='\n');
                                      }
abbatti(&arvais);
numero_abbatti_arvais++;
//reset_abbatti(&arvais);


                                                           }//else if

else if(arvais.posizione_attuale-> tipologia_caverna== uscita){
  printf("sei riuscito a trovare l'uscita, premi 1 per uscire o 2 per avanzare ancora \n");
  while (scanf("%u" , &scelta) != 1 || scelta <1 || scelta >2 ) {
    printf("ora che hai la vittoria in pugno non temporeggiare, premi 1 o 2, decidi\n");
    while (getchar ()!='\n');
switch (scelta) {
  case 1:

uscita_a=1;
break;
case 2:
avanza(&arvais);
break;
}
}

}//chiusura 3 else if (esci)



}//fine mega else



}//turno arvais

static void turno_hartornen(){

int scelta=0;
numero_turni ++;

printf("\033[1;33m");

printf("\n");
printf("\t+-----------+------------+--------------+------------+---------+----------+\n");
printf("\t|  FAMIGLIA |  POSIZIONE | TIPO CAVERNA | IMPREVISTO | ENERGIA | RACCOLTA |\n");
printf("\t+-----------+------------+--------------+------------+---------+----------+\n");
printf("\t| HARTORNEN |");

if(ordinalita_hartornen <10){
  printf(" Caverna: %hu |" , ordinalita_hartornen);
                             }
  else {
    printf(" Caverna: %hu|" , ordinalita_hartornen);
       }
switch (hartornen.posizione_attuale-> tipologia_caverna) {
  case normale:
  printf("    NORMALE   |");
  break;
  case speciale:
  printf("   SPECIALE   |");
  break;
  case accidentata:
  printf("  ACCIDENTATA |");
  break;
  case uscita:
  printf("    USCITA    |");
  break;
  default:
  break;
}//switch
switch(hartornen.posizione_attuale-> imprevisto){
  case nessun_imprevisto:
  printf("  NESSUNO   |");
  break;
  case crollo:
  printf("   CROLLO   |");
  break;
  case baco:
  printf("    BACO    |");
  break;
  default:
  break;
                                                 }

printf(" %d unità |" , hartornen.serbatoio_melassa[energia]);
if (arvais.serbatoio_melassa[raccolta] >9 ){
  printf (" %d unità |\n" , hartornen.serbatoio_melassa[raccolta]);
                                           }
else {
  printf (" %d unità  |\n" , hartornen.serbatoio_melassa[raccolta]);
     }//else
printf("\t+-----------+------------+--------------+------------+---------+----------+\n\n\n");

printf("alla ricerca di guai... \n\n\n");
sleep(3);


stato_imprevisto(&hartornen);
melassa_trovata(&hartornen);
stato_caverna(&hartornen);





if (hartornen.serbatoio_melassa[energia] <= 0  || hartornen.serbatoio_melassa[energia] >4) {
  printf("La scavatrice non può fare nulla, ha finito energia, dunque gli Hartornen sono costretti a dichiarare la resa, vincono quindi gli Arvais!! \n");
  vittoria_a=1;

                                            }

  else {
    if(hartornen.posizione_attuale-> caverna_successiva != NULL && hartornen.posizione_attuale-> imprevisto != crollo && hartornen.posizione_attuale-> tipologia_caverna != uscita){
      printf("Premere: \t 1 per avanzare, \t 2 per abbattere. \n");
      while (scanf("%u" , &scelta )!= 1 || scelta >2 || scelta <1) {
        printf("per favore digita 1 o 2 \n");
        while (getchar ()!='\n');
                                                       }
   switch (scelta) {
     case 1:
     avanza(&hartornen);

     if(hartornen.posizione_attuale-> imprevisto == crollo){
       printf("C'è stato un crollo, non puoi avanzare\n");
       sleep(3);
       printf("consumi energia per liberarti e avanzare \n");// se avessi dovuto aggiungere la funzione aggira avrei consumato 4 ENERGIA
       // poniamo caso -1 per accidentata, -1 per avanza, -1 per liberarsi e -1 per aggirare si perderebbe sempre
       // si è preferito lasciare il serbatoio energia di 4 unità per una maggiore "suspense" nella scelta dei serbatoi
       sleep(3);
       hartornen.serbatoio_melassa[energia]--;//1 unità energia per liberarsi dalle macerie, ciononostante la scavatrice avanza
       ordinalita_hartornen++;
                                       }
      else {
        ordinalita_hartornen++;
           }
     break;
     case 2:
     abbatti(&hartornen);
     reset_abbatti(&hartornen);
     numero_abbatti_hartornen++;
     break;
     default:
     break;}

    }
    else if(hartornen.posizione_attuale-> imprevisto == crollo){
      printf ("C'è stato un crollo, puoi solo aggirare, premi 1 per farlo \n");
      while (scanf("%u" , &scelta )!= 1 || scelta <1 || scelta >1 ) {
        printf("per favore digita 1 \n");
        while (getchar ()!='\n');
                                          }
      aggira(&hartornen);
      ordinalita_hartornen ++;
                                                             }//else if
else if(hartornen.posizione_attuale-> caverna_successiva==NULL){
  printf("non ci sono più caverne disponibili aperte è necessario abbattere, premi 1 per farlo \n");
  while (scanf("%u" , &scelta) != 1 || scelta <1 || scelta >1) {
    printf("la scavatrice può abbattere solo con il comando 1 \n");
    while (getchar ()!='\n');
                                      }
abbatti(&hartornen);

numero_abbatti_hartornen ++;

                                                           }//else if
else if(hartornen.posizione_attuale-> tipologia_caverna== uscita){
  printf("sei riuscito a trovare l'uscita, premi 1 per uscire \n");
  while (scanf("%u" , &scelta) != 1 || scelta <1 || scelta >1 ) {
    printf("ora che hai la vittoria in pugno non temporeggiare, fai la tua scelta \n");
    while (getchar ()!='\n');
                                      }
  //vittoria_h=1;
  switch (scelta) {
    case 1:
  uscita_h=1;
  break;
  case 2:
  avanza(&hartornen);
  break;

}

}//chiusura 3 else if (uscita)


}//fine mega else




}// turno hartornen
