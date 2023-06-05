#include "src/matriz_confusao.h"

/*
Função para testar as funcionalidade da matriz de adjacencias 
*/
void gera_grafo(char nome_arquivo_entrada[], char nome_arquivo_saida[]){
    Flores *flores = le_arquivo_iris(nome_arquivo_entrada);
    //Grafo *grafo = iris_para_grafo(flores);
    print_flores(flores);
    destroi_flores(flores);
    // escreve_arquivo_grafo_txt(grafo, nome_arquivo_saida);
    // Matriz_adj *matriz_adj = cria_matriz_adj(grafo);
    // destroi_grafo(grafo);
    // destroi_matriz_adj(matriz_adj);
}

/*
    Para rodar o programa é preciso dar o seguinte comando:
    gcc main.c grafo.c flores.c matriz.c matriz_adjacencias.c -o main -lm
*/

//    Flores *flores = le_arquivo_iris("IrisDataset.csv");
//    Grafo *grafo = iris_para_grafo(flores, 0.21);
//    Matriz_adj *matriz = cria_matriz_adj(grafo);
//    Clusters *clusters = clusterizacao(matriz, flores);
//    escreve_clusters(clusters, "assets/clusters.csv");
//    destroi_flores(flores);
//    destroi_grafo(grafo);
//    destroi_matriz_adj(matriz);
//    destroi_clusters(clusters);

int main(){
    log_clusters(0.06, 5, 0.001);
}