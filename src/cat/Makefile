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

test: 
	cp ../common/cat_test/*.txt .
	cp ../common/cat_test/M_test_s21_cat.sh .
	./M_test_s21_cat.sh
clf_test: cp_clf
	clang-format -n --style=Google *.c *.h

clf: cp_clf
	clang-format -i --style=Google *.c *.h

cp_clf:
ifeq ("$(wildcard ../.clang-format)","")
	cp ../../materials/linters/.clang-format ../  
	cp ../../materials/linters/.clang-format .
	cp ../../materials/linters/.clang-format ../grep
	cp ../../materials/linters/.clang-format ../common
endif

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf *.o
	rm -rf s21_cat
	rm -rf ../.clang-format
	rm -rf ../common/.clang-format
	rm -rf ../grep/.clang-format
	rm -rf .clang-format
	rm -rf *.txt
	rm -rf *.sh
