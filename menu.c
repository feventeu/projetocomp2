/**
 * @file menu.c
 * @brief Implementação do menu principal e submenus
 */
#include "menu.h"
#include "arquivo.h"
#include "jogo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void limpar_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void cadastrar_dialogo(ListaPerguntas *lista) {
    Pergunta p;
    memset(&p, 0, sizeof(p));
    printf("Digite a palavra: ");
    if (!fgets(p.palavra, sizeof(p.palavra), stdin)) return;
    p.palavra[strcspn(p.palavra, "\r\n")] = '\0';
    printf("Digite a categoria: ");
    if (!fgets(p.categoria, sizeof(p.categoria), stdin)) return;
    p.categoria[strcspn(p.categoria, "\r\n")] = '\0';
    printf("Dificuldade (1-Facil,2-Media,3-Dificil): ");
    int d = 2;
    if (scanf("%d", &d) != 1) d = 2;
    limpar_stdin();
    p.dificuldade = (Dificuldade)d;
    printf("Número de dicas (0-%d): ", MAX_DICAS);
    int nd = 1;
    if (scanf("%d", &nd) != 1) nd = 1;
    limpar_stdin();
    if (nd < 0) nd = 0; if (nd > MAX_DICAS) nd = MAX_DICAS;
    p.num_dicas = nd;
    for (int i = 0; i < p.num_dicas; ++i) {
        printf("Dica %d: ", i + 1);
        if (!fgets(p.dicas[i], sizeof(p.dicas[i]), stdin)) return;
        p.dicas[i][strcspn(p.dicas[i], "\r\n")] = '\0';
    }
    if (inserir_pergunta(lista, &p)) puts("Palavra cadastrada com sucesso.");
    else puts("Erro ao cadastrar palavra.");
}

static void editar_dialogo(ListaPerguntas *lista) {
    listar_todas(lista);
    printf("Digite o índice da palavra a editar: ");
    size_t idx;
    if (scanf("%zu", &idx) != 1) { limpar_stdin(); return; }
    limpar_stdin();
    if (idx >= lista->tamanho) { puts("Índice inválido."); return; }
    Pergunta p = lista->dados[idx];
    printf("Editando [%zu] %s\n", idx, p.palavra);
    printf("Nova palavra (enter para manter): ");
    char buf[256];
    if (!fgets(buf, sizeof(buf), stdin)) return;
    buf[strcspn(buf, "\r\n")] = '\0';
    if (buf[0] != '\0') strncpy(p.palavra, buf, sizeof(p.palavra)-1);
    printf("Nova categoria (enter para manter): ");
    if (!fgets(buf, sizeof(buf), stdin)) return;
    buf[strcspn(buf, "\r\n")] = '\0';
    if (buf[0] != '\0') strncpy(p.categoria, buf, sizeof(p.categoria)-1);
    printf("Dificuldade (1-3, 0 para manter): ");
    int d;
    if (scanf("%d", &d) == 1) {
        if (d >= 1 && d <= 3) p.dificuldade = (Dificuldade)d;
    }
    limpar_stdin();
    printf("Número de dicas (0-%d, -1 para manter): ", MAX_DICAS);
    int nd;
    if (scanf("%d", &nd) == 1) {
        if (nd >= 0 && nd <= MAX_DICAS) {
            p.num_dicas = nd;
            limpar_stdin();
            for (int i = 0; i < p.num_dicas; ++i) {
                printf("Nova dica %d: ", i + 1);
                if (!fgets(p.dicas[i], sizeof(p.dicas[i]), stdin)) return;
                p.dicas[i][strcspn(p.dicas[i], "\r\n")] = '\0';
            }
        } else {
            limpar_stdin();
        }
    } else {
        limpar_stdin();
    }
    if (atualizar_pergunta(lista, idx, &p)) puts("Atualizado com sucesso.");
    else puts("Erro ao atualizar.");
}

static void excluir_dialogo(ListaPerguntas *lista) {
    listar_todas(lista);
    printf("Digite o índice da palavra a excluir: ");
    size_t idx;
    if (scanf("%zu", &idx) != 1) { limpar_stdin(); return; }
    limpar_stdin();
    if (excluir_pergunta(lista, idx)) puts("Excluído com sucesso.");
    else puts("Índice inválido.");
}

void menu_principal(ListaPerguntas *lista, const char *arquivo_binario, const char *arquivo_csv_inicial) {
    int carregou = carregar_binario(arquivo_binario, lista);
    if (!carregou) {
        printf("Nenhum arquivo binário encontrado. Importando CSV inicial: %s\n", arquivo_csv_inicial);
        inicializar_lista(lista);
        int imp = importar_csv(arquivo_csv_inicial, lista);
        printf("Importadas %d palavras do CSV inicial.\n", imp);
    } else {
        puts("Dados carregados de arquivo binário.");
    }

    int opc = 0;
    while (1) {
        puts("\n=== MENU PRINCIPAL ===");
        puts("1 - Jogar (Forca)");
        puts("2 - Listar palavras");
        puts("3 - Cadastrar palavra");
        puts("4 - Editar palavra");
        puts("5 - Excluir palavra");
        puts("6 - Listar por dificuldade");
        puts("7 - Listar por categoria");
        puts("8 - Exportar para CSV");
        puts("9 - Salvar e Sair");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { limpar_stdin(); continue; }
        limpar_stdin();
        if (opc == 1) {
            iniciar_partida(lista);
        } else if (opc == 2) {
            listar_todas(lista);
        } else if (opc == 3) {
            cadastrar_dialogo(lista);
        } else if (opc == 4) {
            editar_dialogo(lista);
        } else if (opc == 5) {
            excluir_dialogo(lista);
        } else if (opc == 6) {
            printf("Dificuldade (1-3): ");
            int d; if (scanf("%d", &d) != 1) { limpar_stdin(); continue; }
            limpar_stdin();
            listar_por_dificuldade(lista, (Dificuldade)d);
        } else if (opc == 7) {
            char cat[64];
            printf("Categoria: ");
            if (!fgets(cat, sizeof(cat), stdin)) continue;
            cat[strcspn(cat, "\r\n")] = '\0';
            listar_por_categoria(lista, cat);
        } else if (opc == 8) {
            char nome[256];
            printf("Nome do CSV de saída: ");
            if (!fgets(nome, sizeof(nome), stdin)) continue;
            nome[strcspn(nome, "\r\n")] = '\0';
            if (exportar_csv(nome, lista)) puts("Exportado com sucesso.");
            else puts("Erro ao exportar.");
        } else if (opc == 9) {
            if (salvar_binario(arquivo_binario, lista)) puts("Dados salvos com sucesso (binário).");
            else puts("Erro ao salvar dados.");
            break;
        } else {
            puts("Opção inválida.");
        }
    }
}
