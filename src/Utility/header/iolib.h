#ifndef __IOLIB_H__
#define __IOLIB_H__


#include <stdio.h>
#include "../../ADT/header/wordmachine.h"

void printLogo();

void printMenu();

void clearConsole();

char getCharInputStream(FILE* file);

char getCharSTDIN();

Word getWordInputStream(FILE* file);

Word getWordSTDIN();

Word convertIntToWord(int in);

int getIntInputStream(FILE* file);

int getIntSTDIN();

FILE* openFile(Word word, const char* mode);

FILE* copyConfig(Word in, Word out);

void wordOutputStream(FILE* outputstream, Word word, boolean newline);

void displayWord(Word word, boolean newline);

#endif