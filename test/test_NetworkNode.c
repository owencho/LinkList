#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"

NetworkNode node;
List linkList;
ListItem  itemA,itemB;
Link  linkItemDataA,linkItemDataB;
List*outputLink;
ListItem*outputListItem;

void setUp(void){}
void tearDown(void){}

void test_NetworkNode_getNodeName(void){
    char* name;
    initNetworkNode(&node,"ABC" ,&linkList);
    name = getNodeName(&node);
    TEST_ASSERT_EQUAL("ABC",name);
}

void test_List_getIteratorOfLinks(void){
    initNetworkNode(&node,"ABC" ,&linkList);
    outputLink=getIteratorOfLinks(&node);
    TEST_ASSERT_EQUAL_PTR(&linkList,outputLink);
}
