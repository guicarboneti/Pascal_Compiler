
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
int num_bloco_vars;
PILHA TS;
SIMBOLO *simb;
SIMBOLO *l_elem;
char comando[30];
int nivel_lexico;
int desloc;
PILHA *l_elem_pilha;
PILHA *E, *T, *F;
PILHA *operacoes;
PILHA *rotulos;
PILHA *pilha_num_vars;
int num_params;
char erro[200];
char ident[30];

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT NUMERO ATRIBUICAO 
%token LABEL INTEGER BOOLEAN ABRE_CHAVES FECHA_CHAVES
%token ABRE_COLCHETES FECHA_COLCHETES ARRAY OF
%token PROCEDURE FUNCTION GOTO IF THEN ELSE
%token WHILE DO OR AND DIV SOMA SUBTRACAO
%token MULTIPLICACAO IGUAL DIFERENTE MENOR
%token MAIOR MENOR_IGUAL MAIOR_IGUAL NOT READ WRITE

/* Para assegurar o funcionamento do IF THEN ELSE
   Precedências são crescentes, logo "lower_than_else" < "else" */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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
bloco       :  { num_bloco_vars = 0; }
              parte_declara_vars
              {
                  empilha(pilha_num_vars, &num_bloco_vars);

                  empilha(rotulos, prox_rotulo());

                  // Gera DSVS com rotulo
                  char *rotulo = buscaItem(rotulos, rotulos->tamanho -1);
                  sprintf(comando, "DSVS %s", rotulo);
                  geraCodigo(NULL, comando);
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
                  /* insere ultima variavel na tabela de simbolos */ 
                  insere(&TS, token, var_simples, criaVarSimples(tipo_indefinido, desloc), nivel_lexico);
                  num_vars++;
                  desloc++;
              }
            | IDENT {
                  /* insere variveis na tabela de simbolos */
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
                     SIMBOLO *simb;
                     int idx = buscaSimbolo(&TS, token);

                     if(idx == -1)
                        imprimeErro("Simbolo não existe");
                     
                     simb = buscaItem(&TS, idx);

                     if(!checaCategoria(simb))
                        imprimeErro("Símbolo não corresponde a variável simples, parâmetro formal, procedimento formal ou função");

                     /* armazena simbolo para posteriormente gerar ARMZ */
                     l_elem = simb;
                  }
                  identificador
                  // | comando_composto
                  | comando_read
                  | comando_write
                  // | comando_repetitivo
                  | comando_condicional
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
                  expressao
                  {
                     int idx = buscaSimbolo(&TS, desempilha(l_elem_pilha));
                     if(idx == -1)
                        imprimeErro("Simbolo não existe");

                     l_elem = buscaItem(&TS, idx);
                     TIPOS *t1 = desempilha(E);

                     VAR_SIMPLES *VS;
                     PARAM_FORMAL *PF;
                     FUNCAO *FUN;

                     if (l_elem->categoria == var_simples) {
                           VS = l_elem->atributos;
                           if(VS->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, VS->deslocamento);
                     }
                     else if (l_elem->categoria == param_formal){
                           PF = l_elem->atributos;
                           if (PF->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           
                           if (PF->parametro == valor)
                              sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, PF->deslocamento);
                           else if (PF->parametro == referencia)
                              sprintf(comando, "ARMI %d,%d", l_elem->nivel_lex, PF->deslocamento);
                           else
                              imprimeErro("Tipo de passsagem de parâmetro inválido");
                     }
                     else if (l_elem->categoria == funcao) {
                        FUN = l_elem->atributos;
                        if(FUN->tipo != (*t1))
                           imprimeErro("Tipos não correspondem");
                        sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, FUN->deslocamento);
                     }
                     else
                        imprimeErro("Categoria inválida");

                     geraCodigo(NULL, comando);
                     l_elem = NULL;
                  }
;

// /* REGRA 24 */
lista_expressoes: lista_expressoes VIRGULA { num_params++; } expressao
                  | expressao
                  |
;

/* REGRA 25 */
expressao: expressao_simples 
      | expressao_simples relacao expressao_simples
         {
            //fprintf(stderr, "DEBUG - Regra E = E <> E\n");
            // E <> E
            TIPOS *t1, *t2;
            t1 = desempilha(E);
            t2 = desempilha(E);

            if((*t1) != (*t2))
               imprimeErro("Tipos não correspondem");

            (*t1) = booleano;
            empilha(E, t1);

            operacoes_t *op = desempilha(operacoes);
            sprintf(comando, "%s", opToString((*op)));
            geraCodigo(NULL, comando);

            // free(t1);
            // free(t2);
         }
;

/* REGRA 26 */
relacao: IGUAL
         {
            operacoes_t op = op_igual;
            empilha(operacoes, &op);
         }
      | DIFERENTE
         {
            operacoes_t op = op_diferente;
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

/* REGRA 27 */
expressao_simples: expressao_simples operacao termo
                  {
                     fprintf(stderr, "DEBUG - Regra E = E + T\n");
                     // E = E + T
                     TIPOS *t1, *t2;
                     t1 = desempilha(E);
                     t2 = desempilha(T);

                     if ((*t1) != (*t2))
                        imprimeErro("Tipos não correspondem");

                     // #ifdef DEBUG
                     // fprintf(stderr, "DEBUG - Empilhando t1: %s em E\n", tipoToString((*t1)));
                     // #endif

                     empilha(E, t1);

                     operacoes_t *op = desempilha(operacoes);
                     sprintf(comando, "%s", opToString((*op)));
                     geraCodigo(NULL, comando);

                     // free(t1);
                     // free(t2);
                  }
               | termo
                  {

                     // fprintf(stderr, "DEBUG - Regra E = T 27\n");
                     // E = T
                     TIPOS *t1;
                     t1 = desempilha(T);

                     // #ifdef DEBUG
                     // fprintf(stderr, "DEBUG - Desempilhando t1: %s de T\n", imprimeTipo((*t1)));
                     // fprintf(stderr, "DEBUG - Empilhando t1: %s em E\n", imprimeTipo((*t1)));
                     // #endif

                     empilha(E, t1);
                     // fprintf(stderr, "free");
                     // free(t1);
                  }
            // | sinal termo 
               {

               }
;

operacao: sinal | DIV | MULTIPLICACAO | AND | OR;

sinal: SOMA | SUBTRACAO;

/* REGRA 28 */
termo: fator
         {
            fprintf(stderr, "DEBUG - Regra T = F 28\n");
            TIPOS *t1;
            t1 = desempilha(F);

            // #ifdef DEBUG
            // fprintf(stderr, "DEBUG - Desempilhando t1: %s de F\n", imprimeTipo((*t1)));
            // fprintf(stderr, "DEBUG - Empilhando t1: %s em T\n", imprimeTipo((*t1)));
            // #endif

            empilha(T, t1);
            // free(t1);
         }
      // | termo operacao fator 
            {

            }
;

/* REGRA 29 */
fator: IDENT   
         {
            fprintf(stderr, "DEBUG - Regra variavel\n");
            int idx = buscaSimbolo(&TS, token);
            SIMBOLO *simb;
            VAR_SIMPLES *VS;
            PARAM_FORMAL *PF;
            FUNCAO *func;
            TIPOS tipo;

            if (idx == -1)
               imprimeErro("Simbolo inexistente");

            simb = buscaItem(&TS, idx);
            if (simb->categoria == var_simples){
                  VS = simb->atributos;
                  tipo = VS->tipo;
            }
            else if(simb->categoria == param_formal){
               PF = simb->atributos;
               tipo = PF->tipo;
            }

            else if(simb->categoria == funcao){
               func = simb->atributos;
               tipo = func->tipo;
            }

            else{
               sprintf(erro, "Simbolo %s não é variável simples, parâmetro formal ou função", token);
               imprimeErro(erro);
            }
            
            strncpy(ident, token, strlen(token));
            ident[strlen(token)] = '\0';

            // #ifdef DEBUG
            fprintf(stderr, "DEBUG - Empilhando tipo de %s em F\n", simb->id);
            // #endif

            empilha(F, &tipo);
         }
      | NUMERO {
         /* carrega constante */
         fprintf(stderr, "REGRA NUMERO\n");
         sprintf(comando, "CRCT %s", token);
         geraCodigo(NULL, comando);

         // if (proc) checaParam();

         /* empilha o tipo inteiro */
         TIPOS tipo = inteiro;
         empilha(F, &tipo);
      }
      | ABRE_PARENTESES expressao FECHA_PARENTESES
         {
            // vem de um fator, precisamos desempilhar de E e colocar em F
            fprintf(stderr, "DEBUG - Regra expressão com parênteses\n");
            TIPOS *t1;
            t1 = desempilha(E);

            // fprintf(stderr, "empilha aqui\n");

            empilha(F, t1);
            // free(t1);
         }

// | chama_func 
| NOT fator;


///* REGRA 20 */
// chama_proc:;

///* REGRA 21 */
// desvio:;

///* REGRA 22 */
comando_condicional:
                     {
                        empilha(rotulos, prox_rotulo());
                        empilha(rotulos, prox_rotulo());
                     }
                     if_then cond_else
                     {
                        free(desempilha(rotulos));
                        free(desempilha(rotulos));
                     }
;

/* REGRA 22 - extra */
if_then: IF expressao
         {
            // verifica se expressão é booleana
            TIPOS *t1;
            t1 = desempilha(E);

            if ((*t1) != booleano){
               imprimeErro("Expressão não é booleana");
            }

            // free(t1);

            // Gera DSVF com rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
            fprintf(stderr, "rotulo %s\n", rotulo);
            sprintf(comando, "DSVF %s", rotulo);
            geraCodigo(NULL, comando);
         }
         THEN comando_sem_rotulo
;

/* REGRA 22 - extra */
cond_else: ELSE
         {
            char *rotulo;
            // Gera DSVS com primeiro rotulo
            rotulo = buscaItem(rotulos, rotulos->tamanho - 2);
            sprintf(comando, "DSVF %s", rotulo);
            geraCodigo(NULL, comando);

            // Gera NADA com segundo rotulo
            rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
            geraCodigo(rotulo, "NADA");
         }
            comando_sem_rotulo
         {
            // Gera NADA com primeiro rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho - 2);
            geraCodigo(rotulo, "NADA");
         }
         | %prec LOWER_THAN_ELSE
         {
            // Gera NADA com segundo rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
            geraCodigo(rotulo, "NADA");
         }
;

///* REGRA 23 */
// comando_repetitivo:;

/* REGRA 31 */
chama_func: IDENT | lista_expressoes;

///* REGRA 11 */
// parte_declara_subrotinas: parte_declara_subrotinas;

/* REGRA LEITURA */
comando_read: READ ABRE_PARENTESES paramentros_leitura FECHA_PARENTESES
;

/* parâmetros do read */
paramentros_leitura: paramentros_leitura VIRGULA IDENT
            {
               SIMBOLO *item;
               VAR_SIMPLES *VS;
               PARAM_FORMAL *PF;

               int idx = buscaSimbolo(&TS, token);
               if (idx == -1)
                  imprimeErro("[ERRO] read() - Simbolo inexistente");

               geraCodigo(NULL, "LEIT");

               item = buscaItem(&TS, idx);

               if (item->categoria == var_simples) {
                     VS = item->atributos;
                     sprintf(comando, "ARMZ %d, %d", item->nivel_lex, VS->deslocamento);
               }
               else if (item->categoria == param_formal){
                     PF = item->atributos;
                     if (PF->parametro == valor)
                        sprintf(comando, "ARMZ %d, %d", item->nivel_lex, PF->deslocamento);
                     else if (PF->parametro == referencia)
                        sprintf(comando, "ARMI %d, %d", item->nivel_lex, PF->deslocamento);
               }
               else
                  imprimeErro("[ERRO] read() - Item lido nao eh variavel simples nem parametro formal");

               geraCodigo(NULL, comando);
            }
           | IDENT
            {
               SIMBOLO *item;
               VAR_SIMPLES *VS;
               PARAM_FORMAL *PF;

               int idx = buscaSimbolo(&TS, token);
               if (idx == -1)
                  imprimeErro("[ERRO] read() - Simbolo inexistente");

               geraCodigo(NULL, "LEIT");

               item = buscaItem(&TS, idx);

               if (item->categoria == var_simples) {
                     VS = item->atributos;
                     sprintf(comando, "ARMZ %d, %d", item->nivel_lex, VS->deslocamento);
               }
               else if (item->categoria == param_formal){
                     PF = item->atributos;
                     if (PF->parametro == valor)
                        sprintf(comando, "ARMZ %d, %d", item->nivel_lex, PF->deslocamento);
                     else if (PF->parametro == referencia)
                        sprintf(comando, "ARMI %d, %d", item->nivel_lex, PF->deslocamento);
               }
               else
                  imprimeErro("[ERRO] read() - Item lido nao eh variavel simples nem parametro formal");

               geraCodigo(NULL, comando);
            }
;

/* REGRA ESCRITA */
comando_write: WRITE ABRE_PARENTESES parametros_escrita FECHA_PARENTESES;

/* parâmetros do write */
parametros_escrita: parametros_escrita VIRGULA expressao
            {
               geraCodigo(NULL, "IMPR");
            }
           | expressao
            {
               geraCodigo(NULL, "IMPR");
            }
;

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
