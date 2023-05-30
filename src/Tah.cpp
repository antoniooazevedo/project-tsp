#include "Tah.h"

unordered_map<int , Vertex *> Tah::mstBuild(Graph *gh) {
    unordered_map<int, Vertex *> vertexSet = gh->getVertexSet();
    if(gh->getVertexSet().empty()) {
        return vertexSet;
    }
    for(auto v : vertexSet){
        v.second->setAuxDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }

    auto s = vertexSet.begin()->second;
    s->setAuxDist(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()){
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()){
            auto w = e->getDest();
            if(!w->isVisited()){
                auto oldDist = w->getAuxDist();
                if(e->getDistance() < oldDist){
                    w->setAuxDist(e->getDistance());
                    w->setPath(e);
                    if(oldDist == INF){
                        q.insert(w);
                    }
                    else{
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
    return vertexSet;
}
