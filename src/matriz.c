#include "matriz.h"

void percorre_matriz(Matriz *matriz){
    for(int i=0; i < matriz->num_i; i++){
        for(int j=0; j < matriz->num_j; j++){
            matriz->mat[i][j] = 0.0;
        }
    }
}

float distancia_euclidiana(Flor f1, Flor f2){
    float distancia;
    distancia = pow((f1.petal_length - f2.petal_length), 2);
    distancia += pow((f1.petal_width - f2.petal_width), 2);
    distancia += pow((f1.sepal_length - f2.sepal_length), 2);
    distancia += pow((f1.sepal_width - f2.sepal_width), 2);
    distancia = sqrt(distancia);
    return distancia;
}

void popula_matriz(Matriz *matriz, Flores *flores){
    for(int i=0; i<flores->tam; i++){
        for(int j=0; j<flores->tam; j++){
            matriz->mat[i][j] = distancia_euclidiana(
                flores->elem[i],
                flores->elem[j]
            );
        }
    }
}

Matriz* cria_matriz(Flores *flores){
    Matriz *matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->num_i = flores->tam;
    matriz->num_j = flores->tam;

    matriz->mat = malloc((matriz->num_i) * sizeof(float*));

    for(int i=0; i<matriz->num_i; i++){
        matriz->mat[i] =  malloc(matriz->num_j * sizeof(int));
    }

    percorre_matriz(matriz);
    popula_matriz(matriz, flores);
    return matriz;
}

float maior_numero_matriz(Matriz *matriz){
    float maior = matriz->mat[0][0];

    for(int i=0; i<matriz->num_i; i++){
        for(int j=0; j<matriz->num_j; j++){
            if(matriz->mat[i][j] > maior){
                maior = matriz->mat[i][j];
            }
        }
    }
    return maior;
}

float menor_numero_matriz(Matriz *matriz){
    float menor = matriz->mat[0][0];

    for(int i=0; i<matriz->num_i; i++){
        for(int j=0; j<matriz->num_j; j++){
            if(matriz->mat[i][j] < menor){
                menor = matriz->mat[i][j];
            }
        }
    }
    return menor;
}

float normaliza(float x, float x_max, float x_min){
    return (x - x_min) / (x_max - x_min);
}

void normaliza_matriz(Matriz *matriz){
    float maior =  maior_numero_matriz(matriz);
    float menor = menor_numero_matriz(matriz);

    for(int i=0; i<matriz->num_i; i++){
        for(int j=0; j<matriz->num_j; j++){
            matriz->mat[i][j] = normaliza(
                matriz->mat[i][j],
                maior,
                menor
            );    
        }
    }
}


Grafo* iris_para_grafo(Flores *flores, float metrica){
    Matriz *matriz = cria_matriz(flores);
    normaliza_matriz(matriz);
    Grafo *grafo = cria_grafo();

    for(int i=0; i<matriz->num_i; i++){
        for(int j=i; j<matriz->num_j; j++){
            if(matriz->mat[i][j] <= metrica && i != j){
                adiciona_adjacencia(grafo, i, j);
            }
        }
    }

    grafo->num_vertices = matriz->num_i;

    destroi_matriz(matriz);
    return grafo;
}

void print_matriz(Matriz *matriz){
    for(int i=0; i<matriz->num_i; i++){
        for(int j=0; j<matriz->num_j; j++){
            printf("%f ", matriz->mat[i][j]);
        }
        printf("\n");
    }
}

void destroi_matriz(Matriz *matriz){
    for(int i=0; i<matriz->num_i; i++){
        free(matriz->mat[i]);
    }
    free(matriz->mat);
    free(matriz);
}

