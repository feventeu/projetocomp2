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

    /* Inicializa a estrutura para valores seguros antes de passar adiante.
       Evita comportamento indefinido caso alguma função verifique os campos. */
    ListaPerguntas lista;
    lista.dados = NULL;
    lista.tamanho = 0;
    lista.capacidade = 0;

    /* menu_principal espera um ponteiro válido para ListaPerguntas.
       Ela irá carregar o binário ou inicializar/carregar o CSV conforme necessário. */
    menu_principal(&lista, arquivo_bin, csv_inicial);

    /* liberar memória antes de sair (liberar_lista aceita dados == NULL) */
    liberar_lista(&lista);

    printf("Programa finalizado. Até mais!\n");
    return 0;
}
