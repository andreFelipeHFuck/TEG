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
    colors = ['#a9b664', '#d8bc71', '#8f70b4']
    
    plt.figure(figsize=(9, 9))
    plt.rcParams['xtick.labelsize'] = 30
    plt.rcParams['ytick.labelsize'] = 30

    plt.title("Clusters de Íris", fontsize = 30)
    plt.xlabel("Espécies", fontsize = 30)
    plt.ylabel("Número de elementos", fontsize = 30)

    plt.bar(especies, tamanhos, color=colors)
    plt.yticks([0, 15, 30, 45, 60])

    plt.savefig("assets/histograma.png")


if __name__ == "__main__":
    plot_histograma("assets/clusters.csv")
