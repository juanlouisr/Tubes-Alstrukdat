gcc -I. src/game.c test/testADT.c src/ADT/implementation/*.c src/Utility/implementation/*.c -o bin/testADT -lm 

./bin/testADT 