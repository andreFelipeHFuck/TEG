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

Pilha* destroi_pilha(Pilha *pilha)
{
    free(pilha->topo);
    pilha->topo = NULL;
    free(pilha);
    return NULL;
}

Cluster cria_cluster(){
    Cluster cluster;
    cluster.num = 0;
    cluster.vertices = NULL;
    cluster.especie = SETOSA;
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

void print_cluster(Flores *flores, Clusters *clusters)
{
    for (int i = 0; i < clusters->num; i++)
    {
        printf("CLUSER %d = %d, TIPO: ",
               i,
               clusters->clusters[i].num               
               );

        print_especie(clusters->clusters[i].especie);
        printf("\n");

        for(int j=0; j<clusters->clusters[i].num; j++){
            printf("%d, ", clusters->clusters[i].vertices[j]);
            print_especie(flores->elem[clusters->clusters[i].vertices[j]].especie);
            printf("\n");
        }
        
    
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
        if(flores->elem[cluster->vertices[i]].especie == SETOSA)
            num_setosa++;

        if(flores->elem[cluster->vertices[i]].especie == VERSICOLOR)
            num_versicolor++;

        if(flores->elem[cluster->vertices[i]].especie == VIRGINICA)
            num_virginica++;
    }

    if(num_setosa >= num_versicolor && num_setosa >= num_virginica)
        return SETOSA;

    if(num_versicolor >= num_setosa && num_versicolor >= num_virginica)
        return VERSICOLOR;
    
    if(num_virginica >= num_setosa && num_virginica >= num_versicolor)
        return VIRGINICA;
}

void centro_geometrico(Flores *flores, Cluster *cluster){
    Flor flor;
    flor.sepal_length = 0;
    flor.sepal_width = 0;
    flor.petal_length = 0;
    flor.petal_width = 0;

    for(int i=0; i<cluster->num; i++){
        flor.sepal_length += flores->elem[cluster->vertices[i]].sepal_length;

        flor.sepal_width += flores->elem[cluster->vertices[i]].sepal_length;

        flor.petal_length += flores->elem[cluster->vertices[i]].petal_length;

        flor.petal_width += flores->elem[cluster->vertices[i]].petal_width;
    }
    
    cluster->centro_geometrico = flor;
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
        centro_geometrico(flores, &cluster);
        adicionar_cluster(clusters, cluster);

        vertice = busca_vertices_nao_marcado(matriz_adj, vertice_marcado);
    } while (vertice != -1);

    free(vertice_marcado);
    return clusters;
}

int* busca_3_maiores_clusters(Clusters *clusters){
    int j = 0;
    int *tres_maiores = malloc(3 * sizeof(int));

    for(int i=0; i<clusters->num; i++){
        if(clusters->clusters[i].num > 30){
            tres_maiores[j] = i;
            j++;
        }
    }
    return tres_maiores;
}

int* busca_clusters_menores(Clusters *clusters, int *maiores){
    int j = 0;
    int *vetores = malloc((clusters->num - 3) * sizeof(int));

    for(int i=0; i<clusters->num; i++){
        if(i != maiores[0] && i != maiores[1] && i != maiores[2]){
            vetores[j] = i;
            j++;
        }

    }

    return vetores;
}

int menor_distancia(float c0, float c1, float c2){
    if(c0 <= c1 && c0 <= c2)
        return 0;
    if(c1 <= c0 && c1 <= c2)
        return 1;
    if(c2 <= c0 && c2 <= c1)
        return 2;
}

Cluster adicionar_elementos_cluster(Flores *flores, Cluster cluster1, Cluster cluster2){
    for(int i=0; i<cluster2.num; i++){
        adicionar_vertice_cluster(&cluster1, cluster2.vertices[i]);
    }

    cluster1.especie = votacao_especie(flores, &cluster1);
    return cluster1;
}

Clusters* minimizar_num_clusters(Flores *flores, Clusters *clusters){    
    Clusters *novo_clusters = cria_clusters();

    int *tres_maiores = busca_3_maiores_clusters(clusters);
    int *clusters_menores = busca_clusters_menores(clusters, tres_maiores);

    int num_clusters = (clusters->num) - 3;
    int distancia =  -1;
    float c0, c1, c2;

    for(int i=0; i<num_clusters; i++){
        c0 = distancia_euclidiana(
            clusters->clusters[tres_maiores[0]].centro_geometrico,
            clusters->clusters[clusters_menores[i]].centro_geometrico
        );
        c1 = distancia_euclidiana(
            clusters->clusters[tres_maiores[1]].centro_geometrico,
            clusters->clusters[clusters_menores[i]].centro_geometrico
        );
        c2 = distancia_euclidiana(
            clusters->clusters[tres_maiores[2]].centro_geometrico,
            clusters->clusters[clusters_menores[i]].centro_geometrico
        );

        distancia = menor_distancia(c0, c1, c2);
        clusters->clusters[tres_maiores[distancia]] = adicionar_elementos_cluster(
            flores,
            clusters->clusters[tres_maiores[distancia]],
            clusters->clusters[clusters_menores[i]]
        );

        centro_geometrico(flores, &clusters->clusters[tres_maiores[0]]);
        centro_geometrico(flores, &clusters->clusters[tres_maiores[1]]);
        centro_geometrico(flores, &clusters->clusters[tres_maiores[2]]);
    }
    
    adicionar_cluster(novo_clusters ,clusters->clusters[tres_maiores[0]]);
    adicionar_cluster(novo_clusters ,clusters->clusters[tres_maiores[1]]);
    adicionar_cluster(novo_clusters ,clusters->clusters[tres_maiores[2]]);

    return novo_clusters;
}

void log_clusters(float metrica, int num_iteracao, float desconto){

    Flores *flores = le_arquivo_iris("../IrisDataset.csv");
    Grafo *grafo;
    Matriz_adj *matriz;
    Clusters *clusters;

    FILE *file = fopen("assets/log.txt", "wd");

    for(int i=0; i<num_iteracao; i++){
        printf("%f\n", metrica);
        grafo = iris_para_grafo(flores, metrica);
        matriz = cria_matriz_adj(grafo);

        clusters = clusterizacao(matriz, flores);
        fprintf(file, "%d - NUMERO DE CLUSTERS %d\nMETRICA: %f\n",
                i, 
                clusters->num,
                metrica);

        for(int j=0; j<clusters->num; j++){
            fprintf(file, "NUMERO DE VERTICES: %d\nTIPO: %d\n", 
                     clusters->clusters[j].num,
                     clusters->clusters[j].especie
                    );
        }

        fprintf(file, "\n");

        clusters = destroi_clusters(clusters);
        destroi_matriz_adj(matriz);
        metrica -= desconto;
    }
    fclose(file);
    destroi_flores(flores);
}

Matriz_confusao* cria_matriz_confusao(){
    Matriz_confusao *matriz = (Matriz_confusao*) malloc(sizeof(Matriz_confusao));
    matriz->tam = 3;

    matriz->mat = malloc((matriz->tam) * sizeof(int *));

    for(int i=0; i<matriz->tam; i++)
        matriz->mat[i] = calloc(matriz->tam, sizeof(int));

    return matriz;
}

void print_matriz_confusao(Matriz_confusao *matriz){
    printf("Matriz de confusao\n");
    for(int i=0; i<matriz->tam; i++){
        for(int j=0; j<matriz->tam; j++){
            printf("%d ", matriz->mat[i][j]);
        }
        printf("\n");
    }
}

void destroi_matriz_confusao(Matriz_confusao *matriz){
    for(int i=0; i<matriz->tam; i++)
        free(matriz->mat[i]);
    free(matriz->mat);
    free(matriz);
}

void calcula_matriz_confusao(Flores *flores, Clusters *clusters, Matriz_confusao *matriz){
    for(int i=0; i<matriz->tam; i++){
        for(int j=0; j<clusters->clusters[i].num; j++){
            if(flores->elem[clusters->clusters[i].vertices[j]].especie == SETOSA)
                matriz->mat[clusters->clusters[i].especie][SETOSA]++;
            if(flores->elem[clusters->clusters[i].vertices[j]].especie == VIRGINICA)
                matriz->mat[clusters->clusters[i].especie][VIRGINICA]++;
            if(flores->elem[clusters->clusters[i].vertices[j]].especie == VERSICOLOR)
                matriz->mat[clusters->clusters[i].especie][VERSICOLOR]++;
        }
    }
}

float calcula_fn(int especie, Matriz_confusao *matriz){
    float fn = 0;

    for(int j=0; j<matriz->tam; j++){
        if(j != especie)
            fn += matriz->mat[especie][j];
    }
    return fn;
}

float calcaula_fp(int especie, Matriz_confusao *matriz){
    float fp = 0;

    for(int i=0; i<matriz->tam; i++){
        if(i != especie)
            fp += matriz->mat[i][especie];
    }

    return fp;
}

float calcula_tn(int especie, Matriz_confusao *matriz){
    float tn = 0;

    for(int i=0; i<matriz->tam; i++){
        for(int j=0; j<matriz->tam; j++){
            if(i != especie && j != especie)
                tn +=  matriz->mat[i][j];
        }
    }

    return tn;
}

float acuracia(int especie, Matriz_confusao *matriz){
    float tp = matriz->mat[especie][especie];
    float fn = calcula_fn(especie, matriz);
    float fp = calcaula_fp(especie, matriz);
    float tn = calcula_tn(especie, matriz);

    return (tp + tn)/(tp + fp + tn + fn);
}

float precisin(int especie, Matriz_confusao *matriz){
    float tp = matriz->mat[especie][especie];
    float fp = calcaula_fp(especie, matriz);

    return tp / (tp + fp);
}

float recall(int especie, Matriz_confusao *matriz){
    float tp = matriz->mat[especie][especie];
    float fn = calcula_fn(especie, matriz);

    return tp / (tp + fn);
}

float f1_score(int especie, Matriz_confusao *matriz){
    float p = precisin(especie, matriz);
    float r = recall(especie, matriz);

    return (2 * p * r) / (p + r);
}


