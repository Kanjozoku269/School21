TARGET = s21_grep

CC = gcc -Wall -Werror -Wextra

all : $(TARGET) clean

$(TARGET).o : $(TARGET).c $(TARGET).h
	$(CC) -c $(TARGET).c 

$(TARGET) : $(TARGET).o
	$(CC) -o $(TARGET) $(TARGET).o

rebuild : clean all		

clean :
	rm -f $(TARGET).o

testfunc :
	sh test_func_grep.sh

testleak : 
	sh test_leak_grep.sh

clangtest :
	clang-format -n $(TARGET).*	