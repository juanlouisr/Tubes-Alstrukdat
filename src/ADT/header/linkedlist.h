#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include "item.h"
#include "boolean.h"
#define NULL ((void *)0)

/* Definisi elemen dan koleksi objek */
typedef struct LinkedList
{
    Item val;
    struct LinkedList *next; 

} LinkedList;

/* ********** SELEKTOR ********** */
#define ToDoVal(linlis) (linlis).val
#define ToDoNext(linlis) (linlis).next

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create linked list to do list */
void CreateToDoList(LinkedList* head);
/* I.S. Head sembarang */
/* membuat todolist kosong dengan next null
dan curr adalah value dummy */


/* ********** OPERASI ********** */
void PrintToDoList(LinkedList head);
/* I.S. head tidak null */
/* menoutput to do list, output dimulai dari head->next */

void InsertToDoList(LinkedList* head, Item item);
/* I.S. head tidak null */
/* menempatkan sembarang item ke dalam todo list */

void DeleteToDoList(LinkedList* head, Item item);
/* I.S. head tidak null */
/* menghapus item yang sama dari to do list */ 

void DeleteAllToDo(LinkedList* head);
/* menghapus seluruh hasil malloc */
/* head tidak null */

boolean IsToDoEmpty(LinkedList head);
/* I.S. head tidak null */
/* return true jika head->next = NULL */ 


#endif