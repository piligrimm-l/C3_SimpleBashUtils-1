CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra 
GRC = s21_grep.c
GRO = s21_grep.o
GRFC = s21_grep_function.c
GRFO = s21_grep_function.o
S21LFC = ../common/s21_list_functions.c 
S21LFO = s21_list_functions.o 

cp_bin: s21_grep
	cp s21_grep ../common/grep_test/s21_grep

s21_grep: $(GRO) $(GRFO) $(S21LFO)  
	$(CC) $(CFLAGS) $(GRO) $(GRFO) $(S21LFO) -o s21_grep 

$(GRO): $(GRC)
	$(CC) $(CFlAGS) -c $(GRC) 

$(GRFO): $(GRFC)
	$(CC) $(CFLAGS) -c $(GRFC)

$(S21LFO): $(S21LFC)
	$(CC) $(CFLAGS) -c $(S21LFC)

clf_test: cp_clf
	clang-format -n *.c *.h

clf: cp_clf
	clang-format -i *.c *.h

cp_clf:
ifeq ("$(wildcard ../.clang-format)","")
	cp ../../materials/linters/.clang-format ../
endif

leaks:
	leaks -atExit -- ./s21_grep

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf *.o
	rm -rf s21_grep
