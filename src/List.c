#include "List.h"
#include "LinkCompare.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

List *createList(void){
    List * list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->count = 0;
    list->previous = NULL;
    return list;
}

void resetCurrentListItem(List * linkList){
    linkList->current = linkList->head;
    linkList->previous = NULL;
}

ListItem * getCurrentListItem(List * linkList){
    return linkList->current;
}

ListItem * getNextListItem(List * linkList){
    ListItem * returnPtr;
    if(linkList->current == NULL){
        return NULL;
    }
    returnPtr = linkList->current;
    linkList->current = linkList->current->next;
    linkList->previous = returnPtr;
    return linkList->current;

}

List* listAddItemToTail(List * linkList, ListItem * item ){
    item->next = NULL;
    if(linkList->head == NULL){
        linkList->head = item;
        linkList->current = item;
        linkList->previous = NULL;
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
        linkList->previous = NULL;
    }
    else{
        if(linkList->current == linkList->head)
            linkList->previous = NULL;
        item->next = linkList->head;
        linkList->head = item;
    }
    linkList->count++;
    return linkList;
}

List* deleteHeadListItem(List * linkList){
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

List* deleteSelectedListItem(List * linkList,void  * listItemData,LinkListCompare compare){
    ListItem * nextListItem;
    int size;
    if(linkList->head ==NULL)
        return linkList;
    resetCurrentListItem(linkList);
    nextListItem = getCurrentListItem(linkList);
    while(nextListItem != NULL){
        size = compare(nextListItem,listItemData);
        if(size){
            linkList = checkAndDeleteListItem(linkList,nextListItem);
            break;
        }
        nextListItem = getNextListItem(linkList);
    }
    resetCurrentListItem(linkList);
    return linkList;
}

List* checkAndDeleteListItem(List * linkList,ListItem * deleteListItem){
    if(deleteListItem == linkList->head){
        linkList = deleteHeadListItem(linkList);
    }
    else if(deleteListItem == linkList->tail){
        linkList->tail = linkList->previous;
        linkList->tail->next = NULL;
        linkList->count--;
    }
    else{
        linkList->count--;
        linkList->previous->next = deleteListItem->next;
    }
    resetCurrentListItem(linkList);
    return linkList;
  }
