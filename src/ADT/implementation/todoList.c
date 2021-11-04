#include "../header/todoList.h"
#include "../header/tas.h"
#include "../header/item.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateListTodoList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmptyTodoList(List l)
/* Mengirim true jika list kosong */
{
    return (FIRST(l) == NULL);
}

/****************** GETTER SETTER ******************/
ElType getElmtTodoList(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    Address p;
    int counter = 0;
    p = FIRST(l);

    while (counter < idx)
    {
        counter++;
        p = NEXT(p);
    }
    // counter == idx
    return (INFO(p));
}

void setElmtTodoList(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    Address p;
    int counter = 0;
    p = FIRST(*l);

    while (counter < idx)
    {
        counter++;
        p = NEXT(p);
    }
    // counter == idx
    INFO(p) = val;
}

int indexOfTodoList(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    Address p;
    p = FIRST(l);
    int counter = 0;
    boolean found;

    found = false;
    while ((NEXT(p) != NULL) && !found)
    {
        if (INFO(p) == val)
        {
            found = true;
        }
        else
        {
            counter++;
            p = NEXT(p);
        }
    }
    if (found)
    {
        return (counter);
    }
    else
    {
        return (-1);
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstTodoList(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p;

    p = newNode(val);
    if (p != NULL)
    {
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLastTodoList(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    Address p, new;

    if (isEmpty(*l))
    {
        insertFirst(l, val);
    }
    else
    {
        new = newNode(val);
        if (new != NULL) // alokasi berhasil
        {
            p = FIRST(*l);
            while (NEXT(p) != NULL)
            {
                p = NEXT(p);
            }
            // NEXT(p) == NULL {artinya last element)}

            NEXT(p) = new;
        }
    }
}

void insertAtTodoList(List *l, ElType val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    Address new, p;
    int counter;

    if (idx == 0)
    {
        insertFirst(l, val);
    }
    else
    {
        new = newNode(val);
        if (new != NULL)
        {
            counter = 0;
            p = FIRST(*l);

            while (counter < idx - 1)
            {
                counter++;
                p = NEXT(p);
            }
            // counter == idx-1
            NEXT(new) = NEXT(p);
            NEXT(p) = new;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirstTodoList(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p;

    p = FIRST(*l);
    *val = INFO(p);
    FIRST(*l) = NEXT(p);
    free(p);
}

void deleteLastTodoList(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    Address p, loc;

    p = FIRST(*l);
    loc = NULL;

    while (NEXT(p) != NULL)
    {
        loc = p;
        p = NEXT(p);
    }
    // NEXT(p) == NULL (artinya last element)
    if (loc == NULL) // artinya cuman ada 1 elemen di list
    {
        FIRST(*l) = NULL;
    }
    else
    {
        NEXT(loc) = NULL;
    }
    *val = INFO(p);
    free(p);
}

void deleteAtTodoList(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    Address p, loc;
    int counter;

    if (idx == 0)
    {
        deleteFirst(l, val);
    }
    else
    {
        counter = 0;
        loc = FIRST(*l);

        while (counter < idx - 1)
        {
            counter++;
            loc = NEXT(loc);
        }
        p = NEXT(loc);
        *val = INFO(p);
        NEXT(loc) = NEXT(p);
        NEXT(p) = NULL;
        free(p);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayTodoList(List l)
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    Address p;

    p = FIRST(l);
    printf("[");
    while (NEXT(p) != NULL)
    {
        printf("%d,", INFO(p));
        p = NEXT(p);
    }
    printf("%d]", INFO(p));
}

int lengthTodoList(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    Address p;
    int count = 0;
    p = FIRST(l);

    while (p != NULL)
    {
        count++;
        p = NEXT(p);
    }
    return count;
}

Item getItemAtLoc(List l, char loc, Tas tas)
{
}