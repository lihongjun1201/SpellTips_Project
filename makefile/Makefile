INC_DIR:=../inc/
SRC_DIR:=../src/
SRCS:=$(wildcard ../src/*.cpp)
LIBS:=-llog4cpp -lpthread

CXX:=g++

CXXFLAGS:= -Wall -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=../bin/main

$(EXE):$(SRCS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
