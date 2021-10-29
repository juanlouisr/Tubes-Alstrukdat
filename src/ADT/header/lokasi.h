#ifndef LOKASI_H
#define LOKASI_H

#include "boolean.h"

typedef struct {
   char Nama; /* Nama bangunan */ 
   int X; /* absis   */
   int Y; /* ordinat */
   char jenis;
} LOKASI;

/* *** Notasi Akses: Selektor LOKASI *** */
#define NAMA(P) (P).Nama
#define Absis(P) (P).X
#define Ordinat(P) (P).Y
#define Type(P) (P).jenis
        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk LOKASI *** */
LOKASI MakeLOKASI (char Nama, int X, int Y, char tipe);
/* Membentuk sebuah LOKASI dari komponen-komponennya */

void TulisLOKASI (LOKASI P);
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */                

/* *** Kelompok operasi relasional terhadap LOKASI *** */
boolean EQ (LOKASI P1, LOKASI P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean NEQ (LOKASI P1, LOKASI P2);
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
LOKASI NextX (LOKASI P);
/* Mengirim salinan P dengan absis ditambah satu */              
LOKASI NextY (LOKASI P);
/* Mengirim salinan P dengan ordinat ditambah satu */
LOKASI PlusDelta (LOKASI P, float deltaX, float deltaY);
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */

void Geser (LOKASI *P, float deltaX, float deltaY);
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void GeserKeSbX (LOKASI *P);
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbY (LOKASI *P);
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */



#endif

