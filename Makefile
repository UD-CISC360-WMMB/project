CC=gcc

test-bin=test/graph-test test/data_test

main: src/project.a

src/project.a: src/graph.o src/rand-graph.o src/partition-graph.o src/color-graph.o src/color-boundary.o src/data.o src/hash.o
	ar rcs $@ $^

src/graph.o:
	$(CC)  -c src/graph.c -o $@

src/rand-graph.o:
	$(CC)  -c src/rand-graph.c -o $@

src/partition-graph.o:
	$(CC)  -c src/partition-graph.c -o $@

src/color-graph.o:
	$(CC) -c src/color-graph.c -o $@

src/color-boundary.o:
	$(CC) -c src/color-boundary.c -o$@

lib/data.o:
	$(CC)  -c lib/data.c -o $@

lib/hash.o:
	$(CC)  -c lib/hash.c -o $@

test: test/graph-test test/data_test

run-test: test
	test/data_test
	test/graph-test

test/graph-test: src/project.a
	$(CC) -o $@ $@.c src/project.a

test/data_test: src/project.a
	$(CC) -o $@ $@.c src/project.a

test/hash_test: src/project.a
	$(CC) -o $@ $@.c src/project.a

clean:
	rm -f main
	rm -f src/*.o
	rm -f src/project.a
	rm -f $(test-bin)
