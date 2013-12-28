.PHONY : all

all : lexer parser *.cpp
	g++ -std=c++11 *.cpp
	rm lexer.cpp parser.cpp parser.hpp location.hh position.hh stack.hh

lexer : lexer.l
	flex -o lexer.cpp lexer.l

parser : parser.y
	bison -d -o parser.cpp parser.y

