#include "CustomAssert.h"
/*
void assertEqualList (const ListItem * head ,
                      const ListItem * tail ,
                      const ListItem * current,
                      const ListItem * previous,
                      const int count ,
                      const UNITY_LINE_TYPE lineNumber){

    char msg[1024];
    int length;
    int i;

    if(actualNode == NULL){
        UNITY_TEST_FAIL(lineNumber,"The actual Node is NULL");
    }
    if(actualNode->left != leftNode){
        if(leftNode == NULL){
            sprintf(msg,"the actual left node is %d and not NULL",actualNode->left->value);
        }
        else if (actualNode->left == NULL){
            sprintf(msg,"the actual left node is NULL and not %d ",leftNode->value);
        }
        else{
            sprintf(msg,"Expected %d but encountered %d in actualNode , the left node is not the same",leftNode->value,actualNode->left->value);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualNode->right != rightNode){
        if(rightNode == NULL){
            sprintf(msg,"the actual right node is %d and not NULL",actualNode->right->value);
        }
        else if (actualNode->right == NULL){
            sprintf(msg,"the actual right node is NULL and not %d ",rightNode->value);
        }
        else{
            sprintf(msg,"Expected %d but encountered %d in actualNode, the right node is not the same",rightNode->value,actualNode->right->value);
        }
        UNITY_TEST_FAIL(lineNumber,msg);
    }

    if(actualNode->bFactor != balanceFactor){
        sprintf(msg,"Expected %d but encountered %d in actualNode, the balanceFactor on node %d is not the same",balanceFactor,actualNode->bFactor,actualNode->value);
        UNITY_TEST_FAIL(lineNumber,msg);
    }

}
*/
