#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>

typedef struct PILHA {
    void** itens;
    int capacidade;
    int tamanho;
    size_t tam_dado;  // tamanho do dado que será armazenado
} PILHA;

PILHA* criaPilha(int capacidade, size_t tam_tipoDeDado);
void empilha(PILHA* pilha, void* item);
void* desempilha(PILHA* pilha);
void* topo(PILHA* pilha);
int checaVazia(PILHA* pilha);
void limpa(PILHA* pilha);
void destroiPilha(PILHA* pilha);

#endif
