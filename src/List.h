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
void resetCurrentListItem(List * node);
void * getNextListItem(List * node);
#endif // _LIST_H
