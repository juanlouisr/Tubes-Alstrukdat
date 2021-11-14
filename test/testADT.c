#include "../src/game.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

Word inptCfg;
Word commands[1000];
int args[1000];
int ccount;
int arguCount;

FILE* input;
FILE* output;

int tests;
int testpass;

void ASSERT_TRUE(const char* __TEST_NAME__, boolean val);
char* char_format(const char *fmt, ...);
void PRINT_HASIL();

int main()
{
    input = stdin;
    output = stdout;

    // INIT
    FILE* file = fopen("src/data/config.cfg", "r");
    STATE state;
    MAP map;
    PLAYER p;
    Queue q;
    LoadConfig(&map, &p, &q, file);
    CreateSTATE(&state, p, map, q, 0);
    updateStatus(&state);

   
    // LOKASI
    LOKASI lokasi = MakeLOKASI('C', 1, 2, 'b');
    ASSERT_TRUE("nama lokasi", NAMA(lokasi) == 'C');
    ASSERT_TRUE("absis lokasi", Absis(lokasi) == 1);
    ASSERT_TRUE("ordinat lokasi", Ordinat(lokasi) == 2);
    ASSERT_TRUE("tipe lokasi", Type(lokasi) == 'b');

    
    // DAFTAR LOKASI
    DaftarLokasi df;
    CreateDaftarLokasi(&df, 10);
    LOKASI lokasi1 = MakeLOKASI('A', 1, 2, 'b');
    LOKASI lokasi2 = MakeLOKASI('B', 1, 2, 'b');
    LOKASI lokasi3 = MakeLOKASI('C', 1, 2, 'b');
    LOKASI lokasi4 = MakeLOKASI('D', 1, 2, 'b');
    insertLast(&df, lokasi1);
    insertLast(&df, lokasi2);
    insertLast(&df, lokasi3);
    insertLast(&df, lokasi4);
    ASSERT_TRUE("insert daftar lokasi 1", NAMA(ELMTLD(df, 0)) == 'A');
    ASSERT_TRUE("insert daftar lokasi 2", NAMA(ELMTLD(df, 1)) == 'B');
    ASSERT_TRUE("insert daftar lokasi 3", NAMA(ELMTLD(df, 2)) == 'C');
    ASSERT_TRUE("insert daftar lokasi 4", NAMA(ELMTLD(df, 3)) == 'D');


    // MAP
    MAP* currMap = &state.map;
    DaftarLokasi *dlmap = &state.map.daftarlok;
    ASSERT_TRUE("row map", ROW(*currMap) == 10);
    ASSERT_TRUE("col map", COL(*currMap) == 15);
    ASSERT_TRUE("jumlah bangungan map", CAPACITY(*dlmap) == 18);
    ASSERT_TRUE("bangunan HQ", NAMA(ELMTLD(*dlmap, 0)) == '8');
    ASSERT_TRUE("bangunan Q", NAMA(ELMTLD(*dlmap, 17)) == 'Q');
    for (int j = 0; j < 18; j++)
    {
        char c;
        if (j==13 ||j == 17) c = '1'; else c = '0';
        char* test_name = char_format("matriks adj %d", j+1);
        ASSERT_TRUE(test_name, ELMTADJ(*currMap, 1, j) == c);
        free(test_name);
    }


    // ITEM
    Item item, item2;
    CreateItemPesanan(&item, NORMAL_ITEM, 'G', 'N', 1, 0);
    CreateItemPesanan(&item2, PERISHABLE_ITEM, 'P', 'Q', 10, 20);
    ASSERT_TRUE("normal item", ItemTipe(item) == 'N');
    ASSERT_TRUE("perishable item tipe", ItemTipe(item2) == 'P');
    ASSERT_TRUE("perishable item waktu", ItemWaktuSampai(item2) == 20);

    
    // LIST STATIS


    // QUEUE
    Queue *queue = &state.itemsQueue;
    ASSERT_TRUE("queue item 1", IsItemSama((*queue).buffer[0], item));
    ASSERT_TRUE("queue item 10", IsItemSama((*queue).buffer[9], item2));
    

    // TO DO LIST
    List *todo = &state.player.todo;
    ASSERT_TRUE("todo awal", lengthTodoList(*todo) == 0);
    incrementWaktu(&state);
    ASSERT_TRUE("todo awal waktu pada detik 1", lengthTodoList(*todo) == 2);


    // TAS
    Tas *tas = &state.player.tas;
    ASSERT_TRUE("tas awal", IDX_TOP(*tas) == -1);
    LOKASI locG = MakeLOKASI('G', 3, 8, 'b');
    PLAYER* player = &state.player;
    (*player).loc = locG;
    fprintf(output, "\x1b[2m");
    pickUp(player);
    fprintf(output, NORMAL);
    ASSERT_TRUE("tas setelah pick up", IDX_TOP(*tas) == 0);
    ASSERT_TRUE("todo setelah pick up", lengthTodoList(*todo) == 1);
    
    
    // PLAYER
    ASSERT_TRUE("lokasi player awal", (*player).loc.Nama == 'G');
    movePlayer(state.map, player, 2);
    ASSERT_TRUE("lokasi player pindah", (*player).loc.Nama == 'E');
    
    
    // STATE
    ASSERT_TRUE("waktu awal", state.waktu == 1);
    incrementWaktu(&state);
    ASSERT_TRUE("waktu berubah", state.waktu == 2);


    PRINT_HASIL();
    return 0;
}

void ASSERT_TRUE(const char* __TEST_NAME__, boolean val)
{
    tests++;
    if (val)
    {
        fprintf(output, "%s%s %s%s\n", GREEN,"V", NORMAL, __TEST_NAME__);
        testpass++;
    }
    else
    {
        fprintf(output, "%s%s %s%s\n", RED,"X", NORMAL, __TEST_NAME__);
    }
}

void PRINT_HASIL()
{
    fprintf(output, "\nTest berhasil %d dari %d test diambil\n", testpass, tests);
}

char* char_format(const char *fmt, ...)
{
    va_list args;
    size_t  len;
    char   *space;

    va_start(args, fmt);
    len = vsnprintf(0, 0, fmt, args);
    va_end(args);
    if ((space = malloc(len + 1)) != 0)
    {
        va_start(args, fmt);
        vsnprintf(space, len+1, fmt, args);
        va_end(args);
        return space;
    }
    return NULL;
}
