CC = g++

CFLAGS = -std=c++11
INCLUDES = tinyxml.h
LIBS = tinyxml/tinylib.a

EXEC_NAME = executable
SRC = graph.cpp state.cpp transition.cpp action.cpp

all : $(EXEC_NAME)

$(EXEC_NAME) :
	$(CC) -o $(EXEC_NAME) main.cpp $(INCLUDES) $(LIBS)

test1 : $(EXEC_NAME)
	./$(EXEC_NAME) graph1.scxml
	$(CC) -o $@ main_test.cpp $(SRC) $(CFLAGS)

test2 : $(EXEC_NAME)
	./$(EXEC_NAME) graph2.scxml
	$(CC) -o $@ main_test.cpp $(SRC) $(CFLAGS)

test3 : $(EXEC_NAME)
	./$(EXEC_NAME) graph3.scxml
	$(CC) -o $@ main_test.cpp $(SRC) $(CFLAGS)

test4 : $(EXEC_NAME)
	./$(EXEC_NAME) graph4.scxml
	$(CC) -o $@ main_test.cpp $(SRC) $(CFLAGS)

clean :
	rm $(EXEC_NAME) graph.cpp test1 test2 test3 test4 

