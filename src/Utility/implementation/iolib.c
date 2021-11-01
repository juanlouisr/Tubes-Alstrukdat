#include "../header/iolib.h"
#include <stdio.h>

static char filePath[] = "src/data/";

void printLogo()
{   
    printf("##     ##  #######  ##    ##    ###    ##    ##  ######   ####  ###### \n");
    printf("###   ### ##     ## ###   ##   ## ##   ###   ## ##    ##   ##  ##    ##\n");
    printf("#### #### ##     ## ####  ##  ##   ##  ####  ## ##         ##  ##      \n");
    printf("## ### ## ##     ## ## ## ## ##     ## ## ## ## ##   ####  ##   ###### \n");
    printf("##     ## ##     ## ##  #### ######### ##  #### ##    ##   ##        ##\n");
    printf("##     ## ##     ## ##   ### ##     ## ##   ### ##    ##   ##  ##    ##\n");
    printf("##     ##  #######  ##    ## ##     ## ##    ##  ######   ####  ###### \n");
}

void printMenu()
{
    printf("Selamat datang di MONANGIS\n");
    printf("1. NEW GAME\n");
    printf("2. LOAD GAME\n");
    printf("3. EXIT\n");
}


void clearConsole()
{
    // system("clear");
    printf("\e[1;1H\e[2J");
}

char getCharInputStream(FILE* file)
{
    start(file);
    ignoreBlank();
    if (currentChar == MARK)
    {
        return getCharInputStream(file);
    }
    else
    {
        return currentChar;
    }
}

char getCharSTDIN()
{
    return getCharInputStream(stdin);
}

Word getWordInputStream(FILE* file)
{
    start(file);
    ignoreBlank();
    if (currentChar == MARK)
    {
        return getWordInputStream(file);
    }
    else
    {
        Word word;
        copyWord();
        word = currentWord;
        return word;
    }
}

Word getWordSTDIN()
{
    return getWordInputStream(stdin);
}

int getIntInputStream(FILE* file)
{
    Word word = getWordInputStream(file);
    int temp, val = 0;
    boolean neg = false;
    int i = 0;
    if (word.contents[0] == '-')
    {
        neg = true;
        i++;
    }
    for (i; i < word.length; i++)
    {
        temp = word.contents[i] - '0';
        val = val*10 + temp;
    }
    if (neg)
    {
        val *= -1;
    }
    return val;
}


int getIntSTDIN()
{
    return getIntInputStream(stdin);
}

FILE* openFile(Word word, const char* mode)
{
    char str[WORDCAP+20];
    concatStrWord(filePath, word, str);
    return fopen(str, mode);
}

void wordOutputStream(FILE* outputstream, Word word, boolean newline)
{
    char str[WORDCAP];
    wordToStr(word, str);
    fprintf(outputstream, str);
    if(newline)fprintf(outputstream, "\n");
}

void displayWord(Word word, boolean newline)
{
    wordOutputStream(stdout, word, newline);
}