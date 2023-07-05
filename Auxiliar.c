#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Auxiliar2.h"

int adicionarjogador(time* time) {
    jogador novojogador;
    char chave1;

    printf("Digite o nome do jogador: ");
    scanf(" %[^\n]", novojogador.nome);

    printf("Digite o numero da camisa: ");
    scanf("%d", &novojogador.numero);

    for (int i = 0; i < time->numtitulares; i++) {
        if (time->titulares[i].numero == novojogador.numero) {
            printf("Esse numero ja esta na lista de titulares. O jogador nao pode ser adicionado.\n");
            return 0;
        }
    }

    while (verificarnumeroexistente(time, novojogador.numero)) {
        printf("Esse numero ja foi usado! Digite novamente o numero do jogador.\n");
        scanf("%d", &novojogador.numero);
    }

    time->jogadores = realloc(time->jogadores, (time->numjogadores + 1) * sizeof(jogador));
    time->jogadores[time->numjogadores] = novojogador;
    time->numjogadores++;

    system("cls");

    printf("Jogador adicionado com sucesso.\n");


    if (time->numjogadores < 15) {
        printf("Voce deseja adicionar outro jogador? [S/N]\n");
        scanf(" %c", &chave1);

        system("cls");

        if (chave1 == 'S' || chave1 == 's') {
            adicionarjogador(time);
        }
    }

    return 0;
}

int visualizarjogadores(time* time) {
    system("cls");
    printf("Jogadores do time:\n");

    printf("Titulares:\n");
    for (int i = 0; i < time->numtitulares; i++) {
        const jogador* jogador = &(time->titulares[i]);
        printf("Nome: %s\n", jogador->nome);
        printf("Numero da camisa: %d\n", jogador->numero);
        printf("-------------------------\n");
    }

    printf("\nReservas:\n");
    for (int i = 0; i < time->numjogadores; i++) {
        const jogador* jogador = &(time->jogadores[i]);

        int jogadorReserva = 1;
        for (int j = 0; j < time->numtitulares; j++) {
            if (time->titulares[j].numero == jogador->numero) {
                jogadorReserva = 0;
                break;
            }
        }

        if (jogadorReserva) {
            printf("Nome: %s\n", jogador->nome);
            printf("Numero da camisa: %d\n", jogador->numero);
            printf("-------------------------\n");
        }
    }

    printf("Digite algo se deseja retornar ao menu.\n");
    scanf("%*c");
    getchar();

    system("cls");
    return 0;
}

int verificarnumeroexistente(time* time, int numero) {

    for (int i = 0; i < time->numjogadores; i++) {
        const jogador* jogador = &(time->jogadores[i]);
        if (jogador->numero == numero) {
            return 1;
        }
    }
    return 0;
}

int removerjogador(time* time) {
    int numero;
    int i;

    printf("Jogadores disponiveis:\n");
    for (i = 0; i < time->numjogadores; i++) {
        printf("Nome: %s\n", time->jogadores[i].nome);
        printf("Numero da camisa: %d\n", time->jogadores[i].numero);
        printf("-------------------------\n");
    }

    printf("Digite o numero da camisa do jogador que deseja remover: ");
    scanf("%d", &numero);
    system("cls");

    for (i = 0; i < time->numjogadores; i++) {
        if (time->jogadores[i].numero == numero) {
            printf("Tem certeza que deseja remover o jogador %s (camisa %d)? [S/N]\n", time->jogadores[i].nome, time->jogadores[i].numero);

            char chave, chave1;
            scanf(" %c", &chave);

            if (chave == 'S' || chave == 's') {
                for (int j = i; j < time->numjogadores - 1; j++) {
                    time->jogadores[j] = time->jogadores[j + 1];
                }

                time->jogadores = realloc(time->jogadores, (time->numjogadores - 1) * sizeof(jogador));
                time->numjogadores--;
                system("cls");
                printf("Jogador removido com sucesso.\n");

                // Verificar se o jogador removido era titular
                for (int k = 0; k < time->numtitulares; k++) {
                    if (time->titulares[k].numero == numero) {
                        // Remover o jogador também da lista de titulares
                        for (int l = k; l < time->numtitulares - 1; l++) {
                            time->titulares[l] = time->titulares[l + 1];
                        }
                        time->numtitulares--;
                        break;
                    }
                }
            } else {
                system("cls");
                printf("Jogador nao removido.\n");
            }

            if (time->numjogadores == 0) {
                system("cls");
                printf("Nao ha jogadores disponiveis para remover.\n");
                return 0;
            } else {
                printf("Voce deseja remover outro jogador? [S/N]\n");
                scanf(" %c", &chave1);
                system("cls");

                if (chave1 == 'S' || chave1 == 's') {
                    removerjogador(time);
                }
            }
            return 0;
        }
    }

    printf("Jogador nao encontrado.\n");
    return 0;
}

void selecionartitulares(time* time) {
    if (time->numjogadores == 0) {
        printf("Nenhum jogador para adicionar.\n");
        printf("Digite algo para retornar ao menu.\n");
        scanf("%*c");
        getchar();
        system("cls");
        gerenciartitulares(time);
        return;
    }

    time->titulares = malloc(6 * sizeof(jogador));
    time->numtitulares = 0;
    printf("Selecione os jogadores titulares:\n");
    printf("Digite o numero do jogador para adiciona-lo como titular.\n");
    printf("Digite 0 para encerrar a selecao de titulares.\n");

    while (1) {
        int jogadoresDisponiveis = 0;

        printf("Jogadores disponiveis:\n");

        for (int i = 0; i < time->numjogadores; i++) {
            const jogador* jogador = &(time->jogadores[i]);
            int jogadorDisponivel = 1;

            for (int j = 0; j < time->numtitulares; j++) {
                if (time->titulares[j].numero == jogador->numero) {
                    jogadorDisponivel = 0;
                    break;
                }
            }

            if (jogadorDisponivel) {
                jogadoresDisponiveis = 1;
                printf("Nome: %s\n", jogador->nome);
                printf("Numero da camisa: %d\n", jogador->numero);
                printf("-------------------------\n");
            }
        }

        if (!jogadoresDisponiveis) {
            printf("Nenhum outro jogador disponivel. (Digite algo para voltar ao menu)\n");
            scanf("%*c");
            getchar();
            system("cls");
            gerenciartitulares(time);
            return;
        }

        int numero;
        printf("Digite o numero do jogador: ");
        scanf("%d", &numero);

        if (numero == 0) {
            break;
        }

        int jogadorEncontrado = 0;
        int indiceJogador = -1;

        for (int i = 0; i < time->numjogadores; i++) {
            if (time->jogadores[i].numero == numero) {
                jogadorEncontrado = 1;
                indiceJogador = i;
                break;
            }
        }

        if (!jogadorEncontrado) {
            printf("Jogador nao encontrado.\n");
            scanf("%*c");
            getchar();
            system("cls");
            gerenciartitulares(time);
            return;
        }

        int titularEncontrado = 0;
        for (int j = 0; j < time->numtitulares; j++) {
            if (time->titulares[j].numero == numero) {
                titularEncontrado = 1;
                break;
            }
        }

        if (titularEncontrado) {
            printf("Jogador de numero %d ja adicionado como titular.\n", numero);
        } else {
            if (time->numtitulares < 6) {
                jogador jogadorSelecionado = time->jogadores[indiceJogador];

                time->titulares[time->numtitulares] = jogadorSelecionado;
                time->numtitulares++;

                for (int i = indiceJogador; i < time->numjogadores - 1; i++) {
                    time->jogadores[i] = time->jogadores[i + 1];
                }
                time->numjogadores--;

                printf("Jogador numero %d adicionado como titular.\n", numero);
            } else {
                system("cls");
                printf("Limite de jogadores titulares atingido.\n");
                scanf("%*c");
                getchar();
                system("cls");
                gerenciartitulares(time);
                return;
            }
        }

        printf("Deseja adicionar outro jogador titular? (S/N): ");
        char resposta;
        scanf(" %c", &resposta);
        system("cls");
        if (resposta == 'N' || resposta == 'n') {
            break;
        }
    }
}

void substituirtitular(time* time) {

    if (time->numtitulares == 0 || time->numjogadores == 0) {
        printf("Nenhum jogador para trocar.\n");
        printf("Digite algo para retornar ao menu.\n");
        scanf("%*c");
        getchar();
        system("cls");
        gerenciartitulares(time);
        return;
    }

    printf("Jogadores titulares atuais:\n");
    for (int i = 0; i < time->numtitulares; i++) {
        printf("Nome: %s\n", time->titulares[i].nome);
        printf("Numero da camisa: %d\n", time->titulares[i].numero);
        printf("-------------------------\n");
    }

    int numTitular;
    printf("Digite o numero do jogador titular que deseja substituir: ");
    scanf("%d", &numTitular);

    int indiceTitular = -1;
    for (int i = 0; i < time->numtitulares; i++) {
        if (time->titulares[i].numero == numTitular) {
            indiceTitular = i;
            break;
        }
    }

    if (indiceTitular == -1) {
        printf("Jogador titular de numero %d nao encontrado.\n", numTitular);
        printf("Digite algo para retornar ao menu.\n");
        scanf("%*c");
        getchar();
        system("cls");
        gerenciartitulares(time);
        return;
    }

    printf("\nJogadores reservas disponiveis:\n");
    for (int i = 0; i < time->numjogadores; i++) {
        printf("Nome: %s\n", time->jogadores[i].nome);
        printf("Numero da camisa: %d\n", time->jogadores[i].numero);
        printf("-------------------------\n");
    }

    int numReserva;
    printf("Digite o numero do jogador reserva que deseja adicionar: ");
    scanf("%d", &numReserva);

    int indiceReserva = -1;
    for (int i = 0; i < time->numjogadores; i++) {
        if (time->jogadores[i].numero == numReserva) {
            indiceReserva = i;
            break;
        }
    }

    if (indiceReserva == -1) {
        printf("Jogador reserva de numero %d nao encontrado.\n", numReserva);
        printf("Digite algo para retornar ao menu.\n");
        scanf("%*c");
        getchar();
        system("cls");
        gerenciartitulares(time);
        return;
    }

    jogador jogadorTitular = time->titulares[indiceTitular];
    jogador jogadorReserva = time->jogadores[indiceReserva];

    time->titulares[indiceTitular] = jogadorReserva;
    time->jogadores[indiceReserva] = jogadorTitular;

    printf("Jogador titular '%s' substituido pelo jogador reserva '%s'.\n", jogadorTitular.nome, jogadorReserva.nome);

    printf("Digite algo para retornar ao menu.\n");
    scanf("%*c");
    getchar();
    system("cls");
    gerenciartitulares(time);
}

void gerenciartitulares(time* time) { 
    printf("Selecione a acao desejada:\n");
    printf("[1] Adicionar jogador titular\n");
    printf("[2] Substituir jogador titular\n");
    printf("[0] Voltar ao menu principal\n");

    int opcao;
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            system("cls");
            selecionartitulares(time);
            break;
        case 2:
            system("cls");
            substituirtitular(time);
            break;
        case 0:
            system("cls");
            printf("Voltando ao menu principal.\n");
            break;
        default:
            system("cls");
            printf("Opcao invalida.\n");
            break;
    }

    system("cls");
}

void imprimirtabela(time* time) {

    printf("Time: %s\n", time->nometime);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            if (index < time->numtitulares) {
                jogador jogadorAtual = time->titulares[index];

                if (strlen(jogadorAtual.nome) > 10) {
                    jogadorAtual.nome[10] = '\0';
                }

                printf("%-10s   | ", jogadorAtual.nome);
            } else {
                printf("              | ");
            }
        }
        printf("\n");
        for (int j = 0; j < 3; j++) {
            int index = i * 3 + j;
            if (index < time->numtitulares) {
                jogador jogadorAtual = time->titulares[index];
                printf("%-10d   | ", jogadorAtual.numero);
            } else {
                printf("              | ");
            }
        }
        printf("\n");
    }
    printf("Digite algo para voltar ao menu.\n");
    scanf("%*c");
    getchar();
}
