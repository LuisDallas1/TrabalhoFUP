#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auxiliar2.h"



int main(){


time time;
time.numjogadores = 0;
time.jogadores = NULL;


printf("Insira o nome do seu time\n");
scanf("%[^\n]", time.nometime);
system("cls");

while (1)
    { 
    int seletor;

    printf("%s\n", time.nometime);

    printf("Digite 1 se voce deseja adicionar jogador.\n");//certo
    printf("Digite 2 se voce deseja escolher formacao.\n"); // 244, 343, 334, 154, 
    printf("Digite 3 se voce deseja modificar escalacao.\n");
    printf("Digite 4 para visualizar jogadores.\n");

    printf("Digite 5 se voce deseja sair.\n");

    scanf("%d", &seletor);

    system("cls");

    switch (seletor){
    case 1:

        if (adicionarjogador(&time)){
            system("cls");
        }
        break;

    case 2:

        selecionarFormacao(&time);
        break;

    case 3:

        break;

    case 4:

        break;

    case 5:

        printf("Saindo...\n");
        free(time.jogadores);
        return 0;

    }
}

    return 0;
}
