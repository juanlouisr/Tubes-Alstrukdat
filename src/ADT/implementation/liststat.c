
#include "../header/liststat.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPos(ListPos *l)
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas LSCAP */
/* Proses: Inisialisasi semua elemen List l dengan VAL_UNDEF */
{
    int i;
    for (i = 0; i < LSCAP; i++)
    {
        ELMTLS(*l, i) = VAL_UNDEF;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListPos l)
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */
{
    boolean notMark = true;
    int i = 0;
    if (isEmpty(l))
    {
        return 0;
    }
    else
    {
        while (i < LSCAP && notMark)
        {
            if (ELMTLS(l, i) != VAL_UNDEF)
            {
                i++;
            }
            else
            {
                notMark = false;
            }
        }
        return i;
    }
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListPos l, int i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (i > IDX_UNDEF && i < LSCAP);
}

boolean isIdxEff(ListPos l, int i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
{
    return (i > IDX_UNDEF && i < length(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListPos l)
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
{
    return (ELMTLS(l, 0) == VAL_UNDEF);
}

/* *** Test List penuh *** */
boolean isFull(ListPos l)
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
{
    return (ELMTLS(l, LSCAP - 1) != VAL_UNDEF);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListPos *l)
/* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= LSCAP */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= LSCAP; Lakukan n kali: 
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
{
    int n;
    int i;
    int x;

    do
    {
        scanf("%d", &n);
    } while (n < 0 || n > LSCAP);

    CreateListPos(l);
    if (n > 0)
    {
        for (i = 0; i < n; i++)
        {
            scanf("%d", &ELMTLS(*l, i));
        }
    }
}

void displayList(ListPos l)
/* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika List kosong : menulis [] */
{
    int i;

    if (isEmpty(l))
    {
        printf("[]");
    }
    else
    {
        printf("[");
        for (i = 0; i < length(l); i++)
        {
            if (i == 0)
            {
                printf("%d", ELMTLS(l, i));
            }
            else
            {
                printf(",%d", ELMTLS(l, i));
            }
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListPos plusMinusTab(ListPos l1, ListPos l2, boolean plus)
/* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
       indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
       elemen l2 pada indeks yang sama */
{
    ListPos l;

    CreateListPos(&l);
    if (plus)
    {
        int i;
        for (i = 0; i < length(l1); i++)
        {
            ELMTLS(l, i) = ELMTLS(l1, i) + ELMTLS(l2, i);
        }
    }
    else
    {
        int i;
        for (i = 0; i < length(l1); i++)
        {
            ELMTLS(l, i) = ELMTLS(l1, i) - ELMTLS(l2, i);
        }
    }
    return (l);
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListPos l1, ListPos l2)
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
   elemennya sama */
{
    int i;
    boolean isEqual = true;

    if (length(l1) == length(l2))
    {
        i = 0;
        while (i < length(l1) && isEqual)
        {
            if (ELMTLS(l1, i) == ELMTLS(l2, i))
            {
                i++;
            }
            else
            {
                isEqual = false;
            }
        }
    }
    else
    {
        isEqual = false;
    }
    return isEqual;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListPos l, ElType val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMTLS(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
/* Skema Searching yang digunakan bebas */
{
    int i = 0;
    boolean notFound = true;

    if (isEmpty(l))
    {
        return IDX_UNDEF;
    }
    else
    {
        while (i < length(l) && notFound)
        {
            if (ELMTLS(l, i) == val)
            {
                notFound = false;
            }
            else
            {
                i++;
            }
        }
        if (!notFound)
        {
            return i;
        }
        else
        {
            return IDX_UNDEF;
        }
    }
}

/* ********** NILAI EKSTREM ********** */
void extremes(ListPos l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. Max berisi nilai terbesar dalam l;
        Min berisi nilai terkecil dalam l */
{
    int i;
    *max = ELMTLS(l, 0);
    *min = ELMTLS(l, 0);

    for (i = 1; i < length(l); i++)
    {
        if (*max < ELMTLS(l, i))
        {
            *max = ELMTLS(l, i);
        }
        else if (*min > ELMTLS(l, i))
        {
            *min = ELMTLS(l, i);
        }
    }
}

/* ********** OPERASI LAIN ********** */
boolean isAllEven(ListPos l)
/* Menghailkan true jika semua elemen l genap */
{
    int i;
    boolean isEven = true;

    while (i < length(l) && isEven)
    {
        if (ELMTLS(l, i) % 2 != 0)
        {
            isEven = false;
        }
        else
        {
            i++;
        }
    }
    return isEven;
}

/* ********** SORTING ********** */
void sort(ListPos *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{
    int i, pass, temp, index;
    if (length(*l) > 1)
    {
        for (pass = 0; pass < length(*l); pass++)
        {
            index = pass;
            for (i = pass + 1; i < length(*l); i++)
            {
                if (asc)
                {

                    if (ELMTLS(*l, index) > ELMTLS(*l, i))
                    {
                        index = i;
                    }
                }
                else
                {
                    if (ELMTLS(*l, index) < ELMTLS(*l, i))
                    {
                        index = i;
                    }
                }
            }
            if (index != pass)
            {
                temp = ELMTLS(*l, index);
                ELMTLS(*l, index) = ELMTLS(*l, pass);
                ELMTLS(*l, pass) = temp;
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListPos *l, ElType val)
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
    ELMTLS(*l, length(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListPos *l, ElType *val)
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
{
    *val = ELMTLS(*l, length(*l) - 1);
    ELMTLS(*l, length(*l) - 1) = VAL_UNDEF;
}
