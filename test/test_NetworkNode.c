#include "unity.h"
#include "NetworkNode.h"
#include "List.h"
#include "ListItem.h"
void setUp(void){}

void tearDown(void){}

void test_NetworkNode_getNodeName(void){
    NetworkNode node;
    List  link;
    char* name;
    initNetworkNode(&node,"ABC" ,&link);
    name = getNodeName(&node);
    TEST_ASSERT_EQUAL("ABC",name);
}
