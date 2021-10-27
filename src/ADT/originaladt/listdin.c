#include "listdin.h"
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
int lengthListDin(ListDin l)
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
{
    return NEFF(l);
}

/* *** Daya tampung container *** */
/* *** Selektor INDEKS *** */
IdxType getLastIdxListDin(ListDin l)
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
{
    return (NEFF(l) - 1);
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListDin(ListDin l, int i)
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IDX_UNDEF < i && i < CAPACITY(l));
}

boolean isIdxEffListDin(ListDin l, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */
{
    return (IDX_UNDEF < i && i < NEFF(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmptyListDin(ListDin l)
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
{
    return (lengthListDin(l) == 0);
}

/* *** Test list penuh *** */
boolean isFullListDin(ListDin l)
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
{
    return (lengthListDin(l) == CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readListDin(ListDin *l)
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

void displayListDin(ListDin l)
{
    int i;

    if (isEmptyListDin(l))
    {
        printf("[]");
    }
    else
    {
        printf("[");
        for (i = 0; i < lengthListDin(l); i++)
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
ListDin plusMinusListDin(ListDin l1, ListDin l2, boolean plus)
{
    ListDin l;

    CreateListDin(&l, CAPACITY(l1));
    NEFF(l) = NEFF(l1);
    int i;

    if (plus)
    {
        for (i = 0; i < lengthListDin(l1); i++)
        {
            ELMTLD(l, i) = ELMTLD(l1, i) + ELMTLD(l2, i);
        }
    }
    else
    {
        for (i = 0; i < lengthListDin(l1); i++)
        {
            ELMTLD(l, i) = ELMTLD(l1, i) - ELMTLD(l2, i);
        }
    }
    return (l);
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListDinEqual(ListDin l1, ListDin l2)
{
    int i;
    boolean isEqual = true;

    if (lengthListDin(l1) == lengthListDin(l2))
    {
        i = 0;
        while (i < lengthListDin(l1) && isEqual)
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
IdxType indexOfListDin(ListDin l, ElType val)
{
    int i = 0;
    boolean notFound = true;

    if (isEmptyListDin(l))
    {
        return IDX_UNDEF;
    }
    else
    {
        while (i < lengthListDin(l) && notFound)
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
{
    int i;
    *max = ELMTLD(l, 0);
    *min = ELMTLD(l, 0);

    for (i = 1; i < lengthListDin(l); i++)
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
void copyListDin(ListDin lIn, ListDin *lOut)
{
    CreateListDin(lOut, CAPACITY(lIn));
    int i;
    NEFF(*lOut) = NEFF(lIn);
    CAPACITY(*lOut) = CAPACITY(lIn);

    for (i = 0; i < lengthListDin(lIn); i++)
    {
        ELMTLD(*lOut, i) = ELMTLD(lIn, i);
    }
}

ElType sumListDin(ListDin l)
{
    int i;
    ElType sum = 0;

    for (i = 0; i < lengthListDin(l); i++)
    {
        sum += ELMTLD(l, i);
    }
    return sum;
}

int countValListDin(ListDin l, ElType val)
{
    int i;
    int count = 0;

    for (i = 0; i < lengthListDin(l); i++)
    {
        if (ELMTLD(l, i) == val)
        {
            count += 1;
        }
    }
    return count;
}

boolean isAllEvenListDin(ListDin l)
/* Menghailkan true jika semua elemen l genap. l boleh kosong */
{
    int i = 0;
    boolean isEven = true;

    while (i < lengthListDin(l) && isEven)
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
void sortListDin(ListDin *l, boolean asc)
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
{
    int i, pass, temp, index;
    if (lengthListDin(*l) > 1)
    {
        for (pass = 0; pass < lengthListDin(*l); pass++)
        {
            index = pass;
            for (i = pass + 1; i < lengthListDin(*l); i++)
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
void insertLastListDin(ListDin *l, ElType val)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
    ELMTLD(*l, lengthListDin(*l)) = val;
    NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLastListDin(ListDin *l, ElType *val)
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
{
    *val = ELMTLD(*l, (lengthListDin(*l) - 1));
    NEFF(*l) -= 1;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growListDin(ListDin *l, int num)
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
{
    CAPACITY(*l) += num;
}

void shrinkListDin(ListDin *l, int num)
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
{
    CAPACITY(*l) -= num;
}

void compactListDin(ListDin *l)
/* Proses : Mengurangi capacity sehingga nEff = capacity */
/* I.S. List lidak kosong */
/* F.S. Ukuran nEff = capacity */
{
    CAPACITY(*l) = NEFF(*l);
}
