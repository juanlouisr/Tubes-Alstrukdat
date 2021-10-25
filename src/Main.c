#include <stdio.h>
#include "adtlib.h"
#include "utillib.h"

int main()
{
    printLogo();
    printMenu();
    FILE* file = fopen("src/data/config.cfg", "r");
    if (file != NULL)
    {
        int row = getIntInputStream(file);
        int col = getIntInputStream(file);
        printf("row : %d, col : %d\n", row, col);
    }
    
    printf(">> ");
    Word word = getWordSTDIN();

    if (isWordEQ(word, "1"))
    {
        printf("NEW GAME!\n");
        
    }
    else if (isWordEQ(word, "2"))
    {
        printf("LOAD GAME!\n");
    }
    else
    {
        printf("SAMPAI JUMPA LAGI!\n");
    }
    

    // printf("hasil get word stdin: ");
    // wordOutputStream(stdout, word, true);

    // char c = getCharSTDIN();
    // printf("hasil get char: %c\n", c);

    

    return 0;
}
