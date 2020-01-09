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

void resetCurrentListItem(List * linkedList){
    linkedList->current = linkedList->head;
    linkedList->previous = NULL;
}

ListItem * getCurrentListItem(List * linkedList){
    return linkedList->current;
}

ListItem * getNextListItem(List * linkedList){
    ListItem * returnPtr;
    if(linkedList->current == NULL){
        return NULL;
    }
    returnPtr = linkedList->current;
    linkedList->current = linkedList->current->next;
    linkedList->previous = returnPtr;
    return linkedList->current;

}

List* listAddItemToTail(List * linkedList, void * data ){
    ListItem * listItem = (ListItem *)malloc(sizeof(ListItem));
    listItem->next = NULL;
    listItem->data = data;
    if(linkedList->head == NULL){
        linkedList->head = listItem;
        linkedList->current = listItem;
        linkedList->previous = NULL;
    }
    else{
        linkedList->tail->next = listItem;
    }
    linkedList->tail = listItem;
    linkedList->count++;
    resetCurrentListItem(linkedList);
    return linkedList;
}

List* listAddItemToHead(List * linkedList, void * data ){
    ListItem * listItem = (ListItem *)malloc(sizeof(ListItem));
    listItem->next = NULL;
    listItem->data = data;
    if(linkedList->head == NULL){
        linkedList->head = listItem;
        linkedList->current = listItem;
        linkedList->tail = listItem;
        linkedList->previous = NULL;
    }
    else{
        if(linkedList->current == linkedList->head)
            linkedList->previous = NULL;
        listItem->next = linkedList->head;
        linkedList->head = listItem;
    }
    linkedList->count++;
    resetCurrentListItem(linkedList);
    return linkedList;
}

List* deleteHeadListItem(List * linkedList){
    ListItem * nextListItem;
    if(linkedList->head ==NULL)
        return linkedList;
    nextListItem = linkedList->head->next;
    if(linkedList->current == linkedList->head)  //if current is point to head
        linkedList->current = nextListItem;   // also change current as the head is deleted
    if(nextListItem == NULL)
        linkedList->tail = NULL;             // if last item deleted , the tail also points to NULL
    linkedList->head = nextListItem;
    linkedList->count--;
    return linkedList;
}

List* deleteSelectedListItem(List * linkedList,void  * listItemData,LinkedListCompare compare){
    ListItem * listItem;
    if(linkedList->head ==NULL)
        return linkedList;
    listItem=findListItem(linkedList,listItemData,compare);
    if(listItem !=NULL)
        linkedList = checkAndDeleteListItem(linkedList,listItem);
    resetCurrentListItem(linkedList);
    return linkedList;
}

ListItem * findListItem(List * linkedList,void * listItemData,LinkedListCompare compare ){
    int size;
    ListItem * nextListItem;
    if(linkedList==NULL)
        return NULL;
    resetCurrentListItem(linkedList);
    nextListItem = getCurrentListItem(linkedList);
    while(nextListItem != NULL){
        size = compare(nextListItem,listItemData);
        if(size)
            return nextListItem;
        nextListItem = getNextListItem(linkedList);
    }
    return NULL;
}

List* checkAndDeleteListItem(List * linkedList,ListItem * deleteListItem){
    if(deleteListItem == linkedList->head){
        linkedList = deleteHeadListItem(linkedList);
    }
    else if(deleteListItem == linkedList->tail){
        linkedList->tail = linkedList->previous;
        linkedList->tail->next = NULL;
        linkedList->count--;
    }
    else{
        linkedList->count--;
        linkedList->previous->next = deleteListItem->next;
    }
    resetCurrentListItem(linkedList);
    return linkedList;
  }
