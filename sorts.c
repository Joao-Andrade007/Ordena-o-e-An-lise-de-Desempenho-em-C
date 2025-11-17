#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>

// Variável global que armazena as métricas para a execução atual
Metrics current_metrics = {0, 0};

// Zera as métricas globais antes de cada execução
void reset_metrics(void) {
    current_metrics.steps_cmp = 0;
    current_metrics.steps_swap = 0;
}

// Função auxiliar para troca (swap) de elementos
void swap(int *a, int *b) {
    if (a == b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
    COUNT_SWAP(); // Conta 1 troca completa
}

// ----------------------------------------------------
// 1. Insertion Sort (O(n^2))
// ----------------------------------------------------
void insertion_sort(int *v, size_t n) {
    for (size_t i = 1; i < n; i++) {
        int key = v[i];
        int j = (int)i - 1;

        // Move os elementos de v[0..i-1] que são maiores que key
        // para uma posição à frente de sua posição atual.
        while (j >= 0) {
            COUNT_CMP(); // Contabiliza a comparação v[j] > key
            if (v[j] > key) {
                // A movimentação do elemento é uma 'troca' em termos de análise
                // mas é uma 'movimentação' de fato. Contaremos como SWAP/mov.
                v[j + 1] = v[j];
                COUNT_SWAP(); 
                j = j - 1;
            } else {
                break;
            }
        }
        // Coloca o key em sua posição correta
        if ((size_t)(j + 1) != i) {
            v[j + 1] = key;
            // Não contamos isso como SWAP, é a inserção final (já coberto acima).
        }
    }
}

// ----------------------------------------------------
// 2. Merge Sort (O(n log n))
// ----------------------------------------------------
static void merge(int *v, int *aux, size_t low, size_t mid, size_t high) {
    // Copia a porção para o vetor auxiliar
    for (size_t k = low; k <= high; k++) {
        aux[k] = v[k];
        COUNT_SWAP(); // Conta o movimento para o vetor auxiliar
    }

    size_t i = low;      // Início da primeira metade
    size_t j = mid + 1;  // Início da segunda metade
    size_t k = low;      // Início do destino (v)

    while (i <= mid && j <= high) {
        COUNT_CMP(); // Contabiliza a comparação aux[i] <= aux[j]
        if (aux[i] <= aux[j]) {
            v[k++] = aux[i++];
        } else {
            v[k++] = aux[j++];
        }
        COUNT_SWAP(); // Conta o movimento de volta para o vetor principal
    }

    // Copia os elementos restantes da primeira metade
    while (i <= mid) {
        v[k++] = aux[i++];
        COUNT_SWAP(); // Conta o movimento
    }

    // (Não é necessário copiar os restantes da segunda metade, pois já estão no lugar)
}

static void sort_merge_recursive(int *v, int *aux, size_t low, size_t high) {
    if (high <= low) return;
    
    size_t mid = low + (high - low) / 2;
    sort_merge_recursive(v, aux, low, mid);
    sort_merge_recursive(v, aux, mid + 1, high);
    merge(v, aux, low, mid, high);
}

void merge_sort(int *v, size_t n) {
    if (n <= 1) return;

    // Aloca vetor auxiliar
    int *aux = (int *)malloc(n * sizeof(int));
    if (!aux) {
        fprintf(stderr, "Erro de alocação de memória no Merge Sort.\n");
        exit(EXIT_FAILURE);
    }
    
    sort_merge_recursive(v, aux, 0, n - 1);

    free(aux);
}

// ----------------------------------------------------
// 3. Quick Sort (O(n log n) na média)
// ----------------------------------------------------
// Partição Hoare - mais eficiente, mas menos intuitiva (Justifique no README)
static size_t partition_hoare(int *v, size_t low, size_t high) {
    int pivot = v[low]; // Pivô simples: o primeiro elemento
    size_t i = low - 1;
    size_t j = high + 1;

    while (1) {
        // Encontra o elemento à esquerda que é >= pivot
        do { 
            i++; 
            COUNT_CMP(); // Conta a comparação v[i] < pivot
        } while (v[i] < pivot);

        // Encontra o elemento à direita que é <= pivot
        do { 
            j--; 
            COUNT_CMP(); // Conta a comparação v[j] > pivot
        } while (v[j] > pivot);

        // Se os índices se cruzarem, a partição está completa
        if (i >= j) return j;

        // Troca os elementos fora de ordem
        swap(&v[i], &v[j]);
    }
}

static void sort_quick_recursive(int *v, size_t low, size_t high) {
    if (low >= high) return;

    // Garante que não há overflow em size_t (caso improvável, mas boa prática)
    if (high == (size_t)-1) return;

    size_t p = partition_hoare(v, low, high);
    
    // Quick Sort na primeira sub-lista
    if (p > low) {
        sort_quick_recursive(v, low, p);
    }
    
    // Quick Sort na segunda sub-lista
    if (p + 1 < high) {
        sort_quick_recursive(v, p + 1, high);
    } else if (p < high) { // Caso p+1 == high
        sort_quick_recursive(v, p + 1, high);
    }
}

void quick_sort(int *v, size_t n) {
    if (n > 1) {
        sort_quick_recursive(v, 0, n - 1);
    }
}