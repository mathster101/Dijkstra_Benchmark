#include<vector>
#include<string>
#include<unordered_set>
#include<map>
#include<atomic>

//////////////////////////////////////////////////////
using namespace std;
typedef map<string, vector<string>> gmap;
//////////////////////////////////////////////////////
static atomic<bool> quit{false};
static atomic<long> perfCounter{0};
//////////////////////////////////////////////////////
void print_progress_bar(int percentage);//stolen from https://stackoverflow.com/a/30831414
vector<string> makeNodeNames(const int numberNodes);
gmap makeGraph(const int numberNodes);
gmap combineGraphs(gmap a, gmap b);
void DijkstraWithTermChecks();
int wrapper();
//////////////////////////////////////////////////////