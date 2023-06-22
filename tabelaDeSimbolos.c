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

PARAMETRO retornaParametro(SIMBOLO *simb) {
    PARAM_FORMAL *pf = simb->atributos;

    return pf->parametro;
}

void printVarSimples(VAR_SIMPLES *atributos) {
    printf("%10d %12s\n", atributos->deslocamento, imprimeTipo(atributos->tipo));
}

void printProcedimento(PROCEDIMENTO *atrib) {
    PARAM_FORMAL *atribParam;

    fprintf(stdout, " / Rotulo: %s / Params: %d {", atrib->rotulo, atrib->num_params);

    for (int i = 0; i < atrib->num_params; i++) {
        atribParam = atrib->parametros[i]->atributos;
        fprintf(stdout, " %s[%s,%s]", atrib->parametros[i]->id, imprimeTipo(atribParam->tipo), imprimeTipoParametro(atribParam->tipo));
    }

    fprintf(stdout, " }");
}

void printParamFormal(PARAM_FORMAL *atributos) {
    printf("%10d %12s %15s\n", atributos->deslocamento, imprimeTipo(atributos->tipo), imprimeTipoParametro(atributos->parametro));
}

void printFuncao(FUNCAO *atributos) {
    printf("%10d %12s %24s %14d\n", atributos->deslocamento, imprimeTipo(atributos->tipo), atributos->rotulo, atributos->num_params);
}

void imprimeSimbolo(void* item) {
    SIMBOLO *simb = item;
    printf("%3s %18s %6d", simb->id, imprimeCategoria(simb->categoria), simb->nivel_lex);

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

char *imprimeTipoParametro(PARAMETRO passagem) {
    switch (passagem) {
        case referencia:
            return "Referência";
        case valor:
            return "Valor";
        case param_indefinido:
            return "Indefinido";
        default:
            return "inválido";
    }
}

void imprimeTS(PILHA *TS, int tam) {
    printf("\n                                          TABELA DE SIMBOLOS\n----------------------------------------------------------------------------------------------------\n");
    printf(" id  |   categoria    | nivel_lex | Desloc |   Tipo   |  Parametro  |    Rotulo    |  Num Parametros\n----------------------------------------------------------------------------------------------------\n");
    imprimePilha(TS, imprimeSimbolo);
}

VAR_SIMPLES *criaVarSimples(TIPOS tipo, int deslocamento) {
    VAR_SIMPLES *atributos = malloc(sizeof(VAR_SIMPLES));

    atributos->tipo = tipo;
    atributos->deslocamento = deslocamento;

    return atributos;
}

PARAM_FORMAL *criaParamFormal(TIPOS tipo, int deslocamento, CATEGORIAS passagem) {
    PARAM_FORMAL *atributos = malloc(sizeof(PARAM_FORMAL));

    atributos->tipo = tipo;
    atributos->deslocamento = deslocamento;
    atributos->parametro = passagem;

    return atributos;
}

PROCEDIMENTO *criaAtrProcedimento(char *rotulo) {
    PROCEDIMENTO *atributos = malloc(sizeof(PROCEDIMENTO));

    atributos->rotulo = malloc(strlen(rotulo) * sizeof(char));
    strncpy(atributos->rotulo, rotulo, strlen(rotulo));
    atributos->rotulo[strlen(rotulo)] = '\0';
    atributos->num_params = 0;
    atributos->parametros = NULL;

    return atributos;
}

FUNCAO *criaAtrFuncao(char *rotulo) {
    FUNCAO *atributos = malloc(sizeof(FUNCAO));

    atributos->rotulo = malloc(strlen(rotulo) * sizeof(char));
    strncpy(atributos->rotulo, rotulo, strlen(rotulo));
    atributos->rotulo[strlen(rotulo)] = '\0';
    atributos->tipo = tipo_indefinido;
    atributos->deslocamento = 0;
    atributos->num_params = 0;
    atributos->parametros = NULL;

    return atributos;
}

// LABEL *criaAtrLabel(char *nome) {
//     LABEL *label = malloc(sizeof(LABEL));

//     label->rotulo = malloc(strlen(nome) * sizeof(char));
//     strncpy(label->rotulo, nome, strlen(nome));
//     label->rotulo[strlen(nome)] = '\0';

//     return label;
// }


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

void atualizaTipoParametro(PILHA *TS, PARAMETRO passagem, int n) {
    PARAM_FORMAL *atribParam;
    SIMBOLO *item;

    if ( !n ) return;

    if ((int) (TS->tamanho - 1 - n) < -1){
        fprintf(stderr, "ERRO - atualizaTipo() - stack smashed\n");
        exit(-1);
    }

    for (int i = TS->tamanho - 1; i > (int) TS->tamanho - 1 - (n); i--) {
        item = buscaItem(TS, i);
        
        atribParam = (PARAM_FORMAL *) (item->atributos);
        atribParam->parametro = passagem;
    }
}

void atualizaTipoFuncao(SIMBOLO *simb, TIPOS tipo) {
    if (simb->categoria != funcao) {
        fprintf(stderr, "ERRO - atualizaTipoFuncao() - simbolo não é função\n");
        exit(-1);
    }
    FUNCAO *aux_func = simb->atributos;
    aux_func->tipo = tipo;
}

SIMBOLO *retUltDaCategoria(PILHA *TS, CATEGORIAS categoria) {
    SIMBOLO *item;
    int i;

    for (i=TS->tamanho-1; i>-1; i--) {
        item = buscaItem(TS, i);
        if (item->categoria == categoria)
            return item;
    }
    return NULL;
}

void deletaPorNivelLexico(PILHA *TS, int nivel_lexico) {
    if (pilhaVazia(TS)) return;
    SIMBOLO *item;
    int i;

    for (i = TS->tamanho-1; i >= 0; i--) {
        item = buscaItem(TS, i);
        if (!item) {
            imprimeErro("ERRO - deletaPorNivelLexico() - stack smashed");
            exit(-1);
        }

        if (item->nivel_lex < nivel_lexico)
            return;
        
        TS->tamanho--;
        free(item);
    }
}


SIMBOLO *retornaUltimo(PILHA *TS, CATEGORIAS categoria) {
    SIMBOLO *item;

    for (int i = TS->tamanho - 1; i > -1; i--) {
        item = buscaItem(TS, i);
        
        if (item->categoria == categoria)
            return item;
    }

    return NULL;
}

void atualizaDesloc(PILHA *TS, int n) {
    PARAM_FORMAL *PF;
    PROCEDIMENTO *proc;
    FUNCAO *func;

    SIMBOLO *item, *simb;
    SIMBOLO **vetor_param;
    int cont = -4;
    int simbIndex = TS->tamanho - 1 - n;

    if ( !n ) return;

    if ((int) (TS->tamanho - 1 - n) < 0){
        fprintf(stderr, "ERRO - atualizaDesloc() - stack smashed\n");
        exit(-1);
    }

    simb = buscaItem(TS, simbIndex);
    if (simb->categoria == procedimento) {
        proc = simb->atributos;
        proc->num_params = n;
        proc->parametros = (SIMBOLO **)
            malloc(proc->num_params * sizeof(SIMBOLO *));
        vetor_param = proc->parametros;
    } else if (simb->categoria == funcao) {
        func = simb->atributos;
        func->num_params = n;
        func->deslocamento = cont - n;
        func->parametros = (SIMBOLO **)
            malloc(func->num_params * sizeof(SIMBOLO *));
        vetor_param = func->parametros;
    }

    for (int i = TS->tamanho - 1; i > (int) TS->tamanho - 1-(n); i--) {
        item = buscaItem(TS, i);

        PF = item->atributos;
        PF->deslocamento = cont--;

        vetor_param[i - simbIndex - 1] = (SIMBOLO *) copiaParamFormal(item);
    }
}

static SIMBOLO *copiaParamFormal(SIMBOLO *param) {
    PARAM_FORMAL *atrib = param->atributos;
    SIMBOLO *copy = malloc(sizeof(SIMBOLO));
    PARAM_FORMAL *atribCopy = criaParamFormal(
        atrib->tipo, atrib->deslocamento, atrib->parametro);
    
    char *ident = malloc(sizeof(char) * strlen(param->id));
    strncpy(ident, param->id, strlen(param->id));

    copy->id = ident;
    copy->categoria = param->categoria;
    copy->nivel_lex = param->nivel_lex;
    copy->atributos = atribCopy;

    return copy;
}

