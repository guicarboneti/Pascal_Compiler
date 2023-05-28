#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

PILHA* criaPilha(int capacidade, size_t tam_tipoDeDado) {
    PILHA* pilha = (PILHA*)malloc(sizeof(PILHA));
    pilha->itens = malloc(capacidade * tam_tipoDeDado);
    pilha->capacidade = capacidade;
    pilha->tamanho = 0;
    pilha->tam_dado = tam_tipoDeDado;
    return pilha;
}

void empilha(PILHA* pilha, void* item) {
    if (pilha->tamanho >= pilha->capacidade) {
        printf("Estouro da pilha!\n");
        return;
    }
    pilha->itens[pilha->tamanho++] = item;
}

void* desempilha(PILHA* pilha) {
    if (pilha->tamanho <= 0) {
        printf("Pilha vazia!\n");
        return NULL;
    }
    return pilha->itens[--pilha->tamanho];
}

void* topo(PILHA* pilha) {
    if (pilha->tamanho <= 0) {
        printf("Pilha vazia!\n");
        return NULL;
    }
    return pilha->itens[pilha->tamanho - 1];
}

int pilhaVazia(PILHA* pilha) {
    return pilha->tamanho == 0;
}

void limpa(PILHA* pilha) {
    pilha->tamanho = 0;
}

void destroiPilha(PILHA* pilha) {
    free(pilha->itens);
    free(pilha);
}

void *buscaItem(PILHA *pilha, int pos) {
    return (void *) (pilha->itens + (pilha->tam_dado * pos));
}
