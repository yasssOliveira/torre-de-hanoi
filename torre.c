#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/*função que imprime as três pilhas
Recebe três pilhas do tipo tipoPilha e um inteiro indicando a quantidade de discos como 
parâmetro
Não retorna nada
cria três vetores, que armazenam os elementos das três pilhas, e imprime esses vetores
linha a linha, até chegar ao final das pilhas*/
void imprime (tipoPilha* p1, tipoPilha* p2, tipoPilha* p3, int qtdDiscos){
    tipoPilha* pilhas[] = {p1, p2, p3};
    tipoNo* topos[3] = {p1->topo, p2->topo, p3->topo};
    int discos[3] = {0, 0, 0};

    for(int cont = 0; cont < 3; cont++){
        tipoNo* atual = pilhas[cont]->topo;
        while(atual){
            discos[cont]++;
            atual = atual->prox;
        }
    }
    printf("\t  torres\n\n");
    for(int cont = qtdDiscos-1; cont >= 0; cont--){
        for(int i = 0; i < 3; i++){
            if(discos[i] > cont){
                printf("    %d   ", topos[i]->info);
                topos[i] = topos[i]->prox;
            }
            else{
                printf("        ");
            }
        }
        printf("\n");
    }
    printf(" |-----| |-----| |-----|\n    1       2       3  \n");
}

/*função que checa se uma jogada é valida ou não
Recebe uma pilha do tipo tipoPilha e dois inteiros topo e disco como parâmetro
Retorna um numero inteiro
caso a pilha esteja vazia ou o elemento do topo da pilha seja maior que o disco,
retorna uma jogada válida, caso contrário, retorna 0 e uma mensagem indicando 
jogada inválida*/
int jogadaValida(tipoPilha* pilha, int topo, int disco){  
    if(pilha->topo == NULL || topo > disco){
        return 1;
    }
 
    printf("a pilha de destino eh menor que o disco que voce deseja mover. tente novamente!\n\n");


    return 0;
}

/*função que define o criterio de vitória do jogo
Recebe três pilhas do tipo tipoPilha e um inteiro que indica a quantidade de discos como
parâmetro
Retorna um numero inteiro
caso a pilha1 (inicial) esteja vazia, checa qual das pilhas está cheia. na pilha
correspondente, inicia um contador com o mesmo valor do primeiro elemento da pilha (1), que aumenta
em uma unidade a cada elemento que passa. 
caso esse contador e o elemento sejam diferentes, é retornado 0, caso sejam iguais, o contador 
aumenta em uma unidade e o próximo elemento é checado. 
se ao final, o contador e a quantidade de discos forem iguais, significa que a 
pilha está na ordem correta, indicando a vitória do jogador e o fim do jogo*/
int vitoria(tipoPilha* pilha, int qtdDiscos){
    int contador = 1;
    tipoNo* atual = pilha->topo;

    while(atual){
        if(atual->info != contador){
            return 0;
        }
        else{
            contador++;
            atual = atual->prox;
        }
    }

    if(contador == qtdDiscos+1){
        printf("\n\t\t  VITORIA!\n\n\t\tFIM DO JOGO!\n\n");
        return 1;
    }
    return 0;
}

/*função que recebe a entrada do usuário (jogada)
Recebe três pilhas do tipo tipoPilha e um inteiro que indica a quantidade de discos
como parâmetro
Não retorna nada
imprime o jogo da maneira inicial. após isso, entra num loop, que recebe as entradas 
do jogador
caso essas entradas estejam fora do parâmetro, as recebe novamente
após isso define a pilha de onde o disco deve sair e a nova pilha onde o disco deve entrar
caso a nova pilha de entrada não esteja vazia, retorna o elemento que esta no topo, se não, 
o topo recebe 0. 
depois, caso a jogada seja válida, coloca o disco no topo da nova pilha,
caso a jogada seja inválida, o disco retorna pro topo da pilha que ele saiu
ao final, se o usuário estiver ganhado o jogo, imprime uma mensagem de vitória e
encerra o programa*/
void recebeJogada(tipoPilha* p1, tipoPilha* p2, tipoPilha* p3, int qtdDiscos){
    int jogada1, jogada2, disco, topo;
    tipoPilha *saida = NULL, *entrada = NULL;
    
    imprime(p1, p2, p3, qtdDiscos);

    while(!(vitoria(p2, qtdDiscos) || vitoria(p3, qtdDiscos))){
        printf("\njogada (numero,numero): ");
        if(scanf("%d,%d", &jogada1, &jogada2) != 2){
            printf("formato de entrada invalido. tente novamente!");
            continue;
        }
        if(((jogada1 > 3 || jogada1 < 1) || (jogada2 > 3 || jogada2 < 1)) || (jogada1 == jogada2)){
            printf("jogada invalida! tente novamente!!");
            continue;
        }
        printf("\n");
        switch (jogada1){
        case 1:
            saida = p1;
            break;
        case 2:
            saida = p2;
            break;
        case 3:
            saida = p3;
            break;
        }

        disco = pop(saida);
        if(disco == -1){
            continue;
        }

        switch (jogada2){
        case 1:
            entrada = p1;
            break;
        case 2:
            entrada = p2;
            break;
        case 3:
            entrada = p3;
            break;
        }
    
        if(entrada->topo != NULL){
            topo = entrada->topo->info;
        }
        else{
            topo = 0;
        }

        if(jogadaValida(entrada, topo, disco)){
            push(entrada, disco);
        }
        else{
            push(saida, disco);
        }

        imprime(p1, p2, p3, qtdDiscos);
    }
}


int main(void){
    //criando as pilhas
    tipoPilha* p1 = criaPilha();
    tipoPilha* p2 = criaPilha();
    tipoPilha* p3 = criaPilha();
    int discos;

    //mensagens de interação com o usuário
    printf("\n\n*************************************************\n");
    printf("*\t\tTORRE DE HANOI\t\t\t*\n");
    printf("*************************************************\n\n\n");
    printf("   quantidade de discos que deseja na torre: ");
    scanf("%d", &discos); //recebe a quantidade de discos
    printf("\n");

    //insere a quantidade de discos desejada na primeira pilha
    int i = discos;
    for(int cont = 0; cont < discos; cont++){
        push(p1, i);
        i--;
    }    

    //chamada da função que recebe as jogadas e desenvolve o jogo
    recebeJogada(p1, p2, p3, discos);
    liberaPilha(p1);
    liberaPilha(p2);
    liberaPilha(p3);

    return 0;
}

