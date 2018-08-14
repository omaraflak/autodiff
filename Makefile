CXX = g++
BIN = bin
LIB = lib
LIB_NAME = autodiff
OBJS_SPEED = root/obj/graph.o root/obj/node.o root/obj/utils.o examples/obj/speed.o
OBJS_DERIVATIVE = root/obj/graph.o root/obj/node.o root/obj/utils.o examples/obj/derivative.o
OBJS_ANN = root/obj/graph.o root/obj/node.o root/obj/utils.o examples/obj/ann.o

all : speed derivative ann

speed : $(BIN) root/include/edge.h root/include/binary_operation_result.h root/include/unary_operation_result.h
	$(MAKE) -C examples obj obj/speed.o
	$(MAKE) -C root obj obj/graph.o obj/node.o obj/utils.o
	$(CXX) -o $(BIN)/speed $(OBJS_SPEED) $(LIBS)

derivative : $(BIN) root/include/edge.h root/include/binary_operation_result.h root/include/unary_operation_result.h
	$(MAKE) -C examples obj obj/derivative.o
	$(MAKE) -C root obj obj/graph.o obj/node.o obj/utils.o
	$(CXX) -o $(BIN)/derivative $(OBJS_DERIVATIVE) $(LIBS)

ann : $(BIN) examples/neural-network/vectmath.h root/include/edge.h root/include/binary_operation_result.h root/include/unary_operation_result.h
	$(MAKE) -C examples obj obj/ann.o
	$(MAKE) -C root obj obj/graph.o obj/node.o obj/utils.o
	$(CXX) -o $(BIN)/ann $(OBJS_ANN) $(LIBS)

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
.PHONY : derivative
.PHONY : ann
.PHONY : clean
.PHONY : install
