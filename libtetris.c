#include "libtetris.h"

typedef struct{
    int Linha[4];
    int Coluna[4];
}peca;

int Aleatorio(int pontuacao){
    time_t tempoAtual;
    time(&tempoAtual);
    srand(tempoAtual*pontuacao);
    return rand() % 7;
}

int pontosLinha(int linhas)
{
    int pontuacao = 0;
    if(linhas==1) pontuacao += 100;
    else if(linhas==2) pontuacao += 300;
    else if(linhas==3) pontuacao += 500;
    else if(linhas==4) pontuacao += 800;
    return pontuacao;
}

void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas) {
    for(int l = linhaParou; l > 0; l--)
        for(int c = 1; c < 11; c++) matriz[l][c] = matriz[l - linhasApagadas][c];
    for(int l = linhaParou-linhasApagadas; l > 0; l--)
        for(int c = 1; c < 11; c++) matriz[l][c] = 0;
}

int apagarLinhasCompletas(int matriz[22][12]) {
    int i, j, g, linhasApagadas = 0, primeiraLinha = 0;
    for(i = 20; i > 0; i--) {
        g = 0;
        for(j = 1; j < 11; j++) if(matriz[i][j] == 2) g++;
            if(g == 10){
                if(primeiraLinha == 0) primeiraLinha = i;
                for(j = 1; j < 11; j++) {
                    matriz[i][j] = 0;
                }
                linhasApagadas++;
            }
    }
    if(linhasApagadas > 0) descerLinhas(matriz, primeiraLinha, linhasApagadas);
    return linhasApagadas;
}

int detectorColisao(char entrada, int l, int c, peca peca, int matriz[22][12]){
    for(int k = 0; k < 4; k++){
        int i = l + peca.Linha[k];
        int j = c + peca.Coluna[k];
        if(i == 21 || (entrada == 'd' && j == 10) || (entrada == 'a' && j == 1)) return 0;
    }
    return 1;
}

void imprimirTela(int matriz[22][12], int pontuacao){
    clear();
    for(int li = 0; 22 > li; li++){
        for(int co = 0; 12 > co; co++){
            if(co == 0 || co == 11 || li == 0 || li == 21)  mvprintw(li, co, "@");
            else if(matriz[li][co] == 1) mvprintw(li, co, "#");
            else if(matriz[li][co] == 2) mvprintw(li, co, "$");
            else if(matriz[li][co] == 0) mvprintw(li, co, ".");
            }
        mvprintw(22, 0, "Pontuacao: %d", pontuacao);
        refresh();
        }
}

void removeLinhas(int i, int j, int l, int c, peca peca, int matriz[22][12]){
    for(int k = 0; 4 > k; k++){
        i = l + peca.Linha[k];
        j = c + peca.Coluna[k];
        matriz[i-1][j] = 0;
    }
}

void adicionaLinhas(int i, int j, int l, int c, peca peca, int matriz[22][12]){
    for(int k = 0; 4 > k; k++){
        i = l + peca.Linha[k];
        j = c + peca.Coluna[k];
        matriz[i-1][j] = 1;
    }
}
