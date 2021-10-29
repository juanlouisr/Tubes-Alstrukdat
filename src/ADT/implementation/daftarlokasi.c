#include <stdio.h>
#include <stdlib.h>
#include "../header/DaftarLokasi.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateDaftarLokasi(DaftarLokasi *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
{
    BUFFER(*l) = (ElTypeDL *)malloc(capacity * sizeof(ElTypeDL));
    NEFF(*l) = 0;
    CAPACITY(*l) = capacity;
}

void dealocateDL(DaftarLokasi *l)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
{
    free(BUFFER(*l));
    CAPACITY(*l) = 0;
    NEFF(*l) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(DaftarLokasi l)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
{
    return NEFF(l);
}

/* *** Daya tampung container *** */
/* *** Selektor INDEKS *** */
IdxType getLastIdx(DaftarLokasi l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
    return (NEFF(l) - 1);
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(DaftarLokasi l, int i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IDX_UNDEF < i && i < CAPACITY(l));
}

boolean isIdxEff(DaftarLokasi l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */
{
    return (IDX_UNDEF < i && i < NEFF(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(DaftarLokasi l)
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
{
    return (length(l) == 0);
}

/* *** Test list penuh *** */
boolean isFull(DaftarLokasi l)
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
{
    return (length(l) == CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(DaftarLokasi *l)
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
{
    int n;
    do
    {
        scanf("%d", &n);
    } while (n > CAPACITY(*l) || n < 0);

    if (n > 0)
    {
        IdxType i;

        NEFF(*l) = n;
        for (i = 0; i < n; i++)
        {
            scanf("%d", &ELMTLD(*l, i));
        }
    }
    else
    {
        NEFF(*l) = 0;
    }
}

void displayList(DaftarLokasi l)
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
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
                printf("%d", ELMTLD(l, i));
            }
            else
            {
                printf(",%d", ELMTLD(l, i));
            }
        }
        printf("]");
    }
}


/* ********** OPERASI LAIN ********** */
void copyList(DaftarLokasi lIn, DaftarLokasi *lOut)
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
{
    CreateDaftarLokasi(lOut, CAPACITY(lIn));
    int i;
    NEFF(*lOut) = NEFF(lIn);
    CAPACITY(*lOut) = CAPACITY(lIn);

    for (i = 0; i < length(lIn); i++)
    {
        ELMTLD(*lOut, i) = ELMTLD(lIn, i);
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(DaftarLokasi *l, ElTypeDL val)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
    ELMTLD(*l, length(*l)) = val;
    NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(DaftarLokasi *l, ElTypeDL *val)
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
{
    *val = ELMTLD(*l, (length(*l) - 1));
    NEFF(*l) -= 1;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growList(DaftarLokasi *l, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
{
    CAPACITY(*l) += num;
}

void shrinkList(DaftarLokasi *l, int num)
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
{
    CAPACITY(*l) -= num;
}

void compactList(DaftarLokasi *l)
/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List lidak kosong */
/* F.S. Ukuran nEff = capacity */
{
    CAPACITY(*l) = NEFF(*l);
}


