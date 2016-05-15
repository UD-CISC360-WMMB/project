CC=gcc

test-bin=test/graph-test test/data-test test/graph-eval

main: src/project.a

src/project.a: src/graph.o src/rand-graph.o src/partition-graph.o src/color-graph.o src/data.o
	ar rcs $@ $^

src/graph.o:
	$(CC)  -c src/graph.c -o $@

src/rand-graph.o:
	$(CC)  -c src/rand-graph.c -o $@

src/partition-graph.o:
	$(CC)  -c src/partition-graph.c -o $@

src/color-graph.o:
	$(CC) -c src/color-graph.c -o $@

lib/data.o:
	$(CC)  -c lib/data.c -o $@

test: test/graph-test test/data-test

run-test: test
	test/graph-test 20 20
#	test/data-test

test/graph-test: src/project.a
	$(CC) -o $@ $@.c src/project.a

test/data-test: src/project.a
	$(CC) -o $@ $@.c src/project.a

clean-test:
	rm -f $(test-bin)

clean:
	rm -f main
	rm -f src/*.o
	rm -f src/project.a
	rm -f $(test-bin)
