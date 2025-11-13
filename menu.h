/**
 * @file menu.h
 * @brief Protótipos do menu interativo
 */
#ifndef MENU_H
#define MENU_H

#include "pergunta.h"

/**
 * @brief Mostra o menu principal e responde à seleção do usuário.
 */
void menu_principal(ListaPerguntas *lista, const char *arquivo_binario, const char *arquivo_csv_inicial);

#endif /* MENU_H */
