#include <stdio.h>
#include "adtlib.h"
#include "utillib.h"

void LoadConfig(MAP *map, PLAYER *player, Queue *queue, FILE *file);
void LoadNewState(STATE *state);
void GameHandler(Word command, STATE *state);
void displayHelp();
void move(STATE *state);
void buy(STATE *state);
void use(STATE *state);


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
        displayMAP(CURR_MAP(state));
        Word command;
        do
        {
            displayCurrLoc(CURR_PLAYER(state));
            displayWaktu(state);
            displayMoney(CURR_PLAYER(state));
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
            fprintf(stderr,"%s%s%s%s", RED, inptCfg.contents," tidak ditemukan, silahkan ulangi\n", NORMAL);
    } while (file == NULL);
    MAP map;
    PLAYER p;
    Queue q;
    LoadConfig(&map, &p, &q, file);
    CreateSTATE(state, p, map, q, 0);
    updateStatus(state);
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
    createPlayer(player,ELMTLD(DL,0),tas, todo, invg, 10000, 0);

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

    CreateQueue(queue);
    readAllItem(queue, file);
}

void GameHandler(Word command, STATE *state)
{
    if (isWordEQ(command, "MOVE"))
    {
        move(state);
    }
    else if (isWordEQ(command, "MAP"))
    {
        displayMAP(CURR_MAP(*state));
    }
    else if (isWordEQ(command, "PICK_UP"))
    {
        pickUp(&CURR_PLAYER(*state));
    }
    else if (isWordEQ(command, "DROP_OFF"))
    {
        dropOff(&CURR_PLAYER(*state));
    }
    else if (isWordEQ(command, "TO_DO"))
    {
        displayTodoList(CURR_TODO(*state));
    }
    else if (isWordEQ(command, "IN_PROGRESS"))
    {
        displayInProgress(CURR_TAS(*state));
    }
    else if (isWordEQ(command, "BUY"))
    {
        buy(state);
    }
    else if (isWordEQ(command, "INVENTORY"))
    {
        use(state);
    }
    else if (isWordEQ(command, "HELP"))
    {
        displayHelp();
    }
    printf("\n");
    updateStatus(state);
}


void move(STATE *state)
{
    displayReachable(CURR_MAP(*state));
    printf(">> ");
    int opt = getIntSTDIN();
    if (opt != 0)
    {
        movePlayer(CURR_MAP(*state), &CURR_PLAYER(*state), opt);
        updateStatus(state);
        incrementWaktu(state);
    }
}

void buy(STATE *state)
{
    if (CURR_PLAYER(*state).loc.Nama == '8')
    {
        displayMoney(CURR_PLAYER(*state));
        displayGadget();
        printf(">> ");
        int idx = getIntSTDIN();
        buyGadget(&CURR_PLAYER(*state),idx);
    }
    else
    {
        printf("Mobita sedang tidak berada di HQ!\n");
    }
}

void use(STATE *state)
{
    displayInventory(CURR_PLAYER(*state).invGadget);
    printf(">> ");
    int idx = getIntSTDIN();
    useGadget(state, idx);
}

void displayHelp(){
    printf(GREEN);
    printf("1. MOVE         : Menampilkan pilihan lokasi yang dapat dicapai lalu menerima input angka sesuai pilihan\n");
    printf("2. PICK_UP      : Mengambil item pada tempat pick up\n");
    printf("3. DROP_OFF     : Mengantarkan item ketika sudah tiba di lokasi, jika tidak ada yang perlu didrop maka akan muncul pesan\n");
    printf("4. MAP          : Menampilkan peta\n");
    printf("5. TO_DO        : Menampilkan urutan pesanan yang masuk\n");
    printf("6. IN_PROGRESS  : Menampilkan pesanan yang sedang diantarkan\n");
    printf("7. BUY          : Menampilkan gadget yang dapat dibeli lalu menerima input untuk membeli\n");
    printf("8. INVENTORY    : Menampilkan isi inventory yang dapat digunakan\n");
    printf("9. HELP         : Menampilkan list command yang dapat digunakan beserta penjelansannya\n");
    printf(NORMAL);
};
