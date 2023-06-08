#include "flores.h"
#include "grafo.h"

#define True 1
#define False 0

typedef struct matriz
{
    int num_i;
    int num_j;
    float **mat;
}Matriz;

Matriz* cria_matriz(Flores *flores);
void normaliza_matriz(Matriz *matriz);
Grafo* iris_para_grafo(Flores *flores, float metrica);
void print_matriz(Matriz *matriz);
void destroi_matriz(Matriz *matriz);
float distancia_euclidiana(Flor f1, Flor f2);
