#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct para Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Funções de ordenação

void bubbleSortNome(Componente componentes[], int n);
void insertionSortTipo(Componente componentes[], int n);
void selectionSortPrioridade(Componente componentes[], int n);

// Função de busca binária
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]);

// Função de exibição de componentes
void mostrarComponentes(Componente componentes[], int n);

// Função para medir tempo de execução de algoritmos
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n);

int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;
int comparacoesBinaria = 0;

int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao, i;
    char nomeBusca[30];

    // Entrada de dados
    printf("Cadastro de componentes para a torre de resgate:\n");
    while (n < MAX_COMPONENTES) {
        printf("\nDigite o nome do componente %d (ou 'fim' para encerrar): ", n + 1);
        fgets(componentes[n].nome, 30, stdin);
        componentes[n].nome[strcspn(componentes[n].nome, "\n")] = '\0'; // Remover '\n'

        if (strcmp(componentes[n].nome, "fim") == 0) break;

        printf("Digite o tipo do componente: ");
        fgets(componentes[n].tipo, 20, stdin);
        componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = '\0'; // Remover '\n'

        printf("Digite a prioridade (1 a 10): ");
        scanf("%d", &componentes[n].prioridade);
        getchar(); // Limpar buffer
        n++;
    }

    do {
        printf("\nEscolha a estrategia de ordenacao:\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar Componente por Nome (Busca Binaria)\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                // Ordenação por Nome usando Bubble Sort
                printf("\nOrdenando por Nome...\n");
                medirTempo(bubbleSortNome, componentes, n);
                mostrarComponentes(componentes, n);
                break;

            case 2:
                // Ordenação por Tipo usando Insertion Sort
                printf("\nOrdenando por Tipo...\n");
                medirTempo(insertionSortTipo, componentes, n);
                mostrarComponentes(componentes, n);
                break;

            case 3:
                // Ordenação por Prioridade usando Selection Sort
                printf("\nOrdenando por Prioridade...\n");
                medirTempo(selectionSortPrioridade, componentes, n);
                mostrarComponentes(componentes, n);
                break;

            case 4:
                // Busca Binária por Nome
                printf("\nDigite o nome do componente a ser buscado: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remover '\n'
                buscaBinariaPorNome(componentes, n, nomeBusca);
                printf("Comparacoes realizadas na busca binaria: %d\n", comparacoesBinaria);
                break;

            case 5:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

// Função de ordenação por Nome usando Bubble Sort
void bubbleSortNome(Componente componentes[], int n) {
    comparacoesBubble = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesBubble++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    printf("Bubble Sort (por Nome) concluido!\n");
    printf("Comparacoes realizadas: %d\n", comparacoesBubble);
}

// Função de ordenação por Tipo usando Insertion Sort
void insertionSortTipo(Componente componentes[], int n) {
    comparacoesInsertion = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            comparacoesInsertion++;
            componentes[j + 1] = componentes[j];
            j = j - 1;
        }
        componentes[j + 1] = chave;
    }
    printf("Insertion Sort (por Tipo) concluido!\n");
    printf("Comparacoes realizadas: %d\n", comparacoesInsertion);
}

// Função de ordenação por Prioridade usando Selection Sort
void selectionSortPrioridade(Componente componentes[], int n) {
    comparacoesSelection = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesSelection++;
            if (componentes[j].prioridade < componentes[minIdx].prioridade) {
                minIdx = j;
            }
        }
        Componente temp = componentes[i];
        componentes[i] = componentes[minIdx];
        componentes[minIdx] = temp;
    }
    printf("Selection Sort (por Prioridade) concluido!\n");
    printf("Comparacoes realizadas: %d\n", comparacoesSelection);
}

// Função de busca binária por Nome
int buscaBinariaPorNome(Componente componentes[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;
    comparacoesBinaria = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        if (strcmp(componentes[meio].nome, nome) == 0) {
            printf("Componente '%s' encontrado na posicao %d!\n", nome, meio);
            return meio;
        } else if (strcmp(componentes[meio].nome, nome) < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Componente '%s' nao encontrado!\n", nome);
    return -1;
}

// Função para exibir os componentes
void mostrarComponentes(Componente componentes[], int n) {
    printf("\nComponentes na torre de resgate:\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %-30s Tipo: %-20s Prioridade: %d\n", componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

// Função para medir o tempo de execução de um algoritmo
void medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int n) {
    clock_t inicio, fim;
    double tempoExecucao;

    inicio = clock();
    algoritmo(componentes, n);
    fim = clock();

    tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6f segundos.\n", tempoExecucao);
}
