#include "game.h"


void LoadNewState(STATE *state)
{
    FILE* file;
    printf("Nama file config:\n");
    do
    {
        printf(">> ");
        inptCfg = getWordSTDIN();
        file = openFile(inptCfg, "r");
        if (file == NULL) 
            fprintf(stderr,"%s%s%s%s", 
            RED, 
            inptCfg.contents,
            " tidak ditemukan, silahkan ulangi\n", 
            NORMAL);
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
    createPlayer(player,ELMTLD(DL,0),tas, todo, invg, 0, 0);

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

void GameHandler(Word command, STATE *state, FILE *file)
{
    if (isWordEQ(command, "MOVE"))
    {
        commands[ccount++] = command;
        move(state, file);
    }
    else if (isWordEQ(command, "MAP"))
    {
        displayMAP(CURR_MAP(*state));
    }
    else if (isWordEQ(command, "PICK_UP"))
    {
        commands[ccount++] = command;
        pickUp(&CURR_PLAYER(*state));
    }
    else if (isWordEQ(command, "DROP_OFF"))
    {
        commands[ccount++] = command;
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
        commands[ccount++] = command;
        buy(state, file);
    }
    else if (isWordEQ(command, "INVENTORY"))
    {
        commands[ccount++] = command;
        use(state, file);
    }
    else if (isWordEQ(command, "HELP"))
    {
        displayHelp();
    }
    else if (isWordEQ(command, "SAVE"))
    {
        save(state);
    }
    else if (isWordEQ(command, "LOAD"))
    {
        load(state);
    }
    else if (isWordEQ(command, "RETURN"))
    {
        commands[ccount++] = command;
        returnToSender(&CURR_PLAYER(*state));
    }
    printf("\n");
    updateStatus(state);
}


void move(STATE *state, FILE *file)
{
    displayReachable(CURR_MAP(*state));
    printf(">> ");
    int opt = getIntInputStream(file);
    args[arguCount++] = opt;
    if (opt != 0)
    {
        movePlayer(CURR_MAP(*state), &CURR_PLAYER(*state), opt);
        updateStatus(state);
        incrementWaktu(state);
    }
}

void buy(STATE *state, FILE *file)
{
    if (CURR_PLAYER(*state).loc.Nama == '8')
    {
        displayMoney(CURR_PLAYER(*state));
        displayGadget();
        printf(">> ");
        int idx = getIntInputStream(file);
        args[arguCount++] = idx;
        buyGadget(&CURR_PLAYER(*state),idx);
    }
    else
    {
        printf("Mobita sedang tidak berada di HQ!\n");
    }
}

void use(STATE *state, FILE *file)
{
    displayInventory(CURR_PLAYER(*state).invGadget);
    printf(">> ");
    int idx = getIntInputStream(file);
    args[arguCount++] = idx;
    useGadget(state, idx);
}

void save(STATE *state)
{
    printf("Masukkan nama file save!\n");
    printf(">> ");
    Word output = getWordSTDIN();
    FILE *save = copyConfig(inptCfg, output);
    fprintf(save, "%d\n", ccount);
    int count = 0;
    for (int i = 0; i < ccount; i++)
    {
        wordOutputStream(save, commands[i], true);
        if (isWordEQ(commands[i], "MOVE")
            || isWordEQ(commands[i], "BUY") 
            || isWordEQ(commands[i], "INVENTORY"))
        {
            fprintf(save, "%d\n", args[count++]);
        }
    }
    fclose(save);
}

void load(STATE *state)
{
    FILE* file;
    printf("Nama file save:\n");
    do
    {
        printf(">> ");
        inptCfg = getWordSTDIN();
        file = openFile(inptCfg, "r");
        if (file == NULL) 
            fprintf(stderr,"%s%s%s%s", 
            RED, 
            inptCfg.contents,
            " tidak ditemukan, silahkan ulangi\n", 
            NORMAL);
    } while (file == NULL);
    MAP map;
    PLAYER p;
    Queue q;
    LoadConfig(&map, &p, &q, file);
    CreateSTATE(state, p, map, q, 0);
    updateStatus(state);
    ccount = 0;
    arguCount = 0;
    int cc = getIntInputStream(file);
    for (int i = 0; i < cc; i++)
    {
        Word command = getWordInputStream(file);
        wordOutputStream(stdout, command, true);
        GameHandler(command, state, file);
    }
    fclose(file);
    updateStatus(state);
    clearConsole();
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
    printf("9. RETURN       : Mengembalikan Item tas paling atas ke sender\n");
    printf("10.SAVE         : Menyimpan State permainan ke dalam output file masukan pemain\n");
    printf("11.LOAD         : Menload State permainan dari file save masukan pemain\n");
    printf("12.HELP         : Menampilkan list command yang dapat digunakan beserta penjelansannya\n");
    printf(NORMAL);
};
