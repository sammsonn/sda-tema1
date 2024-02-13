CC=gcc
DEPS=tema1.c
EXE=tema1

build: $(DEPS)
	$(CC) -Wall $^ -o $(EXE) -g

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f $(EXE)