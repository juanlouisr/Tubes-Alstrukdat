#include "../header/listdin.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
{
    BUFFER(*l) = (ElType *)malloc(capacity * sizeof(ElType));
    NEFF(*l) = 0;
    CAPACITY(*l) = capacity;
}

void dealocate(ListDin *l)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
{
    free(BUFFER(*l));
    CAPACITY(*l) = 0;
    NEFF(*l) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListDin l)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
{
    return NEFF(l);
}

/* *** Daya tampung container *** */
/* *** Selektor INDEKS *** */
IdxType getLastIdx(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
    return (NEFF(l) - 1);
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, int i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IDX_UNDEF < i && i < CAPACITY(l));
}

boolean isIdxEff(ListDin l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */
{
    return (IDX_UNDEF < i && i < NEFF(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l)
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
{
    return (length(l) == 0);
}

/* *** Test list penuh *** */
boolean isFull(ListDin l)
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
{
    return (length(l) == CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l)
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

void displayList(ListDin l)
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

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus)
/* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
{
    ListDin l;

    CreateListDin(&l, CAPACITY(l1));
    NEFF(l) = NEFF(l1);
    int i;

    if (plus)
    {
        for (i = 0; i < length(l1); i++)
        {
            ELMTLD(l, i) = ELMTLD(l1, i) + ELMTLD(l2, i);
        }
    }
    else
    {
        for (i = 0; i < length(l1); i++)
        {
            ELMTLD(l, i) = ELMTLD(l1, i) - ELMTLD(l2, i);
        }
    }
    return (l);
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2)
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
{
    int i;
    boolean isEqual = true;

    if (length(l1) == length(l2))
    {
        i = 0;
        while (i < length(l1) && isEqual)
        {
            if (ELMTLD(l1, i) == ELMTLD(l2, i))
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
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val)
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
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
            if (ELMTLD(l, i) == val)
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
void extremes(ListDin l, ElType *max, ElType *min)
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */
{
    int i;
    *max = ELMTLD(l, 0);
    *min = ELMTLD(l, 0);

    for (i = 1; i < length(l); i++)
    {
        if (*max < ELMTLD(l, i))
        {
            *max = ELMTLD(l, i);
        }
        else if (*min > ELMTLD(l, i))
        {
            *min = ELMTLD(l, i);
        }
    }
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut)
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
{
    CreateListDin(lOut, CAPACITY(lIn));
    int i;
    NEFF(*lOut) = NEFF(lIn);
    CAPACITY(*lOut) = CAPACITY(lIn);

    for (i = 0; i < length(lIn); i++)
    {
        ELMTLD(*lOut, i) = ELMTLD(lIn, i);
    }
}

ElType sumList(ListDin l)
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
{
    int i;
    ElType sum = 0;

    for (i = 0; i < length(l); i++)
    {
        sum += ELMTLD(l, i);
    }
    return sum;
}

int countVal(ListDin l, ElType val)
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
{
    int i;
    int count = 0;

    for (i = 0; i < length(l); i++)
    {
        if (ELMTLD(l, i) == val)
        {
            count += 1;
        }
    }
    return count;
}

boolean isAllEven(ListDin l)
/* Menghailkan true jika semua elemen l genap. l boleh kosong */
{
    int i = 0;
    boolean isEven = true;

    while (i < length(l) && isEven)
    {
        if (ELMTLD(l, i) % 2 != 0)
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
void sort(ListDin *l, boolean asc)
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

                    if (ELMTLD(*l, index) > ELMTLD(*l, i))
                    {
                        index = i;
                    }
                }
                else
                {
                    if (ELMTLD(*l, index) < ELMTLD(*l, i))
                    {
                        index = i;
                    }
                }
            }
            if (index != pass)
            {
                temp = ELMTLD(*l, index);
                ELMTLD(*l, index) = ELMTLD(*l, pass);
                ELMTLD(*l, pass) = temp;
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElType val)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
    ELMTLD(*l, length(*l)) = val;
    NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElType *val)
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
void growList(ListDin *l, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
{
    CAPACITY(*l) += num;
}

void shrinkList(ListDin *l, int num)
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
{
    CAPACITY(*l) -= num;
}

void compactList(ListDin *l)
/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List lidak kosong */
/* F.S. Ukuran nEff = capacity */
{
    CAPACITY(*l) = NEFF(*l);
}
