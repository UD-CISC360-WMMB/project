CC=gcc

main: src/graph.a

src/graph.a: src/graph.o src/rand-graph.o
	ar rcs $@ $^

src/graph.o:
	$(CC)  -c src/graph.c -o $@

src/rand-graph.o:
	$(CC)  -c src/rand-graph.c -o $@

clean:
	rm -f main
	rm -f src/*.o
	rm -f src/graph.a
