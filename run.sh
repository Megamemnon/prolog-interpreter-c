#!/bin/bash

valgrind="none"
if [ $# -gt 0 ]; then
	valgrind=$1
fi

if [ $valgrind == "valgrind" ]; then
	cmd="valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./main"
else
	cmd="./main"
fi


colorgcc -Wall -Wextra -Wshadow -pedantic -g -std=c99 -o main *.c && $cmd
