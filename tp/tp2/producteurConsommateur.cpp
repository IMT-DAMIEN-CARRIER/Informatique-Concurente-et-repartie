//
// Created by dcarrier on 19/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>
using namespace std;

// Declaration des variables necessaire a la creation des semaphores et du mutex
sem_t mutex, vide, plein;
char* p_char;
// id de la mémoire partagée
int shmid;

/* ******************************* */
/*    Déclaration des fonctions    */
/* ******************************* */

void producteur(char[]);
void consommateur();

/* ******************************* */

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage : /producteurConsommateur taille chaine\n");
        printf("Exemple: ./producteurConsommateur 4 Bonjour\n");
        exit(1);
    }

    sem_init(&mutex, 1, 1); // Initialisation du mutex qui permet de poser des vérous
    sem_init(&vide,1 , 1); // Initialisation du nombre de slots à remplir
    sem_init(&plein, 1, 0); // Initialisation du nombre de slots remplis

    // Initialisation de la mémoire partagée et récupération de l'ID
    shmid = shmget(IPC_PRIVATE, sizeof(char), 0600);

    if (shmid == -1) {
        perror("Erreur lors de la création de la mémoire partagée");
    }

    // On récupère l'addresse mémoire correspondante
    p_char = (char *) shmat(shmid, NULL, 0);

    if (p_char == (void *) -1) {
        perror("Erreur lors de la récupération de la mémoire partagée");
    }

    thread producer(producteur, argv[1]);
    thread consumer(consommateur);

    // On attend le retour des 2 threads
    producer.join();
    consumer.join();

    cout << "Destruction des sémaphores" << endl;
    sem_destroy(&vide);
    sem_destroy(&plein);
    sem_destroy(&mutex);

    return 0;
}

/* **************************** */
/* Implémentation des fonctions */
/* **************************** */

void producteur(char phrase[])
{
    cout << "Lancement du producteur, PID : " << getpid() << endl;

    sleep(1);

    for (int i = 0; i < (sizeof(phrase) / sizeof(char)); ++i) {
        sem_wait(&vide);
        sem_wait(&mutex); // On attend que la mémoire partagée soit accessible.

        *p_char = phrase[i]; // On ajoute le message au tampon

        if (sem_post(&mutex) == -1) {
            perror("Erreur lors de l'accès à la mémoire partagée.");
        }

        if (sem_post(&plein) == -1) {
            perror("Erreur lors de l'ajout du message dans le tempon.");
        }
    }
}

void consommateur()
{
    cout << "Lancement du consomateur, PID : " << getpid() << endl;

    do {
        sem_wait(&plein) // plein prend la valeur 0.
        sem_wait(&mutex);

        cout << "Réception du caractère " << *p_char << " par le consomateur." << endl;

        if (sem_post(&vide) == -1) {
            perror("Erreur vide");
        }

        if (sem_post(&mutex) == -1) {
            perror("Erreur lors de l'accès à la mémoire partagée.");
        }
    } while (*p_char != '\0');
}