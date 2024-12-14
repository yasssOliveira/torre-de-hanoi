#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"


tipoPilha* criaPilha(){
    tipoPilha* pilha = (tipoPilha*) malloc(sizeof(tipoPilha));
    pilha->topo = NULL;
    return pilha;
}

void push(tipoPilha* pilha, int disco){
    tipoNo* no = (tipoNo*) malloc(sizeof(tipoNo));
    no->info = disco;
    no->prox = pilha->topo;
    pilha->topo = no;
}

int pop(tipoPilha* pilha){    
    if(pilha->topo == NULL){
        printf("jogada invalida. pilha vazia! tente novamente!\n");
        return -1;
    }

    tipoNo* troca = pilha->topo;
    int disco;
    pilha->topo = pilha->topo->prox;
    disco = troca->info;
    free(troca);
    
    return disco;
}

void liberaPilha(tipoPilha* pilha){
    tipoNo* atual = pilha->topo;
    tipoNo* troca;

    while (atual) {
        troca = atual;         
        atual = atual->prox;  
        free(troca);           
    }
    free(pilha);
}

