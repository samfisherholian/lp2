//autor: Tiago Silva da Costa.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//possui 21 threads, porque eu uso 1 thread para o carro ou seja 20 para pessoas e 1 para o carro
#define NUMTHREADS 21

int volta;

int number = 1;

int next = 1;

int ticket[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int contador_de_pessoas;

void* funcao(void* p){

    long n = (long) p;

    while(1){

        // responsavel para dar as voltas no carrinho
        if (n == 0) {

            printf("aguardando...\n");

            sleep(5);

            printf("fazendo a volta com %i pessoas\n", contador_de_pessoas);

            sleep(rand() % 4);

            volta++;

            printf("volta #%i completada\n", volta);

            printf("pessoas saindo...\n");

            printf("-=-=-=--=-=-=-=-=-\n");    

            sleep(2);

            contador_de_pessoas = 0;

        }

        ticket[n] = __sync_fetch_and_add(&number, 1);

        while(ticket[n] != next);

        // responsavel por delimitar a quantidade de pessoas no carrinho
        if(contador_de_pessoas < 5 && volta < 10){
            
            __sync_fetch_and_add(&contador_de_pessoas, 1);

            printf("pessoa #%ld entrando no carrinho\n", n);

            sleep(1);

        }

        next++;

        // se o numero de voltas for igual a 10 então encerra o programa
        if(volta == 10){

          printf("o parque fechou\n");
          exit(0);

        }

    }

}

int main(){

    int i;

    pthread_t pessoas[NUMTHREADS];

    pthread_t carrinho;

    volta = 0;

    contador_de_pessoas = 0;

    // thread carrinho
    pthread_create(&carrinho, NULL, funcao, (void*) 0);

    // cria as 20 threads pessoas.
    for(i = 1; i < NUMTHREADS; i++){

        pthread_create(&pessoas[i], NULL, funcao, (void*) i);

    }    

    //bloquea a thread main para que as demais threads possam executar as suas tarefas.
    while (1);

    return 0;

}
