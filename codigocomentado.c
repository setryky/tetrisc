#include <stdlib.h> // Biblioteca padrão do C para alocação de memória, controle de processos e outras funções de propósito geral.
#include <ncurses.h> // Biblioteca para controle de interfaces de texto.
#include <time.h> // Biblioteca para manipulação de data e hora.

typedef struct{
    int Linha[4];
    int Coluna[4];
	int numrotacao;
	int rotacaolimite;
}PECA;

void declararPecas(PECA peca[], PECA pecaRodada[], PECA copia[]){
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
    pecaRodada[0].Linha[0]=2;   pecaRodada[1].Linha[0]=2;  pecaRodada[2].Linha[0]=2;  pecaRodada[3].Linha[0]=2;   pecaRodada[4].Linha[0]=2;   pecaRodada[5].Linha[0]=2;  pecaRodada[6].Linha[0]=2;   pecaRodada[7].Linha[0]=2;
    pecaRodada[0].Coluna[0]=5;  pecaRodada[1].Coluna[0]=5; pecaRodada[2].Coluna[0]=5; pecaRodada[3].Coluna[0]=5;  pecaRodada[4].Coluna[0]=5;  pecaRodada[5].Coluna[0]=5; pecaRodada[6].Coluna[0]=5;  pecaRodada[7].Coluna[0]=5;
    pecaRodada[0].Linha[1]=2;   pecaRodada[1].Linha[1]=1;  pecaRodada[2].Linha[1]=3;  pecaRodada[3].Linha[1]=1;   pecaRodada[4].Linha[1]=2;   pecaRodada[5].Linha[1]=1;  pecaRodada[6].Linha[1]=3;   pecaRodada[7].Linha[1]=2;
    pecaRodada[0].Coluna[1]=6;  pecaRodada[1].Coluna[1]=5; pecaRodada[2].Coluna[1]=5; pecaRodada[3].Coluna[1]=5;  pecaRodada[4].Coluna[1]=6;  pecaRodada[5].Coluna[1]=5; pecaRodada[6].Coluna[1]=6;  pecaRodada[7].Coluna[1]=6;
    pecaRodada[0].Linha[2]=2;   pecaRodada[1].Linha[2]=3;  pecaRodada[2].Linha[2]=2;  pecaRodada[3].Linha[2]=3;   pecaRodada[4].Linha[2]=2;   pecaRodada[5].Linha[2]=3;  pecaRodada[6].Linha[2]=2;   pecaRodada[7].Linha[2]=1;
    pecaRodada[0].Coluna[2]=4;  pecaRodada[1].Coluna[2]=5; pecaRodada[2].Coluna[2]=4; pecaRodada[3].Coluna[2]=5;  pecaRodada[4].Coluna[2]=4;  pecaRodada[5].Coluna[2]=5; pecaRodada[6].Coluna[2]=4;  pecaRodada[7].Coluna[2]=5;
    pecaRodada[0].Linha[3]=2;   pecaRodada[1].Linha[3]=2;  pecaRodada[2].Linha[3]=2;  pecaRodada[3].Linha[3]=2;   pecaRodada[4].Linha[3]=1;   pecaRodada[5].Linha[3]=1;  pecaRodada[6].Linha[3]=2;   pecaRodada[7].Linha[3]=3;
    pecaRodada[0].Coluna[3]=3;  pecaRodada[1].Coluna[3]=6; pecaRodada[2].Coluna[3]=6; pecaRodada[3].Coluna[3]=4;  pecaRodada[4].Coluna[3]=4;  pecaRodada[5].Coluna[3]=6; pecaRodada[6].Coluna[3]=6;  pecaRodada[7].Coluna[3]=6;

    //S espe. rotação       //L rotações  															   //limites de rotação
    pecaRodada[8].Linha[0]=2;  pecaRodada[9].Linha[0]=2;  pecaRodada[10].Linha[0]=2;  pecaRodada[11].Linha[0]=2;   peca[0].numrotacao=-1;   peca[5].numrotacao=3;
    pecaRodada[8].Coluna[0]=5; pecaRodada[9].Coluna[0]=5; pecaRodada[10].Coluna[0]=5; pecaRodada[11].Coluna[0]=5;  peca[0].rotacaolimite=2; peca[5].rotacaolimite=4;
    pecaRodada[8].Linha[1]=1;  pecaRodada[9].Linha[1]=2;  pecaRodada[10].Linha[1]=1;  pecaRodada[11].Linha[1]=2;   peca[1].numrotacao=0;    peca[6].numrotacao=7;
    pecaRodada[8].Coluna[1]=6; pecaRodada[9].Coluna[1]=6; pecaRodada[10].Coluna[1]=5; pecaRodada[11].Coluna[1]=6;  peca[1].rotacaolimite=4; peca[6].rotacaolimite=2;
    pecaRodada[8].Linha[2]=2;  pecaRodada[9].Linha[2]=2;  pecaRodada[10].Linha[2]=3;  pecaRodada[11].Linha[2]=2;   peca[2].numrotacao=6;
    pecaRodada[8].Coluna[2]=6; pecaRodada[9].Coluna[2]=4; pecaRodada[10].Coluna[2]=5; pecaRodada[11].Coluna[2]=4;  peca[2].rotacaolimite=2;
    pecaRodada[8].Linha[3]=3;  pecaRodada[9].Linha[3]=3;  pecaRodada[10].Linha[3]=1;  pecaRodada[11].Linha[3]=1;   peca[3].numrotacao=8;
    pecaRodada[8].Coluna[3]=5; pecaRodada[9].Coluna[3]=4; pecaRodada[10].Coluna[3]=4; pecaRodada[11].Coluna[3]=6;  peca[3].rotacaolimite=4;

    for(int n=0; 7>n; n++)
		for(int k=0; 4>k; k++){
			copia[n].Coluna[k]=peca[n].Coluna[k];
			copia[n].Linha[k]=peca[n].Linha[k];
		}
}

void inicializarNcurses(){
    initscr();
    start_color();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    halfdelay(2);

    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(7, COLOR_RED, COLOR_RED);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);
    init_pair(9, COLOR_GREEN, COLOR_GREEN);
    init_pair(10, COLOR_CYAN, COLOR_CYAN);
}

int Aleatorio(int pontuacao) {
    time_t tempoAtual; // Variável para armazenar o tempo atual.
    time(&tempoAtual); // Obtém o tempo atual.
    if (pontuacao == 0) 
        srand(tempoAtual); // Semente aleatória baseada no tempo atual.
    else 
        srand(tempoAtual * pontuacao); // Semente aleatória baseada no tempo atual multiplicado pela pontuação.
    return rand() % 7; // Retorna um número aleatório entre 0 e 6.
}

int pontosLinha(int linhasApagadas) {
    int pontuacao = 0; // Inicializa a pontuação.
    if (linhasApagadas == 1) 
        pontuacao += 100; // 100 pontos para 1 linha apagada.
    else if (linhasApagadas == 2) 
        pontuacao += 300; // 300 pontos para 2 linhas apagadas.
    else if (linhasApagadas == 3) 
        pontuacao += 500; // 500 pontos para 3 linhas apagadas.
    else if (linhasApagadas == 4) 
        pontuacao += 800; // 800 pontos para 4 linhas apagadas.
    return pontuacao; // Retorna a pontuação calculada.
}

void transformaEmFixa(int matriz[22][12], int valorAleatorio){
    for(int linhas = 1; linhas < 21; linhas++)
            for(int colunas = 1; colunas < 11; colunas++){
                if(matriz[linhas][colunas] == 1 && valorAleatorio == 0) matriz[linhas][colunas] = 2;
                else if(matriz[linhas][colunas] == 1 && valorAleatorio == 1) matriz[linhas][colunas] = 3;
                else if(matriz[linhas][colunas] == 1 && valorAleatorio == 2) matriz[linhas][colunas] = 4;
                else if(matriz[linhas][colunas] == 1 && valorAleatorio == 3) matriz[linhas][colunas] = 5;
                else if(matriz[linhas][colunas] == 1 && valorAleatorio == 4) matriz[linhas][colunas] = 6;
                else if(matriz[linhas][colunas] == 1 && valorAleatorio == 5) matriz[linhas][colunas] = 7;
                else if(matriz[linhas][colunas] == 1 && valorAleatorio == 6) matriz[linhas][colunas] = 8;
        }
}

void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas) {
    for(int linha = linhaParou; linha >= linhasApagadas; linha--) 
        for(int coluna = 1; coluna < 11; coluna++) 
            matriz[linha][coluna] = matriz[linha - linhasApagadas][coluna];
    for(int linha = 0; linha < linhasApagadas; linha++) 
        for(int coluna = 1; coluna < 11; coluna++) 
            matriz[linha][coluna] = 0;  
}

int apagarLinhasCompletas(int matriz[22][12]) {
    int linha, coluna, lugarOcupado, linhasApagadas = 0, primeiraLinha = -1;
    for(linha = 20; linha > 0; linha--){
        lugarOcupado = 0;
        for(coluna = 1; coluna < 11; coluna++) 
            if(matriz[linha][coluna] >= 2) lugarOcupado++;
        if(lugarOcupado == 10){
            if(primeiraLinha == -1) primeiraLinha = linha;
            for(coluna = 1; coluna < 11; coluna++) matriz[linha][coluna] = 0;
            linhasApagadas++;
        }
    }
    if(linhasApagadas > 0 && primeiraLinha != -1) descerLinhas(matriz, primeiraLinha, linhasApagadas);
    return linhasApagadas;
}
int detectorColisao(char entrada, int linha, int coluna, PECA peca, int matriz[22][12]) {
    for(int k = 0; k < 4; k++) {
        int novaLinha = linha + peca.Linha[k];
        int novaColuna = coluna + peca.Coluna[k];
        if(novaLinha == 21 || (matriz[novaLinha - 1][novaColuna] == 1 && matriz[novaLinha][novaColuna] >= 2)) return 0;
        else if((entrada == 'd' && novaColuna == 10) || (entrada == 'd' && matriz[novaLinha - 1][novaColuna + 1] >= 2 && matriz[novaLinha - 1][novaColuna] == 1)) return 2;
        else if((entrada == 'a' && novaColuna == 1) || (entrada == 'a' && matriz[novaLinha - 1][novaColuna - 1] >= 2 && matriz[novaLinha - 1][novaColuna] == 1)) return 3;
    }
    return 1;
}

void imprimirTela(int matriz[22][12], int pontuacao){
    clear();
    for(int linha = 0; 22 > linha; linha++){
        for(int coluna = 0; 12 > coluna; coluna++){
            if(coluna == 0 || coluna == 11 || linha == 0 || linha == 21) {attron(COLOR_PAIR(1)); matriz[linha][coluna] = 0; mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(1));}
            else if(matriz[linha][coluna] == 1) {attron(COLOR_PAIR(2)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(2));}
            else if(matriz[linha][coluna] == 2) {attron(COLOR_PAIR(5)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(5));}
            else if(matriz[linha][coluna] == 3) {attron(COLOR_PAIR(3)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(6));}
            else if(matriz[linha][coluna] == 4) {attron(COLOR_PAIR(7)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(7));}
            else if(matriz[linha][coluna] == 5) {attron(COLOR_PAIR(8)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(8));}
            else if(matriz[linha][coluna] == 6) {attron(COLOR_PAIR(9)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(9));}
            else if(matriz[linha][coluna] == 7) {attron(COLOR_PAIR(10)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(10));}
            else if(matriz[linha][coluna] == 8) {attron(COLOR_PAIR(1)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(10));}
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
            else if(matriz[linha][coluna] == 2) {attron(COLOR_PAIR(5)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(5));}
            else if(matriz[linha][coluna] == 3) {attron(COLOR_PAIR(3)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(6));}
            else if(matriz[linha][coluna] == 4) {attron(COLOR_PAIR(7)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(7));}
            else if(matriz[linha][coluna] == 5) {attron(COLOR_PAIR(8)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(8));}
            else if(matriz[linha][coluna] == 6) {attron(COLOR_PAIR(9)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(9));}
            else if(matriz[linha][coluna] == 7) {attron(COLOR_PAIR(10)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(10));}
            else if(matriz[linha][coluna] == 8) {attron(COLOR_PAIR(1)); mvprintw(linha, coluna, " ");attroff(COLOR_PAIR(10));}
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

void removeLinhas(int novaLinha, int novaColuna, int linha, int coluna, PECA peca, int matriz[22][12]) {
    for (int k = 0; k < 4; k++) {
        novaLinha = linha + peca.Linha[k];
        novaColuna = coluna + peca.Coluna[k];
        matriz[novaLinha - 1][novaColuna] = 0; // Remove a peça da matriz.
    }
}

void adicionaLinhas(int novaLinha, int novaColuna, int linha, int coluna, PECA peca, int matriz[22][12]) {
    for (int k = 0; k < 4; k++) {
        novaLinha = linha + peca.Linha[k];
        novaColuna = coluna + peca.Coluna[k];
        matriz[novaLinha - 1][novaColuna] = 1; // Adiciona a peça à matriz.
    }
}

void voltaOriginal(PECA *peca, PECA copia){
    for(int k = 0; 4 > k; k++){
	    peca->Linha[k] = copia.Linha[k];
        peca->Coluna[k] = copia.Coluna[k];
    }
}

void rodaLinhas(PECA *peca, PECA pecaRodada, PECA copia, int *rotacoes){
	for(int k = 0; 4 > k; k++){
		peca->Linha[k] = pecaRodada.Linha[k];
		peca->Coluna[k] = pecaRodada.Coluna[k];
	}
	if(*rotacoes == peca->rotacaolimite){
	    for(int k = 0; 4 > k; k++){
		peca->Linha[k] = copia.Linha[k];
		peca->Coluna[k] = copia.Coluna[k];
        }
        *rotacoes = 0;
    }
}

int main() {
    int pontuacao = 0, linha = 0, coluna = 0, novaLinha, novaColuna, rotacoes = 0;
    int matriz[22][12] = {0};
    char entrada;
    PECA peca[7], pecaRodada[12], copia[7];

    declararPecas(peca, pecaRodada, copia);

    inicializarNcurses();

    // Loop principal do jogo.
    for (int valorAleatorio = Aleatorio(pontuacao); TRUE; valorAleatorio = Aleatorio(pontuacao), linha = 0, coluna = 0, rotacoes = 0) {
        while (1) {
            // Verifica se há peças no topo da matriz.
            for (int k = 1; k <= 2; k++)
                for (int i = 4; i <= 6; i++) 
                    if (matriz[k][i] == 2) 
                        return gameOver(matriz, pontuacao); // Finaliza o jogo se houver peças no topo.

            entrada = getch(); // Lê a entrada do teclado.
            if(entrada >= 65 && entrada <= 90) entrada += 32; //Se as letras estiverem em maiúsculo, converte para minúsculo.

            if (entrada == 'd' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) { // Mexe a peça para a direita quando 'd' é pressionado.
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Remove a peça da posição atual.
                coluna++; // Move a peça para a direita.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Adiciona a peça na nova posição.
            } 
            else if (entrada == 'a' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) { // Mexe a peça para a esquerda quando 'a' é pressionado.
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                coluna--; // Move a peça para a esquerda.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            } 
            else if (entrada == 's' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) { // Soft-drop quando 's' é pressionado.
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                linha++; // Move a peça para baixo.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                pontuacao++; // Incrementa a pontuação por cada linha descida.
            }
            else if (entrada == 'w') { // Hard-drop quando 'w' é pressionado.
                for(; detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz);){ // Loop que repete até detectar colisão com o bloco debaixo.
                    removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                    linha++;
                    adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                    pontuacao += 2; //Hard-drop possui 2x de ponto por linha.
                }
            }  
            else if (entrada == 'r' && valorAleatorio != 4){
				rotacoes++;
				removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                rodaLinhas(&peca[valorAleatorio], pecaRodada[rotacoes + peca[valorAleatorio].numrotacao], copia[valorAleatorio], &rotacoes);
				adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
			}
            else if (entrada != 's' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) {
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                linha++; // Move a peça para baixo.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            } 
            else if (detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 0)
                break; // Sai do loop se houver colisão.

            pontuacao += pontosLinha(apagarLinhasCompletas(matriz)); // Atualiza a pontuação com base nas linhas apagadas.

            imprimirTela(matriz, pontuacao); // Imprime a tela atualizada.

        }
        transformaEmFixa(matriz, valorAleatorio);
    }
    endwin(); // Finaliza o ncurses.
    return 0;
}
