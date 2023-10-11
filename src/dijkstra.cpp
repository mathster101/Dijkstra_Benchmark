#include "../includes/dijkstra.h"
#include<iostream>
#include<limits>
#include<algorithm>

#define INFINITY numeric_limits<float>::infinity()

#define NODE_NAME_LEN 4
#define NUM_CONNECTIONS 10
#define NUM_NODES 5000
#define FULLYCONNECTED true

#define VERBOSE 1

vector<string> makeNodeNames(const int numberNodes)
{
    unordered_set<string> nodes;
    while(nodes.size() < numberNodes)
    {
        string name = "";
        for(int i=0; i<NODE_NAME_LEN; i++)
        {
            name.push_back((char)(65 + rand()%26));
        }
        nodes.insert(name);
    }

    return vector<string>(nodes.begin(), nodes.end());
}

map<string, vector<string>> makeGraph(const int numberNodes)
{
    map<string, vector<string>> graph;
    auto nodeNames = makeNodeNames(numberNodes);
    string prevNode = "None";
    for(auto node : nodeNames)
    {
        unordered_set<string> neighbors;
        for(int i=0; i<NUM_CONNECTIONS; i++)
        {
            string choice = nodeNames[rand()%nodeNames.size()];
            while(choice == node)
            {
                choice = nodeNames[rand()%nodeNames.size()];
            }
            neighbors.insert(choice);
        }
#if FULLYCONNECTED == true
        if(prevNode != "None")
           neighbors.insert(prevNode);
#endif
        prevNode = node;
        graph[node] = vector<string>(neighbors.begin(),neighbors.end());
    }

    return graph;
}

void standard_dijkstra()
{
    auto graph = makeGraph(NUM_NODES);
    string start = graph.begin()->first;
    string end  = graph.rbegin()->first;
    map<string,float> distLookup;

    for(auto node: graph)
    {
        if(node.first == start)
            distLookup[node.first] = 0;
        else
            distLookup[node.first] = INFINITY;
    }

    vector<string> queue;
    unordered_set<string> seen;
    queue.push_back(start);
    while(queue.size())
    {
        string current = queue.front();
        queue.erase(queue.begin());
        seen.insert(current);
        for(auto nbr : graph[current])
        {
            if(distLookup[current]+1<distLookup[nbr])
            {
                distLookup[nbr] = distLookup[current]+1;
            }

            if(std::find(queue.begin(), queue.end(), nbr) == queue.end() && seen.find(nbr) == seen.end())
                queue.push_back(nbr);
        }

    }
#if VERBOSE == true
    cout<<"#####Graph####\n";
    for(auto pair: graph)
    {
        cout<<pair.first<<" -> ";
        for(auto node : pair.second)
            cout<<node<<" ";
        cout<<"\n";
    }
    cout<<"\n####Dists####\n";
    for(auto pair: distLookup)
    {
        cout<<pair.first<<" -> "<<pair.second<<"\n";
    }
#endif
}

void layered_dijkstra()
{
    auto graph = makeGraph(NUM_NODES);
    string start = graph.begin()->first;
    string end  = graph.rbegin()->first;
    map<string,float> distLookup;
    map<int, int> levelCount;

    for(auto node: graph)
    {
        if(node.first == start)
            distLookup[node.first] = 0;
        else
            distLookup[node.first] = INFINITY;
    }

    vector<pair<string,int>> queue;
    unordered_set<string> seen;
    queue.push_back(pair(start,0));
    while(queue.size())
    {
        string current = queue.front().first;
        int level = queue.front().second;
        queue.erase(queue.begin());

        seen.insert(current);
        for(auto nbr : graph[current])
        {
            if(distLookup[current]+1<distLookup[nbr])
            {
                distLookup[nbr] = distLookup[current]+1;
            }

            if(seen.find(nbr) == seen.end())
                queue.push_back(pair(nbr,level+1));
        }

    }

#if VERBOSE == true

    for(auto pair: distLookup)
    {
        int level = pair.second;
        if(levelCount.find(level) == levelCount.end())
            levelCount[level] = 0;
        levelCount[level]++;
    }

    for(auto p: levelCount)
    {
        cout<<p.first<<" - "<<p.second<<"\n";
    }
#endif
}