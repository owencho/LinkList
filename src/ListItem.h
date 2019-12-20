#ifndef _LISTITEM_H
#define _LISTITEM_H

typedef struct ListItem ListItem ;

struct ListItem{
    ListItem * next ;
    void * data ;
};

void initListItem(ListItem * listItem, ListItem * next ,void* data);
#endif // _LISTITEM_H
