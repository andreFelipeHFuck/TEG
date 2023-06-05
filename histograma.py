import matplotlib.pyplot as plt
import csv
from enum import Enum 

class Especies(Enum):
    SETOSA = 0
    VIRGINICA = 1
    VERSICOLOR = 2

def leitura_clusters(nome_arquivo: str) -> tuple:
    tamanhos = []
    tipos = []

    with open(nome_arquivo) as file:
        reader = csv.reader(file)

        for row in reader:
            tamanhos.append(row[0])
            tipos.append(row[1])
        
    return (tipos, tamanhos)

def plot_histograma(nome_arquivo: str) -> None:
    tipos = ["Setosa", "Virginica", "Versicolor"]
    tamanhos = [40, 50, 60]

    plt.bar(tipos, tamanhos) 

    plt.title("Iris Dataset")
    plt.ylabel("Num")

    plt.xticks(range(len(tipos)))
      
    plt.show()

def main():
    ...

if __name__ == "__main__":
    plot_histograma("assets/clusters.csv")