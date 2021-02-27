all: matrix

matrix: matrix.cpp
	g++ -g -o matrix matrix.cpp -lpthread

clean:
	-@rm matrix