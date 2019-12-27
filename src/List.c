#include "List.h"
#include <stdlib.h>
#include <stdio.h>


void resetCurrentListItem(List * linkList){
    linkList->current = linkList->head;
}

ListItem * getNextListItem(List * linkList){
    ListItem * returnPtr;
    if(linkList->current == NULL)
        return NULL;

    returnPtr = linkList->current;
    linkList->current = linkList->current->next;
    return returnPtr;

}

List* listAddItemToTail(List * linkList, ListItem * item ){
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

List* listAddItemToHead(List * linkList, ListItem * item ){
    item->next = NULL;
    if(linkList->head == NULL){
        linkList->head = item;
        linkList->current = item;
        linkList->tail = item;
    }
    else{
        item->next = linkList->head;
        linkList->head = item;
    }
    linkList->count++;
    return linkList;
}

List* deleteListItem(List * linkList){
    ListItem * nextListItem;
    if(linkList->head ==NULL)
        return linkList;
    nextListItem = linkList->head->next;
    if(linkList->current == linkList->head)  //if current is point to head
        linkList->current = nextListItem;   // also change current as the head is deleted
    if(nextListItem == NULL)
        linkList->tail = NULL;             // if last item deleted , the tail also points to NULL
    linkList->head = nextListItem;
    linkList->count--;
    return linkList;
}
