#include "../includes/dijkstra.h"
#include<iostream>

void dbg1()
{
    auto nodes = nodeNames(4);
    for(auto node : nodes)
        std::cout<<node<<" ";

    return;
}


int main(){

    dbg1();
    return 0;
}