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

typedef struct STRUCT_LABEL {
    char *nome;
    int nivel_lex;
} STRUCT_LABEL;

void inicializaTS(PILHA *TS, int tam);

// insere simbolo no topo da pilha
void insere(PILHA *TS, char *id, CATEGORIAS categoria, void *atributos, int nivel_lex);

// devolve o índice na TS correspondente à última ocorrência de id
int buscaSimbolo(PILHA *TS, char *id);

// retira do topo da pilha as n últimas entradas 
void elimina(PILHA *TS, int n);

void imprimeTS(PILHA *TS, int tam);

VAR_SIMPLES *criaVarSimples(TIPOS tipo, int deslocamento);

PARAM_FORMAL *criaParamFormal(TIPOS tipo, int deslocamento, CATEGORIAS passagem);

PROCEDIMENTO *criaAtrProcedimento(char *rotulo);

FUNCAO *criaAtrFuncao(char *rotulo);

void atualizaTipoVar(PILHA *TS, TIPOS tipo, int num_vars);

void atualizaTipoParametro(PILHA *TS, PARAMETRO passagem, int n);

void atualizaTipoFuncao(SIMBOLO *simb, TIPOS tipo);

SIMBOLO *retUltDaCategoria(PILHA *TS, CATEGORIAS categoria);

SIMBOLO *retUltDoNivelLex(PILHA *TS, int nivel_lex);

void printVarSimples(VAR_SIMPLES *atributos);

void atualizaDesloc(PILHA *TS, int n);

void printParamFormal(PARAM_FORMAL *atributos);

void printProcedimento(PROCEDIMENTO *atributos);

void printFuncao(FUNCAO *atributos);

char *imprimeTipo(TIPOS tipo);

char *imprimeCategoria(CATEGORIAS categoria);

char *imprimeTipoParametro(PARAMETRO passagem);

PARAMETRO retornaParametro(SIMBOLO *simb);

SIMBOLO *retornaUltimo(PILHA *TS, CATEGORIAS categoria);

static SIMBOLO *copiaParamFormal(SIMBOLO *param);

// Deleta simbolos do nivel lexico especificado
void deletaPorNivelLexico(PILHA *TS, int nivel_lexico);

#endif