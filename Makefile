all:
	gcc main.c src/grafo.c src/flores.c src/matriz.c src/matriz_adjacencias.c src/matriz_confusao.c -o main -lm
	echo "Arquivos compiladors com sucesso"
run:
	echo "Trabalho de TEG"
	./main
clean:
	rm ./main