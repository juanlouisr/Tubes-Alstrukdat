#include <exotic/cester.h>
#include "../src/adtlib.h"


CESTER_TEST(test_lokasi, inst,
    LOKASI lokasi = MakeLOKASI('C', 1, 2, 'b');
    cester_assert_equal(NAMA(lokasi), 'C');
    cester_assert_equal(Absis(lokasi), 1);
    cester_assert_equal(Ordinat(lokasi), 2);
    cester_assert_equal(Type(lokasi), 'b');
)

CESTER_TEST(test_daftar_lokasi, inst,
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
    cester_assert_equal(NAMA(ELMTLD(df, 0)), 'A');
    cester_assert_equal(NAMA(ELMTLD(df, 1)), 'B');
    cester_assert_equal(NAMA(ELMTLD(df, 2)), 'C');
    cester_assert_equal(NAMA(ELMTLD(df, 3)), 'D');
)

CESTER_TEST(test_map, inst,
    
)

CESTER_TEST(test_item, inst,

)

CESTER_TEST(test_list_statis, inst,

)

CESTER_TEST(test_queue, inst,


)

CESTER_TEST(test_todo_list, inst,

)

CESTER_TEST(test_tas, inst,

)

CESTER_TEST(test_player, inst,

)

CESTER_TEST(test_state, inst,

)