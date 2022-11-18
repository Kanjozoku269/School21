TARGET = s21_cat

.PHONY : all clean $(TARGET).o $(TARGET) rebuild testfunc testleak clangtest

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
	sh test_func_cat.sh

testleak : 
	sh test_leak_cat.sh

clangtest :
	clang-format -n $(TARGET).*	