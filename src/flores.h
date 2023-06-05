#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

enum especie {
    SETOSA,
    VIRGINICA,
    VERSICOLOR
};
typedef enum especie Especie;

typedef struct flor{
    int id;
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    Especie especie;
}Flor;

typedef struct flores
{
    int tam;
    struct flor *elem;
}Flores;


Flores* le_arquivo_iris(char nome_arquivo[]);
void print_flores(Flores *flores);
void destroi_flores(Flores *flores);
void print_especie(Especie especie);
