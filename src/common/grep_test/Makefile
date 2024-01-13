CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra -pedantic
GRC = s21_grep.c
GRO = s21_grep.o

cp_bin: s21_grep
	cp s21_grep ../common/grep_test/s21_grep

s21_grep: $(GRO) 
	$(CC) $(CFLAGS) $(GRO) -o s21_grep 

$(GRO): $(GRC)
	$(CC) $(CFlAGS) -c $(GRC) 

clf_test: cp_clf
	clang-format -n *.c *.h

clf: cp_clf
	clang-format -i *.c *.h

cp_clf:
ifeq ("$(wildcard ../.clang-format)","")
	cp ../../materials/linters/.clang-format ../
endif

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf *.o
	rm -rf s21_grep
