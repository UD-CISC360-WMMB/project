CC=gcc

test-bin=test/graph-test

main: src/graph.a

src/graph.a: src/graph.o src/rand-graph.o
	ar rcs $@ $^

src/graph.o:
	$(CC)  -c src/graph.c -o $@

src/rand-graph.o:
	$(CC)  -c src/rand-graph.c -o $@

build-test: test/graph-test

test/graph-test: src/graph.a
	$(CC) -o $@ $@.c src/graph.a

clean:
	rm -f main
	rm -f src/*.o
	rm -f src/graph.a
	rm -f $(test-bin)
