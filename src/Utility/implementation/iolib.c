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

Word convertIntToWord(int input)
{
    Word word;
    sprintf(word.contents, "%ld", input);
    return word;
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

FILE* copyConfig(Word in, Word out)
{
    FILE *ori = openFile(in, "r");
    FILE *copy =  openFile(out, "w");
    int row = getIntInputStream(ori);
    int col = getIntInputStream(ori);
    int x = getIntInputStream(ori);
    int y = getIntInputStream(ori);
    int jmlBangunan = getIntInputStream(ori);
    fprintf(copy, "%d %d\n%d %d\n%d\n", row, col, x, y, jmlBangunan);
    for(int i=0;i<jmlBangunan;i++){
        char b = getCharInputStream(ori);
        x = getIntInputStream(ori);
        y = getIntInputStream(ori);
        fprintf(copy,"%c %d %d\n",b,x,y);
    }
    for(int i=0;i<jmlBangunan+1;i++){
        for(int j=0;j<jmlBangunan+1;j++){
            if (j)
                fprintf(copy, " ");
            char el = getCharInputStream(ori);
            fprintf(copy, "%c", el);
        }
        fprintf(copy, "\n");
    }
    int count = getIntInputStream(ori);
    fprintf(copy, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        int waktuDatang = getIntInputStream(ori);
        int waktuSampai = 0;
        char locAwal = getCharInputStream(ori);
        char locAkhir = getCharInputStream(ori);
        char tipe = getCharInputStream(ori);
        fprintf(copy, "%d %c %c %c", waktuDatang, locAwal, locAkhir, tipe);
        if (tipe == 'P')
        {
            waktuSampai = getIntInputStream(ori);
            fprintf(copy, " %d", waktuSampai);
        }
        fprintf(copy, "\n");
    }
    return copy;
}

void wordOutputStream(FILE* outputstream, Word word, boolean newline)
{
    fprintf(outputstream,"%s",word.contents);
    if(newline)fprintf(outputstream, "\n");
}

void displayWord(Word word, boolean newline)
{
    wordOutputStream(stdout, word, newline);
}