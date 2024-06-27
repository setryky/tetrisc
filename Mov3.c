#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main()
{
    int pontuacao = 0;
    int velocidade = 3;
    int matriz[10][10]={0};
    int i, j, l=0, c=0, ro=0, rotacoes=0, viradas=0;
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

   //peça I rot            //peça T rotações                                                        //L espe. rotações                                                        //S rotação
   prodada[0].Linha[0]=2;   prodada[1].Linha[0]=2;  prodada[2].Linha[0]=2;  prodada[3].Linha[0]=2;   prodada[4].Linha[0]=2;   prodada[5].Linha[0]=2;  prodada[6].Linha[0]=2;   prodada[7].Linha[0]=2;
   prodada[0].Coluna[0]=5;  prodada[1].Coluna[0]=5; prodada[2].Coluna[0]=5; prodada[3].Coluna[0]=5;  prodada[4].Coluna[0]=5;  prodada[5].Coluna[0]=5; prodada[6].Coluna[0]=5;  prodada[7].Coluna[0]=5;
   prodada[0].Linha[1]=2;   prodada[1].Linha[1]=1;  prodada[2].Linha[1]=3;  prodada[3].Linha[1]=1;   prodada[4].Linha[1]=2;   prodada[5].Linha[1]=1;  prodada[6].Linha[1]=3;   prodada[7].Linha[1]=2;
   prodada[0].Coluna[1]=6;  prodada[1].Coluna[1]=5; prodada[2].Coluna[1]=5; prodada[3].Coluna[1]=5;  prodada[4].Coluna[1]=6;  prodada[5].Coluna[1]=5; prodada[6].Coluna[1]=6;  prodada[7].Coluna[1]=6;
   prodada[0].Linha[2]=2;   prodada[1].Linha[2]=3;  prodada[2].Linha[2]=2;  prodada[3].Linha[2]=3;   prodada[4].Linha[2]=2;   prodada[5].Linha[2]=3;  prodada[6].Linha[2]=2;   prodada[7].Linha[2]=1;
   prodada[0].Coluna[2]=4;  prodada[1].Coluna[2]=5; prodada[2].Coluna[2]=4; prodada[3].Coluna[2]=5;  prodada[4].Coluna[2]=4;  prodada[5].Coluna[2]=5; prodada[6].Coluna[2]=4;  prodada[7].Coluna[2]=5;
   prodada[0].Linha[3]=2;   prodada[1].Linha[3]=2;  prodada[2].Linha[3]=2;  prodada[3].Linha[3]=2;   prodada[4].Linha[3]=1;   prodada[5].Linha[3]=1;  prodada[6].Linha[3]=2;   prodada[7].Linha[3]=3;
   prodada[0].Coluna[3]=3;  prodada[1].Coluna[3]=6; prodada[2].Coluna[3]=6; prodada[3].Coluna[3]=4;  prodada[4].Coluna[3]=4;  prodada[5].Coluna[3]=6; prodada[6].Coluna[3]=6;  prodada[7].Coluna[3]=6;

   //S espe. rotação       //L rotações
   prodada[8].Linha[0]=2;  prodada[9].Linha[0]=2;  prodada[10].Linha[0]=2;  prodada[11].Linha[0]=2;
   prodada[8].Coluna[0]=5; prodada[9].Coluna[0]=5; prodada[10].Coluna[0]=5; prodada[11].Coluna[0]=5;
   prodada[8].Linha[1]=1;  prodada[9].Linha[1]=2;  prodada[10].Linha[1]=1;  prodada[11].Linha[1]=2;
   prodada[8].Coluna[1]=6; prodada[9].Coluna[1]=6; prodada[10].Coluna[1]=5; prodada[11].Coluna[1]=6;
   prodada[8].Linha[2]=2;  prodada[9].Linha[2]=2;  prodada[10].Linha[2]=3;  prodada[11].Linha[2]=2;
   prodada[8].Coluna[2]=6; prodada[9].Coluna[2]=4; prodada[10].Coluna[2]=5; prodada[11].Coluna[2]=4;
   prodada[8].Linha[3]=3;  prodada[9].Linha[3]=3;  prodada[10].Linha[3]=1;  prodada[11].Linha[3]=1;
   prodada[8].Coluna[3]=5; prodada[9].Coluna[3]=4; prodada[10].Coluna[3]=4; prodada[11].Coluna[3]=6;

//fazer uma copia do gabarito
for(int n=0; 7>n; n++){
    for(int k=0; 4>k; k++){
        copia[n].Coluna[k]=peca[n].Coluna[k];
        copia[n].Linha[k]=peca[n].Linha[k];
    }
}

for(int li=0; 10>li; li++){
    for(int co=0; 10>co; co++){
        printf("%d ", matriz[li][co]);
    }
    printf("\n");
}

int valorAleatorio = Aleatorio();
//mover as peças
while(scanf(" %c", &entrada)!=EOF){

    system("cls");
//mover para a direita
    if(entrada=='d'){
        for(int k=0; 4>k;k++){
            i=l+peca[valorAleatorio].Linha[k];
            j=c+peca[valorAleatorio].Coluna[k];
            matriz[i][j]=0;
        }
        c=c+1;
        for(int k=0; 4>k;k++){
            i=l+peca[valorAleatorio].Linha[k];
            j=c+peca[valorAleatorio].Coluna[k];
            matriz[i][j]=1;
        }
    }
// para a esquerda
    else if(entrada=='a'){
        for(int k=0; 4>k;k++){
            i=l+peca[valorAleatorio].Linha[k];
            j=c+peca[valorAleatorio].Coluna[k];
            matriz[i][j]=0;
        }
        c=c-1;
        for(int k=0; 4>k;k++){
            i=l+peca[valorAleatorio].Linha[k];
            j=c+peca[valorAleatorio].Coluna[k];
            matriz[i][j]=1;
        }
    }
//para baixo
    else if(entrada=='s'){
        for(int k=0; 4>k;k++){
            i=l+peca[valorAleatorio].Linha[k];
            j=c+peca[valorAleatorio].Coluna[k];
            matriz[i][j]=0;
        }
        l=l+1;
        for(int k=0; 4>k;k++){
            i=l+peca[valorAleatorio].Linha[k];
            j=c+peca[valorAleatorio].Coluna[k];
            matriz[i][j]=1;
        }
    }
//rodar a I
    else if(entrada=='r' && valorAleatorio==0){
        rotacoes++;  //conta a quantidade de rotações
        for(int k=0; 4>k;k++){ //apaga a peça 
            i=l+peca[0].Linha[k];
            j=c+peca[0].Coluna[k];
            matriz[i][j]=0;
        }
        for(int k=0; 4>k; k++){//atualiza o gabarito normal para ficar igual a do rodado
            peca[0].Linha[k]=prodada[0].Linha[k];
            peca[0].Coluna[k]=prodada[0].Coluna[k];
        }

        if(rotacoes==2){ //se chegar nesse numero é pq voltou para a posição normal ent atualiza o gabarito normal de voltar para como era antes 
            for(int k=0; 4>k; k++){
                peca[0].Linha[k]=copia[0].Linha[k];
                peca[0].Coluna[k]=copia[0].Coluna[k];
            }
            rotacoes=0;// para poder começar a girar de novo
        }
        
        for(int k=0; 4>k;k++){// imprimir a peça
            i=l+peca[0].Linha[k];
            j=c+peca[0].Coluna[k];
            matriz[i][j]=1;
        }
    }
//rodar T
    else if(entrada=='r' && valorAleatorio==1){
        rotacoes++;
        for(int k=0; 4>k;k++){
            i=l+peca[1].Linha[k];
            j=c+peca[1].Coluna[k];
            matriz[i][j]=0;
        }
        for(int k=0; 4>k; k++){
            peca[1].Linha[k]=prodada[rotacoes].Linha[k];
            peca[1].Coluna[k]=prodada[rotacoes].Coluna[k];
        }

        if(rotacoes==4){
            for(int k=0; 4>k; k++){
                peca[1].Linha[k]=copia[1].Linha[k];
                peca[1].Coluna[k]=copia[1].Coluna[k];
            }
            rotacoes=0;
        }
        
        for(int k=0; 4>k;k++){
            i=l+peca[1].Linha[k];
            j=c+peca[1].Coluna[k];
            matriz[i][j]=1;
        }
    }
//rodar L espe.
    else if(entrada=='r' && valorAleatorio==5){
        rotacoes++;
        for(int k=0; 4>k;k++){
            i=l+peca[5].Linha[k];
            j=c+peca[5].Coluna[k];
            matriz[i][j]=0;
        }
        for(int k=0; 4>k; k++){
            peca[5].Linha[k]=prodada[rotacoes+3].Linha[k]; // faz a soma para alcançar a respectiva peça no gabarito das rodadas 
            peca[5].Coluna[k]=prodada[rotacoes+3].Coluna[k];
        }

        if(rotacoes==4){
            for(int k=0; 4>k; k++){
                peca[5].Linha[k]=copia[5].Linha[k];
                peca[5].Coluna[k]=copia[5].Coluna[k];
            }
            rotacoes=0;
        }
        
        for(int k=0; 4>k;k++){
            i=l+peca[5].Linha[k];
            j=c+peca[5].Coluna[k];
            matriz[i][j]=1;
        }
    }
//rodar S
    else if(entrada=='r' && valorAleatorio==2){
        rotacoes++;
        for(int k=0; 4>k;k++){
            i=l+peca[2].Linha[k];
            j=c+peca[2].Coluna[k];
            matriz[i][j]=0;
        }
        for(int k=0; 4>k; k++){
            peca[2].Linha[k]=prodada[rotacoes+6].Linha[k];
            peca[2].Coluna[k]=prodada[rotacoes+6].Coluna[k];
        }

        if(rotacoes==2){
            for(int k=0; 4>k; k++){
                peca[2].Linha[k]=copia[2].Linha[k];
                peca[2].Coluna[k]=copia[2].Coluna[k];
            }
            rotacoes=0;
        }
        
        for(int k=0; 4>k;k++){
            i=l+peca[2].Linha[k];
            j=c+peca[2].Coluna[k];
            matriz[i][j]=1;
        }
    }
//rodar L
    else if(entrada=='r' && valorAleatorio==3){
        rotacoes++;
        for(int k=0; 4>k;k++){
            i=l+peca[3].Linha[k];
            j=c+peca[3].Coluna[k];
            matriz[i][j]=0;
        }
        for(int k=0; 4>k; k++){
            peca[3].Linha[k]=prodada[rotacoes+8].Linha[k];
            peca[3].Coluna[k]=prodada[rotacoes+8].Coluna[k];
        }

        if(rotacoes==4){
            for(int k=0; 4>k; k++){
                peca[3].Linha[k]=copia[3].Linha[k];
                peca[3].Coluna[k]=copia[3].Coluna[k];
            }
            rotacoes=0;
        }
        
        for(int k=0; 4>k;k++){
            i=l+peca[3].Linha[k];
            j=c+peca[3].Coluna[k];
            matriz[i][j]=1;
        }
    }
// S espe.
 else if(entrada=='r' && valorAleatorio==6){
        rotacoes++;
        for(int k=0; 4>k;k++){
            i=l+peca[6].Linha[k];
            j=c+peca[6].Coluna[k];
            matriz[i][j]=0;
        }
        for(int k=0; 4>k; k++){
            peca[6].Linha[k]=prodada[rotacoes+7].Linha[k];
            peca[6].Coluna[k]=prodada[rotacoes+7].Coluna[k];
        }

        if(rotacoes==2){
            for(int k=0; 4>k; k++){
                peca[6].Linha[k]=copia[6].Linha[k];
                peca[6].Coluna[k]=copia[6].Coluna[k];
            }
            rotacoes=0;
        }
        
        for(int k=0; 4>k;k++){
            i=l+peca[6].Linha[k];
            j=c+peca[6].Coluna[k];
            matriz[i][j]=1;
        }
    }

    for(int li=0; 10>li; li++){
        for(int co=0; 10>co; co++){
            printf("%d ", matriz[li][co]);
        }
        printf("\n");
    }
}

return 0;
}
