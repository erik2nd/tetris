CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Werror
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
TEST_FLAGS = -lcheck
LIB_FLAGS = -lncurses

INSTALL_DIR = build
DIST_DIR = brick_game gui tests
TEST_DIR = tests

SOURCES_LIB = $(wildcard brick_game/tetris/*.c)
OBJECTS_LIB = $(SOURCES_LIB:.c=.o)
SOURCES = $(wildcard gui/cli/*.c)
OBJECTS = $(SOURCES:.c=.o)

LIBRARY = $(INSTALL_DIR)/backend.a
MAIN = tetris.c
TESTS = $(TEST_DIR)/*.c 
TARGET = tetris

CLANG = clang-format -i

ifeq ($(OS), Windows_NT)
    SYSTEM := Windows
else
    SYSTEM := $(shell uname -s)
    ifeq ($(SYSTEM), Linux)
		TEST_FLAGS += -lsubunit -lrt -lm
	endif
	ifeq ($(SYSTEM), Darwin)
	endif
endif

all: install run

$(LIBRARY): $(OBJECTS_LIB)
	@mkdir -p $(INSTALL_DIR)
	ar rcs $(LIBRARY) $(OBJECTS_LIB) 
	ranlib $(LIBRARY)
	@rm -rf $(OBJECTS) $(OBJECTS_LIB)
	
clang:
	$(CLANG) $(SOURCES) $(SOURCES_LIB) $(TESTS) $(MAIN) */*/*.h */*.h
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 
	
install: uninstall $(LIBRARY) 
	$(CC) $(CFLAGS) $(MAIN) $(SOURCES) $(LIBRARY) -o $(INSTALL_DIR)/$(TARGET) $(LIB_FLAGS)

uninstall:
	@rm -rf $(INSTALL_DIR)	

run: 
	./$(INSTALL_DIR)/$(TARGET)

test: $(LIBRARY)
	$(CC) $(CFLAGS) $(TESTS) $(LIBRARY) -o $(TEST_DIR)/$(TARGET)_test $(TEST_FLAGS)
	./$(TEST_DIR)/$(TARGET)_test

dvi:
	@rm -rf doc	
	doxygen Doxyfile
	open ./doc/html/index.html

dist:
	tar -czf $(TARGET).tar.gz $(DIST_DIR) $(MAIN) Makefile Doxyfile

fsan: CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
fsan: test	

gcov_report: 
	$(CC) $(GCOV_FLAGS) $(TESTS) $(SOURCES_LIB) -o report.out $(TEST_FLAGS) $(LIB_FLAGS)
	./report.out
	lcov -t "gcov_report" -o coverage.info -c -d .
	lcov --remove coverage.info '*/$(TEST_DIR)/*' -o coverage.info
	genhtml -o ./report coverage.info
	rm -f *.gcno *.gcda *.info *.gcov *.out
	open ./report/index-sort-f.html

clean:
	@rm -f *.o *.a *.out *.gcno *.gcda *.tar.gz $(TEST_DIR)/$(TARGET)_test high_score.txt
	@rm -rf report doc $(INSTALL_DIR)

rebuild: clean all