#ifndef _LIBTETRIS_H
#define _LIBTETRIS_H

#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct{
    int Linha[4];
    int Coluna[4];
	int numrotacao;
	int rotacaolimite;
}PECA;

void declararPecas(PECA peca[], PECA pecaRodada[], PECA copia[]);

void inicializarNcurses();

int Aleatorio(int pontuacao);

int pontosLinha(int linhasApagadas);

void transformaEmFixa(int matriz[22][12], int valorAleatorio);

void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas);

int apagarLinhasCompletas(int matriz[22][12]);

int detectorColisao(char entrada, int linha, int coluna, PECA peca, int matriz[22][12]);

void imprimirTela(int matriz[22][12], int pontuacao);

int gameOver(int matriz[22][12], int pontuacao);

void removeLinhas(int novaLinha, int novaColuna, int linha, int coluna, PECA peca, int matriz[22][12]);

void adicionaLinhas(int novaLinha, int novaColuna, int linha, int coluna, PECA peca, int matriz[22][12]);

void voltaOriginal(PECA *peca, PECA copia);

void rodaLinhas(PECA *peca, PECA pecaRodada, PECA copia, int *rotacoes);

#endif