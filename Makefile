all: create_dirs main.cpp
	g++ -g -I. main.cpp -o bin/srl2tlnt

create_dirs:
	mkdir -p bin