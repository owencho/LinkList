#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"

NetworkNode node;
List linkList;
char* name;
List*outputLink;

void setUp(void){}
void tearDown(void){}

void initNetworkNode(NetworkNode * node, char*name,List * links){
    node->name = name;
    node-> links = links;
}

void test_NetworkNode_getNodeName(void){
    initNetworkNode(&node,"ABC" ,&linkList);
    name = getNodeName(&node);
    TEST_ASSERT_EQUAL("ABC",name);
}
void test_NetworkNode_getNodeName_scan(void){
    initNetworkNode(&node,"Scan" ,&linkList);
    name = getNodeName(&node);
    TEST_ASSERT_EQUAL("Scan",name);
}

void test_List_getIteratorOfLinks(void){
    initNetworkNode(&node,"ABC",&linkList);
    outputLink=getIteratorOfLinks(&node);
    TEST_ASSERT_EQUAL_PTR(&linkList,outputLink);
}
