#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

//struct que guarda o valor das peças;
typedef struct{
    int Linha[4];
    int Coluna[4];
}peca;


//função que define a peça aleatoriamente. O horário da máquina multiplicado pelos pontos é usado como seed para a função "rand()";
int Aleatorio(int pontuacao);
//função que define quantos pontos vão ser adicionados na pontução de acordo com a quantidade de linhas removidas;
int pontosLinha(int linhas);

//função que desce as linhas apagadas;
void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas);

//função que apaga as linhas completas;
int apagarLinhasCompletas(int matriz[22][12]);

//função que detecta a colisão entre a pedra e as paredes e entre as pedras;
int detectorColisao(char entrada, int aleatorio, int l, int c, peca peca, int matriz[22][12]);

//função que imprime a tela usando ncurses;
void imprimirTela(int matriz[22][12], int pontuacao);

//função que remove a posição antiga das pedras;
void removeLinhas(int i, int j, int l, int c, peca peca, int matriz[22][12]);

//fução que adiciona as pedras nas novas posições;
void adicionaLinhas(int i, int j, int l, int c, peca peca, int matriz[22][12]);
