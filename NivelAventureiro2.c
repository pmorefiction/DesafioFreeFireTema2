#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Struct para o item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Contadores de comparacoes
int comparacoesBuscaSequencial = 0;
int comparacoesBuscaBinaria = 0;

// Funcoes para a versao com vetor

void inserirItemVetor(Item vetor[], int *qtdItens);
void removerItemVetor(Item vetor[], int *qtdItens);
void listarItensVetor(Item vetor[], int qtdItens);
void buscarSequencialVetor(Item vetor[], int qtdItens);
void ordenarVetor(Item vetor[], int qtdItens);
int buscarBinariaVetor(Item vetor[], int qtdItens, const char *nome);

// Funcoes para a versao com lista encadeada

void inserirItemLista(No** lista);
void removerItemLista(No** lista);
void listarItensLista(No* lista);
void buscarSequencialLista(No* lista);
int contarComparacoesBuscaSequencialLista(No* lista, const char* nome);

// Funcao principal
int main() {
    int opcao;
    int qtdItensVetor = 0;
    Item mochilaVetor[MAX_ITENS];
    No* listaEncadeada = NULL;

    do {
        printf("\nEscolha a estrutura de dados:\n");
        printf("1. Vetor\n");
        printf("2. Lista Encadeada\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        switch(opcao) {
            case 1:
                // Menu para vetor
                printf("\nEscolha a operacao:\n");
                printf("1. Inserir Item\n");
                printf("2. Remover Item\n");
                printf("3. Listar Itens\n");
                printf("4. Buscar Sequencial\n");
                printf("5. Ordenar e Buscar Binaria\n");
                printf("Escolha uma opcao: ");
                int opcaoVetor;
                scanf("%d", &opcaoVetor);
                getchar();

                switch(opcaoVetor) {
                    case 1: inserirItemVetor(mochilaVetor, &qtdItensVetor); break;
                    case 2: removerItemVetor(mochilaVetor, &qtdItensVetor); break;
                    case 3: listarItensVetor(mochilaVetor, qtdItensVetor); break;
                    case 4: buscarSequencialVetor(mochilaVetor, qtdItensVetor); break;
                    case 5:
                        ordenarVetor(mochilaVetor, qtdItensVetor);
                        printf("Busca binaria:\n");
                        buscarBinariaVetor(mochilaVetor, qtdItensVetor, "ItemCritico");
                        printf("Comparacoes na busca binaria: %d\n", comparacoesBuscaBinaria);
                        break;
                    default: printf("Opcao invalida!\n"); break;
                }
                break;
            case 2:
                // Menu para lista encadeada
                printf("\nEscolha a operacao:\n");
                printf("1. Inserir Item\n");
                printf("2. Remover Item\n");
                printf("3. Listar Itens\n");
                printf("4. Buscar Sequencial\n");
                printf("Escolha uma opcao: ");
                int opcaoLista;
                scanf("%d", &opcaoLista);
                getchar();

                switch(opcaoLista) {
                    case 1: inserirItemLista(&listaEncadeada); break;
                    case 2: removerItemLista(&listaEncadeada); break;
                    case 3: listarItensLista(listaEncadeada); break;
                    case 4:
                        printf("Digite o nome do item a ser buscado: ");
                        char nomeBusca[30];
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        int comparacoes = contarComparacoesBuscaSequencialLista(listaEncadeada, nomeBusca);
                        printf("Comparacoes na busca sequencial: %d\n", comparacoes);
                        break;
                    default: printf("Opcao invalida!\n"); break;
                }
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 3);

    return 0;
}

// Implementacoes para o vetor

void inserirItemVetor(Item vetor[], int *qtdItens) {
    if (*qtdItens < MAX_ITENS) {
        Item novoItem;
        printf("\nDigite o nome do item: ");
        fgets(novoItem.nome, 30, stdin);
        novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remover '\n'

        printf("Digite o tipo do item: ");
        fgets(novoItem.tipo, 20, stdin);
        novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0'; // Remover '\n'

        printf("Digite a quantidade: ");
        scanf("%d", &novoItem.quantidade);
        getchar(); // Limpar buffer

        vetor[*qtdItens] = novoItem;
        (*qtdItens)++;
        printf("Item '%s' inserido com sucesso!\n", novoItem.nome);
    } else {
        printf("A mochila esta cheia!\n");
    }
}

void removerItemVetor(Item vetor[], int *qtdItens) {
    if (*qtdItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remover '\n'

    int i;
    for (i = 0; i < *qtdItens; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            // Deslocar os itens
            for (int j = i; j < *qtdItens - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*qtdItens)--;
            printf("Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }

    printf("Item '%s' nao encontrado na mochila.\n", nome);
}

void listarItensVetor(Item vetor[], int qtdItens) {
    if (qtdItens == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < qtdItens; i++) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

void ordenarVetor(Item vetor[], int qtdItens) {
    // Bubble Sort
    for (int i = 0; i < qtdItens - 1; i++) {
        for (int j = 0; j < qtdItens - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado!\n");
}

int buscarBinariaVetor(Item vetor[], int qtdItens, const char *nome) {
    int inicio = 0, fim = qtdItens - 1;
    comparacoesBuscaBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBuscaBinaria++;

        if (strcmp(vetor[meio].nome, nome) == 0) {
            printf("Item '%s' encontrado!\n", nome);
            return meio;
        } else if (strcmp(vetor[meio].nome, nome) < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Item '%s' nao encontrado!\n", nome);
    return -1;
}

// Implementacoes para a lista encadeada

void inserirItemLista(No** lista) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(novoNo->dados.nome, 30, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0'; // Remover '\n'

    printf("Digite o tipo do item: ");
    fgets(novoNo->dados.tipo, 20, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0'; // Remover '\n'

    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    getchar(); // Limpar buffer

    novoNo->proximo = *lista;
    *lista = novoNo;
    printf("Item '%s' inserido com sucesso!\n", novoNo->dados.nome);
}

void removerItemLista(No** lista) {
    if (*lista == NULL) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remover '\n'

    No* anterior = NULL;
    No* atual = *lista;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                *lista = atual->proximo; // Remover o primeiro no
            } else {
                anterior->proximo = atual->proximo; // Remover o no
            }
            free(atual);
            printf("Item '%s' removido com sucesso!\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item '%s' nao encontrado na mochila.\n", nome);
}

void listarItensLista(No* lista) {
    if (lista == NULL) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    No* atual = lista;
    while (atual != NULL) {
        printf("Nome: %s, Tipo: %s, Quantidade: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int contarComparacoesBuscaSequencialLista(No* lista, const char* nome) {
    comparacoesBuscaSequencial = 0;
    No* atual = lista;
    while (atual != NULL) {
        comparacoesBuscaSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item '%s' encontrado!\n", nome);
            return comparacoesBuscaSequencial;
        }
        atual = atual->proximo;
    }
    printf("Item '%s' nao encontrado!\n", nome);
    return comparacoesBuscaSequencial;
}
