CC= g++ 
CFLAGS= -Wall -Wextra -Werror -std=c++17
LIB_NAME = s21_matrix_oop
OS := $(shell uname -s)
SRC = s21_*.cc
OBJ = $(SRC:.cc=.o)


all: $(LIB_NAME).a test


$(LIB_NAME).a: clean
		$(CC) $(CFLAGS) $(SRC) -c 
		ar rcs $(LIB_NAME).a *.o

test:
	@rm -rf build
	@mkdir build
	@cd build && cmake ../ && make && ./main

clean:
	rm -rf test build
	rm -rf *.a *.out *.o report *.gc* $(LIB_NAME).a *.info 

rebuild:
	make clean
	make all

leak:
	CK_FORK=no leaks --atExit -- ./build/main 

linter:
	cp ../materials/linters/.clang-format ..
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h 
	rm -rf ../.clang-format

