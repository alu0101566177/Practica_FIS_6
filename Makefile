BINDIR		=		bin
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
	cp -pr $(SRCDIR)/static $(BINDIR)
	cp -pr $(SRCDIR)/templates $(BINDIR)
	stat $(BINDIR)/db.sqlite || cp sample.sqlite $(BINDIR)/db.sqlite
