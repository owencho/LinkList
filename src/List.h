#ifndef _LIST_H
#define _LIST_H
#include "ListItem.h"
typedef struct List List ;

struct List{
    ListItem * head ;
    ListItem * tail ;
    int count ;
    ListItem * current ;
};
void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current);
void resetCurrentListItem(List * linkList);
ListItem * getNextListItem(List * linkList);
List*  addListItem(List * linkList, ListItem * item );
List* deleteListItem(List * linkList);
#endif // _LIST_H
