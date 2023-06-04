#include "matriz_confusao.h"

Pilha *criar_pilha()
{
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;

    return pilha;
}

No *criar_no(int valor)
{
    No *no = malloc(sizeof(No));
    no->valor = valor;
    no->anterior = NULL;
    no->proximo = NULL;

    return no;
}

void adicionar_pilha(Pilha *pilha, int valor)
{
    No *no = criar_no(valor);

    no->anterior = pilha->topo;
    pilha->topo = no;
}

int remover_pilha(Pilha *pilha)
{
    No *topo = pilha->topo;
    int valor = topo->valor;

    pilha->topo = topo->anterior;
    free(topo);

    return valor;
}

int pilha_vazia(Pilha *pilha)
{
    return pilha->topo == NULL;
}

int destroi_pilha(Pilha *pilha)
{
    free(pilha->topo);
    pilha->topo = NULL;
}

Cluster cria_cluster(){
    Cluster cluster;
    cluster.num = 0;
    cluster.vertices = NULL;
    cluster.centro_geometrico = 1.0;
    cluster.especie = Setosa;
    return cluster;
}

void adicionar_vertice_cluster(Cluster *cluster ,int elem){
    cluster->vertices = (int*) realloc(cluster->vertices, (cluster->num + 1) * sizeof(int));
    cluster->num++;
    cluster->vertices[cluster->num - 1] = elem;
}

void destroi_cluster(Cluster *cluster){
    free(cluster->vertices);
}

void dfs(int vertice, Matriz_adj *matriz_adj, int *vertice_marcado, Cluster *cluster)
{
    int u = vertice;

    Pilha *pilha = criar_pilha();
    adicionar_pilha(pilha, u);

    while (!pilha_vazia(pilha))
    {
        u = remover_pilha(pilha);

        if (vertice_marcado[u] != 1)
        {
            vertice_marcado[u] = 1;
            adicionar_vertice_cluster(cluster, u);

            for (int v = 0; v < matriz_adj->j; v++)
            {
                if (matriz_adj->mat[u][v] == 1)
                {
                    adicionar_pilha(pilha, v);
                }
            }
        }
    }

    destroi_pilha(pilha);
    free(pilha);
}

int busca_vertices_nao_marcado(Matriz_adj *matriz_adj, int *vertice_marcado)
{
    for (int i = 0; i < matriz_adj->i; i++)
    {
        if (vertice_marcado[i] == 0)
        {
            return i;
        }
    }

    return -1;
}

Clusters *cria_clusters()
{
    Clusters *clusters = malloc(sizeof(Clusters));
    clusters->num = 0;
    clusters->clusters = NULL;
    return clusters;
}

void adicionar_cluster(Clusters *clusters, Cluster cluster)
{   
    clusters->clusters = (Cluster *) realloc(clusters->clusters, (clusters->num + 1) * sizeof(Cluster));
    clusters->num++;
    clusters->clusters[clusters->num - 1] = cluster;
}

void print_cluster(Clusters *clusters)
{
    for (int i = 0; i < clusters->num; i++)
    {
        printf("CLUSER %d = %d, CENTRO: %f TIPO: ",
               i + 1,
               clusters->clusters[i].num,
               clusters->clusters[i].centro_geometrico
               );

        print_especie(clusters->clusters[i].especie);
        printf("\n");
    
    }
}

void escreve_clusters(Clusters *clusters, char nome_arquivo[]){
    FILE *file = fopen(nome_arquivo, "wb");

    if(file == NULL){
        printf("Nao foi possivel abrir o arquivo: %s\n", nome_arquivo);
        return;
    }

    for(int i=0; i<clusters->num; i++){
        fprintf(file, "%d, %d\n",
                clusters->clusters[i].num,
                clusters->clusters[i].especie
                );
    }

    fclose(file);
}

Clusters* destroi_clusters(Clusters *clusters){
    for(int i=0; i<clusters->num; i++)
        destroi_cluster(&clusters->clusters[i]);
    free(clusters->clusters);
    free(clusters);
    return NULL;
}

Especie votacao_especie(Flores *flores, Cluster *cluster){
    int num_setosa = 0, num_versicolor = 0, num_virginica = 0;

    for(int i=0; i<cluster->num; i++){
        if(flores->elem[cluster->vertices[i]].especie == Setosa)
            num_setosa++;

        if(flores->elem[cluster->vertices[i]].especie == Versicolor)
            num_versicolor++;

        if(flores->elem[cluster->vertices[i]].especie == Virginica)
            num_virginica++;
    }

    if(num_setosa >= num_versicolor && num_setosa >= num_virginica)
        return Setosa;

    if(num_versicolor >= num_setosa && num_versicolor >= num_virginica)
        return Versicolor;
    
    if(num_virginica >= num_setosa && num_virginica >= num_versicolor)
        return Virginica;
}

float centro_geometrico(Flores *flores, Cluster *cluster){
    float sepal_length = 0;
    float sepal_width = 0;
    float petal_length = 0;
    float petal_width = 0;

    for(int i=0; i<cluster->num; i++){
        sepal_length += flores->elem[cluster->vertices[i]].sepal_length;

        sepal_width += flores->elem[cluster->vertices[i]].sepal_length;

        petal_length += flores->elem[cluster->vertices[i]].petal_length;

        petal_width += flores->elem[cluster->vertices[i]].petal_width;
    }
    
    return (double) (1.0/cluster->num) * (sepal_length + sepal_width + petal_length + petal_width);
}

Clusters* clusterizacao(Matriz_adj *matriz_adj, Flores *flores)
{
    Clusters *clusters = cria_clusters();
    Cluster cluster;

    int vertice = matriz_adj->mat[0][0];
    int num_vertices, conta;
    int *vertice_marcado = calloc(matriz_adj->i, sizeof(int));
    
    do
    {
        cluster = cria_cluster();
        dfs(vertice, matriz_adj, vertice_marcado, &cluster);

        cluster.especie = votacao_especie(flores, &cluster);
        cluster.centro_geometrico = centro_geometrico(flores, &cluster);
        adicionar_cluster(clusters, cluster);

        vertice = busca_vertices_nao_marcado(matriz_adj, vertice_marcado);
    } while (vertice != -1);

    free(vertice_marcado);
    return clusters;
}

void log_clusters(int intera, float num){
    float metrica = 0.3;

    Flores *flores = le_arquivo_iris("../IrisDataset.csv");
    Grafo *grafo;
    Matriz_adj *matriz;
    Clusters *clusters;

    FILE *file = fopen("log.txt", "wd");

    for(int i=0; i<intera; i++){
        printf("%f\n", metrica);
        grafo = iris_para_grafo(flores, metrica);
        matriz = cria_matriz_adj(grafo);

        clusters = clusterizacao(matriz, flores);
        fprintf(file, "\n%d - NUMERO DE CLUSTERS %d\n",i, clusters->num);

        for(int j=0; j<clusters->num; j++){
            fprintf(file, "NUMERO DE VERTICES: %d\nCENTRO: %3.f\nTIPO: %d\n", 
                     clusters->clusters[j].num,
                     clusters->clusters[j].centro_geometrico,
                     clusters->clusters[j].especie
                    );
        }

        fprintf(file, "\n");

        clusters = destroi_clusters(clusters);
        destroi_matriz_adj(matriz);
        metrica -= num;
    }
    fclose(file);
    destroi_flores(flores);
}



Matriz_confusao* cria_matriz_confusao(){
    Matriz_confusao *matriz = (Matriz_confusao*) malloc(sizeof(Matriz_confusao));
    matriz->i = 3;

    matriz->mat = malloc((matriz->i) * sizeof(int *));

    for(int i=0; i<matriz->i; i++)
        matriz->mat[i] = calloc(matriz->i, sizeof(int));

    return matriz;
}
