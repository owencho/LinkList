#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
#include "ListItemCompare.h"
#include "LinkedListCompare.h"
#include "LinkCompare.h"
#include "LinkedListProcessor.h"
#include "mock_ProcessorFunction.h"
NetworkNode node;
List linkedList;
ListItem  itemA,itemB,itemC;
ListItem * listItemA;
ListItem *listItemB;
ListItem *listItemC;
Link  linkItemDataA,linkItemDataB,linkItemDataC;
Link * outputLink;
List* outList;
ListItem*outputListItem;
void setUp(void){}
void tearDown(void){}


void initList(List * link, ListItem * head ,ListItem * tail ,int count ,ListItem * current){
    link->head = head;
    link->tail = tail;
    link->count = count;
    link->current = current;
    link->previous =NULL;
}

void initListItem(ListItem * listItem, ListItem * next ,void* data){
    listItem->next = next;
    listItem->data = data;
}

List* createLinkList(ListItem * head ,ListItem * tail ,int count ,ListItem * current,ListItem * previous){
    List * list = (List *)malloc(sizeof(List));
    list->head = head;
    list->tail = tail;
    list->count = count;
    list->current = current;
    list->previous =previous;
    return list;
}

ListItem *createListItemTest(ListItem * next ,void* data){
    ListItem * listItem = (ListItem *)malloc(sizeof(ListItem));
    listItem->next = next;
    listItem->data = data;
    return listItem;
}

//Test for createList
void test_List_createList(void){
    outList = createList();
    //createList will malloc for List
    TEST_ASSERT_NULL(outList->head);
    TEST_ASSERT_NULL(outList->tail);
    TEST_ASSERT_NULL(outList->current);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL_PTR(0,outList->count);
    freeList(outList);
}
//Test for createListItem
void test_List_createListItem_without_data(void){
    outputListItem = createListItem(NULL);
    //createListItem will malloc for ListItem
    TEST_ASSERT_NULL(outputListItem->next);
    TEST_ASSERT_NULL(outputListItem->data);
    freeListItem(outputListItem);
}

void test_List_createListItem_with_data(void){
    outputListItem = createListItem((void*)&linkItemDataA);
    //createListItem will malloc for ListItem
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outputListItem->data);
    TEST_ASSERT_NULL(outputListItem->next);
    freeListItem(outputListItem);
}

//Test for resetCurrentListItem
void test_List_resetList(void){
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initList(&linkedList, &itemA ,&itemB ,0 ,&itemB);
    resetCurrentListItem(&linkedList);
    //reset will reset the current back to first item
    TEST_ASSERT_EQUAL_PTR(&itemA,linkedList.current);
}

void test_List_resetList_current_NULL(void){
    initList(&linkedList, NULL ,NULL ,0 ,NULL);
    resetCurrentListItem(&linkedList);
    //reset will reset the current back to first item
    TEST_ASSERT_NULL(linkedList.current);
}

void test_List_resetList_NULL(void){
    initList(&linkedList, NULL ,NULL ,0 ,NULL);
    resetCurrentListItem(NULL);
    // do nothing as NULL passed in
}
//Test for getCurrentListItem
/*
*
*   linkedList -> itemA -> itemB -> NULL
*
*/
void test_List_getCurrentListItem(void){
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initList(&linkedList, &itemA ,&itemB ,0 ,&itemA);
    //Link list with itemA as head and itemB as tail
    // getCurrentListItem will return the first listitem(listitemA)
    outputListItem=getCurrentListItem(&linkedList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
}

void test_List_getCurrentListItem_NULL(void){
    outputListItem=getCurrentListItem(NULL);
    TEST_ASSERT_NULL(outputListItem);
}

//Test for getNextListItem
/*
*
*   linkedList -> itemA -> itemB -> NULL
*
*/
void test_List_getNextListItem(void){
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initList(&linkedList, &itemA ,&itemB ,0 ,&itemA);//er
    //Link list with itemA as head and itemB as tail
    // getCurrentListItem will return the first listitem(listitemA)
    outputListItem=getCurrentListItem(&linkedList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    // getNextListItem will return the second listitem(listitemB)
    outputListItem=getNextListItem(&linkedList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem);
    // getNextListItem will return NULL as nextItem is empty
    outputListItem=getNextListItem(&linkedList);
    TEST_ASSERT_NULL(outputListItem);
}

/*
*
*   linkedList -> itemA -> NULL
*
*/
void test_List_getNextListItem_second_item_is_NULL(void){
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initList(&linkedList, &itemA ,&itemA ,0 ,&itemA);
    //Link list with itemA as head and tail
    // getCurrentListItem will return the first listitem(listitemA)
    outputListItem=getCurrentListItem(&linkedList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    // getNextListItem will return NULL as nextItem is empty
    outputListItem=getNextListItem(&linkedList);
    TEST_ASSERT_NULL(outputListItem);
}

void test_List_getNextListItem_input_NULL(void){
    outputListItem=getNextListItem(NULL);
    TEST_ASSERT_NULL(outputListItem);
}
//Test for listAddItemToTail
/*
*   linkedList -> NULL
*          ↓ add itemA
*   linkedList -> itemA -> NULL
*          ↓ add itemB
*    linkedList -> itemA -> itemB -> NULL
*
*/
void test_List_listAddItemToTail(void){
    initList(&linkedList, NULL ,NULL ,0 ,NULL);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //empty linkedList add itemA
    // head ,tail and current points to itemA
    // count = 1 as 1 item inside
    outList=listAddItemToTail(&linkedList,(void*)&linkItemDataA);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(1,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);

    //linkedList add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToTail(&linkedList,(void*)&linkItemDataB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);

}

/*
*   linkedList -> itemA -> NULL
*          ↓ add itemB
*    linkedList -> itemA -> itemB -> NULL
*          ↓ add itemC
*    linkedList -> itemA -> itemB -> itemC -> NULL
*/
void test_List_listAddItemToTail_addC(void){
    initList(&linkedList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linkedList add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToTail(&linkedList,(void*)&linkItemDataB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);
    //linkedList add itemC
    // head and current points to itemA
    // tail now points to itemC
    // count = 3 as 3 item inside
    outList=listAddItemToTail(&linkedList,(void*)&linkItemDataC);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataC,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(3,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataC);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);
}

void test_List_listAddItemToTail_list_NULL(void){
    outList=listAddItemToTail(NULL,(void*)&linkItemDataB);
    TEST_ASSERT_NULL(outList);
}

void test_List_listAddItemToTail_data_NULL(void){
    initList(&linkedList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);

    outList=listAddItemToTail(&linkedList,NULL);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(1,outList->count);
}

void test_List_listAddItemToTail_both_input_NULL(void){
    outList=listAddItemToTail(NULL,NULL);
    TEST_ASSERT_NULL(outList);
}
//Test for listAddItemToHead
void test_List_listAddItemToHead_linkedList_is_NULL(void){
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);

    outList=listAddItemToHead(NULL,(void*)&linkItemDataB);
    TEST_ASSERT_NULL(outList);
}

void test_List_listAddItemToHead_linkedListData_is_NULL(void){
    initList(&linkedList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);

    outList=listAddItemToHead(&linkedList,NULL);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(1,outList->count);
}
/*
*   linkedList -> itemA -> NULL
*          ↓ add itemB
*    linkedList -> itemB -> itemA -> NULL
*          ↓ add itemC
*    linkedList -> itemC -> itemB -> itemA -> NULL
*/
void test_List_listAddItemToHead_head_null(void){
    initList(&linkedList, NULL ,NULL ,0 ,NULL);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linkedList add itemB
    // head points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToHead(&linkedList,(void*)&linkItemDataB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(1,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
}
/*
*   linkedList -> itemA -> NULL
*          ↓ add itemB
*    linkedList -> itemB -> itemA -> NULL
*          ↓ add itemC
*    linkedList -> itemC -> itemB -> itemA -> NULL
*/
void test_List_listAddItemToHead(void){
    initList(&linkedList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linkedList add itemB
    // head points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToHead(&linkedList,(void*)&linkItemDataB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);

    //linkedList add itemC
    // head points to itemC
    // count = 3 as 3 item inside

    outList=listAddItemToHead(&linkedList,(void*)&linkItemDataC);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataC,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataC,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(3,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataC);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);


}
/*
*   linkedList -> itemA -> NULL
*          ↓ add itemB after A
*    linkedList -> itemA -> itemB -> NULL
*          ↓ add itemC
*    linkedList -> itemA -> itemB -> itemC -> NULL
*/
void test_List_listAddItemToNext_addC(void){
    initList(&linkedList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linkedList add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=listAddItemToNext(&linkedList,&itemA,(void*)&linkItemDataB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);

    outList=listAddItemToNext(&linkedList,&itemA,(void*)&linkItemDataC);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->head->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outList->tail->data);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outList->current->data);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(3,outList->count);
    outputListItem= getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataA);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataC);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(outputListItem->data,&linkItemDataB);
    outputListItem= getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);
    resetCurrentListItem(outList);
}

void test_List_listAddItemToNext_NULL(void){
  initList(&linkedList, &itemA ,&itemA ,1 ,&itemA);
  initListItem(&itemB,NULL,(void*)&linkItemDataB);
  initListItem(&itemA,NULL,(void*)&linkItemDataA);
  initListItem(&itemC,NULL,(void*)&linkItemDataC);
  //linkedList add itemB
  // head and current points to itemA
  // tail now points to itemB
  // count = 2 as 2 item inside
  outList=listAddItemToNext(NULL,&itemA,(void*)&linkItemDataB);
  TEST_ASSERT_NULL(outList);
  outList=listAddItemToNext(&linkedList,NULL,(void*)&linkItemDataC);
  TEST_ASSERT_EQUAL_PTR(&linkedList,outList);
  outList=listAddItemToNext(&linkedList,&itemA,NULL);
  TEST_ASSERT_EQUAL_PTR(&linkedList,outList);
}
// test for deleteHeadListItem
/*
*    linkedList -> itemA -> itemB -> NULL
*          ↓ delete
*   linkedList -> itemB -> NULL
*          ↓ delete
*   linkedList -> NULL
*/
void test_List_deleteHeadListItem(void){
    listItemB = createListItemTest(NULL ,(void*)&linkItemDataB);
    listItemA = createListItemTest(listItemB ,(void*)&linkItemDataA);
    outList = createLinkList(listItemA ,listItemB ,2 ,listItemA,NULL);
    //linkedList with itemA and itemB
    //delete itemA
    // head and current points to itemB
    // tail points to itemB
    // count = 1 as 1 item inside
    outputLink=(Link*)deleteHeadListItem(outList);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->current);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(1,outList->count);
    //linkedList delete itemB
    // head and current points to NULL
    // tail now points to NULL
    // count = 0 as 0 item inside
    outputLink=(Link*)deleteHeadListItem(outList);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outputLink);
    TEST_ASSERT_NULL(outList->head);
    TEST_ASSERT_NULL(outList->tail);
    TEST_ASSERT_NULL(outList->current);
    TEST_ASSERT_NULL(outList->previous);
    TEST_ASSERT_EQUAL(0,outList->count);
    freeList(outList);
}

void test_List_deleteHeadListItemlinkedList_NULL(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //linkedList with itemA and itemB
    //delete itemA
    // head and current points to itemB
    // tail points to itemB
    // count = 1 as 1 item inside
    outputLink=(Link*)deleteHeadListItem(NULL);
    TEST_ASSERT_NULL(outputLink);
}

/*
*   linkedList -> NULL
*/
void test_List_deleteHeadListItem_NULL(void){
    initList(&linkedList, NULL ,NULL ,0 ,NULL );
    //linkedList delete but item has nothing
    // count = 0 as 0 item inside
    outputLink=(Link*)deleteHeadListItem(&linkedList);
    TEST_ASSERT_NULL(outputLink);
}
////checkAndDeleteListItem//////////////////////////
//This function is to check the location of the deleted node
// when this function called the deleted linkItem is already found
// it is used to determine where is the location of the linkItem and delete
// either is head , tail or middle of linkedList

void test_List_checkAndDeleteListItem_linkedList_NULL(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputLink=(Link*)checkAndDeleteListItem(NULL,&itemA);
    TEST_ASSERT_NULL(outputLink);
}

void test_List_checkAndDeleteListItem_deleteListItem_NULL(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputLink=(Link*)checkAndDeleteListItem(&linkedList,NULL);
    TEST_ASSERT_EQUAL_PTR(&itemA,linkedList.head);
    TEST_ASSERT_EQUAL_PTR(&itemB,linkedList.tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,linkedList.current);
    TEST_ASSERT_EQUAL(2,linkedList.count);
    TEST_ASSERT_NULL(outputLink);
}
/*
*    linkedList -> itemA -> itemB -> NULL
*          ↓ deleteA
*   linkedList -> itemB -> NULL
*/
void test_List_checkAndDeleteListItem_delete_firstNode(void){
    listItemB = createListItemTest(NULL ,(void*)&linkItemDataB);
    listItemA = createListItemTest(listItemB ,(void*)&linkItemDataA);
    outList = createLinkList(listItemA ,listItemB ,2 ,listItemA,NULL);
    //current must points to itemA first before check the location of node and delete
    outputLink=(Link*)checkAndDeleteListItem(outList,listItemA);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
    freeList(outList);
    freeListItem(listItemB);
}

/*
*    linkedList -> itemA -> itemB -> NULL
*          ↓ deleteB
*   linkedList -> itemA -> NULL
*/
void test_List_checkAndDeleteListItem_delete_tail(void){
    listItemB = createListItemTest(NULL ,(void*)&linkItemDataB);
    listItemA = createListItemTest(listItemB ,(void*)&linkItemDataA);
    outList = createLinkList(listItemA ,listItemB ,2 ,listItemA,NULL);
    //current must points to itemB first before check the location of node and delete
    outputListItem=getNextListItem(outList);
    outputLink=(Link*)checkAndDeleteListItem(outList,listItemB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemA,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemA,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
    freeList(outList);
    freeListItem(listItemA);

}

/*
*    linkedList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemB
*    linkedList -> itemC -> itemA -> NULL
*
*/
void test_List_checkAndDeleteListItem_delete_middle(void){
    listItemA = createListItemTest(NULL ,(void*)&linkItemDataA);
    listItemB = createListItemTest(listItemA ,(void*)&linkItemDataB);
    listItemC = createListItemTest(listItemB ,(void*)&linkItemDataC);
    outList = createLinkList(listItemC,listItemA ,3 ,listItemC,NULL);
    //current must points to itemB first before check the location of node and delete
    outputListItem=getNextListItem(outList);
    outputLink=(Link*)checkAndDeleteListItem(outList,listItemB);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemC,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);

    outputListItem=getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemC,outputListItem);
    TEST_ASSERT_EQUAL_PTR(listItemA,outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemA,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);

    freeList(outList);
    freeListItem(listItemC);
    freeListItem(listItemA);
}


////Delete Selected item//////////////////////////////////////////////////////////////

/*
*    linkedList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemB
*    linkedList -> itemC -> itemA -> NULL
*
*/
void test_List_deleteSelectedListItem_delete_middle(void){
    listItemA = createListItemTest(NULL ,(void*)&linkItemDataA);
    listItemB = createListItemTest(listItemA ,(void*)&linkItemDataB);
    listItemC = createListItemTest(listItemB ,(void*)&linkItemDataC);
    outList = createLinkList(listItemC,listItemA ,3 ,listItemC,NULL);

    outputLink=(Link*)deleteSelectedListItem(outList,listItemB,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataB,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemC,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemC,outputListItem);
    TEST_ASSERT_EQUAL_PTR(listItemA,outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemA,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);

    freeList(outList);
    freeListItem(listItemC);
    freeListItem(listItemA);
}

/*
*    linkedList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemC
*    linkedList -> itemB -> itemA -> NULL
*
*/
void test_List_deleteSelectedListItem_delete_front(void){
    listItemA = createListItemTest(NULL ,(void*)&linkItemDataA);
    listItemB = createListItemTest(listItemA ,(void*)&linkItemDataB);
    listItemC = createListItemTest(listItemB ,(void*)&linkItemDataC);
    outList = createLinkList(listItemC,listItemA ,3 ,listItemC,NULL);

    outputLink=(Link*)deleteSelectedListItem(outList,listItemC,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataC,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemB,outputListItem);
    TEST_ASSERT_EQUAL_PTR(listItemA,outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemA,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);

    freeList(outList);
    freeListItem(listItemB);
    freeListItem(listItemA);
}

/*
*    linkedList -> itemC -> itemB -> itemA -> NULL
*          ↓ delete itemA
*    linkedList -> itemC -> itemB -> NULL
*
*/
void test_List_deleteSelectedListItem_delete_last(void){
    listItemA = createListItemTest(NULL ,(void*)&linkItemDataA);
    listItemB = createListItemTest(listItemA ,(void*)&linkItemDataB);
    listItemC = createListItemTest(listItemB ,(void*)&linkItemDataC);
    outList = createLinkList(listItemC,listItemA ,3 ,listItemC,NULL);

    outputLink=(Link*)deleteSelectedListItem(outList,listItemA,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&linkItemDataA,outputLink);
    TEST_ASSERT_EQUAL_PTR(listItemC,outList->head);
    TEST_ASSERT_EQUAL_PTR(listItemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(listItemC,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    outputListItem=getCurrentListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemC,outputListItem);
    TEST_ASSERT_EQUAL_PTR(listItemB,outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_EQUAL_PTR(listItemB,outputListItem);
    TEST_ASSERT_NULL(outputListItem->next);
    outputListItem=getNextListItem(outList);
    TEST_ASSERT_NULL(outputListItem);

    freeList(outList);
    freeListItem(listItemC);
    freeListItem(listItemB);
}

void test_List_deleteSelectedListItem_LinkList_NULL(void){
    outputLink=(Link*)deleteSelectedListItem(NULL,listItemA,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_NULL(outputLink);
}

void test_List_deleteSelectedListItem_listItem_NULL(void){
    outputLink=(Link*)deleteSelectedListItem(outList,NULL,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_NULL(outputLink);
}

void test_List_deleteSelectedListItem_function_pointer_NULL(void){
    outputLink=(Link*)deleteSelectedListItem(outList,listItemA,NULL);
    TEST_ASSERT_NULL(outputLink);
}

void test_List_deleteSelectedListItem_LinkList_empty(void){
    outList = createLinkList(NULL,NULL ,0 ,NULL,NULL);
    outputLink=(Link*)deleteSelectedListItem(outList,listItemA,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_NULL(outputLink);

    freeList(outList);
}
// test for findListItem
/*
*    linkedList -> itemA -> itemB -> NULL
*
*/
void test_List_findListItem(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputListItem=findListItem(&linkedList,&itemB,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem);
}

/*
*    linkedList -> itemA -> itemB -> NULL
*
*/
void test_List_findListItem_linkedList_couldnt_found_the_node(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputListItem=findListItem(&linkedList,&itemC,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_NULL(outputListItem);
}

void test_List_findListItem_linkedList_NULL(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputListItem=findListItem(NULL,&itemB,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_NULL(outputListItem);
}

void test_List_findListItem_data_NULL(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputListItem=findListItem(&linkedList,NULL,(LinkedListCompare)ListItemCompare);
    TEST_ASSERT_NULL(outputListItem);
}

void test_List_findListItem_function_pointer_NULL(void){
    initList(&linkedList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);

    outputListItem=findListItem(&linkedList,&itemB,NULL);
    TEST_ASSERT_NULL(outputListItem);
}

// test for listForEach
/*
*    linkedList -> itemC -> itemB -> itemA -> NULL
*
*/
void test_List_listForEach(void){
    initList(&linkedList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);
    printLinkSourceProcessor_Expect(&itemC);
    printLinkSourceProcessor_Expect(&itemB);
    printLinkSourceProcessor_Expect(&itemA);
    listForEach(&linkedList,(LinkedListProcessor)printLinkSourceProcessor);
}

void test_List_listForEach_linked_is_NULL(void){
    initList(&linkedList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);
    listForEach(NULL,(LinkedListProcessor)printLinkSourceProcessor);
}

void test_List_listForEach_processor_NULL(void){
    initList(&linkedList, &itemC ,&itemA ,3 ,&itemC);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,&itemA,(void*)&linkItemDataB);
    initListItem(&itemC,&itemB,(void*)&linkItemDataC);
    listForEach(&linkedList,NULL);
}
