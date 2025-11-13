/**
 * @file main.c
 * @brief Ponto de entrada do programa
 *
 * Uso:
 *  make run
 *
 * Observação: altera os nomes de arquivos se desejar.
 */

#include "pergunta.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *arquivo_bin = "dados.bin";
    const char *csv_inicial = "palavras_iniciais.csv";

    ListaPerguntas lista;
    /* menu_principal chama carregar_binario e inicializa lista se necessário */
    menu_principal(&lista, arquivo_bin, csv_inicial);

    /* liberar memória antes de sair */
    liberar_lista(&lista);

    printf("Programa finalizado. Até mais!\n");
    return 0;
}
