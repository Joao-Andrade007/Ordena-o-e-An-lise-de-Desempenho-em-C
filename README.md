# A2 — Ordenação e Análise de Desempenho em C (RGM: 44982518 )1.
 Descrição do Problema e Métodos ImplementadosEste projeto cumpre o requisito de implementar e comparar três algoritmos de ordenação em C. O objetivo é analisar a escalabilidade dos algoritmos $O(n^2)$ e $O(n \log n)$ medindo o tempo de execução e o número de operações-chave (passos) em vetores pequenos (dígitos do RGM) e grandes amostras aleatórias ($N=100, 1.000, 10.000$).
# 2.  Como Compilar e Rodar
Estrutura do Projeto
O projeto é organizado nos seguintes arquivos:

main.c: Contém a lógica de benchmark, leitura do RGM, geração de amostras aleatórias e a impressão da saída em formato CSV.

sorts.c: Contém a implementação dos três algoritmos de ordenação (insertion_sort, merge_sort, quick_sort) e as funções auxiliares, incluindo a lógica de contagem de passos.

# 3. Política de Contagem de Passos e Medição de Tempo
3.1 Política de Contagem de Passos
As métricas são armazenadas na estrutura global Metrics current_metrics e acumuladas usando as seguintes macros:

Comparações (steps_cmp): O contador é incrementado a cada comparação fundamental entre dois elementos (v[i] < v[j]).

Exemplo: O teste dentro de um if ou while que guia a ordenação.

Trocas/Movimentações (steps_swap): O contador é incrementado a cada troca completa (swap) ou movimentação significativa de um elemento (ex.: a cópia de elementos no vetor auxiliar do Merge Sort, e o deslocamento no Insertion Sort).

3.2 Método de Medição de Tempo
O tempo de CPU é medido utilizando a função clock() da biblioteca <time.h>.

O tempo é calculado em milissegundos usando a constante CLOCKS_PER_SEC.

Cada caso de teste é rodado 5 vezes, e a média aritmética do tempo de execução é reportada para minimizar ruídos de sistema.
