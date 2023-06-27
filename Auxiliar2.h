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
    int formacao;
}time;

int verificarnumeroexistente(const time* time, int numero);

int adicionarjogador(time* time);

int visualizarjogadores(time* time);

int selecionarFormacao(time* time);
