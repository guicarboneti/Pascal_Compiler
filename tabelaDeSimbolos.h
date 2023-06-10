#ifndef TABELA_DE_SIMBOLOS_H
#define TABELA_DE_SIMBOLOS_H

#include "pilha.h"

#define TS_TAM 100

typedef enum CATEGORIAS {
    var_simples, param_formal, procedimento, funcao
} CATEGORIAS;

typedef enum TIPOS {
    inteiro, booleano, tipo_indefinido
} TIPOS;

typedef enum PARAMETRO {
    valor, referencia, param_indefinido
} PARAMETRO;

typedef struct SIMBOLO {
    char *id;
    CATEGORIAS categoria;
    int nivel_lex;
    void *atributos;
} SIMBOLO;

typedef struct VAR_SIMPLES {
    TIPOS tipo;
    int deslocamento;
} VAR_SIMPLES;

typedef struct PARAM_FORMAL {
    TIPOS tipo;
    int deslocamento;
    PARAMETRO parametro;
} PARAM_FORMAL;

typedef struct PROCEDIMENTO {
    char *rotulo;
    int num_params;
    SIMBOLO **parametros;
} PROCEDIMENTO;

typedef struct FUNCAO {
    char *rotulo;
    int deslocamento;
    TIPOS tipo;
    int num_params;
    SIMBOLO **parametros;
} FUNCAO;

void inicializaTS(PILHA *TS, int tam);

// insere simbolo no topo da pilha
void insere(PILHA *TS, char *id, CATEGORIAS categoria, void *atributos, int nivel_lex);

// devolve o índice na TS correspondente à última ocorrência de id
int buscaSimbolo(PILHA *TS, char *id);

// retira do topo da pilha as n últimas entradas 
void elimina(PILHA *TS, int n);

void imprimeTS(PILHA *TS, int tam);

VAR_SIMPLES *criaVarSimples(TIPOS tipo, int deslocamento);

void atualizaTipoVar(PILHA *TS, TIPOS tipo, int num_vars);

void printVarSimples(VAR_SIMPLES *atributos);

void printParamFormal(PARAM_FORMAL *atributos);

void printProcedimento(PROCEDIMENTO *atributos);

void printFuncao(FUNCAO *atributos);

char *imprimeTipo(TIPOS tipo);

char *imprimeCategoria(CATEGORIAS categoria);

/* a completar aqui */

#endif