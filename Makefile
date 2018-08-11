CXX = g++
BIN = bin
LIBS = 
OBJS_MAIN = root/obj/graph.o root/obj/node.o root/obj/utils.o root/obj/main.o 

all : main 

main : $(BIN) root/include/edge.h root/include/binary_operation_result.h root/include/unary_operation_result.h 
	$(MAKE) -C root obj obj/graph.o obj/node.o obj/utils.o obj/main.o 
	$(CXX) -o $(BIN)/main $(OBJS_MAIN) $(LIBS)

$(BIN) : 
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

clean : 
	$(MAKE) -C root clean
	if [ -d $(BIN) ]; then rm $(BIN) -r; fi

.PHONY : all
.PHONY : main
.PHONY : clean

