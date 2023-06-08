#include "matriz_adjacencias.h"

typedef struct no{
    struct no *proximo;
    struct no *anterior;
    int valor;
}No;

typedef struct pilha
{
    struct no *topo;
}Pilha;

typedef struct cluster{
    int num;
    int *vertices;
    Flor centro_geometrico;
    Especie especie;
}Cluster;

typedef struct clusters
{
    int num;
    struct cluster *clusters;
}Clusters;

typedef struct matriz_confusao{
    int tam;
    int **mat;
}Matriz_confusao;

Clusters* clusterizacao(Matriz_adj *matriz_adj, Flores *flores);
void print_cluster(Clusters *clusters);
Clusters* destroi_clusters(Clusters *clusters);
void escreve_clusters(Clusters *clusters, char nome_arquivo[]);
Clusters* minimizar_num_clusters(Flores *flores, Clusters *clusters);
void log_clusters(float metrica, int num_iteracao, float desconto);
Matriz_confusao* cria_matriz_confusao();
void calcula_matriz_confusao(Flores *flores, Clusters *clusters, Matriz_confusao *matriz);
