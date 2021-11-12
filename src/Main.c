#include <stdio.h>
#include "adtlib.h"
#include "utillib.h"
#include "game.h"

Word inptCfg;
Word commands[1000];
int args[1000];
int ccount;
int arguCount;

int main()
{
    printf(GREEN);
    printLogo();
    printf(NORMAL);
    printMenu();
    
    printf(">> ");
    Word word = getWordInputStream(stdin);
    STATE state;
    if (isWordEQ(word, "1"))
    {
        printf("NEW GAME!\n");
        LoadNewState(&state);
        clearConsole();
    }
    else if (isWordEQ(word, "2"))
    {
        printf("LOAD GAME!\n");
        load(&state);
        clearConsole();
    }
    else
    {
        printf("SAMPAI JUMPA LAGI!\n");
        return 0;
    }
    displayMAP(CURR_MAP(state));
    Word command;
    do
    {
        displayCurrLoc(CURR_PLAYER(state));
        displayWaktu(state);
        displayMoney(CURR_PLAYER(state));
        printf(">> ");
        command = getWordSTDIN();
        GameHandler(command, &state, stdin);
    } while (!isWordEQ(command, "EXIT") && !gameOver(state));

    printf("Permainan selesai!\n");
    if (gameOver(state))
    {
        printf("Permainan diselesaikan dalam ");
        displayWaktu(state);
    }

    return 0;
}
