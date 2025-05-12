#include <cstdio>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <MMSystem.h>

/* Definiamo l'intervallo di numeri in base al livello
                    /1 Livello/     /2 Livello/   /3 Livello/   /4 Livello*/
// Definizione degli intervalli di numeri per ogni livello del gioco
int livelloInt[12] = {7, 10, 25, 50, 100, 150, 200, 300, 400, 1000, 2000, 4000};

// Indica il numero del livello a cui si e' arrivati
int numLivello = 0;

//----------------SEZIONE PROTOTIPI----------------//
// Dichiarazione dei prototipi delle funzioni
int sceltaLivello();
int maxTentativi();
int genera_numero();
bool get_tentativo(int numR, int numTentativi);
int verifica_tentativo(int numIndovinato, int numR);
void regole();
void menu();
//------------------------------------------------//

//--------------FUNZIONE PRINCIPALE--------------//
// Funzione principale del programma
int main()
{
    // Dichiarazione delle variabili locali
    int numR /*Numero generato randomicamente*/, tentativo /*Numero di tentativi max.*/, opzione /*Prende in input l'opzione scelta nel menu*/, opzDiff; /*Prende in input l'opzione scelta della difficoltà nel menu*/
    bool isIndovinato;      // Variabile per fermare l'esecuzione del livello se il numero inserito è uguale a quello generato

    // Ciclo per il menu principale
    do
    {
        menu(); // Visualizza il menu

        printf("\nInserisci l'opzione: ");
        scanf("%d", &opzione);

        // Se l'opzione scelta e' 2, mostra le regole del gioco
        if (opzione == 2)
        {
            regole();
        }

        // Se l'opzione scelta non e' ne' 1 ne' 2, mostra un messaggio di errore
        if (opzione != 1 && opzione != 2)
        {
            system("cls");
            printf("----------------------------------\n");
            printf("|Scelta non valida. Riprovare.    |\n");
            printf("----------------------------------\n");
            
            system("pause");
        }

    } while (opzione != 1); // Ripeti finché l'opzione scelta non e' 1 (Inizia a giocare)

    // Ottieni l'opzione scelta per la difficolta'� del gioco
    opzDiff = sceltaLivello();

    // Ciclo per ogni livello del gioco
    do
    {
        // Pulisce lo schermo e visualizza il numero del livello corrente
        system("cls");
        printf("--------------\n");
        printf("|Livello n'%d:|\n", numLivello + 1);
        printf("--------------\n");

        // Genera il numero casuale per il livello corrente
        numR = genera_numero();
        // Ottiene il numero massimo di tentativi per il livello corrente
        tentativo = maxTentativi();
        printf("\n");
        printf("--------------\n");
        printf("|Tentativi: %d|\n", tentativo);
        printf("--------------\n");

        // Ottiene il tentativo dell'utente e controlla se e' corretto
        isIndovinato = get_tentativo(numR, tentativo);

        numLivello++; // Incrementa il numero del livello

    } while (isIndovinato != false && numLivello <= opzDiff); // Continua finché il numero non e' stato indovinato o non sono stati superati tutti i livelli

    // Se il numero e' stato indovinato, mostra un messaggio di vittoria
    if (isIndovinato)
    {
        system("cls");
        system("color 2F");
        printf("-------Gioco INDOVINA NUMERO-------");
        printf("\n|Complimenti hai finito il gioco! |");
        printf("\n-----------------------------------");
        printf("\n");
        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
        system("pause");
        system("color 0F");
    }
    // Altrimenti, mostra un messaggio di sconfitta
    else
    {
        system("cls");
        system("color 4F");
        printf("--------------------------------------------------");
        printf("\n|                                                |");
        printf("\n|                                                |");
        printf("\n|                                                |");
        printf("\n|                   HAI PERSO!                   |");
        printf("\n|                                                |");
        printf("\n|                                                |");
        printf("\n|                                                |");
        printf("\n--------------------------------------------------");
        PlaySound(TEXT("gameover.wav"), NULL, SND_SYNC);
        system("pause");
        system("color 0F");
    }

    return 0;
}

//--------------FUNZIONI SECONDARIE--------------//

// Mostra il menu principale del gioco
void menu()
{
    system("cls");
    printf("-----Gioco INDOVINA NUMERO-----");
    printf("\n|1. Inizia a giocare          |");
    printf("\n|2. Leggi le regole del gioco |");
    printf("\n-------------------------------");
    printf("\n");
}

// Mostra le regole del gioco
void regole()
{
    system("cls");
    printf("---------------------Gioco INDOVINA NUMERO - Le regole --------------------- ");
    printf("\n|Per vincere basta indovinare il numero generato casualmente.              |");
    printf("\n|Avrai un numero massimo di tentativi con i quali indovinare il numero!    |\n");
    printf("---------------------------------------------------------------------------- ");
    system("pause");
}

// Permette all'utente di scegliere la difficoltà del gioco
int sceltaLivello()
{
    int sceltaEff; // Scelta effettuata dall'utente
    system("cls");
    printf("---------SCEGLI IL LIVELLO---------");
    printf("\n|1. Facile                        |");
    printf("\n|2. Normale                       |");
    printf("\n|3. Medio                         |");
    printf("\n|4. Difficile                     |");
    printf("\n-----------------------------------");
    printf("\n-Inserire la scelta: ");
    scanf("%d", &sceltaEff);

    // Imposta il numero effettivo di livelli in base alla scelta dell'utente
    switch (sceltaEff)
    {
    case 1:
        sceltaEff = 2;
        break;
    case 2:
        sceltaEff = 5;
        break;
    case 3:
        sceltaEff = 8;
        break;
    case 4:
        sceltaEff = 11;
        break;
    default:
        // Se la scelta non e' valida, mostra un messaggio di errore e richiede la scelta
        system("cls");
        printf("----------------------------------\n");
        printf("|Scelta non valida. Riprovare.    |\n");
        printf("----------------------------------\n");
        system("pause");

        // Richiede nuovamente la scelta richiamando la funzione
        return sceltaLivello();
    }

    return sceltaEff;
}

// Genera un numero casuale nell'intervallo corretto per il livello corrente
int genera_numero()
{
    int numR;
    int intervallo = livelloInt[numLivello];
    srand(time(NULL));
    numR = rand() % intervallo + 1;
    return numR;
}

// Calcola il numero massimo di tentativi per il livello corrente
int maxTentativi()
{
    double i = 0, intervallo;
    do
    {
        i++;
        intervallo = pow(2, i);

    } while (livelloInt[numLivello] > intervallo);

    return i;
}

// Ottiene il tentativo dell'utente e verifica se e' corretto
bool get_tentativo(int numR, int numTentativi)
{
    int numIndovinato;
    int isGiusto;
    do
    {
        printf("-------------------------------------\n");
        printf("Indovina il numero casuale da 1 a %d: ", livelloInt[numLivello]);
        scanf("%d", &numIndovinato);

        isGiusto = verifica_tentativo(numIndovinato, numR);

        if (isGiusto == 0)
        {
            system("cls");
            system("color 2F");
            printf("------------------------------\n");
            printf("|  HAI INDOVINATO IL NUMERO  |\n");
            printf("------------------------------\n");
            // Stampa il messaggio di indovinato
            system("pause");
            system("color 0F");
            return true;
        }
        else if (isGiusto == 1)
        {
            printf("\n");
            printf("||Il numero e' piu' piccolo||\n");
            // Il numero inserito e' maggiore
        }
        else if (isGiusto == 2)
        {
            printf("\n");
            printf("||Il numero e' piu' grande||\n");
            // Il numero inserito e' minore
        }

        numTentativi--; // Decrementa il numero di tentativi dopo aver verificato la condizione del ciclo

    } while (numTentativi > 0); // Verifica il numero di tentativi dopo averlo decrementato

    return false;
}

// Verifica se il tentativo dell'utente e' corretto rispetto al numero generato
int verifica_tentativo(int numIndovinato, int numR)
{
    if (numIndovinato == numR)
    {
        return 0; // Ritorna 0 se il numero e' corretto
    }
    else if (numIndovinato > numR)
    {
        return 1; // Ritorna 1 se il numero inserito e' maggiore
    }
    else if (numIndovinato < numR)
    {
        return 2; // Ritorna 2 se il numero inserito e' minore
    }
}
