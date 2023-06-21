
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
SIMBOLO *simb_proc;
char comando_buffer[50];

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

void inicializaPilhas()
{
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

char *prox_rotulo()
{
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

void carregaValor(SIMBOLO *simb) {
    VAR_SIMPLES *vs_aux;
    PARAM_FORMAL *pf_aux;

    if (simb->categoria == var_simples) {
		vs_aux = simb->atributos;
		sprintf(comando_buffer, "CRVL %d,%d", simb->nivel_lex, vs_aux->deslocamento);
    }
	else if (simb->categoria == param_formal) {
		pf_aux = simb->atributos;
		sprintf(comando_buffer, "CRVL %d,%d", simb->nivel_lex, pf_aux->deslocamento);
	}
	else
		imprimeErro("Símbolo inválido para carregamento");

    geraCodigo(NULL, comando_buffer);
}

void carregaEndereco(SIMBOLO *simb) {
    VAR_SIMPLES *vs_aux;
    PARAM_FORMAL *pf_aux;

    if (simb->categoria == var_simples) {
		vs_aux = simb->atributos;
		sprintf(comando_buffer, "CREN %d,%d", simb->nivel_lex, vs_aux->deslocamento);
	}
	else if (simb->categoria == param_formal) {
		pf_aux = simb->atributos;
		sprintf(comando_buffer, "CREN %d,%d", simb->nivel_lex, pf_aux->deslocamento);
	}
	else
		imprimeErro("Símbolo inválido para carregamento");

    geraCodigo(NULL, comando_buffer);
}

void carregaIndireto(SIMBOLO *simb) {
    PARAM_FORMAL *pf_aux = simb->atributos;
    sprintf(comando_buffer, "CRVI %d,%d", simb->nivel_lex, pf_aux->deslocamento);

    geraCodigo(NULL, comando_buffer);
}

void comandoCarrega(SIMBOLO *simb) {
	PARAM_FORMAL *pf_aux;
	PROCEDIMENTO *proc_aux;
	FUNCAO *func_aux;

	if (simb_proc && simb_proc->categoria == procedimento) {
		proc_aux = simb_proc->atributos;
		
		if (num_params > proc_aux->num_params)
			imprimeErro("Número inválido de parâmetros");
		
		if (simb->categoria == var_simples) {
			if (retornaParametro(proc_aux->parametros[num_params - 1]) ==
				referencia)
				carregaEndereco(simb);
			else
				carregaValor(simb);
		}
		else if (simb->categoria == param_formal) {
			pf_aux = simb->atributos;
			if (retornaParametro(proc_aux->parametros[num_params - 1]) == referencia)
				if (pf_aux->parametro == referencia)
					carregaValor(simb);
				else
					carregaEndereco(simb);
			else
				carregaValor(simb);
		}
		else if (simb->categoria == funcao) {
			func_aux = simb->atributos;
			geraCodigo(NULL, "AMEM 1");
			sprintf(comando_buffer, "CHPR %s,%d", func_aux->rotulo, nivel_lexico);
			geraCodigo(NULL, comando_buffer);
		}
		else
			imprimeErro("Parâmetro inválido");
	}
	else if (simb_proc && simb_proc->categoria == funcao) {
		func_aux = simb_proc->atributos;

		if (num_params > func_aux->num_params)
			imprimeErro("Número inválido de parâmetros");

		if (simb->categoria == var_simples) {
			if (retornaParametro(func_aux->parametros[num_params - 1]) ==
				referencia)
				carregaEndereco(simb);
			else
				carregaValor(simb);
		}
		else if (simb->categoria ==  param_formal) {
			pf_aux = simb->atributos;
			if (retornaParametro(func_aux->parametros[num_params - 1]) == referencia)
				if (pf_aux->parametro == referencia)
					carregaValor(simb);
				else
					carregaEndereco(simb);
			else
				carregaValor(simb);
		}
		else if (simb->categoria == funcao) {
			geraCodigo(NULL, "AMEM 1");
			sprintf(comando_buffer, "CHPR %s,%d", func_aux->rotulo, nivel_lexico);
			geraCodigo(NULL, comando_buffer);
		}
		else
			imprimeErro("Parâmetro inválido");
	}
	else {
		if (simb->categoria == var_simples)
			carregaValor(simb);
		else if (simb->categoria == param_formal) {
			pf_aux = simb->atributos;
			if (pf_aux->parametro == referencia)
				carregaIndireto(simb);
			else
				carregaValor(simb);
		}
		else if (simb->categoria == funcao) {
			func_aux = simb->atributos;
			geraCodigo(NULL, "AMEM 1");
			sprintf(comando_buffer, "CHPR %s,%d", func_aux->rotulo, nivel_lexico);
			geraCodigo(NULL, comando_buffer);
		}
		else
			imprimeErro("Parâmetro inválido");
	}
}