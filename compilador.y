
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
PILHA *labels;
PILHA *pilha_num_vars;
int num_params;
char erro[200];
char ident[30];
TIPOS tipo_aux;
SIMBOLO *proc = NULL;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT NUMERO ATRIBUICAO 
%token INTEGER BOOLEAN ABRE_CHAVES FECHA_CHAVES
%token ABRE_COLCHETES FECHA_COLCHETES ARRAY OF
%token PROCEDURE FUNCTION IF THEN ELSE
%token WHILE DO OR AND DIV SOMA SUBTRACAO
%token MULTIPLICACAO IGUAL DIFERENTE MENOR
%token MAIOR MENOR_IGUAL MAIOR_IGUAL NOT READ WRITE GOTO LABEL

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
bloco:  { num_bloco_vars = 0; }
         parte_declara_labels
         parte_declara_vars {
            empilha(pilha_num_vars, &num_bloco_vars);

            empilha(rotulos, prox_rotulo());

            // Gera DSVS com rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho -1);
            sprintf(comando, "DSVS %s", rotulo);
            geraCodigo(NULL, comando);
         }
         parte_declara_subrotinas
         {
            // Gera NADA com rotulo
            char *rotulo = desempilha(rotulos);
            geraCodigo(rotulo, "NADA");
            free(rotulo);
         }
         comando_composto {
            int *temp = desempilha(pilha_num_vars);
            num_bloco_vars = (*temp);

            // imprimeTS(&TS, TS_TAM);    // ---------- comentar dps
            deletaPorNivelLexico(&TS, nivel_lexico+1);

            if (num_bloco_vars > 0) {
               elimina(&TS, num_bloco_vars);
               sprintf(comando, "DMEM %d", num_bloco_vars);
               geraCodigo(NULL, comando);
            }
         }
;

parte_declara_labels: LABEL declara_label PONTO_E_VIRGULA | ;

declara_label: declara_label VIRGULA NUMERO {
         // cat = createLabel();
         // cat->label->label = nextLabel();
         // insertST(symbolTable, token, lexLevel, CAT_LABEL, cat);
         STRUCT_LABEL *label_aux;
         label_aux = criaLabel(token, nivel_lexico);
         empilha(labels, label_aux);
      } | NUMERO {
         // Cat cat = createLabel();
         // cat->label->label = nextLabel();
         // insertST(symbolTable, token, lexLevel, CAT_LABEL, cat);
         STRUCT_LABEL *label_aux;
         label_aux = criaLabel(token, nivel_lexico);
         empilha(labels, label_aux);
      }
;

/* REGRA 8 */
parte_declara_vars:   
            | { desloc = 0; } VAR declara_vars
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
                  num_bloco_vars++;
                  num_vars++;
                  desloc++;
              }
            | IDENT {
                  /* insere variveis na tabela de simbolos */
                  insere(&TS, token, var_simples, criaVarSimples(tipo_indefinido, desloc), nivel_lexico);
                  num_bloco_vars++;
                  num_vars++;
                  desloc++;
               }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;

/* REGRA 11 */
parte_declara_subrotinas:
         | parte_declara_subrotinas declara_proc
         | parte_declara_subrotinas declara_func
;

/* REGRA 12 */
declara_proc: PROCEDURE IDENT
            {
               char *rotulo;

               nivel_lexico++;

               // Adiciona procedimento à tabela de simbolos
               if (buscaSimbolo(&TS, token) == -1) {
                  empilha(rotulos, prox_rotulo());
                  rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
                  insere(&TS, token, procedimento,
                     criaAtrProcedimento(rotulo), nivel_lexico);
               }

            }
            parametros_formais
            PONTO_E_VIRGULA parametros_proc
;

/* REGRA 12 - extra */
parametros_proc: { nivel_lexico--; }
            | {
               char *rotulo;

               // Gera ENPR k com rotulo
               rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
               sprintf(comando, "ENPR %d", nivel_lexico);
               geraCodigo(rotulo, comando);

            } bloco PONTO_E_VIRGULA
            {
               char *rotulo;

               SIMBOLO *simb = retornaUltimo(&TS, procedimento);
               PROCEDIMENTO *proc = simb->atributos;

               // Gera RTPR
               sprintf(comando, "RTPR %d, %d", nivel_lexico, proc->num_params);
               geraCodigo(NULL, comando);

               elimina(&TS, proc->num_params);

               nivel_lexico--;

               rotulo = desempilha(rotulos);
               // free(rotulo);
            }
;

/* REGRA 13 */
declara_func: FUNCTION IDENT
            {
               char *rotulo;
               nivel_lexico++;

               // Adiciona função à TS se ainda não existe
               if (buscaSimbolo(&TS, token) == -1) {
                  empilha(rotulos, prox_rotulo());
                  rotulo = buscaItem(rotulos, rotulos->tamanho-1);
                  insere(&TS, token, funcao, criaAtrFuncao(rotulo), nivel_lexico);
               }
            }
            parametros_formais DOIS_PONTOS tipo {
               if (simbolo == simb_integer)
                     atualizaTipoFuncao(retUltDaCategoria(&TS, funcao), inteiro);
               else if (simbolo == simb_boolean)
                     atualizaTipoFuncao(retUltDaCategoria(&TS, funcao), booleano);
            }
            PONTO_E_VIRGULA parametros_funcao
;

/* REGRA 13 - extra */
parametros_funcao: { nivel_lexico--; }
            | {
               char *rotulo;

               rotulo = buscaItem(rotulos, rotulos->tamanho-1);
               sprintf(comando, "ENPR %d", nivel_lexico);
               geraCodigo(rotulo, comando);

            } bloco PONTO_E_VIRGULA {
               char *rotulo;

               SIMBOLO *simb = retUltDaCategoria(&TS, funcao);
               FUNCAO *aux_func = simb->atributos;

               sprintf(comando, "RTPR %d, %d", nivel_lexico, aux_func->num_params);
               geraCodigo(NULL, comando);
               elimina(&TS, aux_func->num_params);

               nivel_lexico--;
               rotulo = desempilha(rotulos);
               free(rotulo);
            }
;

/* REGRA 14 */
parametros_formais:
             | { desloc = 0; } ABRE_PARENTESES secao_parametros_formais FECHA_PARENTESES
             {
               // atualiza deslocamento e adiciona parametros ao procedimento na tabela de simbolos
               atualizaDesloc(&TS, desloc);
             }
;

/* REGRA 15 */
secao_parametros_formais:
                   | PONTO_E_VIRGULA secao_parametros_formais
                   | {num_vars = 0;} VAR lista_id_param DOIS_PONTOS tipo
                   {
                     switch (simbolo) {
                        case simb_integer:
                           atualizaTipoVar(&TS, inteiro, num_vars);
                           break;
                        case simb_boolean:
                           atualizaTipoVar(&TS, booleano, num_vars);
                           break;
                        default:
                           break;
                     }

                     atualizaTipoParametro(&TS, referencia, num_vars);
                   }
                   secao_parametros_formais
                   | {num_vars = 0;} lista_id_param DOIS_PONTOS tipo
                   {
                     switch (simbolo) {
                        case simb_integer:
                           atualizaTipoVar(&TS, inteiro, num_vars);
                           break;
                        case simb_boolean:
                           atualizaTipoVar(&TS, booleano, num_vars);
                           break;
                        default:
                           break;
                     }
                   }
                   secao_parametros_formais
;

/* REGRA 15 - extra */
lista_id_param: lista_id_param VIRGULA IDENT
              {
                  // Adiciona à tabela de simbolos como indefinido
                  insere(&TS, token, param_formal,
                     criaParamFormal(tipo_indefinido, 0, valor), nivel_lexico);

                  num_vars++;
                  desloc++;
              }
            | IDENT {
                  // Adiciona à tabela de simbolos como indefinido
                  insere(&TS, token, param_formal,
                     criaParamFormal(tipo_indefinido, 0, valor), nivel_lexico);

                  num_vars++;
                  desloc++;
               }
;


/* REGRA 16 */
comando_composto: T_BEGIN comandos T_END

comandos:
         | comando PONTO_E_VIRGULA comandos
         | comando
;

/* REGRA 17 */
comando: NUMERO {
            // sprintf(comando, "ENRT %d, %d", l_elem->nivel_lex, pilha_num_vars);
            // geraCodigo(NULL, comando);

            int i;
            STRUCT_LABEL *label;
            SIMBOLO *simb;

            if ((i = buscaSimbolo(labels, token)) < 0)
               imprimeErro("Label não encontrado na pilha");
            label = buscaItem(labels, i);
            
            num_bloco_vars = 0;
            simb = retUltDoNivelLex(&TS, label->nivel_lex);
            if(simb->nivel_lex == 0) {
               // We jumped into main.
               num_bloco_vars = num_vars;
            } else {
               // if(simb->categoria == FUNCAO) {
               //       FUNCAO *aux_func = simb->atributos;
               //       num_bloco_vars = aux_func->num_params;
               // } else if(simb->categoria == CAT_PROCEDURE) {
               //       num_bloco_vars = subroutine->value->procedure->n_local_vars;
               // }
            }

            sprintf(comando, "ENRT %d,%d", nivel_lexico, num_bloco_vars);
            geraCodigo(NULL, comando);

         }
         DOIS_PONTOS comando_sem_rotulo
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
                  | comando_composto
                  | comando_read
                  | comando_write
                  | comando_repetitivo
                  | comando_condicional
                  | desvio
;

/* REGRA 18 - extra */
identificador: comando_atribuicao
            | chama_proc
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
                           sprintf(comando, "ARMZ %d, %d", l_elem->nivel_lex, VS->deslocamento);
                     }
                     else if (l_elem->categoria == param_formal){
                           PF = l_elem->atributos;
                           if (PF->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           
                           if (PF->parametro == valor)
                              sprintf(comando, "ARMZ %d, %d", l_elem->nivel_lex, PF->deslocamento);
                           else if (PF->parametro == referencia)
                              sprintf(comando, "ARMI %d, %d", l_elem->nivel_lex, PF->deslocamento);
                           else
                              imprimeErro("Tipo de passsagem de parâmetro inválido");
                     }
                     else if (l_elem->categoria == funcao) {
                        FUN = l_elem->atributos;
                        if(FUN->tipo != (*t1))
                           imprimeErro("Tipos não correspondem");
                        sprintf(comando, "ARMZ %d, %d", l_elem->nivel_lex, FUN->deslocamento);
                     }
                     else
                        imprimeErro("Categoria inválida");

                     geraCodigo(NULL, comando);
                     l_elem = NULL;
                  }
;

/* REGRA 20 */
chama_proc:
         {
            if (l_elem->categoria != procedimento) {
               sprintf(erro, "Simbolo %s não procedimento", l_elem->id);
               imprimeErro(erro);
            }

            PROCEDIMENTO *atrProc = l_elem->atributos;

            sprintf(comando, "CHPR %s, %d", atrProc->rotulo, nivel_lexico);
            geraCodigo(NULL, comando);

            l_elem = NULL;
         }
         | ABRE_PARENTESES { proc = l_elem; num_params = 1; } lista_expressoes FECHA_PARENTESES
         {
            if (l_elem->categoria != procedimento) {
               sprintf(erro, "Simbolo %s não procedimento", l_elem->id);
               imprimeErro(erro);
            }

            PROCEDIMENTO *atrProc = l_elem->atributos;

            TIPOS *tipo;
            PARAM_FORMAL *atrParam;
            for (int i = 0; i < atrProc->num_params; i++) {
               tipo = desempilha(E);
               atrParam = atrProc->parametros[i]->atributos;

               if ((*tipo) != atrParam->tipo) {
                  sprintf(erro, "Tipo incompatível - Esperava %s e recebeu %s", imprimeTipo(atrParam->tipo), imprimeTipo((*tipo)));
                  imprimeErro(erro);
               }
            }

            sprintf(comando, "CHPR %s, %d", atrProc->rotulo, nivel_lexico);
            geraCodigo(NULL, comando);

            l_elem = NULL;
            proc = NULL;
         }
;


/* REGRA 24 */
lista_expressoes: lista_expressoes VIRGULA { num_params++; } expressao
                  | expressao
                  |
;

/* REGRA 25 */
expressao: expressao_simples | expressao_simples relacao expressao_simples
   {
      // fprintf(stderr, "DEBUG - Regra E = E <> E\n");
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
relacao:
      IGUAL
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
                     // fprintf(stderr, "DEBUG - Regra E = E + T\n");
                     // E = E + T
                     TIPOS *t1, *t2;
                     t1 = desempilha(E);
                     t2 = desempilha(T);

                     if ((*t1) != (*t2))
                        imprimeErro("Tipos não correspondem");

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

                     empilha(E, t1);
                     // free(t1);
                  }
               | sinal { if (proc) checaParam(); } termo
               {
                  // E = -T
                  TIPOS *t1;
                  t1 = desempilha(T);

                  empilha(E, t1);

                  operacoes_t *op = desempilha(operacoes);
                  if ((*op) == op_subt) {
                     sprintf(comando, "INVR");
                     geraCodigo(NULL, comando);
                  }

                  // free(t1);
               }
;

operacao: sinal 
   | DIV {
      operacoes_t op = op_div;
      empilha(operacoes, &op);
   }
   | MULTIPLICACAO {
      operacoes_t op = op_mult;
      empilha(operacoes, &op);
   }
   | AND {
      operacoes_t op = op_and;
      empilha(operacoes, &op);
   }
   | OR {
      operacoes_t op = op_or;
      empilha(operacoes, &op);
   }
;

sinal: SOMA {
         operacoes_t op = op_soma;
         empilha(operacoes, &op);
      }
      | SUBTRACAO {
         operacoes_t op = op_subt;
         empilha(operacoes, &op);
      }
;

/* REGRA 28 */
termo: fator
         {
            // fprintf(stderr, "DEBUG - Regra T = F 28\n");
            TIPOS *t1;
            t1 = desempilha(F);

            empilha(T, t1);
            // free(t1);
         }
      | termo operacao fator 
         {
            // T = T + F
            TIPOS *t1, *t2;
            t1 = desempilha(T);
            t2 = desempilha(F);

            if ((*t1) != (*t2))
               imprimeErro("Tipos não correspondem");

            empilha(T, t1);

            operacoes_t *op = desempilha(operacoes);
            sprintf(comando, "%s", opToString((*op)));
            geraCodigo(NULL, comando);

            // free(t1);
            // free(t2);
         }
;

/* REGRA 29 */
fator: IDENT   
         {
            // fprintf(stderr, "DEBUG - Regra fator\n");
            int idx = buscaSimbolo(&TS, token);
            SIMBOLO *simb;
            VAR_SIMPLES *VS;
            PARAM_FORMAL *PF;
            FUNCAO *func;

            if (idx == -1)
               imprimeErro("Simbolo inexistente");

            simb = buscaItem(&TS, idx);
            if (simb->categoria == var_simples){
               VS = simb->atributos;
               tipo_aux = VS->tipo;
            }
            else if(simb->categoria == param_formal){
               PF = simb->atributos;
               tipo_aux = PF->tipo;
            }

            else if(simb->categoria == funcao){
               func = simb->atributos;
               tipo_aux = func->tipo;
            }

            else{
               sprintf(erro, "Simbolo %s não é variável simples, parâmetro formal ou função", token);
               imprimeErro(erro);
            }
            
            strncpy(ident, token, strlen(token));
            ident[strlen(token)] = '\0';

            // fprintf(stderr, "DEBUG - Empilhando tipo de %s em F\n", simb->id);

            empilha(F, &tipo_aux);
         }
         chamada_funcao
      | NUMERO {
         /* carrega constante */
         sprintf(comando, "CRCT %s", token);
         geraCodigo(NULL, comando);

         // if (proc) checaParam();

         /* empilha o tipo inteiro */
         tipo_aux = inteiro;
         empilha(F, &tipo_aux);
      }
      | ABRE_PARENTESES expressao FECHA_PARENTESES
         {
            // vem de um fator, precisamos desempilhar de E e colocar em F
            // fprintf(stderr, "DEBUG - Regra expressão com parênteses\n");
            TIPOS *t1;
            t1 = desempilha(E);

            // fprintf(stderr, "empilha aqui\n");

            empilha(F, t1);
            // free(t1);
         }

   // | chama_func 
   | NOT fator
;


/* REGRA 21 */
desvio: GOTO NUMERO {
         STRUCT_LABEL *label;
         int i;

         if ((i = buscaSimbolo(labels, token)) < 0)
            imprimeErro("Label não encontrado na pilha");
         label = buscaItem(labels, i);

         sprintf(comando, "DSVR %s, %d, %d", label->nome, label->nivel_lex, nivel_lexico);
         if(label->nivel_lex != nivel_lexico)  // Limpar a TS. Nivel lexico mudou
            deletaPorNivelLexico(&TS, label->nivel_lex);

         geraCodigo(NULL, comando);
      }
;

/* REGRA 22 */
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
            rotulo = buscaItem(rotulos, rotulos->tamanho-2);
            sprintf(comando, "DSVS %s", rotulo);
            geraCodigo(NULL, comando);

            // Gera NADA com segundo rotulo
            rotulo = buscaItem(rotulos, rotulos->tamanho-1);
            geraCodigo(rotulo, "NADA");
         }
            comando_sem_rotulo
         {
            // Gera NADA com primeiro rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho-2);
            geraCodigo(rotulo, "NADA");
         }
         | %prec LOWER_THAN_ELSE
         {
            // Gera NADA com segundo rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho-1);
            geraCodigo(rotulo, "NADA");
         }
;

/* REGRA 23 */
comando_repetitivo: WHILE
                     {
                        char *rotulo = prox_rotulo();
                        empilha(rotulos, rotulo);
                        empilha(rotulos, prox_rotulo());
                        geraCodigo(rotulo, "NADA");
                     }
                     expressao DO
                     {
                        char *rotulo = buscaItem(rotulos, rotulos->tamanho-1);
                        sprintf(comando, "DSVF %s", rotulo);
                        geraCodigo(NULL, comando);
                     }
                     comando_sem_rotulo
                     {
                        char *rotulo;
                        rotulo = buscaItem(rotulos, rotulos->tamanho-2);
                        sprintf(comando, "DSVS %s", rotulo);
                        geraCodigo(NULL, comando);
                        rotulo = desempilha(rotulos);
                        geraCodigo(rotulo, "NADA");

                        free(rotulo);
                        rotulo = desempilha(rotulos);
                        free(rotulo);
                     }
;

chamada_funcao: variavel | chama_func;

/* REGRA 30 */
/* Varifica se é varíavel simples ou parâmetro formal */
variavel:  {
      int idx = buscaSimbolo(&TS, ident);
      SIMBOLO *simb;

      if (idx == -1)
         imprimeErro("Simbolo inexistente");

      simb = buscaItem(&TS, idx);
      comandoCarrega(simb);
   }
;

/* REGRA 31 */
chama_func: ABRE_PARENTESES
            {
               int idx = buscaSimbolo(&TS, ident);

               if (idx == -1)
                  imprimeErro("Simbolo inexistente");

               geraCodigo(NULL, "AMEM 1");

               proc = buscaItem(&TS, idx);
               num_params = 1;
            }
            lista_expressoes FECHA_PARENTESES
            {
               int i;
               if (proc->categoria != funcao) {
                  imprimeErro("Simbolo não é função");
               }

               FUNCAO *aux_func = proc->atributos;

               TIPOS *tipo;
               PARAM_FORMAL *aux_pf;
               for (i=0; i<aux_func->num_params; i++) {
                  tipo = desempilha(E);
                  aux_pf = aux_func->parametros[i]->atributos;
                  if ((*tipo) != aux_pf->tipo)
                     imprimeErro("Tipo incompatível");
               }

               sprintf(comando, "CHPR %s, %d", aux_func->rotulo, nivel_lexico);
               geraCodigo(NULL, comando);

               l_elem = NULL;
               proc = NULL;
            }
;

/* REGRA LEITURA */
comando_read: READ ABRE_PARENTESES parametros_leitura FECHA_PARENTESES
;

/* parâmetros do read */
parametros_leitura: parametros_leitura VIRGULA IDENT
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

   return 0;
}
