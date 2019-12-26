#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
NetworkNode node;
List linkList;
ListItem  itemA,itemB,itemC;
Link  linkItemDataA,linkItemDataB,linkItemDataC;
List* outList;
ListItem*outputListItem;
void setUp(void){}
void tearDown(void){}

void test_List_resetList(void){
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initList(&linkList, &itemA ,&itemB ,0 ,&itemB);
    resetCurrentListItem(&linkList);
    //reset will reset the current back to first item
    TEST_ASSERT_EQUAL_PTR(&itemA,linkList.current);
}

void test_List_resetList_NULL(void){
    initListItem(&itemA, &itemB ,(void*)&linkItemDataA);
    initList(&linkList, NULL ,NULL ,0 ,NULL);
    resetCurrentListItem(&linkList);
    //reset will reset the current back to first item
    TEST_ASSERT_NULL(linkList.current);
}

/*
*
*   LinkList -> itemA -> itemB -> NULL
*
*/
void test_List_getNextListItem(void){
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initList(&linkList, &itemA ,&itemB ,0 ,&itemA);
    //Link list with itemA as head and itemB as tail
    // getNextListItem will return the first listitem(listitemA)
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    // getNextListItem will return the second listitem(listitemB)
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outputListItem);
}

/*
*
*   LinkList -> itemA -> NULL
*
*/
void test_List_getNextListItem_second_item_is_NULL(void){
    initListItem(&itemA,NULL,(void*)&linkItemDataA);;
    initList(&linkList, &itemA ,&itemA ,0 ,&itemA);
    //Link list with itemA as head and tail
    // getNextListItem will return the first listitem(listitemA)
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,outputListItem);
    // getNextListItem will return NULL as nextItem is empty
    outputListItem=getNextListItem(&linkList);
    TEST_ASSERT_NULL(outputListItem);
}
/*
*   LinkList -> NULL
*          ↓ add itemA
*   LinkList -> itemA -> NULL
*          ↓ add itemB
*    LinkList -> itemA -> itemB -> NULL
*
*/
void test_List_addListItem(void){
    initList(&linkList, NULL ,NULL ,0 ,NULL);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //empty linklist add itemA
    // head ,tail and current points to itemA
    // count = 1 as 1 item inside
    outList=addListItem(&linkList,&itemA);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_NULL(itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
    //linklist add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=addListItem(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
}

/*
*   LinkList -> itemA -> NULL
*          ↓ add itemB
*    LinkList -> itemA -> itemB -> NULL
*          ↓ add itemC
*    LinkList -> itemA -> itemB -> itemC -> NULL
*/
void test_List_addListItem_addC(void){
    initList(&linkList, &itemA ,&itemA ,1 ,&itemA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    initListItem(&itemA,NULL,(void*)&linkItemDataA);
    initListItem(&itemC,NULL,(void*)&linkItemDataC);
    //linklist add itemB
    // head and current points to itemA
    // tail now points to itemB
    // count = 2 as 2 item inside
    outList=addListItem(&linkList,&itemB);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,itemA.next);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(2,outList->count);
    //linklist add itemC
    // head and current points to itemA
    // tail now points to itemC
    // count = 3 as 3 item inside
    outList=addListItem(&linkList,&itemC);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->head);
    TEST_ASSERT_NULL(itemC.next);
    TEST_ASSERT_EQUAL_PTR(&itemC,itemB.next);
    TEST_ASSERT_EQUAL_PTR(&itemC,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemA,outList->current);
    TEST_ASSERT_EQUAL(3,outList->count);

}

/*
*    LinkList -> itemA -> itemB -> NULL
*          ↓ delete
*   LinkList -> itemB -> NULL
*          ↓ delete
*   LinkList -> NULL
*/
void test_List_deleteListItem(void){
    initList(&linkList, &itemA ,&itemB ,2 ,&itemA );
    initListItem(&itemA,&itemB,(void*)&linkItemDataA);
    initListItem(&itemB,NULL,(void*)&linkItemDataB);
    //linklist with itemA and itemB
    //delete itemA
    // head and current points to itemB
    // tail points to itemB
    // count = 1 as 1 item inside
    outList=deleteListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->head);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->tail);
    TEST_ASSERT_EQUAL_PTR(&itemB,outList->current);
    TEST_ASSERT_EQUAL(1,outList->count);
    //linklist delete itemB
    // head and current points to NULL
    // tail now points to NULL
    // count = 0 as 0 item inside
    outList=deleteListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->head);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->tail);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->current);
    TEST_ASSERT_EQUAL(0,outList->count);
}

/*
*   LinkList -> NULL
*/
void test_List_deleteListItem_NULL(void){
    initList(&linkList, NULL ,NULL ,0 ,NULL );
    //linklist delete but item has nothing
    // count = 0 as 0 item inside
    outList=deleteListItem(&linkList);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->head);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->tail);
    TEST_ASSERT_EQUAL_PTR(NULL,outList->current);
    TEST_ASSERT_EQUAL(0,outList->count);
}
