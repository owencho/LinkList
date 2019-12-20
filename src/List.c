#include "List.h"
#include <stdlib.h>
#include <stdio.h>
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
}

void resetList(List * node){
    node->current = node->head;
}

void * getNextListItem(List * node){
    void * returnPtr;
    if(node->current == NULL)
        return NULL;

    returnPtr = node->current->data;
    node->current = node->current->next;
    return returnPtr;

}
