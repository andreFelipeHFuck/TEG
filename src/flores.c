#include "flores.h"

Flores* cria_flores(){
    Flores *flores = malloc(sizeof(Flores));
    flores->tam = 0;
    flores->elem = NULL;
    return flores;
}

Especie escolher_especie(char especie[]){
    if(strcmp(especie,"Setosa") == 0)
        return Setosa;

    if(strcmp(especie, "Versicolor") == 0)
        return Versicolor;

    if(strcmp(especie, "Virginica") == 0)
        return Virginica;
}

void adicionar_flor(Flores *flores, Flor flor){
    flores->elem = (Flor *) realloc(flores->elem, (flores->tam + 1) * sizeof(Flor));
    flor.id = flores->tam;
    flores->tam++;
    flores->elem[flores->tam - 1] = flor;
}

Flores* le_arquivo_iris(char nome_arquivo[]){
    Flores *flores = cria_flores();

    Flor flor;

    char especie[10];

    int nfields = 0;

    FILE *file = fopen(nome_arquivo, "r");

    if(!file){
        return NULL;
    }

    while (!feof(file)){
        nfields = fscanf(file, "%f,%f,%f,%f,%s \n", 
                               &(flor.sepal_length), 
                               &(flor.sepal_width),  
                               &(flor.petal_length), 
                               &(flor.petal_width),
                                especie);
        flor.especie = escolher_especie(especie);
        adicionar_flor(flores, flor);

        if(nfields != 5){
            break;
        }
    }

    fclose(file);
    return flores;
}

void print_especie(Especie especie){
    if(especie == Setosa)
        printf("Setosa");

    if(especie == Versicolor)
        printf("Versicolor");

    if(especie == Virginica)
        printf("Virginica");
}


void print_flores(Flores *flores){
    for(int i=0; i<flores->tam; i++){
        printf("%d, %f, %f, %f, %f, ",
            flores->elem[i].id,
            flores->elem[i].sepal_length,
            flores->elem[i].sepal_width,
            flores->elem[i].petal_length,
            flores->elem[i].petal_width
        );
        print_especie(flores->elem[i].especie);
        printf("\n");
    }
}

void destroi_flores(Flores *flores){
    free(flores->elem);
    free(flores);
}

