CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra
CTC = s21_cat.c
CTO = s21_cat.o
CTFC = s21_cat_function.c
CTFO = s21_cat_function.o

s21_cat: $(CTO) $(CTFO)
	$(CC) $(CFLAGS) $(CTO) $(CTFO) -o s21_cat.out

$(CTO): $(CTC)
	$(CC) $(CFlAGS) -c $(CTC) 

$(CTFO): $(CTFC)
	$(CC) $(CFLAGS) -c $(CTFC)

clean:
	rm -rf *.o
	rm -rf *.out
