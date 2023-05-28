#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"
#include "tabelaDeSimbolos.h"

void inicializaTS(PILHA *TS, int tam) {
    TS = criaPilha(tam, sizeof(SIMBOLO));
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

// // devolve o índice na TS correspondente à última ocorrência de id
// void busca(PILHA *TS, char *id) {

// }

// // retira do topo da pilha as n últimas entradas 
// void elimina(PILHA *TS, int n) {

// }

// // Elimina entradas com o nível lexico
// void eliminaNivelLex(PILHA *TS, int nivel) {

// }