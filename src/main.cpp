#include "../includes/dijkstra.h"
#include<iostream>
#include<cstdlib>
#include<ctime>


void dbg1()
{
    layered_dijkstra();
}


int main(){
    srand(time(NULL));

    dbg1();
    return 0;
}