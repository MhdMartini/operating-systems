# CC=g++
# CFLAGS=-I.
# DEPS = mainfunc.h
# OBJ = main.o mainfunc.o 

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# main: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS)
all: main test1 test2 test3 test4 test5

main: main.cpp mainfunc.cpp
	g++ -o main main.cpp mainfunc.cpp -I.
test1: test1.c
	gcc -o test1 test1.c
test2: test2.c
	gcc -o test2 test2.c -lm
test3: test3.c
	gcc -o test3 test3.c
test4: test4.c
	gcc -o test4 test4.c
test5: test5.c
	gcc -o test5 test5.c