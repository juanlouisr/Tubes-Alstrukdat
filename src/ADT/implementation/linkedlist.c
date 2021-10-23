#include "../header/linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create linked list to do list */
void CreateToDoList(LinkedList* head)
/* I.S. Head sembarang */
/* membuat todolist kosong dengan next null
dan curr adalah value dummy */
{
    Item item;
    ToDoVal(*head) = item;
    ToDoNext(*head) = NULL;
}

/* ********** OPERASI ********** */
void PrintToDoList(LinkedList head)
/* I.S. head tidak null */
/* menoutput to do list, output dimulai dari head->next */
{

    LinkedList *current = ToDoNext(head);
    int count = 0;
    while (current != NULL) 
    {
        printf("%d. ", ++count);
        PrintItem(ToDoVal(*current));
        printf("\n");
        current = ToDoNext(*current);
    }
}

void InsertToDoList(LinkedList* head, Item item)
/* I.S. head tidak null, item terdefinisi */
/* menempatkan sembarang item ke dalam todo list */
{
    if (IsToDoEmpty(*head))
    {
        head->next = (LinkedList*) malloc(sizeof(LinkedList));
        head->next->val = item;
        head->next->next = NULL;

    }
    else
    {
        LinkedList* temp = ToDoNext(*head);
        head->next = (LinkedList*) malloc(sizeof(LinkedList));
        head->next->val = item;
        head->next->next = temp;
    }
}

void DeleteToDoList(LinkedList* head, Item item)
/* I.S. head tidak null */
/* menghapus item yang sama dari to do list */ 
{
    LinkedList *current = ToDoNext(*head);
    LinkedList *prev = head;
    boolean found = false;
    while (current != NULL && !found) 
    {
        if (IsItemSama(current->val, item))
        {
            found = true;
            prev->next = ToDoNext(*current);
            free(current);

        }
        prev = current;
        current = ToDoNext(*current);
    }

}

void DeleteAllToDo(LinkedList* head)
/* menghapus seluruh hasil malloc */
/* head tidak null */
{
    LinkedList *current = head->next;
    LinkedList *next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

boolean IsToDoEmpty(LinkedList head)
/* I.S. head tidak null */
/* return true jika head->next = NULL */ 
{
    return head.next == NULL;
}

// Test Linked List
// int main(int argc, char const *argv[])
// {
//     LinkedList ll;
//     Item item, item1, item2;
//     CreateToDoList(&ll);
//     CreateItemPesanan(&item, 'N', 'A', 'B', 2, 0);
//     CreateItemPesanan(&item1, 'N', 'A', 'D', 2, 0);
//     CreateItemPesanan(&item2, 'V', 'E', 'F', 2, 0);

//     PrintToDoList(ll);
//     InsertToDoList(&ll, item);
//     InsertToDoList(&ll, item1);
//     PrintToDoList(ll);
//     DeleteToDoList(&ll, item);
//     PrintToDoList(ll);
//     InsertToDoList(&ll, item2);
//     PrintToDoList(ll);


//     return 0;
// }
