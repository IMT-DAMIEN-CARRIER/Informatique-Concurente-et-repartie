//
// Created by dcarrier on 26/03/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

void traiterSignal (int signalRecu, siginfo_t* info, void* pasUtileIci)
{
    switch ( signalRecu )
    {
        case SIGUSR1 :
            printf ("Le processus %d receptionne le signal SIGUSR1 envoye par le processus %d\n", getpid(), info->si_pid);
            kill ( info->si_pid , SIGUSR2 );

            break;

        case SIGUSR2 :
            printf ("Le processus %d receptionne le signal SIGUSR2 envoye par le processus %d\n", getpid(), info->si_pid);
            printf ("Le processus %d s'arrête!!\n", getpid() );

            exit (0);
    }
}

int main (int argc, char** argv)
{
    /***************************************************/
    /* Création de la structure pour gérer les signaux */
    /***************************************************/

    struct sigaction prepaSignal;
    prepaSignal.sa_sigaction=&traiterSignal;
    prepaSignal.sa_flags=SA_SIGINFO | SA_RESTART;  // Ne pas oublier l'instruction wait du père

    sigemptyset(&prepaSignal.sa_mask);

    int pid = fork();

    switch (pid)
    {
        case -1 :
            perror ("Erreur dans la creation du processus fils.\n");
            exit (-2);

        case  0 :
            printf ("Fils : PID=%d\n", getpid());
            sigaction (SIGUSR2, &prepaSignal, NULL);
            kill ( getppid(), SIGUSR1 );

            while (1)
                pause ();

        default :
            printf ("Pere : PID=%d\n", getpid());
            sigaction (SIGUSR1, &prepaSignal, NULL);
            wait (NULL);
            printf ("Le père constate l'arrêt du fils\n");
            printf ("Le père s'arrête!!\n");
    }

    return 0;
}