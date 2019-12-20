#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"

void setUp(void){}
void tearDown(void){}

void test_List_getIteratorOfLinks(void){
    NetworkNode node;
    List  link;
    List*outputLink;
    initNetworkNode(&node,"ABC" ,&link);
    outputLink=getIteratorOfLinks(&node);
    TEST_ASSERT_EQUAL_PTR(&link,outputLink);
}

void test_List_resetList(void){
    List  linkList;
    ListItem  itemA,itemB;
    Link  linkItemData;
    initListItem(&itemA, &itemB ,(void*)&linkItemData);
    initList(&linkList, &itemA ,&itemB ,0 ,&itemB);
    resetList(&linkList);
    TEST_ASSERT_EQUAL_PTR(&itemA,&linkList->current);
}
/*
void test_List_getNextListItem(void){
    NetworkNode node;
    List  link;
    List*outputLink;
    initNetworkNode(&node,"ABC" ,&link);
    resetList(&node);
    TEST_ASSERT_NULL(node.current);
}
*/
