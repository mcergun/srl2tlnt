CXX = g++
CFLAGS = -I. -Isrllib
LDFLAGS = 
OBJDIR = obj
BINDIR = bin

all: makedirs main srl
	$(CXX) -o $(BINDIR)/srl2tlnt $(LDFLAGS) $(OBJDIR)/main.o $(OBJDIR)/rs232.o

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

main:
	$(CXX) -c -o $(OBJDIR)/main.o $(CFLAGS) main.cpp

srl:
	$(CXX) -c -o $(OBJDIR)/rs232.o $(CFLAGS) srllib/rs232-linux.c

makedirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)