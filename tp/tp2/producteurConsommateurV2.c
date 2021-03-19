//
// Created by dcarrier on 19/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

int main (int argc, char* argv[])
{
    pthread_t t;

    pthread_create(&t, null, (void* (*)()), adrMem);

    pthread_join(t, null);
}