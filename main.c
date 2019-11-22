#define NORMAL 0
#define BOMBA 1
#define FECHADO 2
#define ABERTO 3
#define CHECKPOINT 4 //Aqui foram definidas os valores para cada espaço, assim facilitando na compreensao na hora de programar
#define ATUAL 5

#define ESQUERDA 75
#define DIREITA 77
#define CIMA 72
#define BAIXO 80 //CODIGO DAS SETAS DO TECLADOS PARA LEITURA NO GETCHAR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio2.h>

void gerarCampo(int campo[][16],int minasTotais, int campoJogo[][16]){
    int minasGerar=minasTotais;
    int i,j;
    for (i=0;i<16;i++){
        for (int j=0;j<16;j++){
                campo[i][j]=NORMAL;
                campoJogo[i][j]=FECHADO;
                }
        }

    srand(time(NULL));

    campo[0][0]=CHECKPOINT;
    campoJogo[0][0]=CHECKPOINT;         // Gerar entrada e saida do campo minado nas posicoes matriciais
    campo[7][15]=CHECKPOINT;
    campoJogo[7][15]=CHECKPOINT;

    while (minasGerar>0){
            i=rand()%8;
            j=rand()%16;
            if(campo[i][j]==0 && campo[i][j]!=4){   // bombas geradas em posicoes randomicas
                campo[i][j]=BOMBA;
                if (campo[1][0]==BOMBA || campo[0][1]==BOMBA){
                    campo[1][0]=NORMAL;
                    campo[0][1]=NORMAL;
                    minasGerar++;
                }
                if (campo[7][14]==BOMBA || campo[6][14]==BOMBA){
                    campo[7][14]=NORMAL;
                    campo[6][14]=NORMAL;
                    minasGerar++;
                }
                minasGerar--;
            }
        }
    }

int contarBombas(int campoRevelado[][16],int x,int y){
    int qtdBombas=0;

    if (x==0 && y==0){
        if(campoRevelado[x+1][y]==BOMBA){
            qtdBombas=qtdBombas+1;
        }
        if(campoRevelado[x][y+1]==BOMBA){ // se a bomba estiver em posicao adjacente, cont +1
            qtdBombas=qtdBombas+1;
        }

    }
    else {
        if(campoRevelado[x+1][y]==BOMBA){
            qtdBombas=qtdBombas+1;
        }
        if(campoRevelado[x-1][y]==BOMBA){
            qtdBombas=qtdBombas+1;
        }
        if(campoRevelado[x][y+1]==BOMBA){
            qtdBombas=qtdBombas+1;
        }
        if(campoRevelado[x][y-1]==BOMBA){
            qtdBombas=qtdBombas+1;
        }
    }
        return qtdBombas;
    }

void imprimirBordas(){
                gotoxy(25,9);
                textbackground(BROWN);
                printf("                                ");

                gotoxy(25,18);
                textbackground(BROWN);                        // utilizamos a conio2 para dar cores ao projeto
                printf("                                ");

                for (int i=1;i<11;i++){
                    gotoxy(23,8+i);
                    textbackground(BROWN);
                    printf("  ");
                }
                 for (int i=1;i<11;i++){
                    gotoxy(57,8+i);
                    textbackground(BROWN);
                    printf("  ");
                }

                textbackground(BLACK);}

void imprimir(int campo[][16]){
    for (int i=0;i<8;i++){
        for (int j=0;j<16;j++){

                if(campo[i][j]==3){
                    gotoxy(25+j*2, 10+i);
                    textbackground(LIGHTCYAN);
                    printf("  ");

                }

                else if(campo[i][j]==ATUAL){
                    gotoxy(25+j*2, 10+i);
                    textbackground(BLUE);
                    printf("  ");
                    textbackground(BLACK);
                }

                else if(campo[i][j]==FECHADO){
                         gotoxy(25+j*2, 10+i);
                    textbackground(WHITE);
                    printf("  ");
                }
                else if(campo[i][j]==BOMBA){
                     gotoxy(25+j*2, 10+i);
                    textbackground(RED);
                    printf("  ");
                }

                else if(campo[i][j]==4){
                     gotoxy(25+j*2, 10+i);
                    textbackground(GREEN);
                    printf("  ");
                }
                else if(campo[i][j]==0){
                     gotoxy(25+j*2, 10+i);
                    textbackground(WHITE);
                    printf("  ");
                }
            }
                textbackground(BLACK);
                printf("\n");
        }
}

void jogar(int campoJogo[][16], int campoRevelado[][16],int *pont){
    int x=0,y=0,qtBombas;
    char seta;
    while(1){
        qtBombas=contarBombas(campoRevelado,x,y);
        gotoxy(20,4);
        printf("Pontuacao:%d \t\tBombas proximas:%d\tX:%dY:%d",*pont,qtBombas,x,y);
        imprimirBordas();
        if (x==15 && y==7){
            clrscr();
            printf("Parabens! Seu pontuacao foi %d",*pont);
            imprimir(campoRevelado);                      // funcao para ganhar o jogo na posicao (15,7)
            imprimirBordas();
            delay(1000);
            getch();
            break;
        }
        gotoxy(1,1);
        qtBombas=contarBombas(campoRevelado,x,y);
        imprimir(campoJogo);

        //Parte da movimentacao
        seta = getch();

        if (seta==27){
            clrscr();
            printf("Voce apertou a tecla esc e saiu\nCampo Revelado:\n");
            imprimir(campoRevelado);
            imprimirBordas();
            delay(500);
            getch();
            break;                                                              // funcao para as setas do teclado funcionarem
        }

        if (x<15 && seta==DIREITA && campoJogo[y][x+1]!=5){
                *pont=*pont+1;
               campoJogo[y][x]=5;
               x++;
        }
        if (x>0 && seta==ESQUERDA && campoJogo[y][x-1]!=5){
                 *pont=*pont+1;
                campoJogo[y][x]=5;
                x--;
        }
        if (y>0 && seta==CIMA && campoJogo[y-1][x]!=5){
                 *pont=*pont+1;
                campoJogo[y][x]=5;
                y--;
        }
        if (y<7 && seta==BAIXO && campoJogo[y+1][x]!=5){
                *pont=*pont+1;
                campoJogo[y][x]=5;
                y++;
        }

        if (campoRevelado[x][y]==NORMAL){
            campoJogo[y][x]=ABERTO;

            }

        if (campoRevelado[y][x]==BOMBA){
            clrscr();
            printf("Boom! Vc perdeu! Pontuacao: %d\n", *pont);
            printf("\n\n\nCampo revelado:");
            imprimir(campoRevelado);
            imprimirBordas();
            delay(2000);
            printf("\nDigite qualquer tecla para continuar...");
            getch();
            break;
        }
        system("cls");
        qtBombas=contarBombas(campoRevelado,x,y);
    }
}

int main(){
    int pontuacao=0,minasTotais=20,opcao;
    int campo[16][16],campoJogo[16][16];
    int a, b, c, d ,e;
    FILE *arqPontuacao;

    while(1){
    clrscr();
    printf("\t\t\tCampo Minado");
    textcolor(RED);                             // menu e iniciar jogo chamando a funcao
    printf("\t\tBOOM!\n");
    textcolor(LIGHTGRAY);
    printf("1-Novo jogo\n2-Recordes\n3-Apagar arquivos\n4-Sair\n");
    printf("\nDigite uma opcao:");
    scanf("%i",&opcao);
    switch(opcao){
    case 1:
    clrscr();
    gerarCampo(campo,minasTotais,campoJogo);
    jogar(campoJogo,campo,&pontuacao);

    arqPontuacao=fopen("recordes.txt","a+");
    fprintf(arqPontuacao,"%i\n",pontuacao);
    fclose(arqPontuacao);

    pontuacao=0;

    break;
    case 2:
        clrscr();
        arqPontuacao = fopen("recordes.txt", "r");
        if(arqPontuacao==NULL){
            printf("Erro ao abrir arquivo!");
        }
        else{
            printf("\t\tRecordes anteriores\n");                            //demos read no arquivo gerado e printamaos nos recordes
        fscanf(arqPontuacao, "%i%i%i%i%i", &a, &b, &c,&d,&e);
        printf("\n-%i\n-%i\n-%i\n-%i\n-%i",a,b,c,d,e);
        }
        fclose(arqPontuacao);
        getch();
        break;

    case 3:
        clrscr();
        printf("DESEJA APAGAR OS ULTIMOS RECORDES? ESSA ACAO NÃO PODE SER DESFEITA:\n1-SIM 2-NAO\n");
        int opremover;
        scanf("%d",&opremover);
        if (opremover==1){
        remove("recordes.txt");
        clrscr();
        printf("Recordes apagados...Aperte qualquer tecla para prosseguir"); // apagamos os arquivos
        }
        getch();
        break;
    case 4:
        clrscr();
        exit(0);
        break;
    default:
    printf("Valor invalido, selecione uma opcao valida!\n"); //protecao
    getch();
        }
    }
    return 0;
}
