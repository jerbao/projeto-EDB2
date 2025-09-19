#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <functional>
#include <random>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = chave;
    }
}

void merge(std::vector<int>& arr, int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;
    std::vector<int> vetorEsquerda(n1), vetorDireita(n2);
    for (int i = 0; i < n1; i++)
        vetorEsquerda[i] = arr[esquerda + i];
    for (int j = 0; j < n2; j++)
        vetorDireita[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esquerda;
    while (i < n1 && j < n2) {
        if (vetorEsquerda[i] <= vetorDireita[j]) {
            arr[k] = vetorEsquerda[i];
            i++;
        } else {
            arr[k] = vetorDireita[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = vetorEsquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = vetorDireita[j];
        j++;
        k++;
    }
}

void mergeSortRecursivo(std::vector<int>& arr, int esquerda, int direita) {
    if (esquerda >= direita) {
        return;
    }
    int meio = esquerda + (direita - esquerda) / 2;
    mergeSortRecursivo(arr, esquerda, meio);
    mergeSortRecursivo(arr, meio + 1, direita);
    merge(arr, esquerda, meio, direita);
}

void mergeSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    mergeSortRecursivo(arr, 0, arr.size() - 1);
}

int buscaSequencial(const std::vector<int>& arr, int alvo) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == alvo) {
            return i;
        }
    }
    return -1;
}

int buscaBinaria(const std::vector<int>& arr, int alvo) {
    int esquerda = 0;
    int direita = arr.size() - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (arr[meio] == alvo) {
            return meio;
        }
        if (arr[meio] < alvo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

std::vector<int> gerarVetorAleatorio(int tamanho) {
    std::vector<int> vetor(tamanho);
    std::iota(vetor.begin(), vetor.end(), 0);
    std::random_device dispositivoAleatorio;
    std::mt19937 gerador(dispositivoAleatorio());
    std::shuffle(vetor.begin(), vetor.end(), gerador);
    return vetor;
}

template<typename Func, typename... Args>
long long medirTempoExecucao(Func algoritmo, int repeticoes, Args&&... args) {
    long long duracaoTotal = 0;
    for (int i = 0; i < repeticoes; ++i) {
        auto copiaArgs = std::make_tuple(std::forward<Args>(args)...);
        auto inicio = std::chrono::high_resolution_clock::now();
        std::apply(algoritmo, copiaArgs);
        auto fim = std::chrono::high_resolution_clock::now();
        duracaoTotal += std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio).count();
    }
    return duracaoTotal / repeticoes;
}

int main() {
    const std::vector<int> tamanhosN = {100, 500, 1000, 2500, 5000, 10000, 20000};
    const int repeticoes = 5;
    std::cout << "Algoritmo,TamanhoN,TempoMedioMicrosegundos" << std::endl;

    for (int n : tamanhosN) {
        std::cout << std::flush;
        auto vetorOriginalOrd = gerarVetorAleatorio(n);
        long long tempoInsertionSort = medirTempoExecucao(insertionSort, repeticoes, vetorOriginalOrd);
        std::cout << "InsertionSort," << n << "," << tempoInsertionSort << std::endl;
        long long tempoMergeSort = medirTempoExecucao(mergeSort, repeticoes, vetorOriginalOrd);
        std::cout << "MergeSort," << n << "," << tempoMergeSort << std::endl;
        auto vetorOriginalBusca = gerarVetorAleatorio(n);
        int elementoNaoExistente = -1;
        long long tempoBuscaSequencial = medirTempoExecucao(buscaSequencial, repeticoes, vetorOriginalBusca, elementoNaoExistente);
        std::cout << "BuscaSequencial," << n << "," << tempoBuscaSequencial << std::endl;
        std::sort(vetorOriginalBusca.begin(), vetorOriginalBusca.end());
        long long tempoBuscaBinaria = medirTempoExecucao(buscaBinaria, repeticoes, vetorOriginalBusca, elementoNaoExistente);
        std::cout << "BuscaBinaria," << n << "," << tempoBuscaBinaria << std::endl;
    }
        system("pause");
        return 0;
}