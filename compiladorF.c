
/* -------------------------------------------------------------------
 *            Aquivo: compilador.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [09/08/2020, 19h:01m]
 *
 * -------------------------------------------------------------------
 *
 * Funções auxiliares ao compilador
 *
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

/* -------------------------------------------------------------------
 *  variáveis globais
 * ------------------------------------------------------------------- */

simbolos simbolo, relacao;
char token[TAM_TOKEN];
int rotulos_cont = 0;

FILE *fp = NULL;
void geraCodigo(char *rot, char *comando)
{

	if (fp == NULL)
	{
		fp = fopen("MEPA", "w");
	}

	if (rot == NULL)
	{
		fprintf(fp, "     %s\n", comando);
		fflush(fp);
	}
	else
	{
		fprintf(fp, "%s: %s \n", rot, comando);
		fflush(fp);
	}
}

int imprimeErro(char *erro)
{
	fprintf(stderr, "Erro na linha %d - %s\n", nl, erro);
	exit(-1);
}

void inicializaPilhas(){
	l_elem_pilha = criaPilha(TAM_L_ELEM_PILHA, (TAM_L_ELEM_PILHA + 1) * sizeof(char));
	E = criaPilha(TAM_ETF_PILHA, sizeof(TIPOS));
    T = criaPilha(TAM_ETF_PILHA, sizeof(TIPOS));
    F = criaPilha(TAM_ETF_PILHA, sizeof(TIPOS));
    operacoes = criaPilha(TAM_OPERACOES_PILHA, sizeof(operacoes_t));
	rotulos = criaPilha(TAM_ROTULOS_PILHA, (ROT_SIZE + 1) * sizeof(char));
	pilha_num_vars = criaPilha(TAM_PILHA_NUM_VARS, sizeof(int));
}


int checaCategoria(SIMBOLO *simb)
{
	return (simb->categoria == var_simples || simb->categoria == param_formal || simb->categoria == procedimento || simb->categoria == funcao);
}

char *prox_rotulo() {
	char *rotulo = malloc((ROT_SIZE + 1) * sizeof(char));

    sprintf(rotulo, "R%.2d", rotulos_cont++);
    rotulo[ROT_SIZE + 1] = '\0';

    return rotulo;
}

char *opToString(operacoes_t operacao)
{
	switch (operacao)
	{
	case op_soma:
		return "SOMA";
	case op_subt:
		return "SUBT";
	case op_div:
		return "DIVI";
	case op_mult:
		return "MULT";
	case op_and:
		return "CONJ";
	case op_or:
		return "DISJ";
	case op_not:
		return "NEGA";
	case op_menor:
		return "CMME";
	case op_maior:
		return "CMMA";
	case op_igual:
		return "CMIG";
	case op_diferente:
		return "CMDG";
	case op_menor_igual:
		return "CMEG";
	case op_maior_igual:
		return "CMAG";
	default:
		return "inválido";
	}
}

void imprimeOp(void *operacao) {
	operacoes_t *op = operacao;
    printf("-----> %d\n", *op);
}
