#include "../header/lokasi.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk LOKASI *** */
LOKASI MakeLOKASI(char Nama, int X, int Y, char tipe)
/* Membentuk sebuah LOKASI dari komponen-komponennya */
{
    LOKASI P;
    NAMA(P) = Nama;
    Absis(P) = X;
    Ordinat(P) = Y;
    Type(P) = tipe;
    return P;
}

void TulisLOKASI(LOKASI P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
    printf("%c (%d,%d)\n",NAMA(P), Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap LOKASI *** */
boolean EQ(LOKASI P1, LOKASI P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ(LOKASI P1, LOKASI P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
    return (!EQ(P1, P2));
}






