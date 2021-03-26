//
// Created by dcarrier on 26/03/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//void fct (int signalRecu, siginfo_t* info, void* pasUtileIci)
//{
//    printf("Je receptionne le signal %d envoye par le processus %d\n",
//           signalRecu, info->si_pid); fflush(stdout);
//}
//
//int main (int argc, char** argv)
//{
//    struct sigaction prepaSignal;
//
//    prepaSignal.sa_sigaction=&fct;
//    prepaSignal.sa_flags=SA_SIGINFO;
//    sigemptyset(&prepaSignal.sa_mask);
//
//    sigaction(SIGINT, &prepaSignal, NULL);
//    sigaction(SIGQUIT,&prepaSignal, NULL);
//    sigaction(SIGTERM,&prepaSignal, NULL);
//
//    while (1);
//
//    return 0;
//}
