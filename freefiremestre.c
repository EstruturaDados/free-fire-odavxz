#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

/* ============================================================
                        STRUCT PRINCIPAL
   ============================================================ */

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;   // 1 a 10
} Componente;

/* ============================================================
                  VARIÁVEIS GLOBAIS DE CONTAGEM
   ============================================================ */

long comparacoes = 0;

/* ============================================================
                        FUNÇÕES AUXILIARES
   ============================================================ */

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

/* ============================================================
                     ALGORITMOS DE ORDENAÇÃO
   ============================================================ */

/* ------------ 1. Bubble Sort por NOME ------------ */
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

/* ----------- 2. Insertion Sort por TIPO ----------- */
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(chave.tipo, v[j].tipo) < 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

/* ------- 3. Selection Sort por PRIORIDADE -------- */
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }

        if (min != i) {
            Componente tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
}

/* ============================================================
                    BUSCA BINÁRIA POR NOME
   ============================================================ */

int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/* ============================================================
                        MEDIÇÃO DE TEMPO
   ============================================================ */

double medirTempo(void (*alg)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    alg(v, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

/* ============================================================
                               MAIN
   ============================================================ */

int main() {
    Componente lista[MAX_COMP];
    int total = 0;
    int opcao;
    char chaveBusca[30];
    int ordenadoPorNome = 0;

    do {
        printf("\n========== MENU TORRE DE FUGA ==========\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Exibir componentes\n");
        printf("3 - Ordenar por nome (Bubble Sort)\n");
        printf("4 - Ordenar por tipo (Insertion Sort)\n");
        printf("5 - Ordenar por prioridade (Selection Sort)\n");
        printf("6 - Busca binária por nome (requer ordenação por nome)\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

        /* ------------ CADASTRO ------------ */
        case 1:
            if (total >= MAX_COMP) {
                printf("Limite de componentes atingido!\n");
                break;
            }
            printf("Nome: ");
            fgets(lista[total].nome, 30, stdin);
            lista[total].nome[strcspn(lista[total].nome, "\n")] = 0;

            printf("Tipo: ");
            fgets(lista[total].tipo, 20, stdin);
            lista[total].tipo[strcspn(lista[total].tipo, "\n")] = 0;

            printf("Prioridade (1 a 10): ");
            scanf("%d", &lista[total].prioridade);
            limparBuffer();

            total++;
            printf("Componente cadastrado!\n");
            break;

        /* ------------ EXIBIR ------------ */
        case 2:
            mostrarComponentes(lista, total);
            break;

        /* ------------ ORDENAR POR NOME ------------ */
        case 3: {
            double tempo = medirTempo(bubbleSortNome, lista, total);
            printf("Bubble Sort concluído!\n");
            printf("Comparações: %ld\nTempo: %.6f s\n", comparacoes, tempo);
            ordenadoPorNome = 1;
            mostrarComponentes(lista, total);
            break;
        }

        /* ------------ ORDENAR POR TIPO ------------ */
        case 4: {
            double tempo = medirTempo(insertionSortTipo, lista, total);
            printf("Insertion Sort concluído!\n");
            printf("Comparações: %ld\nTempo: %.6f s\n", comparacoes, tempo);
            ordenadoPorNome = 0;
            mostrarComponentes(lista, total);
            break;
        }

        /* ------------ ORDENAR POR PRIORIDADE ------------ */
        case 5: {
            double tempo = medirTempo(selectionSortPrioridade, lista, total);
            printf("Selection Sort concluído!\n");
            printf("Comparações: %ld\nTempo: %.6f s\n", comparacoes, tempo);
            ordenadoPorNome = 0;
            mostrarComponentes(lista, total);
            break;
        }

        /* ------------ BUSCA BINÁRIA ------------ */
        case 6:
            if (!ordenadoPorNome) {
                printf("ERRO: para usar busca binária, ordene primeiro por NOME.\n");
                break;
            }
            printf("Nome para buscar: ");
            fgets(chaveBusca, 30, stdin);
            chaveBusca[strcspn(chaveBusca, "\n")] = 0;

            int pos = buscaBinariaPorNome(lista, total, chaveBusca);
            printf("Comparações (busca binária): %ld\n", comparacoes);

            if (pos >= 0)
                printf("Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                       lista[pos].nome, lista[pos].tipo, lista[pos].prioridade);
            else
                printf("Componente não encontrado!\n");

            break;

        }
    } while (opcao != 0);

    printf("Encerrando o módulo mestre...\n");
    return 0;
}
