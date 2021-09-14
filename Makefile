lsh: lsh.o class_implementation.o  funs_implementation.o
	g++ lsh.o class_implementation.o  funs_implementation.o -o lsh

lsh.o: lsh.cpp classes.h funs_declaration.h
	g++ -c lsh.cpp -std=c++11

class_implementation.o: class_implementation.cpp classes.h
	g++ -c class_implementation.cpp -std=c++11

funs_implementation.o: funs_implementation.cpp funs_declaration.h classes.h
	g++ -c funs_implementation.cpp -std=c++11

clean:
	rm lsh class_implementation.o  funs_implementation.o lsh.o
