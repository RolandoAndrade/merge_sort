all:
	gcc -c merge_sort.c -o ordenar.o
	gcc ordenar.o -o ordenar

clean:
	rm ordenar.o ordenar