#include "unity.h"
#include "ListItemCompare.h"
#include "LinkedListCompare.h"
ListItem  dataA;
ListItem  dataB;
int   compareValue;
void setUp(void){}
void tearDown(void){}

void test_List_ListItemCompare_same_ListItemCompare(void){
    compareValue=ListItemCompare(&dataB,&dataB);
    TEST_ASSERT_EQUAL(1,compareValue);
}
void test_List_ListItemCompare_different_ListItemCompare(void){
    compareValue=ListItemCompare(&dataA,&dataB);
    TEST_ASSERT_EQUAL(0,compareValue);
}
