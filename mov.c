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

int detectorColisao(char entrada, int aleatorio, int l, int c, peca peca, int matriz[20][10]) {
    for(int k = 0; k < 4; k++){
        int i = l + peca.Linha[k];
        int j = c + peca.Coluna[k];
        if(aleatorio == 0 && (entrada == 's' && i == 21 || entrada == 'd' && j == 11 || entrada == 's' && j == 0 || matriz[i][j])) return 0;
        else if(aleatorio == 1 && (entrada == 's' && i == 20 || entrada == 'd' && j == 10 || entrada == 's' && j == 1)) return 0;
        else if(aleatorio == 2 && (entrada == 's' && i == 21 || entrada == 'd' && j == 10 || entrada == 's' && j == 1)) return 0;
        else if(aleatorio == 3 && (entrada == 's' && i == 21 || entrada == 'd' && j == 10 || entrada == 's' && j == 0)) return 0;
        else if(aleatorio == 4 && (entrada == 's' && i == 23 || entrada == 'd' && j == 10 || entrada == 's' && j == 0)) return 0;
        else if(aleatorio == 5 && (entrada == 's' && i == 23 || entrada == 'd' && j == 10 || entrada == 's' && j == 1)) return 0;
        else if(aleatorio == 6 && (entrada == 's' && i == 22 || entrada == 'd' && j == 11 || entrada == 's' && j == 1)) return 0;
    }
    return 1;
}

int main()
{
    int pontuacao = 0;
    int velocidade = 3;
    int matriz[20][10]={0};
    int i, j, l=0, c=0, ro=0;
    char entrada;
    peca peca[7];

    //peça I             //peça T             //peça S             //peça L             //cubo               //L espe.            //S espe.
    peca[0].Linha[0]=2;  peca[1].Linha[0]=2;  peca[2].Linha[0]=2;  peca[3].Linha[0]=2;  peca[4].Linha[0]=2;  peca[5].Linha[0]=2;  peca[6].Linha[0]=2;
    peca[0].Coluna[0]=5; peca[1].Coluna[0]=5; peca[2].Coluna[0]=5; peca[3].Coluna[0]=5; peca[4].Coluna[0]=5; peca[5].Coluna[0]=5; peca[6].Coluna[0]=5;
    peca[0].Linha[1]=1;  peca[1].Linha[1]=2;  peca[2].Linha[1]=2;  peca[3].Linha[1]=1;  peca[4].Linha[1]=1;  peca[5].Linha[1]=2;  peca[6].Linha[1]=1;
    peca[0].Coluna[1]=5; peca[1].Coluna[1]=4; peca[2].Coluna[1]=4; peca[3].Coluna[1]=5; peca[4].Coluna[1]=5; peca[5].Coluna[1]=4; peca[6].Coluna[1]=5;
    peca[0].Linha[2]=3;  peca[1].Linha[2]=2;  peca[2].Linha[2]=1;  peca[3].Linha[2]=3;  peca[4].Linha[2]=1;  peca[5].Linha[2]=2;  peca[6].Linha[2]=2;
    peca[0].Coluna[2]=5; peca[1].Coluna[2]=6; peca[2].Coluna[2]=5; peca[3].Coluna[2]=5; peca[4].Coluna[2]=6; peca[5].Coluna[2]=6; peca[6].Coluna[2]=4;
    peca[0].Linha[3]=4;  peca[1].Linha[3]=1;  peca[2].Linha[3]=1;  peca[3].Linha[3]=3;  peca[4].Linha[3]=2;  peca[5].Linha[3]=1;  peca[6].Linha[3]=3;
    peca[0].Coluna[3]=5; peca[1].Coluna[3]=5; peca[2].Coluna[3]=6; peca[3].Coluna[3]=6; peca[4].Coluna[3]=6; peca[5].Coluna[3]=6; peca[6].Coluna[3]=4;

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    halfdelay(velocidade);


    while(1){

        int valorAleatorio = Aleatorio();
        i = 0;
        j = 0;
        l = 0;
        c = 0;
        while(i != 19){

            entrada = getch();

            if(entrada == 'd' && detectorColisao(entrada, valorAleatorio, l, c + 1, peca[valorAleatorio], matriz)){
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
            else if(entrada == 'a' && detectorColisao(entrada, valorAleatorio, l, c - 1, peca[valorAleatorio], matriz)) {
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
            else if(entrada == 's' && detectorColisao(entrada, valorAleatorio, l + 1, c, peca[valorAleatorio], matriz)){
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
            else if(i != 19){
                for(int k = 0; 4 > k; k++){
                    i=l+peca[valorAleatorio].Linha[k];
                    j=c+peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 0;
                }
                l++;
                for(int k = 0; 4 > k; k++){
                    i=l+peca[valorAleatorio].Linha[k];
                    j=c+peca[valorAleatorio].Coluna[k];
                    matriz[i][j] = 1;
                }
            }

            clear();

            for(int li = 0; 22 > li; li++){
                for(int co = 0; 12 > co; co++){
                    if(co == 0 || co == 11 || li == 0 || li == 21)  mvprintw(li, co, "#");
                    else if(matriz[li][co] == 1) mvprintw(li, co, "1");
                    else mvprintw(li, co, " ");
                }
                mvprintw(22, 0, "Pontuacao: %d", pontuacao);
                refresh();
            }
        }
    }

endwin();
return 0;
}
