#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <sys/queue.h>

typedef struct{
    int Linha[4];
    int Coluna[4];
	int numrotacao;
	int rotacaolimite;
}peca;

int Aleatorio(int pontuacao){
    time_t tempoAtual;
    time(&tempoAtual);
    if(pontuacao == 0) srand(tempoAtual);
    else srand(tempoAtual*pontuacao);
    return rand() % 7;
}

int pontosLinha(int linhasApagadas)
{
    int pontuacao = 0;
    if(linhasApagadas == 1) pontuacao += 100;
    else if(linhasApagadas == 2) pontuacao += 300;
    else if(linhasApagadas == 3) pontuacao += 500;
    else if(linhasApagadas == 4) pontuacao += 800;
    return pontuacao;
}

void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas) {
    for(int linha = linhaParou; linha > 0; linha--)
        for(int coluna = 1; coluna < 11; coluna++) matriz[linha][coluna] = matriz[linha - linhasApagadas][coluna];
    for(int linha = linhaParou-linhasApagadas; linha > 0; linha--)
        for(int coluna = 1; coluna < 11; coluna++) matriz[linha][coluna] = 0;
}

int apagarLinhasCompletas(int matriz[22][12]) {
    int linha, coluna, lugarOcupado, linhasApagadas = 0, primeiraLinha = 0;
    for(linha = 20; linha > 0; linha--) {
        lugarOcupado = 0;
        for(coluna = 1; coluna < 11; coluna++) if(matriz[linha][coluna] == 2) lugarOcupado++;
            if(lugarOcupado == 10){
                if(primeiraLinha == 0) primeiraLinha = linha;
                for(coluna = 1; coluna < 11; coluna++) {
                    matriz[linha][coluna] = 0;
                }
                linhasApagadas++;
            }
    }
    if(linhasApagadas > 0) descerLinhas(matriz, primeiraLinha, linhasApagadas);
    return linhasApagadas;
}

int detectorColisao(char entrada, int linha, int coluna, peca peca, int matriz[22][12]) {
    for(int k = 0; k < 4; k++) {
        int novaLinha = linha + peca.Linha[k];
        int novaColuna = coluna + peca.Coluna[k];
        if(novaLinha == 21 || (matriz[novaLinha - 1][novaColuna] == 1 && matriz[novaLinha][novaColuna] == 2)) return 0;
        else if((entrada == 'a' && novaColuna == 1) || (entrada == 'd' && novaColuna == 10)) return 2;
        else if(entrada == 'd' && ((matriz[novaLinha - 1][novaColuna + 1] == 2 && matriz[novaLinha][novaColuna + 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1) || (matriz[novaLinha - 1][novaColuna + 1] == 2 && matriz[novaLinha][novaColuna - 1] == 2 && matriz[novaLinha + 1][novaColuna] == 1))) return 2;
        else if(entrada == 'a' && ((matriz[novaLinha - 1][novaColuna - 1] == 2 && matriz[novaLinha][novaColuna - 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1) || (matriz[novaLinha - 1][novaColuna - 1] == 2 && matriz[novaLinha][novaColuna - 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1))) return 2;
    }
    return 1;
}

void imprimirTela(int matriz[22][12], int pontuacao){
    clear();
    for(int linha = 0; 22 > linha; linha++){
        for(int coluna = 0; 12 > coluna; coluna++){
            if(coluna == 0 || coluna == 11 || linha == 0 || linha == 21) {attron(COLOR_PAIR(1)); matriz[linha][coluna] = 0; mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(1));}
            else if(matriz[linha][coluna] == 1) {attron(COLOR_PAIR(2)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(2));}
            else if(matriz[linha][coluna] == 2) {attron(COLOR_PAIR(3)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(3));}
            else if(matriz[linha][coluna] == 0) mvprintw(linha, coluna, "  ");
            }
        attron(COLOR_PAIR(4)); mvprintw(22, 0, "Pontuacao: %d", pontuacao); attroff(COLOR_PAIR(4));
        refresh();
        }
}

int gameOver(int matriz[22][12], int pontuacao){
    for(int linha = 0; 22 > linha; linha++){
        for(int coluna = 0; 12 > coluna; coluna++){
            if(coluna == 0 || coluna == 11 || linha == 0 || linha == 21) {attron(COLOR_PAIR(1)); matriz[linha][coluna] = 0; mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(1));}
            else if(matriz[linha][coluna] == 1) {attron(COLOR_PAIR(2)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(2));}
            else if(matriz[linha][coluna] == 2) {attron(COLOR_PAIR(3)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(3));}
            else if(matriz[linha][coluna] == 0) mvprintw(linha, coluna, "  ");
            }
        attron(COLOR_PAIR(4)); mvprintw(22, 0, "Pontuacao: %d", pontuacao); attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(4)); mvprintw(23, 0, "GAME OVER"); attroff(COLOR_PAIR(4));
        refresh();
        getch();
        endwin();
        }
    return 0;
}

void removeLinhas(int novaLinha, int novaColuna, int linha, int coluna, peca peca, int matriz[22][12]){
    for(int k = 0; 4 > k; k++){
        novaLinha = linha + peca.Linha[k];
        novaColuna = coluna + peca.Coluna[k];
        matriz[novaLinha-1][novaColuna] = 0;
    }
}

void adicionaLinhas(int novaLinha, int novaColuna, int linha, int coluna, peca peca, int matriz[22][12]){
    for(int k = 0; 4 > k; k++){
        novaLinha = linha + peca.Linha[k];
        novaColuna = coluna + peca.Coluna[k];
        matriz[novaLinha-1][novaColuna] = 1;
    }
}

int main()
{
    int pontuacao = 0, linha = 0, coluna = 0, novaLinha, novaColuna, rotacoes = 0;
    double velocidade = 3.0;
    int matriz[22][12] = {0};
    char entrada;
    peca peca[7], prodada[12], copia[7];

    //peça I             //peça T             //peça S             //peça L             //cubo               //L espe.            //S espe.
    peca[0].Linha[0]=2;  peca[1].Linha[0]=2;  peca[2].Linha[0]=2;  peca[3].Linha[0]=2;  peca[4].Linha[0]=2;  peca[5].Linha[0]=2;  peca[6].Linha[0]=2;
    peca[0].Coluna[0]=5; peca[1].Coluna[0]=5; peca[2].Coluna[0]=5; peca[3].Coluna[0]=5; peca[4].Coluna[0]=5; peca[5].Coluna[0]=5; peca[6].Coluna[0]=5;
    peca[0].Linha[1]=1;  peca[1].Linha[1]=2;  peca[2].Linha[1]=2;  peca[3].Linha[1]=1;  peca[4].Linha[1]=1;  peca[5].Linha[1]=1;  peca[6].Linha[1]=1;
    peca[0].Coluna[1]=5; peca[1].Coluna[1]=4; peca[2].Coluna[1]=4; peca[3].Coluna[1]=5; peca[4].Coluna[1]=5; peca[5].Coluna[1]=5; peca[6].Coluna[1]=5;
    peca[0].Linha[2]=3;  peca[1].Linha[2]=2;  peca[2].Linha[2]=1;  peca[3].Linha[2]=3;  peca[4].Linha[2]=1;  peca[5].Linha[2]=3;  peca[6].Linha[2]=2;
    peca[0].Coluna[2]=5; peca[1].Coluna[2]=6; peca[2].Coluna[2]=5; peca[3].Coluna[2]=5; peca[4].Coluna[2]=6; peca[5].Coluna[2]=5; peca[6].Coluna[2]=6;
    peca[0].Linha[3]=4;  peca[1].Linha[3]=1;  peca[2].Linha[3]=1;  peca[3].Linha[3]=3;  peca[4].Linha[3]=2;  peca[5].Linha[3]=3;  peca[6].Linha[3]=1;
    peca[0].Coluna[3]=5; peca[1].Coluna[3]=5; peca[2].Coluna[3]=6; peca[3].Coluna[3]=6; peca[4].Coluna[3]=6; peca[5].Coluna[3]=4; peca[6].Coluna[3]=4;

    //peça I rotação         //peça T rotações                                                        //L espe. rotações                                                        //S rotação
    prodada[0].Linha[0]=2;   prodada[1].Linha[0]=2;  prodada[2].Linha[0]=2;  prodada[3].Linha[0]=2;   prodada[4].Linha[0]=2;   prodada[5].Linha[0]=2;  prodada[6].Linha[0]=2;   prodada[7].Linha[0]=2;
    prodada[0].Coluna[0]=5;  prodada[1].Coluna[0]=5; prodada[2].Coluna[0]=5; prodada[3].Coluna[0]=5;  prodada[4].Coluna[0]=5;  prodada[5].Coluna[0]=5; prodada[6].Coluna[0]=5;  prodada[7].Coluna[0]=5;
    prodada[0].Linha[1]=2;   prodada[1].Linha[1]=1;  prodada[2].Linha[1]=3;  prodada[3].Linha[1]=1;   prodada[4].Linha[1]=2;   prodada[5].Linha[1]=1;  prodada[6].Linha[1]=3;   prodada[7].Linha[1]=2;
    prodada[0].Coluna[1]=6;  prodada[1].Coluna[1]=5; prodada[2].Coluna[1]=5; prodada[3].Coluna[1]=5;  prodada[4].Coluna[1]=6;  prodada[5].Coluna[1]=5; prodada[6].Coluna[1]=6;  prodada[7].Coluna[1]=6;
    prodada[0].Linha[2]=2;   prodada[1].Linha[2]=3;  prodada[2].Linha[2]=2;  prodada[3].Linha[2]=3;   prodada[4].Linha[2]=2;   prodada[5].Linha[2]=3;  prodada[6].Linha[2]=2;   prodada[7].Linha[2]=1;
    prodada[0].Coluna[2]=4;  prodada[1].Coluna[2]=5; prodada[2].Coluna[2]=4; prodada[3].Coluna[2]=5;  prodada[4].Coluna[2]=4;  prodada[5].Coluna[2]=5; prodada[6].Coluna[2]=4;  prodada[7].Coluna[2]=5;
    prodada[0].Linha[3]=2;   prodada[1].Linha[3]=2;  prodada[2].Linha[3]=2;  prodada[3].Linha[3]=2;   prodada[4].Linha[3]=1;   prodada[5].Linha[3]=1;  prodada[6].Linha[3]=2;   prodada[7].Linha[3]=3;
    prodada[0].Coluna[3]=3;  prodada[1].Coluna[3]=6; prodada[2].Coluna[3]=6; prodada[3].Coluna[3]=4;  prodada[4].Coluna[3]=4;  prodada[5].Coluna[3]=6; prodada[6].Coluna[3]=6;  prodada[7].Coluna[3]=6;

    //S espe. rotação       //L rotações  															   //limites de rotação
    prodada[8].Linha[0]=2;  prodada[9].Linha[0]=2;  prodada[10].Linha[0]=2;  prodada[11].Linha[0]=2;   peca[0].numrotacao=-1;   peca[5].numrotacao=3;
    prodada[8].Coluna[0]=5; prodada[9].Coluna[0]=5; prodada[10].Coluna[0]=5; prodada[11].Coluna[0]=5;  peca[0].rotacaolimite=2; peca[5].rotacaolimite=4;
    prodada[8].Linha[1]=1;  prodada[9].Linha[1]=2;  prodada[10].Linha[1]=1;  prodada[11].Linha[1]=2;   peca[1].numrotacao=0;    peca[6].numrotacao=7;
    prodada[8].Coluna[1]=6; prodada[9].Coluna[1]=6; prodada[10].Coluna[1]=5; prodada[11].Coluna[1]=6;  peca[1].rotacaolimite=4; peca[6].rotacaolimite=2;
    prodada[8].Linha[2]=2;  prodada[9].Linha[2]=2;  prodada[10].Linha[2]=3;  prodada[11].Linha[2]=2;   peca[2].numrotacao=6;
    prodada[8].Coluna[2]=6; prodada[9].Coluna[2]=4; prodada[10].Coluna[2]=5; prodada[11].Coluna[2]=4;  peca[2].rotacaolimite=2;
    prodada[8].Linha[3]=3;  prodada[9].Linha[3]=3;  prodada[10].Linha[3]=1;  prodada[11].Linha[3]=1;   peca[3].numrotacao=8;
    prodada[8].Coluna[3]=5; prodada[9].Coluna[3]=4; prodada[10].Coluna[3]=4; prodada[11].Coluna[3]=6;  peca[3].rotacaolimite=4;

    for(int n=0; 7>n; n++)
		for(int k=0; 4>k; k++){
			copia[n].Coluna[k]=peca[n].Coluna[k];
			copia[n].Linha[k]=peca[n].Linha[k];
		}

    initscr();
    start_color();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    halfdelay(velocidade);

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);

    for(int valorAleatorio = Aleatorio(pontuacao); TRUE; valorAleatorio = Aleatorio(pontuacao), linha = 0, coluna = 0, rotacoes = 0){
        while(1){
            for (int k = 1; k <= 2; k++)
                for (int i = 4; i <= 6; i++) if(matriz[k][i] == 2) return gameOver(matriz, pontuacao);

            entrada = getch();
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
            else if(entrada == 'r' && valorAleatorio!=4){
				rotacoes++;  //conta a quantidade de rotações
				removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
				
				for(int k = 0; 4 > k; k++){//atualiza o gabarito normal para ficar igual a do rodado
					peca[valorAleatorio].Linha[k] = prodada[rotacoes+peca[valorAleatorio].numrotacao].Linha[k];
					peca[valorAleatorio].Coluna[k] = prodada[rotacoes+peca[valorAleatorio].numrotacao].Coluna[k];
				}
				if(rotacoes == peca[valorAleatorio].rotacaolimite){ //se chegar nesse numero é pq voltou para a posição normal ent atualiza o gabarito normal de voltar para como era antes 
					for(int k=0; 4>k; k++){
						peca[valorAleatorio].Linha[k]=copia[valorAleatorio].Linha[k];
						peca[valorAleatorio].Coluna[k]=copia[valorAleatorio].Coluna[k];
				}
				rotacoes = 0;// para poder começar a girar de novo
                }
				adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
			}
            else if(detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1){
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                linha++;
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            }
            else if(detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 0) break;
            
            pontuacao += pontosLinha(apagarLinhasCompletas(matriz));

            clear();refresh();
            imprimirTela(matriz, pontuacao);

            if(pontuacao % 200 == 0) velocidade -= 0.5;

        }
        for(int linhas = 1; linhas < 21; linhas++)
            for(int colunas = 1; colunas < 11; colunas++)
                if(matriz[linhas][colunas] == 1) matriz[linhas][colunas] = 2;
    }

    endwin();
return 0;
}