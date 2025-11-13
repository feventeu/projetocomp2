/**
 * @file jogo.c
 * @brief Implementação do modo Forca (exemplo)
 *
 * Implementação simples: usuário tenta adivinhar letras; erros até 6.
 */

#include "jogo.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

static void mask_palavra(const char *pal, char *saida) {
    size_t n = strlen(pal);
    for (size_t i = 0; i < n; ++i) {
        if (isalpha((unsigned char)pal[i])) saida[i] = '_';
        else saida[i] = pal[i];
    }
    saida[n] = '\0';
}

void jogar_forca(const Pergunta *p) {
    char resposta[MAX_PALAVRA_LEN];
    char palavra[MAX_PALAVRA_LEN];
    /* palavra em lowercase para consistência */
    for (size_t i = 0; i < strlen(p->palavra) && i < MAX_PALAVRA_LEN - 1; ++i)
        palavra[i] = (char)tolower((unsigned char)p->palavra[i]);
    palavra[strlen(p->palavra)] = '\0';

    mask_palavra(palavra, resposta);
    int erros = 0;
    const int max_erros = 6;
    char usadas[256] = {0};
    int num_usadas = 0;

    printf("=== Jogo: Forca ===\n");
    printf("Categoria: %s | Dificuldade: %d\n", p->categoria, (int)p->dificuldade);
    if (p->num_dicas > 0) {
        printf("Dica 1: %s\n", p->dicas[0]);
    }
    while (erros < max_erros) {
        printf("\nPalavra: %s\nErros: %d/%d\nLetras usadas: ", resposta, erros, max_erros);
        for (int i = 0; i < num_usadas; ++i) printf("%c ", usadas[i]);
        puts("");
        printf("Digite uma letra (ou '!' para desistir): ");
        char linha[128];
        if (!fgets(linha, sizeof(linha), stdin)) break;
        char ch = linha[0];
        if (ch == '\n' || ch == '\r') continue;
        if (ch == '!') { printf("Você desistiu. Palavra: %s\n", palavra); return; }
        ch = (char)tolower((unsigned char)ch);
        if (!isalpha((unsigned char)ch)) { puts("Digite uma letra válida."); continue; }
        int ja = 0;
        for (int i = 0; i < num_usadas; ++i) if (usadas[i] == ch) { ja = 1; break; }
        if (ja) { puts("Letra já usada."); continue; }
        usadas[num_usadas++] = ch;

        int acerto = 0;
        for (size_t i = 0; i < strlen(palavra); ++i) {
            if (palavra[i] == ch) {
                resposta[i] = palavra[i];
                acerto = 1;
            }
        }
        if (!acerto) {
            erros++;
            printf("Letra incorreta!\n");
            /* mostrar próxima dica se houver */
            if (erros == 2 && p->num_dicas >= 2) {
                printf("Dica extra: %s\n", p->dicas[1]);
            } else if (erros == 4 && p->num_dicas == 3) {
                printf("Dica extra: %s\n", p->dicas[2]);
            }
        } else {
            printf("Acertou uma letra!\n");
        }
        if (strcmp(resposta, palavra) == 0) {
            printf("\nParabéns! Você adivinhou: %s\n", palavra);
            return;
        }
    }
    printf("Você perdeu. A palavra era: %s\n", palavra);
}

void iniciar_partida(ListaPerguntas *lista) {
    if (lista->tamanho == 0) {
        puts("Nenhuma palavra disponível para jogar.");
        return;
    }
    /* Seleciona aleatoriamente uma palavra */
    srand((unsigned)time(NULL));
    size_t idx = (size_t)(rand() % lista->tamanho);
    jogar_forca(&lista->dados[idx]);
}
