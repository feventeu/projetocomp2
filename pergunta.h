/**
 * @file pergunta.h
 * @brief Definições e operações sobre perguntas (palavra, dicas, dificuldade)
 *
 * Estrutura Pergunta com até 3 dicas. Lista dinâmica de perguntas.
 */

#ifndef PERGUNTA_H
#define PERGUNTA_H

#include <stddef.h>

#define MAX_PALAVRA_LEN 64
#define MAX_DICA_LEN 128
#define MAX_DICAS 3

typedef enum {
    DIFICULDADE_FACIL = 1,
    DIFICULDADE_MEDIA = 2,
    DIFICULDADE_DIFICIL = 3
} Dificuldade;

/**
 * @brief Estrutura que representa uma pergunta/questão do jogo.
 */
typedef struct {
    char palavra[MAX_PALAVRA_LEN];
    char dicas[MAX_DICAS][MAX_DICA_LEN];
    int num_dicas;
    Dificuldade dificuldade;
    char categoria[64]; /* tema ou categoria */
} Pergunta;

/**
 * @brief Estrutura que contém uma lista dinâmica de Pergunta.
 */
typedef struct {
    Pergunta *dados;
    size_t tamanho;    /* número de elementos usados */
    size_t capacidade; /* capacidade alocada */
} ListaPerguntas;

/* Criação / liberação */
void inicializar_lista(ListaPerguntas *lista);
void liberar_lista(ListaPerguntas *lista);

/* CRUD */
int inserir_pergunta(ListaPerguntas *lista, const Pergunta *p);
int atualizar_pergunta(ListaPerguntas *lista, size_t index, const Pergunta *p);
int excluir_pergunta(ListaPerguntas *lista, size_t index);

/* Busca / listagem */
ssize_t buscar_por_palavra(const ListaPerguntas *lista, const char *palavra);
void listar_todas(const ListaPerguntas *lista);
void listar_por_dificuldade(const ListaPerguntas *lista, Dificuldade d);
void listar_por_categoria(const ListaPerguntas *lista, const char *categoria);

#endif /* PERGUNTA_H */
