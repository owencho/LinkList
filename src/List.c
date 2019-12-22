#include "List.h"
#include <stdlib.h>
#include <stdio.h>
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
}

void resetCurrentListItem(List * node){
    node->current = node->head;
}

ListItem * getNextListItem(List * linkList){
    ListItem * returnPtr;
    if(linkList->current == NULL)
        return NULL;

    returnPtr = linkList->current;
    linkList->current = linkList->current->next;
    return returnPtr;

}

List* addListItem(List * linkList, ListItem * item ){
    item->next = NULL;
    if(linkList->head == NULL){
        linkList->head = item;
        linkList->current = item;
    }
    else{
        linkList->tail->next = item;
    }
    linkList->tail = item;
    linkList->count++;
    return linkList;
}

List* deleteListItem(List * linkList){
    ListItem * nextListItem;
    nextListItem = linkList->head->next;
    if(linkList->head ==NULL)
        return linkList;
    if(linkList->current == linkList->head)
        linkList->current = linkList->head->next;
    if(nextListItem == NULL)
        linkList->tail = NULL;
    linkList->head = nextListItem;
    linkList->count--;
    return linkList;
}
