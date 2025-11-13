/**
 * @file arquivo.h
 * @brief Operações de I/O: leitura CSV, salvar/carregar binário, export CSV
 */
#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "pergunta.h"

/**
 * @brief Tenta carregar dados binários. Retorna 1 se carregou, 0 se não existe.
 */
int carregar_binario(const char *nome_arquivo, ListaPerguntas *lista);

/**
 * @brief Salva a lista em formato binário. Retorna 1 em sucesso.
 */
int salvar_binario(const char *nome_arquivo, const ListaPerguntas *lista);

/**
 * @brief Lê um arquivo CSV com formato:
 * palavra,categoria,dificuldade,num_dicas,dica1,dica2,dica3
 * (dicas extras podem faltar). Retorna número de entradas importadas.
 */
int importar_csv(const char *nome_csv, ListaPerguntas *lista);

/**
 * @brief Exporta lista para CSV (mesmo formato acima). Retorna 1 sucesso.
 */
int exportar_csv(const char *nome_csv, const ListaPerguntas *lista);

#endif /* ARQUIVO_H */
