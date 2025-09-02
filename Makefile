# DO NOT MODIFY THIS FILE

GCC = gcc -std=c11 -g -Wall -Wshadow --pedantic -Wvla -Werror
SRCS = main.c stack.c tree.c
OBJS = $(SRCS:%.c=%.o)

all: expr

expr: $(OBJS) 
	$(GCC) $(OBJS) -o expr

%.o: %.c
	$(GCC) -c $< -o $@

test%: expr
	./expr tests/test$*.txt output$*
	diff output$* expected/expected$*.txt



testall: test1 test2 test3 test4 test5

memory: expr
	cat tests/test5 | valgrind --leak-check=full ./expr

clean:
	rm -f expr $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
