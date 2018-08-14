CXX = g++
ODIR = obj
CXXFLAGS = -std=c++11 -O3
OBJS = $(ODIR)/speed.o $(ODIR)/simple.o 

all : $(ODIR) $(OBJS) 

$(ODIR)/speed.o : speed.cpp ../root/include/graph.h 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR)/simple.o : simple.cpp ../root/include/graph.h 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR) : 
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

clean : 
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi

.PHONY : all
.PHONY : clean

