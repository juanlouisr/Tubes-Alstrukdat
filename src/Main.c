#include <stdio.h>
#include "adtlib.h"
#include "utillib.h"

void LoadConfig(MAP *map, PLAYER *player, Queue *queue, FILE *file);
void LoadNewState(STATE *state);
void GameHandler(Word command, STATE *state);

STATE state;

int main()
{
    printLogo();
    printMenu();
    
    printf(">> ");
    Word word = getWordInputStream(stdin);

    if (isWordEQ(word, "1"))
    {
        printf("NEW GAME!\n");
        LoadNewState(&state);
        displayMAP(CURR_MAP(state));
        displayReachable(CURR_MAP(state));
        Word command;
        do
        {
            printf(">> ");
            command = getWordSTDIN();
            GameHandler(command, &state);
        } while (!isWordEQ(command, "EXIT"));
        

    }
    else if (isWordEQ(word, "2"))
    {
        printf("LOAD GAME!\n");
    }
    else
    {
        printf("SAMPAI JUMPA LAGI!\n");
    }
    


    return 0;
}

void LoadNewState(STATE *state)
{
    FILE* file;
    printf("Nama file config:\n");
    do
    {
        printf(">> ");
        Word inptCfg = getWordSTDIN();
        file = openFile(inptCfg, "r");
        if (file == NULL) 
            printf("File tidak ada, silahkan ulangi\n");
    } while (file == NULL);
    MAP map;
    PLAYER p;
    Queue q;
    LoadConfig(&map, &p, &q, file);
    CreateSTATE(state, p, map, q, 0);
    fclose(file);
}

void LoadConfig(MAP *map, PLAYER *player, Queue *queue, FILE *file)
{
    int row = getIntInputStream(file);
    int col = getIntInputStream(file);
    char b;
    int x,y;
    LOKASI P;
    DaftarLokasi DL;
    int i,j;
    x = getIntInputStream(file);
    y = getIntInputStream(file);
    P = MakeLOKASI('8',x,y,'h');
    int jmlBangunan = getIntInputStream(file);
    CreateDaftarLokasi(&DL, jmlBangunan+1);
    insertLast(&DL,P);

    Tas tas;
    ListPos invg;
    List todo;
    CreateTas(&tas);
    CreateListStat(&invg);
    CreateListTodoList(&todo);
    createPlayer(player,ELMTLD(DL,0),tas, todo, invg, 0, 5);

    for(i=0;i<jmlBangunan;i++){
        b = getCharInputStream(file);
        x = getIntInputStream(file);
        y = getIntInputStream(file);
        P = MakeLOKASI(b,x,y,'b');
        insertLast(&DL,P);
    }
    alokasiMAP(map,row,col,DL);
    mapBuilding(map);
    getAdjacent(map,file);
    updateStatus(map,*player);

    CreateQueue(queue);
    readAllItem(queue, file);
}

void GameHandler(Word command, STATE *state)
{
    wordOutputStream(stdout, command, true);
    if (isWordEQ(command, "HMM"))
    {
        printf("WOKE\n");
    }
}