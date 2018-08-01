CXX = g++
CFLAGS = -std=c++11 -I. -Isrllib -Iserial -Itelnet -g -Wall -D_DEBUG
LDFLAGS = -pthread
OBJDIR = obj
BINDIR = bin
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/telnet.o $(OBJDIR)/telnet-cli.o
all: makedirs main telnet telnetcli
	$(CXX) -o $(BINDIR)/srl2tlnt $(LDFLAGS) $(OBJECTS)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

telnet: telnet/TelnetManager.cpp
	$(CXX) -c -o $(OBJDIR)/telnet.o $(CFLAGS) telnet/TelnetManager.cpp

telnetcli: telnet/TelnetClient.cpp
	$(CXX) -c -o $(OBJDIR)/telnet-cli.o $(CFLAGS) telnet/TelnetClient.cpp

main: main.cpp
	$(CXX) -c -o $(OBJDIR)/main.o $(CFLAGS) main.cpp

makedirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)