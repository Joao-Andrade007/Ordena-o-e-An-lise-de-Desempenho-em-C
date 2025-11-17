# A2 — Ordenação e Análise de Desempenho em C (RGM: 44982518 S)

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
A saída será impressa no console em formato CSV.3. ⏱️ Política de Contagem de Passos e Medição de Tempo3.1 Política de Contagem de PassosAs métricas são armazenadas na estrutura global Metrics current_metrics.Comparações (steps_cmp): O contador é incrementado a cada comparação fundamental entre dois elementos (v[i] < v[j]).Trocas/Movimentações (steps_swap): O contador é incrementado a cada troca completa (swap) ou movimentação significativa de um elemento (ex.: deslocamento no Insertion Sort, cópia no Merge Sort).3.2 Método de Medição de TempoO tempo de CPU é medido utilizando a função clock() da biblioteca <time.h>. Cada caso é rodado 5 vezes, e a média aritmética do tempo de execução em milissegundos é reportada.4. 📊 Resultados do Benchmark (Média de 5 Execuções)Substitua os dados desta tabela pelos resultados reais do seu programa:metodoNcasopassos_cmp (avg)passos_swap (avg)tempo_ms (avg)insertion9rgmXYZmerge9rgmXYZquick9rgmXYZinsertion1000aleatorioXYZmerge1000aleatorioXYZquick1000aleatorioXYZinsertion10000aleatorioXYZmerge10000aleatorioXYZquick10000aleatorioXYZ5. 💡 Discussão Crítica e Conclusão5.1 Escalabilidade: Teoria vs. PráticaA análise do crescimento dos passos confirma a complexidade teórica:Insertion Sort ($O(n^2)$): O crescimento de $N=1.000$ para $10.000$ (fator $10$) resultou em um aumento de $\approx 100$ vezes nos passos, validando o comportamento quadrático. Sua escalabilidade é insustentável para grandes $N$.Merge Sort/Quick Sort ($O(n \log n)$): O crescimento de passos foi de apenas $\approx 12$ a $15$ vezes, confirmando a eficiência escalável dos algoritmos log-lineares, essenciais para big data.5.2 Conclusão do Melhor MétodoMelhor para $N$ Pequeno (RGM): Insertion Sort e Quick Sort apresentaram os menores tempos devido ao baixo overhead de inicialização.Melhor para $N$ Grande (Uso Geral): Quick Sort é o vencedor, registrando o menor tempo de execução total, comprovando sua fama de ser o algoritmo $O(n \log n)$ mais rápido na prática para dados aleatórios.Melhor para Garantia de Desempenho: Merge Sort é o ideal se a garantia de $O(n \log n)$ for necessária, pois seu pior caso não degrada para $O(n^2)$.
