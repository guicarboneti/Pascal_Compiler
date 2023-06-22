/* -------------------------------------------------------------------
 *            Arquivo: compilador.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [09/08/2020, 19h:01m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e variáveis globais do compilador (via extern)
 *
 * ------------------------------------------------------------------- */

#include "pilha.h"
#include "tabelaDeSimbolos.h"

#define TAM_TOKEN 16
#define TAM_ETF_PILHA 50
#define TAM_OPERACOES_PILHA 50
#define TAM_L_ELEM_PILHA 50
#define TAM_ROTULOS_PILHA 50
#define TAM_PILHA_NUM_VARS 50
#define ROT_SIZE 3

typedef enum simbolos {
  simb_program,
  simb_var,
  simb_begin,
  simb_end,
  simb_identificador,
  simb_numero,
  simb_ponto,
  simb_virgula,
  simb_ponto_e_virgula,
  simb_dois_pontos,
  simb_atribuicao,
  simb_abre_parenteses,
  simb_fecha_parenteses,
  simb_igual,
  simb_diferente,
  simb_menor,
  simb_maior,
  simb_menor_igual,
  simb_maior_igual,
  simb_label,
  simb_integer,
  simb_boolean,
  simb_abre_chaves,
  simb_fecha_chaves,
  simb_abre_colchetes,
  simb_fecha_colchetes,
  simb_array,
  simb_of,
  simb_procedure,
  simb_function,
  simb_goto,
  simb_if,
  simb_then,
  simb_else,
  simb_while,
  simb_do,
  simb_or,
  simb_and,
  simb_not,
  simb_div,
  simb_soma,
  simb_subt,
  simb_mult,
  simb_read,
  simb_write,
  simb_forward
} simbolos;

typedef enum operacoes_t {
    op_soma,
    op_subt,
    op_div,
    op_mult,
    op_and,
    op_or,
    op_not,
    op_menor,
    op_maior,
    op_igual,
    op_diferente,
    op_menor_igual,
    op_maior_igual
} operacoes_t;


/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;
extern int num_params;
extern PILHA *l_elem_pilha;
extern PILHA *E, *T, *F;
extern PILHA *operacoes;
extern PILHA *rotulos;
extern PILHA *pilha_num_vars;
extern SIMBOLO *simb_proc;
extern SIMBOLO *proc;
extern char comando_buffer[50];

/* -------------------------------------------------------------------
 * prototipos globais
 * ------------------------------------------------------------------- */

void geraCodigo (char*, char*);
int imprimeErro ( char* );
void inicializaPilhas();
char *prox_rotulo();
int checaCategoria(SIMBOLO* simb);
char* opToString(operacoes_t operacao);
int yylex();
void yyerror(const char *s);
void comandoCarrega(SIMBOLO *simb);
void carregaValor(SIMBOLO *simb);
void carregaEndereco(SIMBOLO *simb);
void carregaIndireto(SIMBOLO *simb);

void imprimeOp(void *operacao);
void checaParam();
