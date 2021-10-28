
#include <stdio.h>
#include "../header/queue.h"

/* *** Kreator *** */
void CreateQueue(Queue *q)
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah q kosong */
{
    IDX_HEAD(*q) = IDX_UNDEF;
    IDX_TAIL(*q) = IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean isEmptyQ(Queue q)
/* Mengirim true jika q kosong: lihat definisi di atas */
{
    return (IDX_HEAD(q) == IDX_UNDEF && IDX_TAIL(q) == IDX_UNDEF);
}

boolean isFullQ(Queue q)
/* Mengirim true jika tabel penampung elemen q sudah penuh */
/* yaitu jika index head bernilai 0 dan index tail bernilai QUEUECAP-1 */
{
    return (IDX_HEAD(q) == 0 && IDX_TAIL(q) == (QUEUECAP - 1));
}

int lengthQ(Queue q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong. */
{
    return (isEmptyQ(q) ? 0 : (IDX_TAIL(q) - IDX_HEAD(q)) + 1);
}

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, Item val)
/* Proses: Menambahkan val pada q dengan aturan FIFO */
/* I.S. q mungkin kosong, tabel penampung elemen q TIDAK penuh */
/* F.S. val menjadi TAIL yang baru, IDX_TAIL "mundur".
        Jika q penuh semu, maka perlu dilakukan aksi penggeseran "maju" elemen-elemen q
        menjadi rata kiri untuk membuat ruang kosong bagi TAIL baru  */
{
    if (isEmptyQ(*q))
    {
        IDX_HEAD(*q) = 0;
        IDX_TAIL(*q) = 0;
    }
    else
    {
        if (IDX_TAIL(*q) == QUEUECAP - 1)
        {
            int i;
            for (i = IDX_HEAD(*q); i <= IDX_TAIL(*q); i++)
            {
                ((*q).buffer[i - IDX_HEAD(*q)]) = (*q).buffer[i];
            }
            IDX_TAIL(*q) -= IDX_HEAD(*q);
            IDX_HEAD(*q) = 0;
        }
        IDX_TAIL(*q) += 1;
    }
    TAIL(*q) = val;
}

void dequeue(Queue *q, Item *val)
/* Proses: Menghapus val pada q dengan aturan FIFO */
/* I.S. q tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., HEAD dan IDX_HEAD "mundur"; 
        q mungkin kosong */
{
    *val = HEAD(*q);

    // More than one element
    if (IDX_HEAD(*q) != IDX_TAIL(*q))
    {
        IDX_HEAD(*q) += 1;
    }
    else //just one element
    {
        IDX_HEAD(*q) = IDX_UNDEF;
        IDX_TAIL(*q) = IDX_UNDEF;
    }
}

/* *** Display Queue *** */
void displayQueue(Queue q)
/* Proses : Menuliskan isi Queue dengan traversal, Queue ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */
{
    if (isEmptyQ(q))
    {
        printf("[]");
    }
    else
    {
        int i;
        printf("[");
        for (i = IDX_HEAD(q); i <= IDX_TAIL(q); i++)
        {
            printf("%d", (q).buffer[i].waktudatang);
            if (i == IDX_TAIL(q))
            {
                printf("]");
            }
            else
            {
                printf(",");
            }
        }
    }
}

void readAllItem(Queue *q, FILE *file)
{
    int count = getIntInputStream(file);
    Item item;
    for (int i = 0; i < count; i++)
    {
        readItem(&item, file);
        enqueue(q, item);
    }
    sortQueue(q);
}

// Sort queue berdasarkan waktu masuk (kyk prioqueue)
void sortQueue(Queue *q)
{
    int i = 0;  
    int j = 0;
    int n= IDX_HEAD(*q) + lengthQ(*q);
    for (i = IDX_HEAD(*q); i < n-1; i++) {
        for (j = IDX_HEAD(*q); j < n-i-1; j++) {
            if ( (*q).buffer[j].waktudatang > (*q).buffer[j+1].waktudatang) {
                Item temp = (*q).buffer[j];
                (*q).buffer[j] = (*q).buffer[j+1];
                (*q).buffer[j+1] = temp;
            }
        }
    }
}