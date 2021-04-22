#CXX=clang++
CXX=g++

FLAGS = -O3 -g -std=c++14 

all:
	${CXX} ${FLAGS} *.cpp
