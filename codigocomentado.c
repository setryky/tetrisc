#include <stdlib.h> // Biblioteca padrão do C para alocação de memória, controle de processos e outras funções de propósito geral.
#include <ncurses.h> // Biblioteca para controle de interfaces de texto.
#include <time.h> // Biblioteca para manipulação de data e hora.

typedef struct {
    int Linha[4]; // Array para armazenar as linhas da peça.
    int Coluna[4]; // Array para armazenar as colunas da peça.
	int numrotacao;
	int rotacaolimite;
} peca; // Definição da estrutura da peça.

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

void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas) {
    for (int linha = linhaParou; linha > 0; linha--)
        for (int coluna = 1; coluna < 11; coluna++) 
            matriz[linha][coluna] = matriz[linha - linhasApagadas][coluna]; // Desce as linhas da matriz.
    for (int linha = linhaParou - linhasApagadas; linha > 0; linha--)
        for (int coluna = 1; coluna < 11; coluna++) 
            matriz[linha][coluna] = 0; // Limpa as linhas acima.
}

int apagarLinhasCompletas(int matriz[22][12]) {
    int linha, coluna, lugarOcupado, linhasApagadas = 0, primeiraLinha = 0;
    for (linha = 20; linha > 0; linha--) {
        lugarOcupado = 0;
        for (coluna = 1; coluna < 11; coluna++) 
            if (matriz[linha][coluna] == 2) 
                lugarOcupado++; // Conta os lugares ocupados na linha.
        if (lugarOcupado == 10) {
            if (primeiraLinha == 0) 
                primeiraLinha = linha; // Define a primeira linha completa.
            for (coluna = 1; coluna < 11; coluna++) {
                matriz[linha][coluna] = 0; // Limpa a linha completa.
            }
            linhasApagadas++; // Incrementa o contador de linhas apagadas.
        }
    }
    if (linhasApagadas > 0) 
        descerLinhas(matriz, primeiraLinha, linhasApagadas); // Desce as linhas se houver linhas apagadas.
    return linhasApagadas; // Retorna o número de linhas apagadas.
}

int detectorColisao(char entrada, int linha, int coluna, peca peca, int matriz[22][12]) {
    for (int k = 0; k < 4; k++) {
        int novaLinha = linha + peca.Linha[k];
        int novaColuna = coluna + peca.Coluna[k];
        if (novaLinha == 21 || (matriz[novaLinha - 1][novaColuna] == 1 && matriz[novaLinha][novaColuna] == 2)) 
            return 0; // Detecta colisão com o fundo ou outras peças.
        else if ((entrada == 'a' && novaColuna == 1) || (entrada == 'd' && novaColuna == 10)) 
            return 2; // Detecta colisão com as bordas.
        else if (entrada == 'd' && matriz[novaLinha - 1][novaColuna + 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1) 
            return 2; // Detecta colisão com outras peças à direita.
        else if (entrada == 'a' && matriz[novaLinha - 1][novaColuna - 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1) 
            return 2; // Detecta colisão com outras peças à esquerda.
    }
    return 1; // Retorna 1 se não houver colisão.
}

void imprimirTela(int matriz[22][12], int pontuacao) {
    clear(); // Limpa a tela.
    for (int linha = 0; linha < 22; linha++) {
        for (int coluna = 0; coluna < 12; coluna++) {
            if (coluna == 0 || coluna == 11 || linha == 0 || linha == 21) {
                attron(COLOR_PAIR(1)); 
                matriz[linha][coluna] = 0; 
                mvprintw(linha, coluna, " "); 
                attroff(COLOR_PAIR(1)); // Desenha as bordas.
            } else if (matriz[linha][coluna] == 1) {
                attron(COLOR_PAIR(2)); 
                mvprintw(linha, coluna, " "); 
                attroff(COLOR_PAIR(2)); // Desenha as peças em movimento.
            } else if (matriz[linha][coluna] == 2) {
                attron(COLOR_PAIR(3)); 
                mvprintw(linha, coluna, " "); 
                attroff(COLOR_PAIR(3)); // Desenha as peças fixas.
            } else if (matriz[linha][coluna] == 0) {
                mvprintw(linha, coluna, "  "); // Espaços vazios.
            }
        }
    }
    attron(COLOR_PAIR(4)); 
    mvprintw(22, 0, "Pontuacao: %d", pontuacao); 
    attroff(COLOR_PAIR(4)); // Exibe a pontuação.
    refresh(); // Atualiza a tela.
}

int gameOver(int matriz[22][12], int pontuacao) {
    for (int linha = 0; linha < 22; linha++) {
        for (int coluna = 0; coluna < 12; coluna++) {
            if (coluna == 0 || coluna == 11 || linha == 0 || linha == 21) {
                attron(COLOR_PAIR(1)); 
                matriz[linha][coluna] = 0; 
                mvprintw(linha, coluna, " "); 
                attroff(COLOR_PAIR(1)); // Desenha as bordas.
            } else if (matriz[linha][coluna] == 1) {
                attron(COLOR_PAIR(2)); 
                mvprintw(linha, coluna, " "); 
                attroff(COLOR_PAIR(2)); // Desenha as peças em movimento.
            } else if (matriz[linha][coluna] == 2) {
                attron(COLOR_PAIR(3)); 
                mvprintw(linha, coluna, " "); 
                attroff(COLOR_PAIR(3)); // Desenha as peças fixas.
            } else if (matriz[linha][coluna] == 0) {
                mvprintw(linha, coluna, "  "); // Espaços vazios.
            }
        }
        attron(COLOR_PAIR(4)); 
        mvprintw(22, 0, "Pontuacao: %d", pontuacao); 
        attroff(COLOR_PAIR(4)); // Exibe a pontuação.
        attron(COLOR_PAIR(4)); 
        mvprintw(23, 0, "GAME OVER"); 
        attroff(COLOR_PAIR(4)); // Exibe a mensagem de game over.
        refresh(); // Atualiza a tela.
        getch(); // Aguarda uma tecla.
        endwin(); // Finaliza o ncurses.
    }
    return 0; // Retorna 0 para indicar game over.
}

void removeLinhas(int novaLinha, int novaColuna, int linha, int coluna, peca peca, int matriz[22][12]) {
    for (int k = 0; k < 4; k++) {
        novaLinha = linha + peca.Linha[k];
        novaColuna = coluna + peca.Coluna[k];
        matriz[novaLinha - 1][novaColuna] = 0; // Remove a peça da matriz.
    }
}

void adicionaLinhas(int novaLinha, int novaColuna, int linha, int coluna, peca peca, int matriz[22][12]) {
    for (int k = 0; k < 4; k++) {
        novaLinha = linha + peca.Linha[k];
        novaColuna = coluna + peca.Coluna[k];
        matriz[novaLinha - 1][novaColuna] = 1; // Adiciona a peça à matriz.
    }
}

int main() {
    int pontuacao = 0, linha = 0, coluna = 0, novaLinha, novaColuna, rotacoes = 0;
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

    initscr(); // Inicializa a tela do ncurses.
    start_color(); // Inicia o modo de cores.
    noecho(); // Não exibe os caracteres digitados.
    curs_set(FALSE); // Esconde o cursor.
    keypad(stdscr, TRUE); // Habilita o uso do teclado.
    halfdelay(2); // Define a velocidade inicial.

    // Inicializa os pares de cores.
    init_pair(1, COLOR_BLUE, COLOR_BLUE); // Bordas.
    init_pair(2, COLOR_RED, COLOR_RED); // Peças em movimento.
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW); // Peças fixas.
    init_pair(4, COLOR_BLACK, COLOR_WHITE); // Texto.

    // Loop principal do jogo.
    for (int valorAleatorio = Aleatorio(pontuacao); TRUE; valorAleatorio = Aleatorio(pontuacao), linha = 0, coluna = 0, rotacoes = 0) {
        while (1) {
            // Verifica se há peças no topo da matriz.
            for (int k = 1; k <= 2; k++)
                for (int i = 4; i <= 6; i++) 
                    if (matriz[k][i] == 2) 
                        return gameOver(matriz, pontuacao); // Finaliza o jogo se houver peças no topo.

            entrada = getch(); // Lê a entrada do teclado.

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
            else if (entrada == 'w' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) { // Hard-drop quando 'w' é pressionado.
                for(; detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz);){ // Loop que repete até detectar colisão com o bloco debaixo.
                    removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                    linha++;
                    adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                    pontuacao += 2; //Hard-drop possui 2x de ponto por linha.
                }
            }  
            else if (entrada == 'r' && valorAleatorio!=4) { // Rotaciona quando 'r' é pressionado. Todas as peças, menos o cubo, giram.
				rotacoes++;  // Contagem de rotações, se chegar peca[valorAleatorio].rotacaolimite, ele volta para o valor original.
				removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
				for (int k = 0; 4 > k; k++) { // Atualiza a peça até ficar igual a peça rodada.
					peca[valorAleatorio].Linha[k] = prodada[rotacoes+peca[valorAleatorio].numrotacao].Linha[k];
					peca[valorAleatorio].Coluna[k] = prodada[rotacoes+peca[valorAleatorio].numrotacao].Coluna[k];
				}
				if (rotacoes == peca[valorAleatorio].rotacaolimite) { // Se chegar nesse número é porque voltou para a posição original. Então atualiza o gabarito base para voltar como era antes.
					for (int k=0; 4>k; k++) {
						peca[valorAleatorio].Linha[k]=copia[valorAleatorio].Linha[k];
						peca[valorAleatorio].Coluna[k]=copia[valorAleatorio].Coluna[k];
				}
				rotacoes = 0; // Reseta o valor rotacoes para poder rotacionar novamente.
                }
				adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
			} 
            else if (detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) {
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
                linha++; // Move a peça para baixo.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz);
            } 
            else if (detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 0)
                break; // Sai do loop se houver colisão.

            pontuacao += pontosLinha(apagarLinhasCompletas(matriz)); // Atualiza a pontuação com base nas linhas apagadas.

            clear(); refresh(); // Limpa e atualiza a tela.
            imprimirTela(matriz, pontuacao); // Imprime a tela atualizada.

        }

        // Converte peças em movimento para peças fixas.
        for (int linhas = 1; linhas < 21; linhas++)
            for (int colunas = 1; colunas < 11; colunas++)
                if (matriz[linhas][colunas] == 1) 
                    matriz[linhas][colunas] = 2;
    }

    endwin(); // Finaliza o ncurses.
    return 0;
}