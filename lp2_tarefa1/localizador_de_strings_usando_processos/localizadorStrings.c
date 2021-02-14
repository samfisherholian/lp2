#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int checka_string_arquivo(char entrada[], int indice);

int main(){

    char string[11];

    int pid_parent = getpid();

    int i;

    printf("digite uma string de ate 10 caracteres: ");
    scanf("%s",string);


    for (i = 0; i < 5; i++) {

        if (getpid() == pid_parent) {
           
            printf("processo[%i] encontrada no arquivo [%i] \n",i, checka_string_arquivo(string, i));

            fork();
            sleep(2);
            
        } else {

            break;

        }
    }

    sleep(5);

    return 0;
}

int checka_string_arquivo(char entrada[], int indice){

    int soma = 0;

    char entrada2[11];

    FILE *file = NULL;

    if(indice == 0){

        file = fopen("0.txt", "r");

    }

    if(indice == 1){

         file = fopen("1.txt", "r");
    }

    if(indice == 2){

         file = fopen("2.txt", "r");

    }

    if(indice ==  3){

         file = fopen("3.txt", "r");

    }

    if(indice == 4){

         file = fopen("4.txt", "r");

    }

     while ((fscanf(file, "%s", entrada2)) != EOF) {

        if(strcmp(entrada, entrada2) == 0){

            soma++;

        }

    }

        fclose(file);

        return soma;

}
