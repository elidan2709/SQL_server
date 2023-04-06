COMPILER=g++
FLAGS= -std=c++17 -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -Wuninitialized
LINK_COMPILER_FLAGS = -fsanitize=undefined -g -o

all: server client

server: server.o sockets.o dbms.o lexical_analyzer.o parser.o
	$(COMPILER) $(LINK_COMPILER_FLAGS) $@ $^

client: client.o sockets.o
	$(COMPILER) $(LINK_COMPILER_FLAGS) $@ $^

sockets.o: sockets.cpp sockets.hpp
	$(COMPILER) $(FLAGS) -c sockets.cpp
dbms.o: dbms.cpp dbms.hpp
	$(COMPILER) $(FLAGS) -c dbms.cpp
lexical_analyzer.o: lexical_analyzer.cpp lexical_analyzer.hpp
	$(COMPILER) $(FLAGS) -c lexical_analyzer.cpp
parser.o: parser.cpp parser.hpp
	$(COMPILER) $(FLAGS) -c parser.cpp
server.o: server.cpp
	$(COMPILER) $(FLAGS) -c server.cpp
client.o: client.cpp
	$(COMPILER) $(FLAGS) -c client.cpp


clear:
	rm client server *.o
clear_bin:
	rm TEST Students
