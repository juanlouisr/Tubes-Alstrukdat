
#include <stdio.h>
#include "../header/matrix.h"
#include "boolean.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void CreateMatrix(int nRow, int nCol, Matrix *m)
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
{
   ROWS(*m) = nRow;
   COLS(*m) = nCol;
}

/* *** Selektor "DUNIA Matrix" *** */
boolean isIdxValid(int i, int j)
/* Mengirimkan true jika i, j adalah Index yang valid untuk matriks apa pun */
{
   return ((i >= 0 && i < ROW_CAP) && (j >= 0 && j < COL_CAP));
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
Index getLastIdxRow(Matrix m)
/* Mengirimkan Index baris terbesar m */
{
   return (ROWS(m) - 1);
}

Index getLastIdxCol(Matrix m)
/* Mengirimkan Index kolom terbesar m */
{
   return (COLS(m) - 1);
}

boolean isIdxEff(Matrix m, Index i, Index j)
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
{
   return ((i >= 0 && i < ROWS(m)) && (j >= 0 && j < COLS(m)));
}

ElType getElmtDiagonal(Matrix m, Index i)
/* Mengirimkan elemen m(i,i) */
{
   return (ELMT(m, i, i));
}

/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mRes)
/* Melakukan assignment MRes = MIn */
{
   CreateMatrix(ROWS(mIn), COLS(mIn), mRes);

   int i, j;
   for (i = 0; i < ROWS(mIn); i++)
   {
      for (j = 0; j < COLS(mIn); j++)
      {
         ELMT(*mRes, i, j) = ELMT(mIn, i, j);
      }
   }
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol)
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
   CreateMatrix(nRow, nCol, m);
   int i, j;
   for (i = 0; i < nRow; i++)
   {
      for (j = 0; j < nCol; j++)
      {
         scanf("%d", &ELMT(*m, i, j));
      }
   }
}

void displayMatrix(Matrix m)
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: Menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
   int i, j;
   for (i = 0; i < ROWS(m); i++)
   {
      for (j = 0; j < COLS(m); j++)
      {
         printf("%d", ELMT(m, i, j));
         if (j < getLastIdxCol(m))
         {
            printf(" ");
         }
      }
      if (i < getLastIdxRow(m))
      {
         printf("\n");
      }
   }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil penjumlahan matriks: m1 + m2 */
{
   Matrix m;
   CreateMatrix(ROWS(m1), COLS(m1), &m);

   int i, j;
   for (i = 0; i < ROWS(m1); i++)
   {
      for (j = 0; j < COLS(m1); j++)
      {
         ELMT(m, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
      }
   }
   return m;
}

Matrix subtractMatrix(Matrix m1, Matrix m2)
/* Prekondisi : m1 berukuran sama dengan m2 */
/* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
{
   Matrix m;
   CreateMatrix(ROWS(m1), COLS(m1), &m);

   int i, j;
   for (i = 0; i < ROWS(m1); i++)
   {
      for (j = 0; j < COLS(m1); j++)
      {
         ELMT(m, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
      }
   }
   return m;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2)
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan m1 * m2 */
{
   Matrix m;
   CreateMatrix(ROWS(m1), COLS(m2), &m);

   int i, j, k;
   for (i = 0; i < ROWS(m1); i++)
   {
      for (j = 0; j < COLS(m2); j++)
      {
         ELMT(m, i, j) = 0;
         for (k = 0; k < ROWS(m2); k++)
         {
            ELMT(m, i, j) += ELMT(m1, i, k) * ELMT(m2, k, j);
         }
      }
   }
   return m;
}

Matrix multiplyConst(Matrix m, ElType x)
/* Mengirim hasil perkalian setiap elemen m dengan x */
{
   Matrix mRes;
   CreateMatrix(ROWS(m), COLS(m), &mRes);

   int i, j;
   for (i = 0; i < ROWS(m); i++)
   {
      for (j = 0; j < COLS(m); j++)
      {
         ELMT(mRes, i, j) = x * ELMT(m, i, j);
      }
   }
   return mRes;
}

void pMultiplyConst(Matrix *m, ElType k)
/* I.S. m terdefinisi, k terdefinisi */
/* F.S. Mengalikan setiap elemen m dengan k */
{
   int i, j;
   for (i = 0; i < ROWS(*m); i++)
   {
      for (j = 0; j < COLS(*m); j++)
      {
         ELMT(*m, i, j) = k * ELMT(*m, i, j);
      }
   }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
{
   boolean equal = true;

   if (count(m1) == count(m2))
   {
      int i, j;
      i = 0;
      while ((i < ROWS(m1)) && equal)
      {
         j = 0;
         while ((j < COLS(m1)) && equal)
         {
            if (ELMT(m1, i, j) != ELMT(m2, i, j))
            {
               equal = false;
            }
            else
            {
               j++;
            }
         }
         i++;
      }
   }
   else
   {
      equal = false;
   }
   return equal;
}

boolean isNotEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika m1 tidak sama dengan m2 */
{
   return (!isEqual(m1, m2));
}

boolean isSizeEqual(Matrix m1, Matrix m2)
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
{
   return ((ROWS(m1) == ROWS(m2)) && (COLS(m1) == COLS(m2)));
}

/* ********** Operasi lain ********** */
int count(Matrix m)
/* Mengirimkan banyaknya elemen m */
{
   return (ROWS(m) * COLS(m));
}

/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m)
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
{
   return (ROWS(m) == COLS(m));
}

boolean isSymmetric(Matrix m)
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
{
   boolean symmetric = true;

   if (isSquare(m))
   {
      int i, j;
      i = 0;
      while ((i < ROWS(m)) && symmetric)
      {
         j = 0;
         while ((j < COLS(m)) && symmetric)
         {
            if (ELMT(m, i, j) != ELMT(m, j, i))
            {
               symmetric = false;
            }
            else
            {
               j++;
            }
         }
         i++;
      }
   }
   else
   {
      symmetric = false;
   }
   return symmetric;
}

boolean isIdentity(Matrix m)
/* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
   setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
   boolean identity = true;

   if (isSquare(m))
   {
      int i, j;
      i = 0;
      while ((i < ROWS(m)) && identity)
      {
         j = 0;
         while ((j < COLS(m)) && identity)
         {
            if (i == j)
            {
               if (getElmtDiagonal(m, i) != 1)
               {
                  identity = false;
               }
            }
            else
            {
               if (ELMT(m, i, j) != 0)
               {
                  identity = false;
               }
            }
            j++;
         }
         i++;
      }
   }
   else
   {
      identity = false;
   }
   return identity;
}

boolean isSparse(Matrix m)
/* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
   int i, j;
   int counter = 0;

   for (i = 0; i < ROWS(m); i++)
   {
      for (j = 0; j < COLS(m); j++)
      {
         if (ELMT(m, i, j) != 0)
         {
            counter += 1;
         }
      }
   }
   return (counter <= (0.05 * (count(m))));
}

Matrix inverse1(Matrix m)
/* Menghasilkan salinan m dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
   return (multiplyConst(m, -1));
}

void pInverse1(Matrix *m)
/* I.S. m terdefinisi */
/* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
   pMultiplyConst(m, -1);
}

float determinant(Matrix m)
/* Prekondisi: isSquare(m) */
/* Menghitung nilai determinan m */
{
   float det;
   if (ROWS(m) == 1)
   {
      det = ELMT(m, 0, 0);
   }
   else
   {
      det = 0;
      int i;
      for (i = 0; i < ROWS(m); i++)
      {
         Matrix matMinor;

         CreateMatrix(ROWS(m) - 1, COLS(m) - 1, &matMinor);
         int iMat, jMat, iMatMinor, jMatMinor;

         iMatMinor = 0;
         for (iMat = 0; iMat < ROWS(m); iMat++)
         {
            if (iMat != i)
            {
               jMatMinor = 0;
               for (jMat = 1; jMat < COLS(m); jMat++)
               {
                  if (jMat != 0)
                  {
                     ELMT(matMinor, iMatMinor, jMatMinor) = ELMT(m, iMat, jMat);
                     jMatMinor++;
                  }
               }
               iMatMinor++;
            }
         }
         det += (i % 2 == 0 ? 1 : -1) * ELMT(m, i, 0) * determinant(matMinor);
      }
   }
   return det;
}

void transpose(Matrix *m)
/* I.S. m terdefinisi dan isSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
{
   Matrix tempMat;
   CreateMatrix(ROWS(*m), COLS(*m), &tempMat);
   copyMatrix(*m, &tempMat);

   int i, j;
   for (i = 0; i < ROWS(*m); i++)
   {
      for (j = 0; j < COLS(*m); j++)
      {
         ELMT(*m, i, j) = ELMT(tempMat, j, i);
      }
   }
}