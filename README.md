# Análise Empírica de Complexidade de Algoritmos

![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B%20%26%20Python-blue)

Este projeto apresenta uma análise prática do desempenho de algoritmos de ordenação e busca, desenvolvido como parte da disciplina de Estruturas de Dados Básicas II. O objetivo é comparar a complexidade teórica (Notação Big O) com o tempo de execução empírico medido em um ambiente real.

---

## Algoritmos Analisados

Foram implementados e analisados quatro algoritmos com diferentes ordens de complexidade:

*   **Ordenação:**
    *   `Insertion Sort` - Complexidade $O(n^2)$
    *   `Merge Sort` - Complexidade $O(n \log n)$
*   **Busca:**
    *   `Busca Sequencial` - Complexidade $O(n)$
    *   `Busca Binária` - Complexidade $O(\log n)$

---

## Tecnologia Utilizada

*   **C++:** Utilizado para a implementação dos algoritmos e para a medição precisa do tempo de execução, usando a biblioteca `<chrono>`.

---

## Como Executar o Projeto

Siga os passos abaixo para replicar a análise.

### Pré-requisito

*   Um compilador C++ (como G++).

### Coleta de Dados de Desempenho

O programa em C++ irá executar os algoritmos e imprimir os resultados no terminal.

1.  **Compile o código C++:**
    ```sh
    g++ -o script main.cpp
    ```

---

## Autor

*   **Jerônimo Rafael Bezerra Filho**
