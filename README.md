# A2 — Ordenação e Análise de Desempenho em C (RGM: 44982518)

## 1.  Descrição do Problema e Métodos Implementados

Este projeto implementa e compara a eficiência de três algoritmos de ordenação em C. O objetivo é analisar a **escalabilidade** dos algoritmos $O(n^2)$ e $O(n \log n)$ medindo o **tempo de execução** e o número de **operações-chave** (*passos*) em vetores pequenos (dígitos do RGM) e grandes amostras aleatórias ($N=100, 1.000, 10.000$).

### 1.1 Algoritmos Escolhidos e Justificativa

| Método | Complexidade Assintótica (Pior Caso) | Tipo | Justificativa |
| :--- | :--- | :--- | :--- |
| **Insertion Sort** | $O(n^2)$ | Quadrático | Essencial para medir o limite de escalabilidade. É eficiente para $N$ muito pequenos. |
| **Merge Sort** | $O(n \log n)$ | Log-Linear (Garantido) | Ideal para testes por ter desempenho consistentemente $O(n \log n)$ em todos os casos. |
| **Quick Sort** | $O(n^2)$ (Pior); $O(n \log n)$ (Média) | Log-Linear (Prática) | O algoritmo mais rápido na prática para dados aleatórios. Foi utilizada a **Partição de Hoare**. |

---

## 2.  Como Compilar e Rodar

### Estrutura do Projeto

O projeto é composto por `main.c`, `sorts.c`, e `sorts.h`.

### Compilação

Para compilar o código usando o padrão C11 e a otimização mínima (`-O1`), conforme recomendado:

```bash
gcc -O1 -std=c11 main.c sorts.c -o ordena

ExecuçãoO programa requer que o seu RGM seja passado como único argumento. Substitua SEU_RGM pelo seu número:Bash./ordena SEU_RGM

Exemplo:Bash./ordena 123456789
A saída será impressa no console em formato CSV.
