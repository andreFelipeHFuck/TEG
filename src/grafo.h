#include <stdio.h>
#include <stdlib.h>

typedef struct adjacencia
{
    int vi;
    int vj;
}Adj;

typedef struct grafo
{
    int num_vertices; 
    int num_arestas; 
    struct adjacencia *adj; // Lista de adjacencias    
}Grafo;

Grafo* cria_grafo();
void adiciona_adjacencia(Grafo *grafo, int vi, int vj);
void print_grafo(Grafo *grafo);
Grafo* le_arquivo_grafo_csv(char nome_arquivo[]);
Grafo* le_arquivo_grafo_txt(char nome_arquivo[]);
int numero_vertices(Grafo *grafo);
void escreve_arquivo_grafo_csv(Grafo *grafo, char nome_arquivo[]);
void escreve_arquivo_grafo_txt(Grafo *grafo, char nome_arquivo[]);
void destroi_grafo(Grafo *grafo);