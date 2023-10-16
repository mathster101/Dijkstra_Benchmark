#include "../includes/dijkstra.h"
#include<iostream>
#include<limits>
#include<algorithm>
#include<chrono>
#include<thread>

#define INFINITY numeric_limits<float>::infinity()

#define NODE_NAME_LEN 4
#define NUM_CONNECTIONS 20
#define NUM_NODES 5000
#define FULLYCONNECTED true
#define RUNTIME 60000//1 minute
#define VERBOSE 0

void print_progress_bar(int percentage){
  string progress = "RUNNING[" + string(percentage, '*') + string(100 - percentage, ' ') + "]";
  cout << progress << "\r\033[F\033[F\033[F" << flush;
}

vector<string> makeNodeNames(const int numberNodes)
{
    unordered_set<string> nodes;
    while(nodes.size() < (long long unsigned)numberNodes)
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

gmap makeGraph(const int numberNodes)
{
    gmap graph;
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

gmap combineGraphs(gmap a, gmap b)
{
    return gmap();
}

void standardDijkstra()
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

    return;
}

void DijkstraWithTermChecks()
{
    while(1)
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
            if(quit)
                return;
        }
        ++perfCounter;
    }

    return;    
}

int wrapper()
{
    auto threadCount = std::thread::hardware_concurrency();
    auto start = std::chrono::system_clock::now();
    vector<thread> threads;
    for(unsigned i = 0; i < threadCount; i++)
    {
        thread t1(DijkstraWithTermChecks);
        t1.detach();
        threads.push_back(move(t1));
    }
    
    while(true)
    {
        auto now = std::chrono::system_clock::now();
        int elapsed = std::chrono::duration<double, std::milli>(now - start).count(); 
        if(elapsed >= RUNTIME)
        {
            quit = true;
            break;
        }
        print_progress_bar((int)(100*elapsed/RUNTIME));
        std::this_thread::sleep_for(std::chrono::milliseconds(20));//reduces system load from this pbar thread
    }

    return perfCounter;
}