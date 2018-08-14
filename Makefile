CXX = g++
BIN = bin
LIB = lib
LIB_NAME = autodiff
OBJS_SPEED = root/obj/graph.o root/obj/node.o root/obj/utils.o examples/obj/speed.o
OBJS_SIMPLE = root/obj/graph.o root/obj/node.o root/obj/utils.o examples/obj/simple.o

all : speed simple

speed : $(BIN) root/include/edge.h root/include/binary_operation_result.h root/include/unary_operation_result.h
	$(MAKE) -C root obj obj/graph.o obj/node.o obj/utils.o
	$(MAKE) -C examples obj obj/speed.o
	$(CXX) -o $(BIN)/speed $(OBJS_SPEED) $(LIBS)

simple : $(BIN) root/include/edge.h root/include/binary_operation_result.h root/include/unary_operation_result.h
	$(MAKE) -C root obj obj/graph.o obj/node.o obj/utils.o
	$(MAKE) -C examples obj obj/simple.o
	$(CXX) -o $(BIN)/simple $(OBJS_SIMPLE) $(LIBS)

$(BIN) :
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

$(LIB) :
	if [ ! -d $(LIB) ]; then mkdir $(LIB); fi

clean :
	$(MAKE) -C root clean
	$(MAKE) -C examples clean
	if [ -d $(BIN) ]; then rm $(BIN) -r; fi

install : $(LIB)
	ar rcs $(LIB)/lib$(LIB_NAME).a root/obj/graph.o root/obj/node.o root/obj/utils.o
	if [ ! -d /usr/local/include/$(LIB_NAME) ]; then mkdir /usr/local/include/$(LIB_NAME) -r; fi
	sudo cp $(LIB)/lib$(LIB_NAME).a /usr/local/lib
	sudo cp root/include/*.h /usr/local/include/$(LIB_NAME)

.PHONY : all
.PHONY : speed
.PHONY : simple
.PHONY : clean
.PHONY : install
