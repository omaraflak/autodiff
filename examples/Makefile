CXX = g++
ODIR = obj
CXXFLAGS = -std=c++11 -O3
OBJS = $(ODIR)/speed.o $(ODIR)/derivative.o $(ODIR)/ann.o 

all : $(ODIR) $(OBJS) 

$(ODIR)/speed.o : speed.cpp ../root/include/graph.h 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR)/derivative.o : derivative.cpp ../root/include/graph.h 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR)/ann.o : neural-network/ann.cpp neural-network/vectmath.h ../root/include/graph.h 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR) : 
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

clean : 
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi

.PHONY : all
.PHONY : clean

