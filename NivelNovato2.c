#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções protótipos
void inserirItem(Item mochila[], int *qtdItens);
void removerItem(Item mochila[], int *qtdItens);
void listarItens(Item mochila[], int qtdItens);
void buscarItem(Item mochila[], int qtdItens);

int main() {
    Item mochila[MAX_ITENS]; // Vetor de itens (mochila)
    int qtdItens = 0; // Quantidade de itens na mochila
    int opcao;

    // Menu principal do sistema
    do {
        printf("\nSistema de Inventario - Mochila de Loot\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Para capturar o '\n' deixado pelo scanf

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtdItens);
                break;
            case 2:
                removerItem(mochila, &qtdItens);
                break;
            case 3:
                listarItens(mochila, qtdItens);
                break;
            case 4:
                buscarItem(mochila, qtdItens);
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 5);

    return 0;
}

// Função para inserir um item na mochila
void inserirItem(Item mochila[], int *qtdItens) {
    if (*qtdItens < MAX_ITENS) {
        Item novoItem;
        printf("\nDigite o nome do item: ");
        fgets(novoItem.nome, 30, stdin);
        novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remover o '\n' deixado pelo fgets
        
        printf("Digite o tipo do item: ");
        fgets(novoItem.tipo, 20, stdin);
        novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0'; // Remover o '\n' deixado pelo fgets
        
        printf("Digite a quantidade: ");
        scanf("%d", &novoItem.quantidade);
        getchar(); // Capturar o '\n' após o número
        
        mochila[*qtdItens] = novoItem; // Adiciona o item na mochila
        (*qtdItens)++; // Incrementa a quantidade de itens
        printf("Item '%s' cadastrado com sucesso!\n", novoItem.nome);
    } else {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
    }
}

// Função para remover um item da mochila
void removerItem(Item mochila[], int *qtdItens) {
    if (*qtdItens == 0) {
        printf("A mochila esta vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item para remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0'; // Remover o '\n' deixado pelo fgets

    int encontrado = 0;
    for (int i = 0; i < *qtdItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Item encontrado, removendo
            for (int j = i; j < *qtdItens - 1; j++) {
                mochila[j] = mochila[j + 1]; // Desloca os itens para preencher o espaço
            }
            (*qtdItens)--; // Decrementa a quantidade de itens
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila!\n", nomeRemover);
    }
}

// Função para listar todos os itens da mochila
void listarItens(Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < qtdItens; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar um item na mochila pelo nome
void buscarItem(Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nomeBuscar[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBuscar, 30, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0'; // Remover o '\n' deixado pelo fgets

    int encontrado = 0;
    for (int i = 0; i < qtdItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("Item encontrado! Nome: %s, Tipo: %s, Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila!\n", nomeBuscar);
    }
}
