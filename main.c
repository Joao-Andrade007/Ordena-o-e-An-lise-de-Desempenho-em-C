#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> // clock_t, time, CLOCKS_PER_SEC

#define NUM_RUNS 5
#define MAX_RGM_LEN 20

// Função auxiliar para copiar um vetor
static void copy_array(int *dest, const int *src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Função para gerar um vetor aleatório
static void generate_random_array(int *v, size_t n) {
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned int)time(NULL));
        initialized = 1;
    }
    
    for (size_t i = 0; i < n; i++) {
        v[i] = rand() % 1000; // Números aleatórios entre 0 e 999
    }
}

/**
 * @brief Roda uma função de ordenação N_RUNS vezes e calcula a média das métricas.
 * @param sort_fn Ponteiro para a função de ordenação.
 * @param v Vetor base a ser ordenado (não é modificado).
 * @param n Tamanho do vetor.
 * @param num_runs Número de execuções.
 * @param avg_metrics Ponteiro para onde as métricas médias serão armazenadas.
 * @return double Tempo médio de execução em milissegundos.
 */
double run_benchmark(void (*sort_fn)(int *, size_t), const int *v, size_t n, int num_runs, Metrics *avg_metrics) {
    double total_time = 0.0;
    Metrics total_metrics = {0, 0};

    // Alocação de memória para a cópia a ser ordenada (CORRIGIDO)
    int *v_copy = (int *)malloc(n * sizeof(int));
    if (!v_copy) {
        fprintf(stderr, "Erro de alocação de memória para cópia do vetor.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_runs; i++) {
        // 1. Resetar métricas e copiar o vetor base (v -> v_copy)
        reset_metrics();
        copy_array(v_copy, v, n);

        // 2. Medir tempo e rodar o sort
        clock_t t0 = clock();
        sort_fn(v_copy, n);
        clock_t t1 = clock();

        // 3. Acumular métricas
        total_time += 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
        total_metrics.steps_cmp += current_metrics.steps_cmp;
        total_metrics.steps_swap += current_metrics.steps_swap;
    }

    // 4. Calcular média e desalocar memória
    avg_metrics->steps_cmp = total_metrics.steps_cmp / num_runs;
    avg_metrics->steps_swap = total_metrics.steps_swap / num_runs;
    
    free(v_copy);
    return total_time / num_runs;
}

// Função para converter string RGM para vetor de dígitos
static size_t rgm_to_digits(const char *rgm_str, int *digits) {
    size_t count = 0;
    size_t len = strlen(rgm_str);

    for (size_t i = 0; i < len && count < MAX_RGM_LEN; i++) {
        if (isdigit((unsigned char)rgm_str[i])) {
            digits[count++] = rgm_str[i] - '0';
        }
    }
    return count;
}

// Definição dos métodos de ordenação e seus nomes
typedef struct {
    char *name;
    void (*sort_fn)(int *, size_t);
} SortMethod;

static SortMethod methods[] = {
    {"insertion", insertion_sort},
    {"merge", merge_sort},
    {"quick", quick_sort},
    {NULL, NULL}
};

// Tamanhos de amostras aleatórias
static size_t N_sizes[] = {100, 1000, 10000};
#define NUM_N_SIZES (sizeof(N_sizes) / sizeof(N_sizes[0]))


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <RGM>\n", argv[0]);
        fprintf(stderr, "Exemplo: %s 123456789\n", argv[0]);
        return 1;
    }

    // --- Configuração da Saída CSV ---
    printf("metodo,N,caso,passos_cmp,passos_swap,tempo_ms\n");
    
    // --- 1. Teste com RGM (Entrada A) ---
    const char *rgm_str = argv[1];
    int rgm_digits[MAX_RGM_LEN];
    size_t n_rgm = rgm_to_digits(rgm_str, rgm_digits);

    if (n_rgm == 0) {
        fprintf(stderr, "Erro: O RGM fornecido não contém dígitos válidos.\n");
        return 1;
    }

    for (SortMethod *m = methods; m->name != NULL; m++) {
        Metrics avg_metrics;
        double avg_time = run_benchmark(m->sort_fn, rgm_digits, n_rgm, NUM_RUNS, &avg_metrics);

        // Imprime resultado CSV para o RGM
        printf("%s,%zu,rgm,%lld,%lld,%.3f\n", 
               m->name, n_rgm, avg_metrics.steps_cmp, avg_metrics.steps_swap, avg_time);
    }
    
    // --- 2. Teste com Amostras Aleatórias (Entrada B) ---
    for (size_t i = 0; i < NUM_N_SIZES; i++) {
        size_t N = N_sizes[i];
        
        // Alocação de memória para o vetor base (CORRIGIDO)
        int *v_base = (int *)malloc(N * sizeof(int));
        if (!v_base) {
            fprintf(stderr, "Erro de alocação de memória para N=%zu. Pulando teste.\n", N);
            continue;
        }

        // Gera um vetor aleatório BASE
        generate_random_array(v_base, N);

        for (SortMethod *m = methods; m->name != NULL; m++) {
            Metrics avg_metrics;
            double avg_time = run_benchmark(m->sort_fn, v_base, N, NUM_RUNS, &avg_metrics);

            // Imprime resultado CSV para amostra aleatória
            printf("%s,%zu,aleatorio,%lld,%lld,%.3f\n", 
                   m->name, N, avg_metrics.steps_cmp, avg_metrics.steps_swap, avg_time);
        }
        
        free(v_base);
    }

    return 0;
}