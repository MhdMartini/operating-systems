all: main1 main2

main1: fork-join.c
	gcc -o main1 fork-join.c -pthread

main2: rendezvous.c
	gcc -o main2 rendezvous.c -pthread