#ifndef _LIST_H
#define _LIST_H
#include "ListItem.h"
#include "LinkListCompare.h"
typedef struct List List ;

struct List{
    ListItem * head ;
    ListItem * tail ;
    int count ;
    ListItem * previous;
    ListItem * current ;
};
List * createList(void);
void resetCurrentListItem(List * linkList);
ListItem * getCurrentListItem(List * linkList);
ListItem * getNextListItem(List * linkList);
List*  listAddItemToHead(List * linkList, void * data );
List*  listAddItemToTail(List * linkList, void * data );
List* deleteHeadListItem(List * linkList);
List* deleteSelectedListItem(List * linkList,void  * listItemData,LinkListCompare compare);
List* checkAndDeleteListItem(List * linkList,ListItem * deleteListItem);
#endif // _LIST_H
