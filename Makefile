# =============================== 
# Makefile for Mu1Mu2 Analysis 
# =============================== 

ROOTGLIBS     = $(shell $(HOME)/Desktop/ROOT/bin/root-config --glibs)
ROOTCFLAGS    = $(shell $(HOME)/Desktop/ROOT/bin/root-config --cflags) 

SRCDIR = Sources/
INCDIR = -IIncludes/

CXX           = g++ -std=c++11
CXXFLAGS      = -g -Wall -fPIC   	
CXXFLAGS      += $(ROOTCFLAGS) 

SOURCES = HistoZmumu.cc lumiana.cc Zmumu.cc

SRCLIST = $(addprefix $(SRCDIR), $(SOURCES))
OBJLIST = $(SRCLIST:.cc=.o)

.PHONY: all clean

all: runZmumu

# ===========================================================================
.cc.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCDIR)

runZmumu: $(OBJLIST) runZmumu.o 
	$(CXX) -o runZmumu $^ $(ROOTGLIBS)

runZmumu.o: runZmumu.cc
	$(CXX) -o $@ -c -IIncludes $< $(CXXFLAGS) $(INCDIR)

# =========================================================================== 
clean: 
	rm -f *.o Sources/*.o 
