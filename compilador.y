
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
char comando[30];
int nivel_lexico;
int desloc;

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

declara_var : { num_vars = 0; }
              lista_id_var DOIS_PONTOS
              tipo
              { 
                  // Aloca memória pras variáveis
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
                     
                  }
                  comando_composto
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

   yyin=fp;
   yyparse();

   imprimeTS(&TS, TS_TAM);

   return 0;
}
