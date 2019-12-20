#include "NetworkNode.h"

char* getNodeName(NetworkNode * node){
    return node->name;
}
void initNetworkNode(NetworkNode * node, char*name,List * links){
    node->name = name;
    node-> links = links;
}

ListItem * getIteratorOfLinks(NetworkNode * node){
    return node->links;
}
