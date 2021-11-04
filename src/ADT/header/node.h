#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "item.h"

typedef Item ElTypeNode;
typedef struct node* Address;
typedef struct node {
    ElTypeNode info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(ElTypeNode val);


#endif