all: main1 main2 main3

main1: fork-join.c
	gcc -o main1 fork-join.c -pthread

main2: rendezvous.c
	gcc -o main2 rendezvous.c -pthread

main3: barrier.c
	gcc -o main3 barrier.c -pthread