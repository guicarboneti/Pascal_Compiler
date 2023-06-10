
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "pilha.h"
#include "tabelaDeSimbolos.h"

int num_vars;
PILHA TS;
SIMBOLO *simb;
SIMBOLO *l_elem;
char comando[30];
int nivel_lexico;
int desloc;
PILHA *l_elem_pilha;
PILHA *E, *T, *F;
PILHA *operacoes;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT NUMERO ATRIBUICAO 
%token LABEL INTEGER BOOLEAN ABRE_CHAVES FECHA_CHAVES
%token ABRE_COLCHETES FECHA_COLCHETES ARRAY OF
%token PROCEDURE FUNCTION GOTO IF THEN ELSE
%token WHILE DO OR AND DIV SOMA SUBTRACAO
%token MULTIPLICACAO IGUAL DIFERENTE MENOR
%token MAIOR MENOR_IGUAL MAIOR_IGUAL NOT

%%


/* REGRA 1 */
programa    :{
               nivel_lexico = 0;
               geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
               geraCodigo (NULL, "PARA");
             }
;


/* REGRA 2 */
bloco       :
              parte_declara_vars
              {
                  
              }

              comando_composto
              ;



/* REGRA 8 */
parte_declara_vars:  { desloc = 0; } VAR declara_vars | declara_vars
            |
;

declara_vars: declara_vars declara_var
            | declara_var
;

/* REGRA 9 */
declara_var : { num_vars = 0; }
              lista_id_var DOIS_PONTOS
              tipo
              { 
                  /* Aloca memória pras variáveis */
                  sprintf(comando, "AMEM %d", num_vars);
                  geraCodigo(NULL, comando);
              }
              PONTO_E_VIRGULA
;

tipo        : INTEGER {
                  atualizaTipoVar(&TS, inteiro, num_vars);
               }
            | BOOLEAN {
                  atualizaTipoVar(&TS, booleano, num_vars);
               }
;

/* REGRA 10 */
lista_id_var: lista_id_var VIRGULA IDENT
              {
                  /* insere ultima vars na tabela de simbolos */ 
                  insere(&TS, token, var_simples, criaVarSimples(tipo_indefinido, desloc), nivel_lexico);
                  num_vars++;
                  desloc++;
              }
            | IDENT {
                  /* insere vars na tabela de s�mbolos */
                  insere(&TS, token, var_simples, criaVarSimples(tipo_indefinido, desloc), nivel_lexico);
                  num_vars++;
                  desloc++;
               }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;


/* REGRA 16 */
comando_composto: T_BEGIN comandos T_END

comandos:
         | comando PONTO_E_VIRGULA comandos
         | comando
;

/* REGRA 17 */
comando: NUMERO DOIS_PONTOS comando_sem_rotulo
         | comando_sem_rotulo
;

/* REGRA 18 */
comando_sem_rotulo: IDENT
                  {
                     int idx = buscaSimbolo(&TS, token);
                     SIMBOLO *simb;

                     if(idx == -1)
                        imprimeErro("Simbolo não existe");
                     
                     simb = buscaItem(&TS, idx);

                     if(!checaCategoria(simb))
                        imprimeErro("Símbolo não corresponde a variável simples, parâmetro formal, procedimento formal ou função");

                     // armazena simbolo para posteriormente gerar ARMZ
                     l_elem = simb;
                  }
                  identificador
                  // | comando_composto
                  // | comando_read
                  // | comando_write
                  // | comando_repetitivo
                  // | comando_condicional
;

/* REGRA 18 - extra */
identificador: comando_atribuicao
            //| chama_proc
;

/* REGRA 19 */
comando_atribuicao: ATRIBUICAO
                  {
                     empilha(l_elem_pilha, l_elem->id);
                  }
                  // expr
                  {
                     int idx = buscaSimbolo(&TS, desempilha(l_elem_pilha));
                     if(idx == -1)
                        imprimeErro("Simbolo não existe");

                     l_elem = buscaItem(&TS, idx);
                     TIPOS *t1 = desempilha(E);

                     VAR_SIMPLES *t_simples;
                     PARAM_FORMAL *t_formal;
                     FUNCAO *t_funcao;

                     switch(l_elem->categoria){

                        case var_simples:
                           t_simples = l_elem->atributos;
                           if(t_simples->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, t_simples->deslocamento);
                           break;
                        
                        case param_formal:
                           t_formal = l_elem->atributos;
                           if (t_formal->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           
                           if (t_formal->tipo == valor)
                              sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, t_formal->deslocamento);
                           else if (t_formal->tipo == referencia)
                              sprintf(comando, "ARMI %d,%d", l_elem->nivel_lex, t_formal->deslocamento);
                           else
                              imprimeErro("Tipo de passsagem inválido");
                           break;

                        case funcao:
                           t_funcao = l_elem->atributos;
                           if(t_funcao->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, t_funcao->deslocamento);
                           break;

                        default:
                           imprimeErro("Categoria inválida");
                           break;
                     }

                     geraCodigo(NULL, comando);
                     l_elem = NULL;
                  }
;

/* REGRA 25 */
//expr: expr_simples
      //| expr_simples relacao expr_simples
         //{
            //TIPOS *t1, *t2;
            //t1 = desempilha(E);
            //t2 = desempilha(E);

            //if((*t1) != (*t2))
               //imprimeErro("Tipos não correspondem");

            //(*t1) = booleano;
            //empilha(E, t1);

            //operacoes_t *op = desempilha(operacoes);
            //sprintf(comando, "%s", opToString((*op)));
            //geraCodigo(NULL, comando);

            //free(t1);
            //free(t2);
         //}
//;

/* REGRA 26 */
relacao: IGUAL
         {
            operacoes_t op = op_igual;
            empilha(operacoes, &op);
         }
      | DIFERENTE
         {
            operacoes_t = op_diferente;
            empilha(operacoes, &op);
         }
      | MENOR
         {
            operacoes_t op = op_menor;
            empilha(operacoes, &op);
         }
      | MAIOR
         {
            operacoes_t op = op_maior;
            empilha(operacoes, &op);
         }
      | MENOR_IGUAL
         {
            operacoes_t op = op_menor_igual;
            empilha(operacoes, &op);
         }
      | MAIOR_IGUAL
         {
            operacoes_t op = op_maior_igual;
            empilha(operacoes,  &op);
         }
;
// parte_declara_subrotinas: parte_declara_subrotinas;

%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   inicializaTS(&TS, TS_TAM);
   inicializaPilhas();

   yyin=fp;
   yyparse();

   imprimeTS(&TS, TS_TAM);

   return 0;
}
