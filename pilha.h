#include <stdio.h>
#include <stdlib.h>

typedef struct tipoNo tipoNo;

typedef struct tipoNo{
    int info;
    tipoNo* prox;
    tipoNo* ant;
}tipoNo;

typedef struct tipoPilha{
    tipoNo* topo;
}tipoPilha;

/*função que cria uma pilha
Não recebe nada como parâmetro
Retorna uma pilha criada
cria uma variável pilha do tipo tipoPilha, realiza a alocação de memória e define a pilha
como vazia*/
tipoPilha* criaPilha();

/*função que insere um elemento na pilha
Recebe uma pilha do tipo tipoPilha e um inteiro disco como parâmetro
Não retorna nada
insere o elemento recebido no parâmetro no final da pilha e os próximos no topo da pilha*/
void push(tipoPilha* pilha, int disco);

/*função que remove um elemento da pilha
Recebe uma pilha do tipo tipoPilha como parâmetro
Retorna um numero inteiro
checa se a pilha está vazia, caso esteja, retorna -1 e uma mensagem, caso não esteja vazia,
retira e retorna o elemento do topo da pilha, depois seta o elemento após o que foi retirado
como novo topo da pilha*/
int pop(tipoPilha* pilha);

/*função que libera a memória alocada para as pilhas
Recebe uma pilha do tipo tipoPilha como parâmetro 
Não retorna nada
desempilha todos os elementos da pilha e libera a memória alocada*/
void liberaPilha(tipoPilha* pilha);
