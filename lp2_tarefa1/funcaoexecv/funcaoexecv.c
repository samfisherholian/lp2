#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TRUE 1

int main(){

    int *status;

    char caminho[100];
    char comando[100];

    int indice = 0;

     // para executar com exemplo um programa abaixo   
     //execute[] = {"/bin/ls" , "-l", NULL};
     char *execute[]={caminho, comando, NULL};
     
    while(TRUE){

        scanf("%s", caminho);
        scanf("%s", comando);

        if (fork() != 0){

            waitpid(-1, status, 0);

        }else{

            execv(execute[0], execute);

        }
            exit(0);
 
    }

    return 0;
}
