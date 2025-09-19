#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>  //Para iota
#include <algorithm>//Para sort e shuffle
#include <functional>
#include <random>

using namespace std;

//ALGORITMOS DE ORDENAÇÃO

/**
 * @brief Ordena um vetor de inteiros usando o algoritmo Insertion Sort
 * Complexidade teórica: O(n^2)
 * @param arr Vetor a ser ordenado
 */
void insertionSort(vector<int>& arr) {
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

/**
 * @brief Função auxiliar para o Merge Sort: mescla dois subvetores.
 */
void merge(vector<int>& arr, int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    vector<int> vetorEsquerda(n1), vetorDireita(n2);

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

/**
 * @brief Função recursiva principal do Merge Sort
 */
void mergeSortRecursivo(vector<int>& arr, int esquerda, int direita) {
    if (esquerda >= direita) {
        return;
    }
    int meio = esquerda + (direita - esquerda) / 2;
    mergeSortRecursivo(arr, esquerda, meio);
    mergeSortRecursivo(arr, meio + 1, direita);
    merge(arr, esquerda, meio, direita);
}

/**
 * @brief Ordena um vetor de inteiros usando o algoritmo Merge Sort
 * Complexidade teórica: O(n*log(n))
 * @param arr Vetor a ser ordenado
 */
void mergeSort(vector<int>& arr) {
    if (arr.empty()) return;
    mergeSortRecursivo(arr, 0, arr.size() - 1);
}


//ALGORITMOS DE BUSCA

/**
 * @brief Procura por um elemento em um vetor usando Busca Sequencial
 * Complexidade teórica: O(n)
 * @param arr Vetor onde a busca será realizada
 * @param alvo O elemento a ser buscado
 * @return O índice do elemento ou -1 se não for encontrado
 */
int buscaSequencial(const vector<int>& arr, int alvo) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == alvo) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Procura por um elemento em um vetor ORDENADO usando Busca Binária
 * Complexidade teórica: O(log(n))
 * @param arr Vetor ordenado onde a busca será realizada
 * @param alvo O elemento a ser buscado
 * @return O índice do elemento ou -1 se não for encontrado
 */
int buscaBinaria(const vector<int>& arr, int alvo) {
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


//TESTE E MEDIÇÃO

/**
 * @brief Gera um vetor com `tamanho` elementos aleatórios
 * @param tamanho O tamanho do vetor a ser gerado
 * @return Um std::vector<int> com números aleatórios
 */
vector<int> gerarVetorAleatorio(int tamanho) {
    vector<int> vetor(tamanho);
    //Preenche o vetor com valores de 0 a tamanho-1
    iota(vetor.begin(), vetor.end(), 0);
    //Embaralha os elementos para garantir um caso médio para os algoritmos de ordenação
    random_device dispositivoAleatorio;
    mt19937 gerador(dispositivoAleatorio());
    shuffle(vetor.begin(), vetor.end(), gerador);
    return vetor;
}

/**
 * @brief Mede o tempo médio de execução de uma função de algoritmo
 * Executa a função `repeticoes` vezes e calcula a média
 * * @param algoritmo A função do algoritmo a ser medida
 * @param repeticoes Número de vezes para executar e tirar a média
 * @param args Os dados de entrada para o algoritmo
 * @return O tempo médio de execução em microssegundos
 */
template<typename Func, typename... Args>
long long medirTempoExecucao(Func algoritmo, int repeticoes, Args&&... args) {
    long long duracaoTotal = 0;

    for (int i = 0; i < repeticoes; ++i) {
        //Cria uma cópia dos dados para cada execução para garantir que o algoritmo não se beneficie de execuções anteriores (ex: vetor já ordenado)
        auto copiaArgs = make_tuple(forward<Args>(args)...);
        
        auto inicio = chrono::high_resolution_clock::now();
        //Chama o algoritmo com os argumentos copiados
        apply(algoritmo, copiaArgs);
        auto fim = chrono::high_resolution_clock::now();
        
        duracaoTotal += chrono::duration_cast<chrono::microseconds>(fim - inicio).count();
    }

    return duracaoTotal / repeticoes;
}


// ===================================================================================
// FUNÇÃO PRINCIPAL
// ===================================================================================

int main() {
    //Define os tamanhos de entrada (n) a serem testados
    const vector<int> tamanhosN = {100, 500, 1000, 2500, 5000, 10000, 20000};
    //Define o número de repetições para obter uma média de tempo mais estável
    const int repeticoes = 5;

    //Imprime o cabeçalho no terminal
    cout << "Algoritmo,TamanhoN,TempoMedioMicrosegundos" << endl;

    for (int n : tamanhosN) {
        //Teste dos Algoritmos de Ordenação
        cout << flush; //Garante que a saída seja impressa em ordem
        
        auto vetorOriginalOrd = gerarVetorAleatorio(n);

        //Mede o tempo do Insertion Sort
        long long tempoInsertionSort = medirTempoExecucao(insertionSort, repeticoes, vetorOriginalOrd);
        cout << "InsertionSort," << n << "," << tempoInsertionSort << endl;

        //Mede o tempo do Merge Sort
        long long tempoMergeSort = medirTempoExecucao(mergeSort, repeticoes, vetorOriginalOrd);
        cout << "MergeSort," << n << "," << tempoMergeSort << endl;


        //Teste dos Algoritmos de Busca
        auto vetorOriginalBusca = gerarVetorAleatorio(n);
        //Para a busca, o pior caso é buscar um elemento que não existe
        int elementoNaoExistente = -1;

        //Mede o tempo da Busca Sequencial
        long long tempoBuscaSequencial = medirTempoExecucao(buscaSequencial, repeticoes, vetorOriginalBusca, elementoNaoExistente);
        cout << "BuscaSequencial," << n << "," << tempoBuscaSequencial << endl;

        //Para a Busca Binária, o vetor PRECISA estar ordenado
        //O tempo de ordenação NÃO deve ser contado
        sort(vetorOriginalBusca.begin(), vetorOriginalBusca.end());
        long long tempoBuscaBinaria = medirTempoExecucao(buscaBinaria, repeticoes, vetorOriginalBusca, elementoNaoExistente);
        cout << "BuscaBinaria," << n << "," << tempoBuscaBinaria << endl;
    }
        //Pausa para ver os resultados no terminal
        system("pause");
        return 0;
}
