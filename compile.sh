#!/bin/bash

echo "compiling $1"
rm -f lex.yy.c
rm -f $1.tab.c
rm -f $1
bison -Wcounterexamples -d $1.y
lex $1.l
g++ lex.yy.c  $1.tab.c -std=c++17 -o $1
