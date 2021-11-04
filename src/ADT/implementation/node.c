/* File: node.c */
/* Implementasi Node */

#include "../header/node.h"
#include <stdlib.h>

Address newNode(ElTypeNode val)
{
    Address p = (Address)malloc(sizeof(Node));
    if (p != NULL)
    {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}