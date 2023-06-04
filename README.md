# Tarefa 1 de TEG

**Alunos:** André Felipe Fuck e Kauan Henrique Werlich

---

## Divisão do trabalho:

O trabalho foi divido em 4 arquivos, estes são:

+ Flores: faz a leitura do arquivo csv do iris dataset. Passando os dados para um struct flores.
+ Grafo: faz a leitura e a escrita do arquivo de um arquivo txt. Para isso é preciso usar o struct grafo.
+ Matriz: faz o processo de normalização dos dados obtidos por Flores, e devolve um struct grafo
+ Matriz de Adjacências: transforma a struct grafo em uma matriz de adjacências

## Comando para rodar o programa:

Para rodar o programa é preciso dar o seguinte comando no terminal:

```
gcc main.c grafo.c flores.c matriz.c matriz_adjacencias.c -o main -lm
```

## Representação gráfica:

Na implementação gráfica usamos o script em python feito pelo monitor da disciplina. Usamos o programa que estava no diretório do Github do monitor.

Infelizmente não conseguimos rodar o grafo em 3D. Então geramos uma versão 2D. Segue a baixo a imagem do grafo:

![grafo](assets/imagem_grafo.png)
