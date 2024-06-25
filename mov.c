#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <sys/queue.h>

typedef struct{
    int Linha[4];
    int Coluna[4];
}peca;

int Aleatorio(){
    time_t tempoAtual;
    time(&tempoAtual);
    srand(tempoAtual);
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

void descerLinhas(int matriz[22][12], int linhaParou, int linhasApagadas){
    for(int l = 1 ; l < (linhaParou + linhasApagadas); l++){
        for(int c = 1; c < 12; c++){
            matriz[l+1][c] = matriz[l][c];
        }
    }
}

int apagarLinhasCompletas(int matriz[22][12]) {
    int i, j, g, linhasApagadas = 0, primeiraLinha = 0;
    for(i = 1; i < 20; i++) {
        g = 0;
        for(j = 1; j < 11; j++) if(matriz[i][j] == 1) g++;

        if(g == 10){
            if(primeiraLinha == 0) primeiraLinha = i;
            for(j = 1; j < 12; j++) matriz[i][j] = 0;
            linhasApagadas++;
        }
    }
    descerLinhas(matriz, primeiraLinha, linhasApagadas);
    return linhasApagadas;
}

int detectorColisao(char entrada, int aleatorio, int l, int c, peca peca, int matriz[22][12]) {
    for(int k = 0; k < 4; k++){
        int i = l + peca.Linha[k];
        int j = c + peca.Coluna[k];
        if((i == 20 || entrada == 'd' && j == 10 || entrada == 'a' && j == 1)) return 0;
    }
    return 1;
}

void imprimirTela(int matriz[22][12], int pontuacao){
    clear();
    for(int li = 0; 22 > li; li++){
        for(int co = 0; 12 > co; co++){
            if(co == 0 || co == 11 || li == 0 || li == 21)  mvprintw(li, co, "@");
            else if(matriz[li][co] == 1) mvprintw(li, co, "#");
            else if(matriz[li][co] == 0) mvprintw(li, co, ".");
            }
        mvprintw(22, 0, "Pontuacao: %d", pontuacao);
        refresh();
        }
}

int main()
{
    int pontuacao = 0;
    int velocidade = 3;
    int matriz[22][12]={0};
    int i, j, l=0, c=0, ro=0;
    char entrada;
    peca peca[7];

    //peça I             //peça T             //peça S             //peça L             //cubo               //L espe.            //S espe.
    peca[0].Linha[0]=2;  peca[1].Linha[0]=2;  peca[2].Linha[0]=2;  peca[3].Linha[0]=2;  peca[4].Linha[0]=2;  peca[5].Linha[0]=2;  peca[6].Linha[0]=2;
    peca[0].Coluna[0]=5; peca[1].Coluna[0]=5; peca[2].Coluna[0]=5; peca[3].Coluna[0]=5; peca[4].Coluna[0]=5; peca[5].Coluna[0]=5; peca[6].Coluna[0]=5;
    peca[0].Linha[1]=1;  peca[1].Linha[1]=2;  peca[2].Linha[1]=2;  peca[3].Linha[1]=1;  peca[4].Linha[1]=1;  peca[5].Linha[1]=1;  peca[6].Linha[1]=1;
    peca[0].Coluna[1]=5; peca[1].Coluna[1]=4; peca[2].Coluna[1]=4; peca[3].Coluna[1]=5; peca[4].Coluna[1]=5; peca[5].Coluna[1]=5; peca[6].Coluna[1]=5;
    peca[0].Linha[2]=3;  peca[1].Linha[2]=2;  peca[2].Linha[2]=1;  peca[3].Linha[2]=3;  peca[4].Linha[2]=1;  peca[5].Linha[2]=3;  peca[6].Linha[2]=2;
    peca[0].Coluna[2]=5; peca[1].Coluna[2]=6; peca[2].Coluna[2]=5; peca[3].Coluna[2]=5; peca[4].Coluna[2]=6; peca[5].Coluna[2]=5; peca[6].Coluna[2]=6;
    peca[0].Linha[3]=4;  peca[1].Linha[3]=1;  peca[2].Linha[3]=1;  peca[3].Linha[3]=3;  peca[4].Linha[3]=2;  peca[5].Linha[3]=3;  peca[6].Linha[3]=1;
    peca[0].Coluna[3]=5; peca[1].Coluna[3]=5; peca[2].Coluna[3]=6; peca[3].Coluna[3]=6; peca[4].Coluna[3]=6; peca[5].Coluna[3]=4; peca[6].Coluna[3]=4;

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    halfdelay(velocidade);


    for(int valorAleatorio = Aleatorio(); 1; valorAleatorio = Aleatorio(), i = 0, j = 0, l = 0, c = 0){
        while(i != 19 && (valorAleatorio == 1 || valorAleatorio == 2 || valorAleatorio == 6) || i != 20 && (valorAleatorio == 0 || valorAleatorio == 3 || valorAleatorio == 4 || valorAleatorio == 5)){

            entrada = getch();

            if(entrada == 'd' && detectorColisao(entrada, valorAleatorio, l, c, peca[valorAleatorio], matriz)){
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 0;
                }
                c++;
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 1;
                }
            }
            else if(entrada == 'a'  && detectorColisao(entrada, valorAleatorio, l, c, peca[valorAleatorio], matriz)) {
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 0;
                }
                c--;
                for(int k = 0; 4 > k; k++){
                    i =l + peca[valorAleatorio].Linha[k];
                    j =c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 1;
                }

            }
            else if(entrada == 's' && detectorColisao(entrada, valorAleatorio, l, c, peca[valorAleatorio], matriz)){
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 0;
                }
                l++;
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 1;
                }
                pontuacao++;
            }
            else if(detectorColisao(entrada, valorAleatorio, l, c, peca[valorAleatorio], matriz)){
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 0;
                }
                l++;
                for(int k = 0; 4 > k; k++){
                    i = l + peca[valorAleatorio].Linha[k];
                    j = c + peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 1;
                }
            }
            int linhasApagadas = apagarLinhasCompletas(matriz);
            pontuacao += pontosLinha(linhasApagadas);
            imprimirTela(matriz, pontuacao);
        }
    }

endwin();
return 0;
}
