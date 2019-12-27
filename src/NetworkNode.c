#include "NetworkNode.h"

char* getNodeName(NetworkNode * node){
    return node->name;
}

List * getIteratorOfLinks(NetworkNode * node){
    return node->links;
}
