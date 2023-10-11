#include "../includes/dijkstra.h"
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<cstdio>
#include<cstring>

vector<string> nodeNames(const int numberNodes)
{
    unordered_set<string> nodes;
    while(nodes.size() < numberNodes)
    {
        string name = "";
        for(int i=0; i<3; i++)
        {
            name.push_back((char)(65 + rand()%26));
        }
        nodes.insert(name);
    }


    return vector<string>(nodes.begin(), nodes.end());
}