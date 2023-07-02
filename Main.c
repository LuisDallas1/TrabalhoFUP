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

    printf("[1] se voce deseja adicionar jogador.\n");
    printf("[2] se voce deseja remover jogador.\n");
    printf("[3] se voce deseja adicionar jogadores aos titulares.\n");
    printf("[4] se voce deseja remover jogadores dos titulares.\n");
    printf("[5] para visualizar jogadores.\n");
    printf("[6] se voce deseja gerenciar a formacao.\n");

    printf("Digite 7 se voce deseja sair.\n");

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

        selecionartitulares(&time);
        system("cls");
        break;

    case 4:

        if (time.numtitulares == 0) {
            printf("Nenhum jogador titular encontrado.\n");
            printf("Digite algo para retornar ao menu.\n");
            scanf("%*c");
            getchar();
            system("cls");
        } else {
            removertitular(&time);
        }
        break;

    case 5:

        visualizarjogadores(&time);
        break;

    case 6:

        gerenciarFormacao(&time);
        system("cls");
        break;

    case 7:

        printf("Saindo...\n");
        free(time.jogadores);
        return 0;

    }
}

    return 0;
}
