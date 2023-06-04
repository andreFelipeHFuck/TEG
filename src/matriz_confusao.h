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
    float centro_geometrico;
    Especie especie;
}Cluster;

typedef struct clusters
{
    int num;
    struct cluster *clusters;
}Clusters;

typedef struct matriz_confusao{
    int i;
    int **mat;
}Matriz_confusao;

Clusters* clusterizacao(Matriz_adj *matriz_adj, Flores *flores);
void print_cluster(Clusters *clusters);
Clusters* destroi_clusters(Clusters *clusters);
void escreve_clusters(Clusters *clusters, char nome_arquivo[]);
void log_clusters(int intera, float num);
