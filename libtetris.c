#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define LINHAS 22
#define COLUNAS 12

//função que define a peça aleatoriamente. O horário da máquina é usado como seed para a função "rand()";
int Aleatorio(){
    time_t tempoAtual;
    time(&tempoAtual);
    srand(tempoAtual);
    int Aleatorio = rand() % 7;
    return Aleatorio;
}


