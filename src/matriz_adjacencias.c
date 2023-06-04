#include "matriz_adjacencias.h"

void percorre_matriz_adj(Matriz_adj *matriz)
{
    for (int i = 0; i < matriz->i; i++)
    {
        for (int j = 0; j < matriz->j; j++)
        {
            matriz->mat[i][j] = 0;
        }
    }
}

void popula_matriz_adj(Matriz_adj *matriz, Grafo *grafo)
{
    int col = matriz->i;
    for (int i = 0; i < grafo->num_arestas; i++)
    {
        matriz->mat[grafo->adj[i].vi][grafo->adj[i].vj] += 1;
        matriz->mat[grafo->adj[i].vj][grafo->adj[i].vi] += 1;
    }
}

Matriz_adj *cria_matriz_adj(Grafo *grafo)
{
    Matriz_adj *matriz = (Matriz_adj *)malloc(sizeof(Matriz_adj));
    matriz->i = grafo->num_vertices;
    matriz->j = grafo->num_vertices;

    matriz->mat = malloc((matriz->i) * sizeof(int *));

    for (int i = 0; i < matriz->i; i++)
    {
        matriz->mat[i] = malloc(matriz->j * sizeof(int));
    }

    percorre_matriz_adj(matriz);
    popula_matriz_adj(matriz, grafo);
    return matriz;
}

void print_matriz_adj(Matriz_adj *matriz)
{
    for (int i = 0; i < matriz->i; i++)
    {
        for (int j = 0; j < matriz->j; j++)
        {
            printf("%d ", matriz->mat[i][j]);
        }
        printf("\n");
    }
}

void destroi_matriz_adj(Matriz_adj *matriz_adj)
{
    for (int i = 0; i < matriz_adj->i; i++)
    {
        free(matriz_adj->mat[i]);
    }
    free(matriz_adj->mat);
    free(matriz_adj);
}
