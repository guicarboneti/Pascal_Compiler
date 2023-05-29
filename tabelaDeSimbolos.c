#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"
#include "tabelaDeSimbolos.h"

void inicializaTS(PILHA *TS, int tam) {
    *TS = *criaPilha(tam, sizeof(SIMBOLO));
}

// insere simbolo no topo da pilha
void insere(PILHA *TS, char *id, CATEGORIAS categoria, void *atributos, int nivel_lex) {
    SIMBOLO *simbolo = malloc(sizeof(SIMBOLO));
    char *ident = malloc(sizeof(char) * strlen(id));    // ?
    strncpy(ident, id, strlen(id));
    simbolo->id = ident;
    simbolo->categoria = categoria;
    simbolo->atributos = atributos;
    simbolo->nivel_lex = nivel_lex;

    empilha(TS, simbolo);
}

// devolve o índice na TS correspondente à última ocorrência de id
int busca(PILHA *TS, char *id) {
    if (pilhaVazia(TS)) return -1;

    SIMBOLO *item;

    for (int i = TS->tamanho; i >= 0; i--) {
        item = buscaItem(TS, i);
        if (!strcmp(item->id, id))            
            return i;
    }
}

// retira do topo da pilha as n últimas entradas 
void elimina(PILHA *TS, int n) {
    TS->tamanho -= n;
    return;
}

void printVarSimples(VAR_SIMPLES *atributos) {
    // printf(" / Desloc: %d / Tipo: %s", atributos->deslocamento, tipoToString(atributos->tipo));
}

void printParamFormal(PARAM_FORMAL *atributos) {
    return;
}

void printProcedimento(PROCEDIMENTO *atributos) {
    return;
}

void printFuncao(FUNCAO *atributos) {
    return;
}


void imprimeSimbolo(void* item) {
    SIMBOLO *simb = item;
    printf("%s: %d %d \n", simb->id, simb->categoria, simb->nivel_lex);

    switch (simb->categoria) {
        case var_simples:
            printVarSimples(simb->atributos);
            break;
        case param_formal:
            printParamFormal(simb->atributos);
            break;
        case procedimento:
            printProcedimento(simb->atributos);
            break;
        case funcao:
            printFuncao(simb->atributos);
            break;
        default:
            break;
    }
}

void imprimeTS(PILHA *TS, int tam) {
    imprimePilha(TS, imprimeSimbolo);
}

VAR_SIMPLES *criaVarSimples(TIPOS tipo, int deslocamento) {
    VAR_SIMPLES *atributos = malloc(sizeof(VAR_SIMPLES));

    atributos->tipo = tipo;
    atributos->deslocamento = deslocamento;

    return atributos;
}