/**
 * @file arquivo.c
 * @brief Implementação das operações de arquivo (csv/bin)
 */

#include "arquivo.h"
#include "pergunta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int carregar_binario(const char *nome_arquivo, ListaPerguntas *lista) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f)
        return 0; /* arquivo inexistente */

    size_t n;
    if (fread(&n, sizeof(size_t), 1, f) != 1) {
        fclose(f);
        return 0;
    }

    inicializar_lista(lista);

    for (size_t i = 0; i < n; ++i) {
        Pergunta p;
        if (fread(&p, sizeof(Pergunta), 1, f) != 1) {
            fclose(f);
            liberar_lista(lista);
            return 0;
        }
        inserir_pergunta(lista, &p);
    }

    fclose(f);
    return 1;
}

int salvar_binario(const char *nome_arquivo, const ListaPerguntas *lista) {
    FILE *f = fopen(nome_arquivo, "wb");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s para escrita: %s\n",
                nome_arquivo, strerror(errno));
        return 0;
    }

    if (fwrite(&lista->tamanho, sizeof(size_t), 1, f) != 1) {
        fclose(f);
        return 0;
    }

    if (lista->tamanho > 0) {
        if (fwrite(lista->dados, sizeof(Pergunta), lista->tamanho, f) != lista->tamanho) {
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

static char *trim_newline(char *s) {
    char *p = s + strlen(s) - 1;
    while (p >= s && (*p == '\n' || *p == '\r')) {
        *p = '\0';
        --p;
    }
    return s;
}

int importar_csv(const char *nome_csv, ListaPerguntas *lista) {
    FILE *f = fopen(nome_csv, "r");
    if (!f) {
        fprintf(stderr, "Não foi possível abrir %s: %s\n", nome_csv, strerror(errno));
        return 0;
    }

    char linha[1024];
    int importadas = 0;

    while (fgets(linha, sizeof(linha), f)) {
        trim_newline(linha);

        if (linha[0] == '\0')
            continue;

        char *tokens[10];
        int t = 0;

        char *p = strtok(linha, ",");
        while (p && t < 10) {
            tokens[t++] = p;
            p = strtok(NULL, ",");
        }

        if (t < 4)
            continue;

        Pergunta q;
        memset(&q, 0, sizeof(q));

        strncpy(q.palavra, tokens[0], MAX_PALAVRA_LEN - 1);
        strncpy(q.categoria, tokens[1], sizeof(q.categoria) - 1);
        q.dificuldade = (Dificuldade)atoi(tokens[2]);
        q.num_dicas = atoi(tokens[3]);
        if (q.num_dicas > MAX_DICAS) q.num_dicas = MAX_DICAS;

        for (int i = 0; i < q.num_dicas; i++) {
            if (4 + i < t)
                strncpy(q.dicas[i], tokens[4 + i], MAX_DICA_LEN - 1);
            else
                q.dicas[i][0] = '\0';
        }

        inserir_pergunta(lista, &q);
        importadas++;
    }

    fclose(f);
    return importadas;
}

int exportar_csv(const char *nome_csv, const ListaPerguntas *lista) {
    FILE *f = fopen(nome_csv, "w");
    if (!f) {
        fprintf(stderr, "Erro ao abrir %s para escrita\n", nome_csv);
        return 0;
    }

    for (size_t i = 0; i < lista->tamanho; i++) {
        const Pergunta *p = &lista->dados[i];

        fprintf(f, "%s,%s,%d,%d",
                p->palavra, p->categoria, p->dificuldade, p->num_dicas);

        for (int j = 0; j < p->num_dicas; j++)
            fprintf(f, ",%s", p->dicas[j]);

        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}
