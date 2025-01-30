TARGET=Snake
C_FLAGS=-Wall -Werror -Wextra -std=c11
CXX_FLAGS=-Wall -Werror -Wextra -std=c++17
C_CC=gcc
CXX_CC=g++
FILE=Snake
FILETEST=tests/*
FILEREPORT=s21_test_report
FILETESTO=s21_test
DIRREPORT=report
COVFLAG=-fprofile-arcs -ftest-coverage #--coverage 
SNAKE_LIB=libsnake.a
TETRIS_LIB=libtetris.a
CONTROLLER=controller/controller.cpp
CLI_LIB=libcli.a
FLAGCUR=-lncurses
CLI_MAIN=gui/cli/main_cli.c
OS = $(shell uname)

ifeq ($(OS), Darwin)
	TESTFLAGS=-pthread -lcheck -lgtest -lstdc++
	OPEN_CMD=open
else
	TESTFLAGS=  -lrt -lsubunit -lgtest #-lcheck_pic#-pthread #-lstdc++
	OPEN_CMD=xdg-open
endif

all: clean gcov_report install

$(SNAKE_LIB):
	$(CXX_CC) $(CXX_FLAGS) -c brick_game/snake/*.cpp
	ar rcs $(SNAKE_LIB) *.o
	ranlib $(SNAKE_LIB)

$(TETRIS_LIB):
	$(C_CC) $(C_FLAGS) -c brick_game/tetris/*.c
	ar rcs $(TETRIS_LIB) *.o
	ranlib $(TETRIS_LIB)

$(CLI_LIB):
	$(C_CC) $(C_FLAGS) -c gui/cli/cli_backend.c
	ar rcs $(CLI_LIB) *.o
	ranlib $(CLI_LIB)

snake_cli: clean $(SNAKE_LIB) $(CLI_LIB)
	$(CXX_CC) $(CXX_FLAGS) $(CLI_MAIN) $(CLI_LIB) $(SNAKE_LIB) -o snake_cli $(FLAGCUR) 
	./snake_cli

tetris_cli: clean $(TETRIS_LIB) $(CLI_LIB)
	$(C_CC) $(C_FLAGS) $(CLI_MAIN) $(CLI_LIB) $(TETRIS_LIB) -o tetris_cli $(FLAGCUR)
	./tetris_cli

tetris_gui: uninstall clean $(TETRIS_LIB)
	mkdir ./build
	cp gui/desktop/pro_files/tetris/desktop.pro gui/desktop/desktop.pro 
	cd ./build && qmake ../gui/desktop/ && make && mv desktop Tetris.app

install: uninstall clean $(SNAKE_LIB)
	mkdir ./build
	cp gui/desktop/pro_files/snake/desktop.pro gui/desktop/desktop.pro 
	cd ./build && qmake ../gui/desktop && make && mv desktop $(TARGET).app
	
uninstall:
	rm -rf ./build

dist: clean uninstall
	mkdir dist
	mkdir dist/src
	cp -r brick_game/ gui/ controller/ tests/ Makefile *.md dist/src/
	cd ./dist && tar cvzf $(TARGET)_v1.0.tgz *
	rm -rf dist/src/

dvi:
	$(OPEN_CMD) README.md

test: $(SNAKE_LIB)
	$(CXX_CC) $(FILETEST).cpp $(SNAKE_LIB) -o $(FILETESTO) $(TESTFLAGS)
	./$(FILETESTO)


test_val: 
	$(CXX_CC) $(FILETEST).cpp brick_game/snake/snake_lib.cpp -o $(FILETESTO) $(TESTFLAGS)
	valgrind --tool=memcheck --log-file="valgrind_check.log" --leak-check=yes \
	--track-origins=yes -s ./$(FILETESTO)

gcov_report: clean $(SNAKE_LIB)
	$(CXX_CC) $(COVFLAG)  -o $(FILEREPORT) $(FILETEST) brick_game/snake/snake_lib.cpp  $(TESTFLAGS)
	./$(FILEREPORT)
	gcovr --html-details --exclude $(FILETEST) -o report.html
	$(OPEN_CMD) report.html

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.log *.html *.css *.txt tetris_cli snake_cli greport $(DIRREPORT) $(FILETESTO) $(FILEREPORT) ./build* ./dist

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n controller/*.cpp
	clang-format -n controller/*.h
	clang-format -n brick_game/snake/*.h
	clang-format -n brick_game/*.h
	clang-format -n brick_game/snake/*.cpp
	clang-format -n brick_game/tetris/*.h
	clang-format -n brick_game/tetris/*.c
	clang-format -n gui/desktop/*.cpp
	clang-format -n gui/desktop/*.h
	clang-format -n gui/cli/*.c
	clang-format -n gui/cli/*.h
	clang-format -n tests/*.cpp
	clang-format -i tests/*.cpp
	clang-format -i controller/*.cpp
	clang-format -i controller/*.h
	clang-format -i brick_game/snake/*.h
	clang-format -i brick_game/*.h
	clang-format -i brick_game/snake/*.cpp
	clang-format -i brick_game/tetris/*.h
	clang-format -i brick_game/tetris/*.c
	clang-format -i gui/desktop/*.cpp
	clang-format -i gui/desktop/*.h
	clang-format -i gui/cli/*.c
	clang-format -i gui/cli/*.h
	rm .clang-format 
