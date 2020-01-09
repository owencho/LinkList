#ifndef _LIST_H
#define _LIST_H
#include "ListItem.h"
#include "LinkedListCompare.h"
typedef struct List List ;

struct List{
    ListItem * head ;
    ListItem * tail ;
    int count ;
    ListItem * previous;
    ListItem * current ;
};
List * createList(void);
void resetCurrentListItem(List * linkedList);
ListItem * getCurrentListItem(List * linkedList);
ListItem * getNextListItem(List * linkedList);
List*  listAddItemToHead(List * linkedList, void * data );
List*  listAddItemToTail(List * linkedList, void * data );
List* deleteHeadListItem(List * linkedList);
ListItem * findListItem(List * linkedList,void * listItemData,LinkedListCompare compare );
List* deleteSelectedListItem(List * linkedList,void  * listItemData,LinkedListCompare compare);
List* checkAndDeleteListItem(List * linkedList,ListItem * deleteListItem);
#endif // _LIST_H
