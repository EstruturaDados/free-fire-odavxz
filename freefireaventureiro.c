#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 50

/* ===========================================================
                STRUCTS UTILIZADAS
   =========================================================== */

/* Struct Item usada em ambas as mochilas */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* Nó da lista encadeada */
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* ===========================================================
                VARIÁVEIS GLOBAIS PARA CONTAGEM
   =========================================================== */
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* ===========================================================
            FUNÇÕES DA MOCHILA USANDO VETOR
   =========================================================== */

void inserirItemVetor(Item vetor[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome do item: ");
    scanf("%29s", vetor[*total].nome);

    printf("Tipo do item: ");
    scanf("%19s", vetor[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &vetor[*total].quantidade);

    (*total)++;
    printf("Item inserido no vetor!\n");
}

void removerItemVetor(Item vetor[], int *total) {
    if (*total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    scanf("%29s", nome);

    for (int i = 0; i < *total; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

void listarItensVetor(Item vetor[], int total) {
    printf("\n=== ITENS NO VETOR ===\n");
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("%d) %s (%s) x%d\n", i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

int buscarSequencialVetor(Item vetor[], int total, char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < total; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

/* Ordenação Selection Sort */
void ordenarVetor(Item vetor[], int total) {
    for (int i = 0; i < total - 1; i++) {
        int min = i;
        for (int j = i + 1; j < total; j++) {
            if (strcmp(vetor[j].nome, vetor[min].nome) < 0) {
                min = j;
            }
        }
        if (min != i) {
            Item tmp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = tmp;
        }
    }
    printf("Vetor ordenado por nome!\n");
}

/* Busca binária */
int buscarBinariaVetor(Item vetor[], int total, char nome[]) {
    comparacoesBinaria = 0;
    int ini = 0, fim = total - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/* ===========================================================
        FUNÇÕES DA MOCHILA USANDO LISTA ENCADEADA
   =========================================================== */

void inserirItemLista(No** lista) {
    No* novo = (No*) malloc(sizeof(No));

    printf("Nome do item: ");
    scanf("%29s", novo->dados.nome);

    printf("Tipo: ");
    scanf("%19s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *lista;
    *lista = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista(No** lista) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    char nome[30];
    printf("Nome do item para remover: ");
    scanf("%29s", nome);

    No *atual = *lista, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *lista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado!\n");
}

void listarItensLista(No* lista) {
    printf("\n=== ITENS NA LISTA ===\n");
    if (lista == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (lista != NULL) {
        printf("%s (%s) x%d\n", lista->dados.nome, lista->dados.tipo, lista->dados.quantidade);
        lista = lista->proximo;
    }
}

No* buscarSequencialLista(No* lista, char nome[]) {
    comparacoesSequencial = 0;
    while (lista != NULL) {
        comparacoesSequencial++;
        if (strcmp(lista->dados.nome, nome) == 0)
            return lista;
        lista = lista->proximo;
    }
    return NULL;
}

/* ===========================================================
                        MAIN
   =========================================================== */

int main() {
    Item mochilaVetor[MAX_ITENS];
    int totalVetor = 0;

    No* mochilaLista = NULL;

    int opcao, estrutura;
    char nomeBusca[30];

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1 - Usar vetor\n");
        printf("2 - Usar lista encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        printf("\n1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (sequencial)\n");
        if (estrutura == 1)
            printf("5 - Ordenar vetor\n"
                   "6 - Busca binária\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (estrutura) {

        /* ----------------- SISTEMA COM VETOR ------------------ */
        case 1:
            switch (opcao) {
                case 1: inserirItemVetor(mochilaVetor, &totalVetor); break;
                case 2: removerItemVetor(mochilaVetor, &totalVetor); break;
                case 3: listarItensVetor(mochilaVetor, totalVetor); break;

                case 4:
                    printf("Nome para busca sequencial: ");
                    scanf("%29s", nomeBusca);
                    {
                        int pos = buscarSequencialVetor(mochilaVetor, totalVetor, nomeBusca);
                        printf("Comparações: %d\n", comparacoesSequencial);
                        if (pos >= 0)
                            printf("Item encontrado: %s\n", mochilaVetor[pos].nome);
                        else
                            printf("Item não encontrado.\n");
                    }
                    break;

                case 5:
                    ordenarVetor(mochilaVetor, totalVetor);
                    break;

                case 6:
                    printf("Nome para busca binária: ");
                    scanf("%29s", nomeBusca);
                    {
                        int pos = buscarBinariaVetor(mochilaVetor, totalVetor, nomeBusca);
                        printf("Comparações: %d\n", comparacoesBinaria);
                        if (pos >= 0)
                            printf("Item encontrado: %s\n", mochilaVetor[pos].nome);
                        else
                            printf("Item não encontrado.\n");
                    }
                    break;
            }
            break;

        /* ------------- SISTEMA COM LISTA ENCADEADA ------------ */
        case 2:
            switch (opcao) {
                case 1: inserirItemLista(&mochilaLista); break;
                case 2: removerItemLista(&mochilaLista); break;
                case 3: listarItensLista(mochilaLista); break;

                case 4:
                    printf("Nome para busca: ");
                    scanf("%29s", nomeBusca);
                    {
                        No* aux = buscarSequencialLista(mochilaLista, nomeBusca);
                        printf("Comparações: %d\n", comparacoesSequencial);
                        if (aux)
                            printf("Item encontrado: %s\n", aux->dados.nome);
                        else
                            printf("Item não encontrado.\n");
                    }
                    break;
            }
            break;
        }
    } while (1);

    printf("Encerrando...\n");
    return 0;
}
