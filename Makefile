BINDIR		=		bin
OBJDIR		=		obj
BINNAME   =   server

SRCDIR		     =		src

CXX				=		g++
CXXFLAGS	=		-g -std=c++17
CXXSQLITE = -l sqlite3

SRCS = $(shell find $(SRC_DIR) -name '*.cc')

all: precompile $(BINNAME) 

run: precompile $(BINNAME)
	cd $(BINDIR) && ./$(BINNAME)

$(BINNAME): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(CXXSQLITE) -o $(BINDIR)/$@

precompile:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	cp -pr $(SRCDIR)/static $(BINDIR)
	cp -pr $(SRCDIR)/templates $(BINDIR)

clean:
	rm -rf bin/*
	rm -rf obj/*
