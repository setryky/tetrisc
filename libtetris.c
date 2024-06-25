#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

//struct que guarda o valor das peças;
typedef struct{
    int Linha[4];
    int Coluna[4];
}peca;


//função que define a peça aleatoriamente. O horário da máquina é usado como seed para a função "rand()";
int Aleatorio(){
    time_t tempoAtual;
    time(&tempoAtual);
    srand(tempoAtual);
    return rand() % 7;
}

//função que define quantos pontos vão ser adicionados na pontução de acordo com a quantidade de linhas removidas;
int pontosLinha(int linhas)
{
    int pontuacao = 0;
    if(linhas==1) pontuacao += 100;
    else if(linhas==2) pontuacao += 300;
    else if(linhas==3) pontuacao += 500;
    else if(linhas==4) pontuacao += 800;
    return pontuacao;
}

//função que apaga as linhas completas;
int apagarLinhasCompletas(int matriz[22][12]) {
    int i, j, g;
    int linhasApagadas = 0;
    for(i = 0; i < 22; i++) {
        g = 0;
        for(j = 1; j < 12; j++) if(matriz[i][j] == 1) g++;

        if(g == 10){
            for(j = 0; j < 12; j++) matriz[i][j] = 0;
            linhasApagadas++;
        }
    }
    return linhasApagadas;
}

//função que detecta a colisão entre a pedra e as paredes e entre as pedras;
int detectorColisao(char entrada, int aleatorio, int l, int c, peca peca, int matriz[22][12]) {
    for(int k = 0; k < 4; k++){
        int i = l + peca.Linha[k];
        int j = c + peca.Coluna[k];
        if((i == 20 || entrada == 'd' && j == 10 || entrada == 'a' && j == 1)) return 0;
    }
    return 1;
}

