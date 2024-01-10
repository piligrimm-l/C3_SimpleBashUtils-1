CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra -pedantic
CTC = s21_cat.c
CTO = s21_cat.o
CTFC = s21_cat_function.c
CTFO = s21_cat_function.o

cp_bin: s21_cat
	cp s21_cat ../common/cat_test/s21_cat

s21_cat: $(CTO) $(CTFO)
	$(CC) $(CFLAGS) $(CTO) $(CTFO) -o s21_cat 

$(CTO): $(CTC)
	$(CC) $(CFlAGS) -c $(CTC) 

$(CTFO): $(CTFC)
	$(CC) $(CFLAGS) -c $(CTFC)

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
	rm -rf s21_cat
	rm -rf ../.clang-format
