#include "../header/point.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT(char N, float X, float Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
    POINT P;
    Name(P) = N;
    Absis(P) = X;
    Ordinat(P) = Y;
    return (P);
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT(POINT *P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
    char n;
    float x, y;
    scanf("%c", &n);
    scanf("%f", &x);
    scanf("%f", &y);
    *P = MakePOINT(n, x, y);
}

void TulisPOINT(POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
    printf("%c (%.2f,%.2f)", Name(P), Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ(POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ(POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
    return (!EQ(P1, P2));
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin(POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
    return ((Absis(P) == 0) && (Ordinat(P) == 0));
}

boolean IsOnSbX(POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
    return (Ordinat(P) == 0);
}

boolean IsOnSbY(POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
    return (Absis(P) == 0);
}

int Kuadran(POINT P)
{
    if (Absis(P) > 0)
    {
        if (Ordinat(P) > 0)
        {
            return 1;
        }
        else /* Ordinat(P) < 0 */
        {
            return 4;
        }
    }
    else /* Absis(P) < 0 */
    {
        if (Ordinat(P) > 0)
        {
            return 2;
        }
        else /* Ordinat(P) < 0 */
        {
            return 3;
        }
    }
}

