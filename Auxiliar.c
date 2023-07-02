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

    system("cls");

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

    if (time->numjogadores<15)
    {
        printf("Voce deseja adicionar outro jogador?[S/N]\n");
        scanf(" %c", &chave1);

        system("cls");

        if (chave1 == 'S' || chave1 == 's')
        {
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

    printf("Reservas:\n");
    for (int i = 0; i < time->numjogadores; i++) {
        const jogador* jogador = &(time->jogadores[i]);

        // Verifica se o jogador não está na lista de titulares
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
            return 1; // Número já existe
        }
    }
    return 0; // Número não existe
}

int removerjogador(time* time) {
    int numero;
    int i;

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
            } else {
                system("cls");
                printf("Jogador não removido.\n");
            }
            printf("Voce deseja remover outro jogador?[S/N]\n");
            scanf(" %c", &chave1);

            system("cls");

            if (chave1 == 'S' || chave1 == 's')
            {
                removerjogador(time);
            }
            return 0;
        }
    }

    printf("Jogador não encontrado.\n");
    return 0;
}

void selecionartitulares(time* time) {
    if (time->numjogadores == 0) {
        printf("Nenhum jogador adicionado.\n");
        return;
    }

    time->titulares = malloc(15 * sizeof(jogador)); // Aloca memória para a lista de jogadores titulares
    time->numtitulares = 0; // Inicializa o número de jogadores titulares

    printf("Selecione os jogadores titulares:\n");
    printf("Digite o numero do jogador para adiciona-lo como titular.\n");
    printf("Digite 0 para encerrar a selecao de titulares.\n");

    while (1) {
        int jogadoresDisponiveis = 0;

        for (int i = 0; i < time->numjogadores; i++) {
            const jogador* jogador = &(time->jogadores[i]);
            int jogadorDisponivel = 1;

            // Verifica se o jogador já foi selecionado como titular
            for (int j = 0; j < time->numtitulares; j++) {
                if (time->titulares[j].numero == jogador->numero) {
                    jogadorDisponivel = 0;
                    break;
                }
            }

            if (jogadorDisponivel) {
                jogadoresDisponiveis = 1;
                printf("Jogadores disponiveis:\n");
                printf("Nome: %s\n", jogador->nome);
                printf("Numero da camisa: %d\n", jogador->numero);
                printf("-------------------------\n");
            }
        }

        if (!jogadoresDisponiveis) {
            printf("Nenhum outro jogador disponivel. (Digite algo para voltar ao menu)\n");
            scanf("%*c");
            getchar();
            break;
        }

        int numero;
        printf("Digite o numero do jogador: ");
        scanf("%d", &numero);

        if (numero == 0) {
            break; // Encerra a seleção de titulares
        }

        int jogadorEncontrado = 0;
        for (int i = 0; i < time->numjogadores; i++) {
            if (time->jogadores[i].numero == numero) {
                jogadorEncontrado = 1;

                // Verifica se o jogador já foi adicionado como titular
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
                    if (time->numtitulares < 7) {
                        time->titulares[time->numtitulares] = time->jogadores[i];
                        time->numtitulares++;

                        // Remove o jogador do vetor de jogadores disponíveis
                        for (int j = i; j < time->numjogadores - 1; j++) {
                            time->jogadores[j] = time->jogadores[j + 1];
                        }
                        time->numjogadores--;
                        system("cls");
                        printf("Jogador numero %d adicionado como titular.\n", numero);
                    } else {
                        printf("Limite de jogadores titulares atingido.\n");
                        scanf("%*c");
                        getchar();
                        break;
                    }
                }
                break;
            }
        }

        if (!jogadorEncontrado) {
            printf("Jogador nao encontrado.\n");
            scanf("%*c");
            getchar();
            break;
        } else {
            printf("Deseja adicionar outro jogador titular? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);

            if (resposta == 'N' || resposta == 'n') {
                break;
            }
        }
    }
}

void removertitular(time* time) {

    int numero;
    int jogadorEncontrado = 0;
    int indiceJogador = -1;

    while (!jogadorEncontrado) {
        printf("Jogadores titulares atuais:\n");
        for (int i = 0; i < time->numtitulares; i++) {
            printf("Nome: %s\n", time->titulares[i].nome);
            printf("Numero da camisa: %d\n", time->titulares[i].numero);
            printf("-------------------------\n");
        }

        printf("Digite o numero do jogador titular que deseja remover: ");
        scanf("%d", &numero);

        for (int i = 0; i < time->numtitulares; i++) {
            if (time->titulares[i].numero == numero) {
                jogadorEncontrado = 1;
                indiceJogador = i;
                break;
            }
        }

        if (!jogadorEncontrado) {
            printf("Jogador titular de numero %d não encontrado.\n", numero);
        }
    }

    jogador jogadorRemovido = time->titulares[indiceJogador];

    // Desloca os jogadores à esquerda do jogador removido
    for (int i = indiceJogador; i < time->numtitulares - 1; i++) {
        time->titulares[i] = time->titulares[i + 1];
    }

    time->numtitulares--;

    // Insere o jogador removido no vetor de jogadores disponíveis
    time->jogadores[time->numjogadores] = jogadorRemovido;
    time->numjogadores++;

    printf("Jogador '%s' removido dos titulares.\n", jogadorRemovido.nome);

    printf("Deseja continuar removendo jogadores titulares? (S/N): ");
    char resposta;
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
        removertitular(time);
    } else {
        printf("Digite algo para retornar ao menu.\n");
        scanf("%*c");
        getchar();

        system("cls");
    }
}



void gerenciarFormacao(time *time) {
    printf("Formacao:\n");

    // Exibir a formação atual
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (time->formacao[i][j] == 0) {
                printf("%-10s", "-");
            } else {
                int jogadorIndex = time->formacao[i][j] - 1;
                if (jogadorIndex >= 0 && jogadorIndex < time->numtitulares) {
                    printf("%-10s", time->titulares[jogadorIndex].nome);
                } else {
                    printf("%-10s", "-");
                }
            }
        }
        printf("\n");
    }

    printf("\nJogadores Titulares:\n");

    // Exibir os jogadores titulares, incluindo o técnico
    if (time->numtitulares == 0) {
        printf("Nenhum jogador titular encontrado.\n");
    } else {
        for (int i = 0; i < time->numtitulares; i++) {
            if (i == time->numtitulares - 1) {
                printf("%d - %s (Tecnico)\n", i + 1, time->titulares[i].nome);
            } else {
                printf("%d - %s\n", i + 1, time->titulares[i].nome);
            }
        }

        printf("Digite o número do jogador titular que deseja posicionar na formacao (0 para cancelar): ");
        int jogadorSelecionado;
        scanf("%d", &jogadorSelecionado);

        if (jogadorSelecionado < 1 || jogadorSelecionado > time->numtitulares) {
            printf("Jogador titular inválido.\n");
        } else {
            printf("Digite a linha (0 ou 1) onde o jogador titular irá ficar na formacao: ");
            int linha;
            scanf("%d", &linha);

            if (linha < 0 || linha > 1) {
                printf("Linha inválida.\n");
            } else {
                printf("Digite a coluna (0, 1 ou 2) onde o jogador titular irá ficar na formacao: ");
                int coluna;
                scanf("%d", &coluna);

                if (coluna < 0 || coluna > 2) {
                    printf("Coluna inválida.\n");
                } else {
                    if (time->formacao[linha][coluna] != 0) {
                        printf("Posição já ocupada na formação.\n");
                    } else {
                        time->formacao[linha][coluna] = jogadorSelecionado;
                        printf("Jogador titular %s posicionado na formacao.\n", time->titulares[jogadorSelecionado - 1].nome);
                    }
                }
            }
        }
    }

    printf("Digite algo para retornar ao menu.\n");
    scanf("%*c");
    getchar();
}
