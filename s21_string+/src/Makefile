
CC = gcc
FLAG_C = -c
FLAG_O = -o
# ASAN = -fsanitize=address
FLAG_COV = --coverage 
FLAG_ER = -Wall -Werror -Wextra -std=c11
s21_STRING_C = s21_*.c 
s21_STRING_O = s21_*.o
TEST_CASES_C = test_*.c
TEST_CASES_O = test_*.o

all: clean s21_string.a test gcov_report
# --- СОЗДАНИЕ БИБЛИОТЕКИ ФУНКЦИЙ ---

s21_string.a:
	gcc $(FLAG_C) $(FLAG_ER) --coverage $(s21_STRING_C) 
	ar rc s21_string.a $(s21_STRING_O) 
	ranlib s21_string.a

test: s21_string.a
	gcc -std=c11 -D_GNU_SOURCE --coverage test.c -L. s21_string.a  -lcheck -lm -lpthread -o ./test.out
	./test.out

gcov_report: test
	gcov s21_*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details $(FLAG_O) ./report.html

valgrind:
	make s21_string.a
	gcc -g test.c s21_string.a -o test -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./test	

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f tests
	-rm -f report
	find . -type d -name 'tests.dSYM' -exec rm -r {} +

.PHONY:
	test1.c
