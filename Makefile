CXX = g++
CFLAGS = -std=c++11 -I. -Isrllib -Iserial -Itelnet -g -Wall -D_DEBUG
LDFLAGS = -pthread
OBJDIR = obj
BINDIR = bin

all: makedirs main telnet
	$(CXX) -o $(BINDIR)/srl2tlnt $(LDFLAGS) $(OBJDIR)/main.o $(OBJDIR)/telnet.o

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

telnet: telnet/TelnetManager.cpp
	$(CXX) -c -o $(OBJDIR)/telnet.o $(CFLAGS) telnet/TelnetManager.cpp

main: main.cpp
	$(CXX) -c -o $(OBJDIR)/main.o $(CFLAGS) main.cpp

makedirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)