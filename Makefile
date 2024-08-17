CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
CHECK_FLAGS = $(shell pkg-config --cflags --libs check)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage

all: s21_string.a test gcov_report

rebuild: clean all

test: string/*.c __test__/*.c sprintf/*.c shared/*.c
	$(CC) $(CFLAGS) $^ -o $@ $(GCOV_FLAGS) $(CHECK_FLAGS)
	./test

s21_string.a:
	$(CC) $(CFLAGS) -c string/string.c -o string.o
	$(CC) $(CFLAGS) -c shared/utils.c -o utils.o
	$(CC) $(CFLAGS) -c shared/str_format_parser.c -o str_format_parser.o
	$(CC) $(CFLAGS) -c sprintf/sprintf.c -o sprintf.o
	$(CC) $(CFLAGS) -c sprintf/sprintf_strategy.c -o sprintf_strategy.o
	ar rcs $@ *.o

gcov_report:
	gcovr --html -o gcov.html
	open gcov.html

clean:
	rm -fr *.o *.a s21_math.a test test.dSYM/ *.gcda *.gcno report/ test.info *.html
