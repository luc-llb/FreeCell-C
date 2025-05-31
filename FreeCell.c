#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>

typedef struct no{
	short int numCarta;
	char naipe;
	struct no *prox;
}tCarta;

//inicializando ponteiro das mesas
tCarta *primMesa[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

//incializando pilha de nipes
tCarta *primNape[4] = {NULL, NULL, NULL, NULL};

//inicializando o temporário
tCarta *tempo[4] = {NULL, NULL, NULL, NULL};

//inicializando o monte
tCarta *primMonte = NULL;

//matriz usada para controlar e já embaralhar as cartas
int mat[4][13], fim;

void warning(char string[250]){ //printf versão Lucas
    int cont, i;
    
    cont = 0; //conta o numro de caracteres
    while(string[cont]!=0){
        cont++;
    }
    
    system("cls");
    
    //enfeites de cima
    printf("         %c", 201);
    for(i=0;i<cont;i++){
        printf("%c",205);
    }
    printf("%c\n", 187);

    //impressão da mensagem com enfeites laterais
    printf("         %c", 186);
    printf("%s\a", string);

    printf("%c\n", 186);

    //enfeites de baixo
    printf("         %c", 200);
    for(i=0;i<cont;i++){
        printf("%c",205);
    }
    printf("%c\n", 188);

    printf("\n\n");
}

void gerarBaralho(){ //gera e embaralha
	tCarta *novo;
    int i, j, cnt=0;

    //zera a matriz
    for(i=0;i<4;i++){
        for(j=0;j<13;j++){
            mat[i][j]=0;
        }
    }
    //sorteio de cartas
    while(cnt<52){
        i=rand()%4+3; //sorteia o naipe 
        j=rand()%13+1; //sorteia o numero
        if(mat[i-3][j-1]!=1){ //condicao para confirmar se a posicao (carta) já foi inclusa

            //aloca e passa os valores para o monte
            novo = (tCarta *) malloc(sizeof(tCarta));
            novo->numCarta = j;
            novo->naipe = i;
            novo->prox = primMonte;
            primMonte = novo;
            mat[i-3][j-1] = 1; //altera o valor na matriz para não repetir depois
            cnt++;
        }
    }//end while
}//end gerarBaralho

void distribuirMesa(){
	int i;
    tCarta *atual = primMonte; //anda no monte
    tCarta *aux; //troca a carta do monte para a mesa

    for(i=0;i<28;i++){ //para mesas de 7 cartas
        aux = atual;
        atual = atual->prox;
        aux->prox = primMesa[i%4];
        primMesa[i%4] = aux;
    }

    for(i=0;i<24;i++){ //para mesas de 6 cartas
        aux = atual;
        atual = atual->prox;
        aux->prox = primMesa[(i%4)+4];
        primMesa[(i%4)+4] = aux;
    }
}

void imprime(){
	int i, j, cont;
    tCarta *aux; //caminha pelos ponteiros

    //enfeite de cima
    printf("         %c", 201);
    for(i=0;i<74;i++){
        printf("%c",205);
    }
    printf("%c\n", 187);

    //impressão da Temp
    printf("         %c             [Temp]=", 186);
    for(i=0;i<4;i++){
        aux = tempo[i];
        if(aux!=NULL){
            if(aux->numCarta<10){
                printf("%d-[0%d/%c] ", i, aux->numCarta, aux->naipe);
            }else{
                printf("%d-[%d/%c] ", i, aux->numCarta, aux->naipe);
            }
        }else{
            printf("%d-[    ] ", i);
        }
    }

    //enfeite
    printf("                  %c", 186);  
    printf("\n         %c", 204);
    for(i=0;i<74;i++){
        printf("%c",205);
    }
    printf("%c\n", 185);

    //impressão do Naipe
    for(i=0;i<4;i++){
        cont = 0; //contador para ajustar o enfeite lateral
        aux = primNape[i];
        printf("         %c            [NAIPE %d]=", 186, i);
        while(aux!=NULL){
            if(aux->numCarta<=9){
                printf("[0%d/%c]", aux->numCarta, aux->naipe);
            }else{
                printf("[%d/%c]", aux->numCarta, aux->naipe);
            }
            cont+=6;
            aux = aux->prox;
        }

        //enfeite
        for(j=0;j<(52-cont);j++){
            printf(" ");
        }
        printf("%c", 186);

        printf("\n");
    }

    //enfeite
    printf("         %c", 204);
    for(i=0;i<74;i++){
        printf("%c",205);
    }
    printf("%c\n", 185);

    //impressão da mesa
    for(i=0;i<8;i++){
        cont = 0;
        aux = primMesa[i];
        printf("         %c[MESA %d]=", 186, i);
        while(aux!=NULL){
            if(aux->numCarta<10){
                printf("[0%d/%c]", aux->numCarta, aux->naipe);
            }else{
                printf("[%d/%c]", aux->numCarta, aux->naipe);
            }
            cont+=6;
            aux = aux->prox;
        }

        //enfeite
        for(j=0;j<(65-cont);j++){
            printf(" ");
        }
        printf("%c", 186);
        printf("\n");
    }

    //enfeite de baixo
    printf("         %c", 200);
    for(i=0;i<74;i++){
        printf("%c",205);
    }
    printf("%c\n", 188);
}


void moveMesaTemp(){
	int pos, t, i;
    tCarta *aux, *movimento;

    printf("\n         Informe a MESA de onde deseja retirar a carta: ");
    scanf("%d", &pos);

    if(pos>=0 && pos<8){ //limita o pos
        if(primMesa[pos]!=NULL){ //verifica se a mesa esta vazia

            printf("\n          Informe a posicao de TEMPORARIO: ");
            scanf("%d", &t);

            if(t>=0 && t<4){ //limita t
                i=0;
                aux = tempo[t];

                while(aux!=NULL){ //anda pela pilha de tempo para determinar o numero de itens
                    i++;
                    aux = aux->prox;
                }

                if(i==4){
                    warning("Posicao em TEMP esta CHEIA");
                }else{ //caso haja espaço
                    movimento = primMesa[pos];
                    primMesa[pos] = primMesa[pos]->prox;
                    movimento->prox = tempo[t];
                    tempo[t] = movimento;
                    system("cls");
                }
            }else{
                warning("A MESA esta vazia");
            }
        }else{
            warning("Informe uma posicao em TEMP existente");
        }
    }else{
        warning("Informe uma MESA existente");
    }
}

void moveTempMesa(){
    int mesa, t, i;
    tCarta *aux; //anda em primMesa

    printf("\n           Informe a pilha de TEMPORARIO que deseja retirar: ");
    scanf("%d", &t);

    if(t>=0 && t<=4){ //limita
        if(tempo[t]!=NULL){
            printf("\n           Informe a MESA em que deseja colocar: ");
            scanf("%d", &mesa);

            if(mesa>=0 && mesa<=7){ //limita
                if(primMesa[mesa]->numCarta == ((tempo[t]->numCarta)+1)){ //confere se o numero das cartas se difere em 1

                    if(tempo[t]->naipe == 3 || tempo[t]->naipe == 5){ //para naipes pretos

                        if(primMesa[mesa]->naipe == 4 || primMesa[mesa]->naipe == 6){ //confere se outro naipe é vermelho
                            aux = tempo[t];
                            tempo[t] = tempo[t]->prox;
                            aux->prox = primMesa[mesa];
                            primMesa[mesa]  = aux;
                            system("cls");
                        }else{
                            warning("Os NAIPES devem ser de cores opostas");
                        }

                    }else{
                        //caso venha para está parte o nipe é vermelho
                        if(primMesa[mesa]->naipe == 3 || primMesa[mesa] == 5){ //confere se outro naipe é preto
                            aux = tempo[t];
                            tempo[t] = tempo[t]->prox;
                            aux->prox = primMesa[mesa];
                            primMesa[mesa]  = aux;
                            system("cls");
                        }else{
                            warning("Os NAIPES devem ser de cores opostas");
                        }

                    }

                    }else{
                        warning("Apenas cartas MENORES em UMA UNIDADE da TEMP podem ser movidas para MESA");
                    }
            }else{
                warning("MESA inexistente");
            }
        }else{
            warning("A posicao de TEMPORARIO informada esta VAZIA");
        }
    }else{
        warning("Posicao de TEMPORARIO inexistente");
    }
}

void moveMesaNaipe(){
    int mesa,naipe;
    tCarta *aux;

    printf("\n         Informe a MESA que deseja retirar: ");
    scanf("%d", &mesa);

    if(mesa>=0 && mesa<=7){ //limita
        printf("\n         Informe a posicao de NAIPE que deseja colocar: ");
        scanf("%d", &naipe);

        if(naipe>=0 && naipe<=4){//limita

            if(primNape[naipe]==NULL){ //verifica se a pilha de Naipe está vazia

                if(primMesa[mesa]->numCarta==1){ //caso esteja, verifica se a primeira carta sera AS
                    aux = primMesa[mesa];
                    primMesa[mesa] = primMesa[mesa]->prox;
                    aux->prox = primNape[naipe];
                    primNape[naipe] = aux;
                    fim++; //contador para verificar se o jogo acabou
                    system("cls");
                }else{
                    warning("A posicao de NAIPE deve COMEÇAR com um AS(01)!");
                }

            }else{ 
                //verifica se a carta tem 1 de diferença 
                if(((primNape[naipe]->numCarta)+1) == primMesa[mesa]->numCarta){
                    //verifica se é o mesmo naipe
                    if(primNape[naipe]->naipe == primMesa[mesa]->naipe){
                        aux = primMesa[mesa];
                        primMesa[mesa] = primMesa[mesa]->prox;
                        aux->prox = primNape[naipe];
                        primNape[naipe] = aux;
                        fim++;
                        system("cls");
                    }else{
                        warning("Apenas cartas de MESMO NAIPE podem ser adicionados na posicao de NAIPE!");
                    }

                }else{
                    warning("Apenas VALORES MAIORES EM UMA UNIDADE podem ser adicionados na posicao de NAIPE!");
                }
            }

        }else{
            warning("Informe uma posicao de NAIPE valida!");
        }

    }else{
        warning("Informe uma MESA valida!");
    }
}

void destruirPilhas(){
    int i;
    tCarta *apaga; //recebe o valor a ser apagado
    free(primMonte);
    for(i=0;i<7;i++){ //limpa primMesa
        while(primMesa[i]!=NULL){
            apaga = primMesa[i];
            primMesa[i] = primMesa[i]->prox;
            free(apaga);
        }
        free(primMesa[i]);
    }
    
    for(i=0;i<4;i++){
        while(primNape[i]!=NULL){ //limpa primNape
            apaga = primNape[i];
            primNape[i] = primNape[i]->prox;
            free(apaga);
        }
        while(tempo[i]!=NULL){ //limpa primNape
            apaga = tempo[i];
            tempo[i] = tempo[i]->prox;
            free(apaga);
        }
        free(primNape[i]);
        free(tempo[i]);
    }
}

int main(int argc, char **argv){
    int op=0;
    srand(time(NULL));
    gerarBaralho();
    distribuirMesa();
    fim = 0; //será incrementado apenas quando houver um movimento bem sucedido de mesa para naipe
    warning("Seja bem-vindo(a) ao Free Cell");
    
    while(op!=4){
        imprime();
        printf("           1- Move Mesa-Temp\n");
        printf("           2- Move Mesa-Naipe\n");
        printf("           3- Move Temp-Mesa\n");
        printf("           4- Sair\n");
        printf("           Opcao: ");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                moveMesaTemp();
                break;
            case 2:
                moveMesaNaipe();
                break;
            case 3:
                moveTempMesa();
                break;
            case 4:
                break;

            default:
                warning("Opcao Invalida");
                break;
        }

        if(fim==52){ //checa se o jogo acabou
            warning("PARABENS voce venceu");
            break;
        }
    }
    destruirPilhas();
    return 0;
}