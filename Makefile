BINDIR		=		bin
OBJDIR		=		obj
BINNAME   =   server

SRCDIR		     =		src

CXX				=		g++
CXXFLAGS	=		-g -std=c++17

SRCS = $(shell find $(SRC_DIR) -name '*.cc')

all: precompile $(BINNAME) 

$(BINNAME): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(BINDIR)/$@

# $(OBJDIR)/%.o: $(SRCDIR)/%.cc
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

precompile:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	cp -pr $(SRCDIR)/static $(BINDIR)
	cp -pr $(SRCDIR)/templates $(BINDIR)

clean:
	rm -rf bin/*
	rm -rf obj/*
