CXX = g++
CFLAGS = -std=c++11 -I. -Isrllib -Iserial -Itelnet -g -Wall
LDFLAGS = -pthread
OBJDIR = obj
BINDIR = bin

all: makedirs main
	$(CXX) -o $(BINDIR)/srl2tlnt $(LDFLAGS) $(OBJDIR)/main.o

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

main:
	$(CXX) -c -o $(OBJDIR)/main.o $(CFLAGS) main.cpp

makedirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)