#ifndef __IOLIB_H__
#define __IOLIB_H__


#include <stdio.h>
#include "../../adtlib.h"

void printLogo();

void printMenu();

void clearConsole();

char getCharInputStream(FILE* file);

char getCharSTDIN();

Word getWordInputStream(FILE* file);

Word getWordSTDIN();

int getIntInputStream(FILE* file);

int getIntSTDIN();

void wordOutputStream(FILE* outputstream, Word word, boolean newline);

void displayWord(Word word, boolean newline);

#endif