#include <stdlib.h> // Biblioteca padrão do C para alocação de memória, controle de processos e outras funções de propósito geral.
#include <ncurses.h> // Biblioteca para controle de interfaces de texto.
#include <time.h> // Biblioteca para manipulação de data e hora.
#include <sys/queue.h> // Biblioteca para manipulação de listas, filas e outras estruturas de dados.

typedef struct {
    int Linha[4]; // Array para armazenar as linhas da peça.
    int Coluna[4]; // Array para armazenar as colunas da peça.
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
            return 0; // Detecta colisão com o fundo ou outras peças embaixo.
        else if ((entrada == 'a' && novaColuna == 1) || (entrada == 'd' && novaColuna == 10)) 
            return 2; // Detecta colisão com as bordas.
        else if (entrada == 'd' && ((matriz[novaLinha - 1][novaColuna + 1] == 2 && matriz[novaLinha][novaColuna + 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1) || (matriz[novaLinha - 1][novaColuna + 1] == 2 && matriz[novaLinha][novaColuna - 1] == 2 && matriz[novaLinha + 1][novaColuna] == 1))) 
            return 2; // Detecta colisão com outras peças à direita.
        else if (entrada == 'a' && ((matriz[novaLinha - 1][novaColuna - 1] == 2 && matriz[novaLinha][novaColuna - 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1) || (matriz[novaLinha - 1][novaColuna - 1] == 2 && matriz[novaLinha][novaColuna - 1] == 2 && matriz[novaLinha - 1][novaColuna] == 1))) 
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
    double velocidade = 3.0; // Velocidade inicial do jogo.
    int matriz[22][12] = {0}; // Inicializa a matriz do jogo com zeros.
    char entrada;
    peca peca[7]; // Array para armazenar as peças.

    // Definindo as coordenadas das peças.
    // Peça I
    peca[0].Linha[0] = 2; peca[0].Coluna[0] = 5;
    peca[0].Linha[1] = 1; peca[0].Coluna[1] = 5;
    peca[0].Linha[2] = 3; peca[0].Coluna[2] = 5;
    peca[0].Linha[3] = 4; peca[0].Coluna[3] = 5;

    // Peça T
    peca[1].Linha[0] = 2; peca[1].Coluna[0] = 5;
    peca[1].Linha[1] = 2; peca[1].Coluna[1] = 4;
    peca[1].Linha[2] = 2; peca[1].Coluna[2] = 6;
    peca[1].Linha[3] = 1; peca[1].Coluna[3] = 5;

    // Peça S
    peca[2].Linha[0] = 2; peca[2].Coluna[0] = 5;
    peca[2].Linha[1] = 2; peca[2].Coluna[1] = 4;
    peca[2].Linha[2] = 1; peca[2].Coluna[2] = 5;
    peca[2].Linha[3] = 1; peca[2].Coluna[3] = 6;

    // Peça L
    peca[3].Linha[0] = 2; peca[3].Coluna[0] = 5;
    peca[3].Linha[1] = 1; peca[3].Coluna[1] = 5;
    peca[3].Linha[2] = 3; peca[3].Coluna[2] = 5;
    peca[3].Linha[3] = 3; peca[3].Coluna[3] = 6;

    // Cubo
    peca[4].Linha[0] = 2; peca[4].Coluna[0] = 5;
    peca[4].Linha[1] = 1; peca[4].Coluna[1] = 5;
    peca[4].Linha[2] = 1; peca[4].Coluna[2] = 6;
    peca[4].Linha[3] = 2; peca[4].Coluna[3] = 6;

    // L espelhado
    peca[5].Linha[0] = 2; peca[5].Coluna[0] = 5;
    peca[5].Linha[1] = 1; peca[5].Coluna[1] = 5;
    peca[5].Linha[2] = 3; peca[5].Coluna[2] = 5;
    peca[5].Linha[3] = 3; peca[5].Coluna[3] = 4;

    // S espelhado
    peca[6].Linha[0] = 2; peca[6].Coluna[0] = 5;
    peca[6].Linha[1] = 1; peca[6].Coluna[1] = 5;
    peca[6].Linha[2] = 2; peca[6].Coluna[2] = 6;
    peca[6].Linha[3] = 1; peca[6].Coluna[3] = 4;

    initscr(); // Inicializa a tela do ncurses.
    start_color(); // Inicia o modo de cores.
    noecho(); // Não exibe os caracteres digitados.
    curs_set(FALSE); // Esconde o cursor.
    keypad(stdscr, TRUE); // Habilita o uso do teclado.
    halfdelay(velocidade); // Define a velocidade inicial.

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
            if(entrada == 'd' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) {
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Remove a peça da posição atual.
                coluna++; // Move a peça para a direita.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Adiciona a peça na nova posição.
            } 
            else if(entrada == 'a' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) {
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Remove a peça da posição atual.
                coluna--; // Move a peça para a esquerda.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Adiciona a peça na nova posição.
            } 
            else if(entrada == 's' && detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) {
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Remove a peça da posição atual.
                linha++; // Move a peça para baixo.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Adiciona a peça na nova posição.
                pontuacao++; // Incrementa a pontuação.
            } 
            else if(detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 1) {
                removeLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Remove a peça da posição atual.
                linha++; // Move a peça para baixo.
                adicionaLinhas(novaLinha, novaColuna, linha, coluna, peca[valorAleatorio], matriz); // Adiciona a peça na nova posição.
            } 
            else if(detectorColisao(entrada, linha, coluna, peca[valorAleatorio], matriz) == 0)
                break; // Sai do loop se houver colisão.
                

            pontuacao += pontosLinha(apagarLinhasCompletas(matriz)); // Atualiza a pontuação com base nas linhas apagadas.

            clear(); refresh(); // Limpa e atualiza a tela.
            imprimirTela(matriz, pontuacao); // Imprime a tela atualizada.

            if (pontuacao % 200 == 0)
                velocidade -= 0.5; // Aumenta a velocidade do jogo a cada 200 pontos.
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