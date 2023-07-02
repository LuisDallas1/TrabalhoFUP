typedef struct
{
    char nome[100];
    int numero;
    char tipo;

}jogador;

typedef struct {
    char nometime[100];
    jogador* jogadores;
    int numjogadores;
    int formacao[2][3];
    jogador* titulares;
    int numtitulares;
}time;

int verificarnumeroexistente(time* time, int numero);

int adicionarjogador(time* time);

int visualizarjogadores(time* time);

int removerjogador(time* time);

void selecionartitulares(time* time);

void removertitular(time* time);
