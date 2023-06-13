#include "src/matriz_confusao.h"

/*
Função para testar as funcionalidade da matriz de adjacencias 
*/
void gera_grafo(char nome_arquivo_saida[], float metrica){
    Flores *flores = le_arquivo_iris("IrisDataset.csv");
    Grafo *grafo = iris_para_grafo(flores, metrica);
    print_flores(flores);
    destroi_flores(flores);
    escreve_arquivo_grafo_txt(grafo, nome_arquivo_saida);
    Matriz_adj *matriz_adj = cria_matriz_adj(grafo);
    destroi_grafo(grafo);
    destroi_matriz_adj(matriz_adj);
}

Matriz_confusao* gera_clusters(float metrica){
    Flores *flores = le_arquivo_iris("IrisDataset.csv");
    Grafo *grafo = iris_para_grafo(flores, metrica);
    Matriz_adj *matriz = cria_matriz_adj(grafo);
    Clusters *clusters = clusterizacao(matriz, flores);
    Clusters *novo_clusters = minimizar_num_clusters(flores, clusters);
    Matriz_confusao *matriz_conf = cria_matriz_confusao();

    calcula_matriz_confusao(flores, novo_clusters, matriz_conf);

    escreve_clusters(novo_clusters, "assets/clusters.csv");
    escreve_arquivo_grafo_txt(grafo, "assets/grafo.txt");
    destroi_flores(flores);
    destroi_grafo(grafo);   
    destroi_matriz_adj(matriz);
    destroi_clusters(clusters);

    return matriz_conf;
}


int main(){
    log_clusters(0.3, 30, 0.01);
    printf("\n\n");

    Matriz_confusao *matriz_conf = gera_clusters(0.057);
    print_matriz_confusao(matriz_conf);

    float ac0 = 0, ac1 = 0, ac2 = 0;

    ac0 = acuracia(0, matriz_conf);
    printf("Acuracia Setosa: %f\n", ac0);

    ac1 = acuracia(1, matriz_conf);
    printf("Acuracia Virginica: %f\n", ac1);

    ac2 = acuracia(2, matriz_conf);
    printf("Acuracia Versicolor: %f\n", ac2);

    destroi_matriz_confusao(matriz_conf);

}