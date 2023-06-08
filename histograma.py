import matplotlib.pyplot as plt
import numpy as np
import csv

def tipo_para_string(tipo: int)->str:
    if tipo == 0:
        return "Setosa"
    if tipo == 1:
        return "Virginica"
    if tipo == 2:
        return "Versicolor"

def leitura_clusters(nome_arquivo: str) -> tuple:
    tamanhos = []   
    especies = []

    with open(nome_arquivo) as file:
        reader = csv.reader(file)

        for row in reader:
            tamanhos.append(int(row[0]))
            especies.append(tipo_para_string(int(row[1])))
        
    return (especies, tamanhos)

def plot_histograma(nome_arquivo: str) -> None:
    especies, tamanhos = leitura_clusters(nome_arquivo)
    
    plt.figure(figsize=(10, 10))
    plt.rcParams['xtick.labelsize'] = 30
    plt.rcParams['ytick.labelsize'] = 20
    plt.title("Clusters de Iris", fontsize = 30)
    colors = ['red', 'green', 'blue']

    plt.bar(especies, tamanhos, color=colors)
    plt.yticks([0, 15, 30, 45, 60])

    plt.savefig("assets/histograma.png")


if __name__ == "__main__":
    plot_histograma("assets/clusters.csv")
