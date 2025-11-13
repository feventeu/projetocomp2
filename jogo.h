/**
 * @file jogo.h
 * @brief Prototipos das rotinas de jogo (partida)
 */
#ifndef JOGO_H
#define JOGO_H

#include "pergunta.h"

/**
 * @brief Executa uma partida de Forca usando uma pergunta selecionada.
 * @param p Pergunta a ser usada
 */
void jogar_forca(const Pergunta *p);

/**
 * @brief Executa uma sessão de jogo: escolhe palavras e controla sequência.
 */
void iniciar_partida(ListaPerguntas *lista);

#endif /* JOGO_H */
