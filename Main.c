#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auxiliar2.h"



int main(){


time time;
time.numjogadores = 0;
time.jogadores = NULL;
time.numtitulares = 0;

printf("Bem vindo ao Volei Lineup!\nOnde voce montara o seu propio time de volei com os jogadores que voce quiser!\n");
printf("Primeiramente, insira o nome do seu time:\n");
scanf("%[^\n]", time.nometime);
system("cls");

while (1)
    { 
    int seletor;

    printf("Bem vindo ao menu!\n");
    printf("Seu time: %s\n\n", time.nometime);

    printf("[1] Adcionar jogador.\n");
    printf("[2] Remover jogador.\n");
    printf("[3] Gerenciar titulares.\n");
    printf("[4] Para visualizar jogadores.\n");
    printf("[5] Para criar planilha de jogadores.\n");
    printf("[0] Sair.\n");

    scanf("%d", &seletor);

    system("cls");

    switch (seletor){
    case 1:

        if (adicionarjogador(&time)){
            system("cls");
        }
        break;

    case 2:

        removerjogador(&time);
        break;

    case 3:

        gerenciartitulares(&time);
        break;
  
    case 4:

        visualizarjogadores(&time);
        break;

    case 5:

        imprimirtabela(&time);
        system("cls");
        break;

    case 0:

        printf("Saindo...\n");
        free(time.jogadores);
        return 0;

    }
}

    return 0;
}
