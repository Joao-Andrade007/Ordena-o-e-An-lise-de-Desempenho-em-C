#ifndef SORTS_H
#define SORTS_H

#include <stddef.h> // Para size_t

// Estrutura para armazenar as métricas de desempenho
typedef struct {
    long long steps_cmp; // Contador de Comparações
    long long steps_swap; // Contador de Trocas/Movimentações
} Metrics;

// Variável global para as métricas correntes (Simplificação do esqueleto)
extern Metrics current_metrics;

// Macros para incrementar as métricas de forma limpa
#define COUNT_CMP()     (current_metrics.steps_cmp++)
#define COUNT_SWAP()    (current_metrics.steps_swap++)

// Protótipos das funções
void reset_metrics(void);
void swap(int *a, int *b);

// Algoritmos de Ordenação (funções requeridas)
void insertion_sort(int *v, size_t n);
void merge_sort(int *v, size_t n);
void quick_sort(int *v, size_t n); // Implementa a chamada inicial (wrapper)

#endif // SORTS_H