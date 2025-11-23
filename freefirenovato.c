#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

/*
    Struct Item:
    Representa um item da mochila.
    - nome: nome do item
    - tipo: categoria do item (arma, munição, cura, etc.)
    - quantidade: número de unidades que o jogador possui
*/
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* ===========================================================
                       INSERIR ITEM
   =========================================================== */
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Cadastro de Item ===\n");

    printf("Nome do item: ");
    scanf("%29s", mochila[*total].nome);

    printf("Tipo do item (arma, municao, cura...): ");
    scanf("%19s", mochila[*total].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++; // Atualiza o número de itens cadastrados

    printf("Item adicionado com sucesso!\n");
}

/* ===========================================================
                       REMOVER ITEM
   =========================================================== */
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    int encontrado = -1;

    printf("\nInforme o nome do item que deseja remover: ");
    scanf("%29s", nomeRemover);

    // Busca pelo item
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Item não encontrado!\n");
        return;
    }

    // Desloca itens para preencher o espaço removido
    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*total)--;

    printf("\nItem removido com sucesso!\n");
}

/* ===========================================================
                       LISTAR ITENS
   =========================================================== */
void listarItens(Item mochila[], int total) {
    printf("\n===== Itens da Mochila =====\n");

    if (total == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

/* ===========================================================
                      BUSCAR ITEM
   =========================================================== */
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia. Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nInforme o nome do item a buscar: ");
    scanf("%29s", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado na mochila.\n");
}

/* ===========================================================
                           MAIN
   =========================================================== */
int main() {
    Item mochila[MAX_ITENS]; // Vetor de até 10 itens
    int totalItens = 0;      // Quantos itens existem atualmente
    int opcao;

    do {
        printf("\n=====================================\n");
        printf("        SISTEMA DE INVENTÁRIO        \n");
        printf("=====================================\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;

            case 3:
                listarItens(mochila, totalItens);
                break;

            case 4:
                buscarItem(mochila, totalItens);
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
