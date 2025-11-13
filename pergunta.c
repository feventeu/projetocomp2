/**
 * @file pergunta.c
 * @brief Implementação das operações sobre ListaPerguntas
 */

#include "pergunta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCREMENTO_CAP 16

void inicializar_lista(ListaPerguntas *lista) {
    lista->dados = malloc(sizeof(Pergunta) * INCREMENTO_CAP);
    if (!lista->dados) {
        fprintf(stderr, "Erro de memória ao inicializar lista\n");
        exit(EXIT_FAILURE);
    }
    lista->tamanho = 0;
    lista->capacidade = INCREMENTO_CAP;
}

void liberar_lista(ListaPerguntas *lista) {
    free(lista->dados);
    lista->dados = NULL;
    lista->tamanho = 0;
    lista->capacidade = 0;
}

static int garantir_capacidade(ListaPerguntas *lista, size_t adicionais) {
    if (lista->tamanho + adicionais <= lista->capacidade) return 1;
    size_t nova = lista->capacidade;
    while (nova < lista->tamanho + adicionais) nova *= 2;
    Pergunta *tmp = realloc(lista->dados, nova * sizeof(Pergunta));
    if (!tmp) return 0;
    lista->dados = tmp;
    lista->capacidade = nova;
    return 1;
}

int inserir_pergunta(ListaPerguntas *lista, const Pergunta *p) {
    if (!garantir_capacidade(lista, 1)) return 0;
    lista->dados[lista->tamanho++] = *p;
    return 1;
}

int atualizar_pergunta(ListaPerguntas *lista, size_t index, const Pergunta *p) {
    if (index >= lista->tamanho) return 0;
    lista->dados[index] = *p;
    return 1;
}

int excluir_pergunta(ListaPerguntas *lista, size_t index) {
    if (index >= lista->tamanho) return 0;
    /* move elementos */
    for (size_t i = index; i + 1 < lista->tamanho; ++i) {
        lista->dados[i] = lista->dados[i + 1];
    }
    lista->tamanho--;
    return 1;
}

ssize_t buscar_por_palavra(const ListaPerguntas *lista, const char *palavra) {
    for (size_t i = 0; i < lista->tamanho; ++i) {
        if (strcmp(lista->dados[i].palavra, palavra) == 0) return (ssize_t)i;
    }
    return -1;
}

void imprimir_pergunta(const Pergunta *p, size_t idx) {
    printf(" [%zu] Palavra: %s | Dificuldade: %d | Categoria: %s\n", idx, p->palavra, (int)p->dificuldade, p->categoria);
    for (int i = 0; i < p->num_dicas; ++i) {
        printf("      Dica %d: %s\n", i + 1, p->dicas[i]);
    }
}

void listar_todas(const ListaPerguntas *lista) {
    if (lista->tamanho == 0) {
        puts("Nenhuma palavra cadastrada.");
        return;
    }
    for (size_t i = 0; i < lista->tamanho; ++i) {
        imprimir_pergunta(&lista->dados[i], i);
    }
}

void listar_por_dificuldade(const ListaPerguntas *lista, Dificuldade d) {
    int found = 0;
    for (size_t i = 0; i < lista->tamanho; ++i) {
        if (lista->dados[i].dificuldade == d) {
            imprimir_pergunta(&lista->dados[i], i);
            found = 1;
        }
    }
    if (!found) printf("Nenhuma palavra encontrada para dificuldade %d\n", (int)d);
}

void listar_por_categoria(const ListaPerguntas *lista, const char *categoria) {
    int found = 0;
    for (size_t i = 0; i < lista->tamanho; ++i) {
        if (strcmp(lista->dados[i].categoria, categoria) == 0) {
            imprimir_pergunta(&lista->dados[i], i);
            found = 1;
        }
    }
    if (!found) printf("Nenhuma palavra encontrada para categoria '%s'\n", categoria);
}
