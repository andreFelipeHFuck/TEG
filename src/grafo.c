#include "grafo.h"

Grafo* cria_grafo(){
    Grafo* grafo = malloc(sizeof(Grafo));
    grafo->num_vertices = 0;
    grafo->num_arestas = 0;
    grafo->adj = NULL;
    return grafo;
}

void adiciona_adjacencia_leitura(Grafo *grafo, Adj adj, int num_aresta){
    grafo->adj = (Adj*) realloc(grafo->adj, (grafo->num_arestas + 1) * sizeof(Adj));
    grafo->adj[num_aresta] = adj;
}

void adiciona_adjacencia(Grafo *grafo, int vi, int vj){
    Adj adj;
    adj.vi = vi;
    adj.vj = vj;
    grafo->adj = (Adj*) realloc(grafo->adj, (grafo->num_arestas + 1) * sizeof(Adj));
    grafo->num_arestas++;
    grafo->adj[grafo->num_arestas - 1] = adj;
}

Grafo* le_arquivo_grafo_csv(char nome_arquivo[]){
    Grafo *grafo = cria_grafo();
    Adj adj;
    int nfields = 0, i = 0;

    FILE *file = fopen(nome_arquivo, "r");
    
    if(!file){
        return NULL;
    }

    nfields = fscanf(file, "%d,%d\n", &grafo->num_vertices, &grafo->num_arestas);
    
    while (!feof(file))
    {
        nfields = fscanf(file, "%d,%d\n", &(adj.vi), &(adj.vj));
        adiciona_adjacencia_leitura(grafo, adj, i);
        i++;

        if(nfields != 2){
            break;
        }
    }
    fclose(file);
    return grafo;
}

Grafo* le_arquivo_grafo_txt(char nome_arquivo[]){
    Grafo *grafo = cria_grafo();
    Adj adj;
    int nfields = 0, i=0;

    FILE *file = fopen(nome_arquivo, "r");
    
    if(!file){
        return NULL;
    }

    nfields = fscanf(file, "%d\n", &grafo->num_arestas);

  
    while (!feof(file))
    {
        nfields = fscanf(file, "%d, %d\n", &(adj.vi), &(adj.vj));
        adiciona_adjacencia_leitura(grafo, adj, i);
        i++;

        if(nfields != 2){
            break;
        }
    }

    grafo->num_vertices = numero_vertices(grafo);
    fclose(file);
    return grafo;
}

int maior_adj(Adj adj){
    return adj.vi > adj.vj ? adj.vi : adj.vj;
}

int numero_vertices(Grafo *grafo){
    int maior = 0,  ajacencia_maior;

    for(int i=0; i<grafo->num_arestas; i++){
        ajacencia_maior = maior_adj(grafo->adj[i]);
        if(ajacencia_maior > maior)
            maior = ajacencia_maior;
    }

    return maior + 1;
}

/*
Escreve arquivo num documento .csv, tem na primeira linha o número de vertices e arestas.
Abaixo uma lista de adjacencias, todos estão separados por virgula
*/
void escreve_arquivo_grafo_csv(Grafo *grafo, char nome_arquivo[]){
    FILE *file = fopen(nome_arquivo, "wd");

    fprintf(file, "%d,%d\n", grafo->num_vertices, grafo->num_arestas);

    for(int i=0; i<grafo->num_arestas; i++){
        fprintf(file, "%d,%d\n", grafo->adj[i].vi, grafo->adj[i].vj);
    }

    fclose(file);
}

/*
Escreve arquivo num documento .txt, não tem na primeira linha o número de 
vertices e arestas. Apenas a lista de adjacencias
*/
void escreve_arquivo_grafo_txt(Grafo *grafo, char nome_arquivo[]){
    FILE *file = fopen(nome_arquivo, "wd");

    fprintf(file, "%d\n", grafo->num_arestas);

    for(int i=0; i<grafo->num_arestas; i++){
        fprintf(file, "%d, %d\n", grafo->adj[i].vi, grafo->adj[i].vj);
    }

    fclose(file);
}

void print_grafo(Grafo *grafo){
    printf("Número de vertices: %d\n", grafo->num_vertices);
    printf("Número de arestas: %d\n", grafo->num_arestas);

    for(int i=0; i<grafo->num_arestas; i++){
        printf("%d, %d\n",
                grafo->adj[i].vi,
                grafo->adj[i].vj
        );
    }
}

void destroi_grafo(Grafo *grafo){
    free(grafo->adj);
    free(grafo);
}

