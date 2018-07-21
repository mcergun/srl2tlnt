CXX = g++
CFLAGS = -I. -Isrllib -Iserial -g
LDFLAGS = 
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