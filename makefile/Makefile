
MUDUO_DIRECTORY ?= $(HOME)/build/release-install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib

INC_DIR:=../inc/ $(MUDUO_INCLUDE)
SRC_DIR:=../src/
SRCS:=$(wildcard ../src/*.cpp)
LIBS:=-L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt

CXX:=clang++

CXXFLAGS:= -Wall -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS) -Wno-deprecated

EXE:=../bin/main

$(EXE):$(SRCS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
