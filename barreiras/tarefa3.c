#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUMTHREADS 6

pthread_barrier_t minhaBarreira;

int contador;

char String[6];

void * simpleThread(void *p){

    long n = (long) p;

    String[n] = 65 + (char)(rand () % 26);

    printf("sou a thread#%ld vou gerar uma letra = %c\n", n, String[n]);
            
    pthread_barrier_wait(&minhaBarreira);
          
    return NULL;

}

void palindromo(){

     for(int i = 0 ; i < 6; i++){

            printf("%c", String[i]);

        }

        printf("\n");

        int esquerda = 0;

        int direito = strlen(String) - 1;

        while(direito > esquerda){

            if(String[esquerda++] != String[direito--]){

                printf("não eh palindromo\n");

                return;

            }

        }

        printf("eh palindromo\n");

}

int main(){

    int i;

    contador = 0;

    srand(time(NULL));

    pthread_t threads[NUMTHREADS];

    pthread_barrier_init(&minhaBarreira, NULL, NUMTHREADS);

    while(contador < 10){
        
        for(i = 0; i < NUMTHREADS; i++){

            pthread_create(&threads[i], NULL, simpleThread, (void*) i);

            sleep(1);

        }

        palindromo();

        __sync_fetch_and_add(&contador,1);   

    }

    for(i = 0; i < NUMTHREADS; i++){

        pthread_join(threads[i], NULL);

    }

    pthread_barrier_destroy(&minhaBarreira);

    return 0;

}
