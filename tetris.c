#include "libtetris.h"

int main()
{
    int pontuacao = 0, linha = 0, coluna = 0, novaLinha, novaColuna, rotacoes = 0;
    int matriz[22][12] = {0};
    char entrada;
    PECA peca[7], pecaRodada[12], copia[7];
    
    declararPecas(peca, pecaRodada, copia);
    inicializarNcurses();

    for(int valorAleatorio = Aleatorio(pontuacao); TRUE; valorAleatorio = Aleatorio(pontuacao), linha = 0, coluna = 0, rotacoes = 0){
        while(TRUE){
            for (int k = 1; k <= 2; k++)
                for (int i = 4; i <= 6; i++) if(matriz[k][i] >= 2) return gameOver(matriz, pontuacao);

            entrada = getch();
            if(entrada >= 65 && entrada <= 90) entrada += 32;

            if(entrada == 'd' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1){
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                coluna++;
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            }
            else if(entrada == 'a' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1){
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                coluna--;
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            }
            else if(entrada == 's' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1){
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                linha++;
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                pontuacao++;
            }
            else if(entrada == 'w'){
                for(;detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz);){
                    removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                    linha++;
                    adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                    pontuacao += 2;
                }
            }
            else if(entrada == 'r' && valorAleatorio != 4){
				rotacoes++;
				removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                rodaLinhas(&peca[valorAleatorio], pecaRodada[rotacoes + peca[valorAleatorio].numrotacao], copia[valorAleatorio], &rotacoes);
				adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
			}
            else if(entrada != 's' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1){
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                linha++;
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            }
            if(detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 0){ 
                voltaOriginal(&peca[valorAleatorio], copia[valorAleatorio]);
                break;
            }

            pontuacao += pontosLinha(apagarLinhasCompletas(matriz));
            imprimirTela(matriz, pontuacao);

        }
        transformaEmFixa(matriz, valorAleatorio);
    }

    endwin();
    return 0;
}
