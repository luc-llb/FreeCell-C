#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

typedef struct noCarta{
    short numero;
    char nape;
    struct noCarta *prox;
}tCarta;

tCarta *primMonte = NULL;
tCarta *primMesa[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
tCarta *primNape[] = {NULL,NULL,NULL,NULL};
tCarta *temp[] = {NULL,NULL,NULL,NULL};

bool ehVermelho(tCarta *carta){
    return ((carta->nape>=3) && (carta->nape<=4));
}//end ehVermelho

bool ehPreto(tCarta *carta){
    return ((carta->nape>=5)&&(carta->nape<=6));
}//end ehPreto

bool saoCoresDiferentes(tCarta *carta1, tCarta *carta2){
    return ((ehVermelho(carta1)&&ehPreto(carta2))||
             (ehPreto(carta1)&&ehVermelho(carta2)));
}//end saoCoresDiferentes

void warning(char string[250]){ //impressão de mensagens 
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

    printf("\n");
}

void gerarBaralho(){
    int i,j;
    tCarta *ult;

    //coracao=3, ouro=4, paus=5, espada=6
    for(i=0; i<4; i++){
        for(j=1; j<14; j++){
            if(primMonte==NULL){
                primMonte = (tCarta *)malloc(sizeof(tCarta));
                ult = primMonte;
            }//end if
            else{
                ult->prox=(tCarta *)malloc(sizeof(tCarta));
                ult=ult->prox;
            }//end else
            ult->nape=i+3;
            ult->numero=j;
            ult->prox=NULL;
        }//end for j
    }//end for i
}//end gerarBaralho

void embaralhaBaralho(){
    int i,j,sort;
    tCarta *ant, *atual;

    for(i=0; i<26; i++){
        //total de mudanca
        sort=rand()%52;
        ant=NULL;
        atual=primMonte;
        for(j=0; j<sort; j++){
            //localizar a carta no monte
            ant = atual;
            atual=atual->prox;
        }//end for j
        if(sort>0){
            ant->prox=atual->prox;
            atual->prox=primMonte;
            primMonte=atual;
        }//end if
    }//end for i
}//end embaralhaBaralho

void distribuirMesa(){
    int i=0;
    tCarta *auxMonte, *auxMesa;

    while(primMonte != NULL){
        auxMonte = primMonte;
        primMonte=primMonte->prox;

        if(primMesa[i]==NULL){
            primMesa[i]=auxMonte;
            primMesa[i]->prox=NULL;
        }//end if
        else{
            auxMesa=primMesa[i];
            primMesa[i]=auxMonte;
            primMesa[i]->prox=auxMesa;
        }//end else
        if(primMonte==NULL){
            break;
        }//end if
        i=(i+1)%8;
    }//end while
}//end distribuirMesa

void imprime(){
    int i;
    tCarta *atual;

    for(i=0;i<76;i++){
        printf("%c",205);
    }
    printf("\n");

    printf("[TEMP]=");
    for(i=0; i<4; i++){
        if(temp[i]!=NULL){
            printf("%d[%02d/%c] ", i, temp[i]->numero,temp[i]->nape);
        }//end if
        else{
            printf("%d[    ] ", i);
        }//end else
    }//end for i
    printf("\n");

    for(i=0;i<76;i++){
        printf("%c",205);
    }
    printf("\n");

    for(i=0; i<4; i++){
        atual=primNape[i];
        printf("[NAPE %d]=", i);
        while(atual!=NULL){
            printf("[%02d/%c]", atual->numero,atual->nape);
            atual=atual->prox;
        }//end while
        printf("\n");
    }//end for i

    for(i=0;i<76;i++){
        printf("%c",205);
    }
    printf("\n");

    for(i=0; i<8; i++){
        atual=primMesa[i];
        printf("[MESA %d]=", i);
        while(atual!=NULL){
            printf("[%02d/%c]", atual->numero, atual->nape);
            atual=atual->prox;
        }//end while
        printf("\n");
    }//end for i

    for(i=0;i<76;i++){
        printf("%c",205);
    }
    printf("\n");

}//end imprime

void moveMesaNape(){
    int posMesa, posNape;
    tCarta *aux, *ant, *atual;

    printf("Posicao Pilha Mesa (0-7): ");
    scanf("%d", &posMesa);
    getchar();
    if((posMesa>=0)&&(posMesa<=7)&&(primMesa[posMesa]!=NULL)){
        printf("Posicao Nape (0-3): ");
        scanf("%d", &posNape);
        getchar();
        ant = NULL;
        atual=primMesa[posMesa];
        while(atual->prox!=NULL){
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posNape>=0)&&(posNape<=3)&&
           (((atual->numero==1)&&(primNape[posNape]==NULL))||
           ((primNape[posNape]!=NULL)&&
            (atual->nape==primNape[posNape]->nape)&&
            (atual->numero-1==primNape[posNape]->numero)))){
            if(ant==NULL){
                primMesa[posMesa]=NULL;
            }else{
            ant->prox=NULL; /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
            }//end else
            if(primNape[posNape]==NULL){
                primNape[posNape]=atual;
                system("cls");
            }//end if
            else{
                aux = primNape[posNape];
                primNape[posNape]=atual;
                primNape[posNape]->prox=aux;
                system("cls");
            }//end else
        }//end if
        else{
            warning("Nao pode mover carta para nape");
        }//end else
    }//end if
    else{
        warning("Pilha invalida ou vazia");
    }//end else
}//end moveMesaNape

void moveMesaTemp(){
    int posMesa, posTemp;
    tCarta *ant, *atual, *aux;

    printf("Posicao Pilha Mesa (0-7): ");
    scanf("%d", &posMesa);
    getchar();
    if((posMesa>=0)&&(posMesa<=7)&&(primMesa[posMesa]!=NULL)){
        printf("Posicao Temp (0-3): ");
        scanf("%d", &posTemp);
        getchar();
        ant=NULL;
        atual=primMesa[posMesa];
        while(atual->prox!=NULL){
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]==NULL)){
           if(ant==NULL){
                primMesa[posMesa]=NULL;
                system("cls");
           }else{
           ant->prox=NULL;    /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
           temp[posTemp]=atual;  /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
           system("cls");
           }//end else
        }//end if
        else{
            warning("Nao pode mover carta para temp");
        }//end else
    }//end if
    else{
        warning("Pilha invalida ou vazia");
    }//end else
}//end moveMesaTemp

void moveTempMesa(){
    int posTemp, posMesa;
    tCarta *atual;
    printf("Posicao Temp (0-3): ");
    scanf("%d",&posTemp);
    getchar();
    if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]!=NULL)){
        printf("Posicao Pilha Mesa (0-7): ");
        scanf("%d", &posMesa);
        getchar();
        if((posMesa>=0)&&(posMesa<=7)){
            if(primMesa[posMesa]==NULL){
                primMesa[posMesa]=temp[posTemp];
                temp[posTemp]=NULL;
                system("cls");
            }//end if
            else{
                atual=primMesa[posMesa];
                while(atual->prox!=NULL){
                    atual=atual->prox;
                }//end while
                if((saoCoresDiferentes(temp[posTemp],atual))&&
                   ((atual->numero-1==temp[posTemp]->numero))){
                    atual->prox=temp[posTemp];
                    temp[posTemp]=NULL;
                    system("cls");
                }//end if
                else{
                    warning("Nao pode mover temp para mesa");
                }//end else
            }//end else
        }//end if
    }//end if
    else{
        warning("Temp vazio");
    }//end else
}//end moveTempMesa

//---------------------------segunda parte-----------------------

void moveNapeTemp(){
    int tempo, naipe;
    tCarta *aux;

    printf("Informe a pilha de Naipe da qual deseja retirar a carta: ");
    scanf("%d", &naipe);

    if(naipe>-1 && naipe<4){ //delimitação
        if(primNape[naipe]!=NULL){ //verificando se há carta na pilha

            printf("Informe a pilha de TEMP em que deseja colocar a carta: ");
            scanf("%d", &tempo);

            if(tempo>-1 && tempo<4){
                if(temp[tempo]==NULL){
                    aux = primNape[naipe];
                    primNape[naipe] = primNape[naipe]->prox;
                    aux->prox = temp[tempo];
                    temp[tempo] = aux;
                    system("cls");
                }else{
                    warning("A pilha de TEMP deve estar VAZIA!");
                }
            }else{
                warning("Selecione uma pilha VALIDA!");
            }
        }else{
            warning("Selecione uma pilha de NAIPE que nao esteja VAZIA!");
        }
    }else{
        warning("Selecione uma pilha VALIDA!");
    }
}

void moveTempNape(){
    int posTemp, posNape;
    tCarta *aux, *ant, *atual;

    printf("Informe a pilha de TEMP: ");
    scanf("%d", &posTemp);
    getchar();
    if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]!=NULL)){
        printf("Informe a pilha de NAIPE: ");
        scanf("%d", &posNape);
        getchar();
        ant = NULL;
        atual=temp[posTemp];
        while(atual->prox!=NULL){
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posNape>=0)&&(posNape<=3)&&
           (((atual->numero==1)&&(primNape[posNape]==NULL))||
           ((primNape[posNape]!=NULL)&&
            (atual->nape==primNape[posNape]->nape)&&
            (atual->numero-1==primNape[posNape]->numero)))){
            if(ant==NULL){
                temp[posTemp]=NULL;
            }else{
            ant->prox=NULL; /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
            }//end else
            if(primNape[posNape]==NULL){
                primNape[posNape]=atual;
                system("cls");
            }//end if
            else{
                aux = primNape[posNape];
                primNape[posNape]=atual;
                primNape[posNape]->prox=aux;
                system("cls");
            }//end else
        }//end if
        else{
            warning("Nao pode mover carta para NAPE");
        }//end else
    }//end if
    else{
        warning("TEMP invalida ou vazia");
    }//end else
}

void moveNapeMesa(){
    int posNape, posMesa;
    tCarta *atual, *aux;
    printf("Posicao nape (0-3): ");
    scanf("%d",&posNape);
    getchar();
    if((posNape>=0)&&(posNape<=3)&&(primNape[posNape]!=NULL)){
        printf("Posicao Pilha Mesa (0-7): ");
        scanf("%d", &posMesa);
        getchar();
        if((posMesa>=0)&&(posMesa<=7)){
            if(primMesa[posMesa]==NULL){
                primMesa[posMesa]=primNape[posNape];
                primNape[posNape]=NULL;
                system("cls");
            }else{
                atual=primMesa[posMesa];
                while(atual->prox!=NULL){
                    atual=atual->prox;
                }//end while
                if((saoCoresDiferentes(primNape[posNape],atual))&&
                    ((atual->numero-1==primNape[posNape]->numero))){
                    aux = primNape[posNape];                       // aux pega o primeiro valor do naipe
                    primNape[posNape] = primNape[posNape]->prox;     // 2o valor do naipe agora é o primeiro
                    atual->prox = aux;
                    aux->prox=NULL;
                    system("cls");
                }else{
                    printf("Nao pode mover nape para mesa\n");
                }//end else
            }//end else
        }//end if
    }else{
        printf("nape vazio\n");
    }//end else
}

void moveMesaMesa(){
    tCarta *Carta,*aux,*ini, *atual,*penultimo;
    int posMesa1=75,posMesa2=99,i,op;

    if((posMesa1<0)||(posMesa1>=8)){
        if(posMesa1!=75){
            warning("Erro");
        }//end for
        printf("Indique a mesa de origem: ");
        scanf(" %d",&posMesa1);
    }//end while

    if((posMesa2<0)||(posMesa2>=8)){
        if(posMesa2!=99){
           warning("Erro");
        }//end for
        printf("Indique a mesa de destino: ");
        scanf(" %d",&posMesa2);
    }//end while

    if(primMesa[posMesa1]==NULL){
        warning("Erro");
        return;
    }

    //encontra sequencia ou ultimo elem
    ini = primMesa[posMesa1];
    aux = primMesa[posMesa1];
    atual = primMesa[posMesa1];

    while(atual!=NULL){

        if(((aux->nape == 3)||(aux->nape == 4))&&((atual->nape == 6)||
            (atual->nape == 5))&&(aux->numero - atual->numero == 1)){

            aux = atual;
            atual = atual->prox;

        }else if(((aux->nape == 5)||(aux->nape == 6))&&((atual ->nape == 3)||
                (atual->nape == 4))&&(aux->numero - atual->numero == 1)){

            aux = atual;
            atual = atual->prox;

        }else{

            aux = atual;
            ini = aux;
            atual = atual->prox;

        }//end else

    }//end while


    //encontra penultimo
    penultimo = primMesa[posMesa1];
    while((penultimo->prox!=ini)&&(penultimo!=ini)){
        penultimo = penultimo->prox;
    }//end while

    if(primMesa[posMesa2]==NULL){
        primMesa[posMesa2] = ini;
        if(primMesa[posMesa1]==ini){
            primMesa[posMesa1] = NULL;
        }else{
            penultimo->prox = NULL;
        }
        return;
    }//end if mesa 2 vazia

    Carta = primMesa[posMesa2];
    while(Carta->prox!=NULL){
        Carta = Carta->prox; //descobre ultimo elemento da mesa de destino
    }//end while

    //init regras do jogo.
    if(((Carta->nape == 3)||(Carta->nape == 4))&&((ini->nape == 6)||
        (ini->nape == 5))&&(Carta->numero - ini->numero == 1)){

        Carta->prox = ini;
        if(primMesa[posMesa1]==ini){
            primMesa[posMesa1] = NULL;
        }else{
            penultimo->prox = NULL;
        }
        system("cls");
    }else if(((Carta->nape == 5)||(Carta->nape == 6))&&((ini ->nape == 3)||
            (ini->nape == 4))&&(Carta->numero - ini->numero == 1)){
        Carta->prox = ini;
        if(primMesa[posMesa1]==ini){
            primMesa[posMesa1] = NULL;
        }else{
            penultimo->prox = NULL;
        }
        system("cls");
    }else{

        warning("Erro");
        return;

    }//end else
    return;

}//end move mesa-mesa

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
        while(temp[i]!=NULL){ //limpa primNape
            apaga = temp[i];
            temp[i] = temp[i]->prox;
            free(apaga);
        }
        free(primNape[i]);
        free(temp[i]);
    }
}

int main(int argc, char **argv){
    int op=0, cnt, i;
    srand(time(NULL));
    gerarBaralho();
    embaralhaBaralho();
    distribuirMesa();

    warning("Bem vindo(a) oa Free Cell");

    while(op!=8){
        imprime();
        printf("(1) Move Mesa-Nape\n");
        printf("(2) Move Mesa-Temp\n");
        printf("(3) Move Temp-Mesa\n");
        printf("(4) Move Nape-Temp\n");
        printf("(5) Move Temp-Nape\n");
        printf("(6) Move Nape-Mesa\n");     
        printf("(7) Move Mesa-Mesa\n");    
        printf("(8) Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch(op){
            case 1:
                moveMesaNape();
                break;

            case 2:
                moveMesaTemp();
                break;

            case 3:
                moveTempMesa();
                break;

            case 4:
                moveNapeTemp();
                break;

            case 5:
                moveTempNape();
                break;

            case 6:
                moveNapeMesa();
                break;

            case 7:
                moveMesaMesa();
                break;

            case 8:
                warning("Obrigado por jogar(^-^)");

            default:
                system("cls");
                printf("Opcao Invalida\n");
                break;
        }//end switch

        //confere se ainda há cartas fora das pilhas de naipe
        cnt = 0;
        for(i=0;i<8;i++){ //caso a primeira carta da pilha seja nula a pilha estara vazia
            if(primMesa[i]==NULL){
                cnt++;
            }
        }
        for(i=0;i<4;i++){
            if(temp[i]==NULL){
                cnt++;
            }
        }
        if(cnt==12){ //o jogo eh encerrado e considera-se vitoria
            system("cls");
            op = 8;
            warning("VOCÊ GANHOU!!!!!!!");
            printf("Como normalmente esse jogo eh utilizado para relaxar\n");
            printf("Caso ainda tenha um tempo e deseje relaxar mais um pouco, segue o link:\n");
            printf("https://www.youtube.com/watch?v=Y_plhk1FUQA");
        }

    }//end while
    destruirPilhas();
    return 0;
}//end main