#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auxiliar2.h"

int adicionarjogador(time* time) {

    
    jogador jogador;
    char chave, chave1;

    printf("Digite o nome do jogador: ");
    scanf(" %[^\n]", jogador.nome);

    printf("Digite o numero da camisa: ");
    scanf("%d", &jogador.numero);
    while (verificarnumeroexistente(time, jogador.numero))
    {
        printf("Esse numero ja foi usado! Digite novamente o numero do jogador.\n");
        scanf("%d", &jogador.numero);
    }

    printf("Digite o tipo do jogador (A para Atacante, D para Defesa, M para Meio, G para Gol,T para Tecnico): ");
    scanf(" %c", &jogador.tipo);

    while (jogador.tipo != 'A' && jogador.tipo != 'D' && jogador.tipo != 'M' && jogador.tipo != 'G' && jogador.tipo != 'T')
    {
        printf("Tipo invalido! Digite novamente os dados do seu jogador.\n");
        scanf(" %c", &jogador.tipo);
    }

    printf("Tem certeza que deseja adicionar esse jogador?[S/N]\n");
    scanf(" %c", &chave);

    if (chave == 'S' || chave == 's')
    {
        time->jogadores = realloc(time->jogadores, (time->numjogadores + 1) * sizeof(jogador));
        time->jogadores[time->numjogadores] = jogador;
        time->numjogadores++;

        system("cls");

        printf("Jogador adicionado com sucesso.\n");
    }
    else
    {
        printf("Jogador nao adicionado.\n");
    }

    printf("Voce deseja adicionar outro jogador?[S/N]\n");
    scanf(" %c", &chave1);

    system("cls");

    if (chave1 == 'S' || chave1 == 's')
    {
        adicionarjogador(time);
    }
    return 0;
}

int visualizarjogadores(time* time) {
    printf("Jogadores do time:\n");

    for (int i = 0; i < time->numjogadores; i++) {
        const jogador* jogador = &(time->jogadores[i]);
        printf("Nome: %s\n", jogador->nome);
        printf("Numero da camisa: %d\n", jogador->numero);
        switch (jogador->tipo)
        {
        case 'A':
            printf("Posicao do jogador: Atacante\n");
            break;
        
        case 'D':
            printf("Posicao do jogador: Defesa\n");
            break;

        case 'M':
            printf("Posicao do jogador: Meio\n");
            break;

        case 'G':
            printf("Posicao do jogador: Goleiro\n");
            break;

        case 'T':
            printf("Posicao do jogador: Tecnico\n");
            break;
        }
        printf("-------------------------\n");
    }
    printf("Digite algo se deseja retornar ao menu.\n");
    scanf("%*c");

    getchar();

    system("cls");
    return 0;
}

int verificarnumeroexistente(const time* time, int numero) {

    for (int i = 0; i < time->numjogadores; i++) {
        const jogador* jogador = &(time->jogadores[i]);
        if (jogador->numero == numero) {
            return 1; // Número já existe
        }
    }
    return 0; // Número não existe
}

int selecionarFormacao(time* time) {
    int formacao;

    printf("Escolha a formacao:\n");
    printf("1 - 2-4-4\n");
    printf("2 - 3-4-3\n");
    printf("3 - 3-3-4\n");
    printf("4 - 1-5-4\n");

    scanf("%d", &formacao);
    time->formacao = formacao;

    while (formacao != 1 && formacao != 2 && formacao != 3 && formacao != 4)
    {
        printf("Insira um numero valido!\n");
        scanf(" %d", &formacao);
    }
    
    system("cls");

    printf("Voce tem certeza de que deseja manter a formacao selecionada? [S/N] \n");

    char confirmacao;
    scanf(" %c", &confirmacao);


    if (confirmacao == 'S' || confirmacao == 's') {
        system("cls");
        printf("Formacao selecionada com sucesso.\n");
        return 0;
    } else {
        system("cls");
        printf("Formacao descartada. Voltando para o menu.\n");
        time->formacao = 0;
        return 0;
    }
}
