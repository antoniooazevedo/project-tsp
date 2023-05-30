#ifndef PROJECT_TSP_TAH_H
#define PROJECT_TSP_TAH_H

#include "Graph.h"

using namespace std;

class Tah {

public:
    static unordered_map<int , Vertex *> mstBuild(Graph *gh);
};


#endif
