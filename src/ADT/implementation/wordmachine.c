#include <stdio.h>
#include "../header/wordmachine.h"

boolean endWord;
Word currentWord;

void ignoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang 
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */
{
    while (currentChar == BLANK)
    {
        adv();
    }
}

void startWord(FILE* file)
/* I.S. : currentChar sembarang 
   F.S. : endWord = true, dan currentChar = MARK; 
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
{
    start(file);
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        endWord = false;
        copyWord();
    }
}

void advWord()
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi 
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi, 
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.		  
   Proses : Akuisisi kata menggunakan procedure copyWord */
{
    ignoreBlank();
    if (currentChar == MARK)
    {
        endWord = true;
    }
    else
    {
        copyWord();
        ignoreBlank();
    }
}

void copyWord()
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi; 
          currentChar = BLANK atau currentChar = MARK; 
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi CAPACITY, maka sisa kata terpotong */
{
    int i;

    i = 0;
    while (currentChar != MARK && currentChar != BLANK)
    {
        if (i < WORDCAP)
        {
            currentWord.contents[i] = currentChar;
            i++;
        }
        adv();
    }
    currentWord.length = i;
}

int getStrLength(const char* str)
/* mengembalikan panjang str, mengembalikan
   0 jika string kosong */
{
    int size = 0;
    while (*str)
    {
        size++;
        str++;
    }
    return size;
} 

boolean isWordEQ(Word word, const char* str)
/* mengembalikan true jika kata dengan string sama
   0 jika string kosong */
{
    if (word.length != getStrLength(str))
    {
        return false;
    }
    else
    {
        int i = word.length;
        boolean equal = true;
        while (i && equal) 
        {
            if (word.contents[i-1] != str[i-1])
            {
                equal = false;
            }
            i--;
        }
        return equal;
    }
}

void wordToStr(Word word, char* str)
{
    for (int i = 0; i < word.length; i++)
    {
        str[i] = word.contents[i];
    }
    str[word.length] = '\0';
}
