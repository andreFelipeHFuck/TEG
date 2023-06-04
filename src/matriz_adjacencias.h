#include "matriz.h"

typedef struct matriz_adjacencias
{
    int i;
    int j;
    int **mat;
}Matriz_adj;



Matriz_adj* cria_matriz_adj(Grafo *grafo);
void print_matriz_adj(Matriz_adj *matriz);
void destroi_matriz_adj(Matriz_adj *matriz_adj);
