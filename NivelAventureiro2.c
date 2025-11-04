#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura para o item
typedef struct {
    char nome[30];
    char tipo[20];
    int qtd;
} Item;

// Estrutura para a lista encadeada
typedef struct No {
    Item dados;
    struct No *prox;
} No;

// Funcoes para vetor
void inserirVetor(Item mochila[], int *qtd);
void removerVetor(Item mochila[], int *qtd);
void listarVetor(Item mochila[], int qtd);
void buscarSeqVetor(Item mochila[], int qtd, const char *nome);
void ordenarVetor(Item mochila[], int qtd);
void buscarBinVetor(Item mochila[], int qtd, const char *nome);

// Funcoes para lista encadeada
void inserirLista(No **inicio);
void removerLista(No **inicio);
void listarLista(No *inicio);
void buscarSeqLista(No *inicio, const char *nome);
void destruirLista(No **inicio);

int comparacoesSeq = 0;
int comparacoesBin = 0;

int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;

    No *mochilaLista = NULL;

    int opcao, tipoEstrutura;
    
    do {
        printf("\n1. Vetor\n2. Lista Encadeada\n3. Sair\nEscolha: ");
        scanf("%d", &tipoEstrutura);
        getchar(); // Limpa o buffer

        if (tipoEstrutura == 1) {
            do {
                printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar Seq\n5. Buscar Bin\n6. Voltar\nEscolha: ");
                scanf("%d", &opcao);
                getchar();

                switch(opcao) {
                    case 1: inserirVetor(mochilaVetor, &qtdVetor); break;
                    case 2: removerVetor(mochilaVetor, &qtdVetor); break;
                    case 3: listarVetor(mochilaVetor, qtdVetor); break;
                    case 4: {
                        char nome[30];
                        printf("Nome: ");
                        fgets(nome, 30, stdin);
                        nome[strcspn(nome, "\n")] = 0;  // Remove '\n'
                        buscarSeqVetor(mochilaVetor, qtdVetor, nome);
                        break;
                    }
                    case 5: {
                        char nome[30];
                        printf("Nome: ");
                        fgets(nome, 30, stdin);
                        nome[strcspn(nome, "\n")] = 0;  // Remove '\n'
                        ordenarVetor(mochilaVetor, qtdVetor);
                        buscarBinVetor(mochilaVetor, qtdVetor, nome);
                        break;
                    }
                    case 6: break;
                    default: printf("Opcao invalida!\n");
                }
            } while(opcao != 6);
        } else if (tipoEstrutura == 2) {
            do {
                printf("\n1. Inserir\n2. Remover\n3. Listar\n4. Buscar Seq\n5. Voltar\nEscolha: ");
                scanf("%d", &opcao);
                getchar();

                switch(opcao) {
                    case 1: inserirLista(&mochilaLista); break;
                    case 2: removerLista(&mochilaLista); break;
                    case 3: listarLista(mochilaLista); break;
                    case 4: {
                        char nome[30];
                        printf("Nome: ");
                        fgets(nome, 30, stdin);
                        nome[strcspn(nome, "\n")] = 0;  // Remove '\n'
                        buscarSeqLista(mochilaLista, nome);
                        break;
                    }
                    case 5: break;
                    default: printf("Opcao invalida!\n");
                }
            } while(opcao != 5);
        }

    } while(tipoEstrutura != 3);

    destruirLista(&mochilaLista);
    return 0;
}

// Funcoes para o vetor

void inserirVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; // Remove '\n'
    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;
    printf("Qtd: ");
    scanf("%d", &novo.qtd);
    getchar(); // Limpa o buffer
    mochila[*qtd] = novo;
    (*qtd)++;
    printf("Item inserido!\n");
}

void removerVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;  // Remove '\n'

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void listarVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("Nome: %s, Tipo: %s, Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].qtd);
    }
}

void buscarSeqVetor(Item mochila[], int qtd, const char *nome) {
    comparacoesSeq = 0;
    for (int i = 0; i < qtd; i++) {
        comparacoesSeq++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: %s, %s, %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].qtd);
            printf("Comparacoes: %d\n", comparacoesSeq);
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void ordenarVetor(Item mochila[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                Item temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
}

void buscarBinVetor(Item mochila[], int qtd, const char *nome) {
    comparacoesBin = 0;
    int inicio = 0, fim = qtd - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBin++;
        int comp = strcmp(mochila[meio].nome, nome);
        if (comp == 0) {
            printf("Item encontrado: %s, %s, %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].qtd);
            printf("Comparacoes binarias: %d\n", comparacoesBin);
            return;
        } else if (comp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Item nao encontrado!\n");
}

// Funcoes para lista encadeada

void inserirLista(No **inicio) {
    No *novo = (No*)malloc(sizeof(No));
    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = 0;
    printf("Qtd: ");
    scanf("%d", &novo->dados.qtd);
    getchar();
    novo->prox = *inicio;
    *inicio = novo;
    printf("Item inserido!\n");
}

void removerLista(No **inicio) {
    if (*inicio == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    No *atual = *inicio, *ant = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (ant == NULL) {
                *inicio = atual->prox;
            } else {
                ant->prox = atual->prox;
            }
            free(atual);
            printf("Item removido!\n");
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
    printf("Item nao encontrado!\n");
}

void listarLista(No *inicio) {
    if (inicio == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    No *atual = inicio;
    while (atual != NULL) {
        printf("Nome: %s, Tipo: %s, Qtd: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.qtd);
        atual = atual->prox;
    }
}

void buscarSeqLista(No *inicio, const char *nome) {
    comparacoesSeq = 0;
    No *atual = inicio;
    while (atual != NULL) {
        comparacoesSeq++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("Item encontrado: %s, %s, %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.qtd);
            printf("Comparacoes: %d\n", comparacoesSeq);
            return;
        }
        atual = atual->prox;
    }
    printf("Item nao encontrado!\n");
}

void destruirLista(No **inicio) {
    No *atual = *inicio;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}
