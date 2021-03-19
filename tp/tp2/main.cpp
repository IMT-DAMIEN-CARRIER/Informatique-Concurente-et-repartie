#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <thread>
#include <semaphore.h>
#include <iostream>
using namespace std;

// Declaration des variables necessaire a la creation des semaphores et du mutex
sem_t mutex, emptySlot, filledSlot;
char* p_char;
// id de la mémoire partagée
int shmid;


/* ******************************* */
/*    Déclaration des fonctions    */
/* ******************************* */

void producteur();
void consommateur();

/* ******************************* */


int main(void)
{
    sem_init(&mutex,1,1); // Initialisation du mutex qui permet de poser des vérous
    sem_init(&emptySlot,1,1); // Initialisation du nombre de slots à remplir
    sem_init(&filledSlot,1,0); // Initialisation du nombre de slots remplis

    // Initialisation de la mémoire partagée et récupération de l'ID
    shmid = shmget(IPC_PRIVATE,sizeof(char),0600);
    
    if (shmid == -1) perror("Erreur lors de la création de la mémoire partagée");
    // On récupère l'addresse mémoire correspondante
    p_char = (char *) shmat(shmid, NULL, 0);
    if (p_char == (void *) -1) perror("Erreur lors de la récupération de la mémoire partagée");

    // On lance les threads du producteur et du consommateur
    thread producer(producteur);
    thread consumer(consommateur);

    // On attend le retour des 2 threads
    producer.join();
    consumer.join();

    cout << "Destruction des sémaphores" << endl;
    sem_destroy(&emptySlot);
    sem_destroy(&filledSlot);
    sem_destroy(&mutex);

    return 0;
}

/* **************************** */
/* Implémentation des fonctions */
/* **************************** */

/*
    @brief Producteur qui envoie la chaine "Hello World" au consommateur
*/
void producteur()
{
    char phrase[] = "Hello World";
    cout << "Lancement du producteur, PID : " << getpid() << endl;
    
    sleep(1);

    for(int i = 0; i < (sizeof(phrase) / sizeof(char)); ++i)
    {
        sem_wait(&emptySlot);
        sem_wait(&mutex); // On attent que la mémoire partagée soit accessible

        *p_char = phrase[i]; // je met le message dans le tampon
        
        //cout << "Le producteur a inséré le caractère " << phrase[i] << " dans la mémoire partagée." << endl;

        if (sem_post(&mutex) == -1) perror("Erreur lors du post"); // On notifie que la mémoire partagée est accessible
        if (sem_post(&filledSlot) == -1) perror("Erreur lors du post");
    }
}

/*
    @brief Consommateur qui affiche ce que le producteur lui envoie
*/
void consommateur()
{
    cout << "Lancement du consomateur, PID : " << getpid() << endl;
    do{
        sem_wait(&filledSlot);
        sem_wait(&mutex);

        cout << "Réception du caractère " << *p_char << " par le consomateur." << endl;

        if (sem_post(&emptySlot) == -1) perror("Erreur lors du post");
        if (sem_post(&mutex) == -1) perror("Erreur lors du post");

    } while (*p_char != '\0');
}

/* **************************** */