#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"
#include "tabelaDeSimbolos.h"
#include "compilador.h"

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
int buscaSimbolo(PILHA *TS, char *id) {
    if (pilhaVazia(TS)) return -1;

    SIMBOLO *item;

    for (int i = TS->tamanho-1; i >= 0; i--) {
        item = buscaItem(TS, i);
        if (!strcmp(item->id, id))            
            return i;
    }

    return -1;
}

// retira do topo da pilha as n últimas entradas 
void elimina(PILHA *TS, int n) {
    TS->tamanho -= n;
    return;
}

char *imprimeTipo(TIPOS tipo) {
    char *aux;
    switch (tipo) {
        case inteiro:
            aux = "inteiro";
            break;
        case booleano:
            aux = "booleano";
            break;
        case tipo_indefinido:
            aux = "indefinido";
            break;
    }
    return aux;
}

char *imprimeCategoria(CATEGORIAS categoria) {
    char *aux;
    switch (categoria) {
        case var_simples:
            aux = "variavel simples";
            break;
        case param_formal:
            aux = "parametro formal";
            break;
        case procedimento:
            aux = "procedimento";
            break;
        case funcao:
            aux = "funcao";
            break;
    }
    return aux;
}

void printVarSimples(VAR_SIMPLES *atributos) {
    printf("         %d       %s\n", atributos->deslocamento, imprimeTipo(atributos->tipo));
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
    printf(" %s       %s       %d", simb->id, imprimeCategoria(simb->categoria), simb->nivel_lex);

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
    printf("\n                        PILHA\n----------------------------------------------------------\n");
    printf(" id  |     categoria      | nivel_lex | Desloc |   Tipo\n----------------------------------------------------------\n");
    imprimePilha(TS, imprimeSimbolo);
}

VAR_SIMPLES *criaVarSimples(TIPOS tipo, int deslocamento) {
    VAR_SIMPLES *atributos = malloc(sizeof(VAR_SIMPLES));

    atributos->tipo = tipo;
    atributos->deslocamento = deslocamento;

    return atributos;
}

void atualizaTipoVar(PILHA *TS, TIPOS tipo, int num_vars) {
    int i;
    SIMBOLO *item;
    VAR_SIMPLES *VS;
    PARAM_FORMAL *PF;
    if (!num_vars) return;

    for(i=0; i<num_vars; i++) {
        item = buscaItem(TS, TS->tamanho-i-1);
        if (!item) {
            imprimeErro("ERRO - atualizaTipoVar() - stack smashed");
            exit(-1);
        }
        if (item->categoria == var_simples) {
            VS = item->atributos;
            VS->tipo = tipo;
        }
        else if (item->categoria == param_formal) {
            PF = item->atributos;
            PF->tipo = tipo;
        }
    }

}