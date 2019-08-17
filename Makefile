
objects = main.o policies.o generate.o

test: $(objects)
	g++ -o test $(objects)
main.o: policies.h

.PHONY: clean
clean:
	-rm test $(objects)
