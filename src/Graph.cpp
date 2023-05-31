// By: Gonçalo Leão

#include "Graph.h"


std::unordered_map<int , Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const int &id) const {
    auto v = vertexSet.find(id);
    if (v == vertexSet.end()) return nullptr;
    else return v->second;
}

bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.insert({id, new Vertex(id)});
    return true;
}

bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getId()) != nullptr)
        return false;
    vertexSet.insert({v->getId(), v});
    return true;
}

bool Graph::removeVertex(const int &id) {
    if (findVertex(id) == nullptr) return false;
    auto v = findVertex(id);
    v->removeOutgoingEdges();
    vertexSet.erase(id);
    return true;
}

bool Graph::removeVertex(Vertex *v) {
    if (findVertex(v->getId()) == nullptr) return false;
    v->removeOutgoingEdges();
    vertexSet.erase(v->getId());
    return true;
}

Graph::~Graph() {
}

bool Graph::addEdge(Vertex *v1, Vertex *v2, double distance) {
    if (v1 == nullptr || v2 == nullptr) return false;
    v1->addEdge(v2, distance);
    return true;
}

bool Graph::addBidirectionalEdge(Vertex * &v1, Vertex * &v2, double dist) {
    if (v1 == nullptr || v2 == nullptr) return false;
    auto e1 = v1->addEdge(v2, dist);
    auto e2 = v2->addEdge(v1, dist);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

double Graph::tspBT(vInt &path) {
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    findVertex(0)->setVisited(true);
    path[0] = 0;

    return tspBacktracking(path, 0, 0, DBL_MAX, 1);
}

double Graph::tspBacktracking(vInt &path, int currVertexId, double currSum, double bestSum, uint step) {
    // TODO: add the Haversine function if the edge isn't found to run on large graphs

    double thisSum = 0;
    Vertex *currVertex = findVertex(currVertexId);

    if (step == vertexSet.size()) {
        Edge *e = currVertex->findEdge(0);
        return e != nullptr ? currSum + e->getDistance() : bestSum;
    }

    for (auto v: vertexSet) {
        Vertex *destVertex = v.second;
        Edge *e = currVertex->findEdge(v.first);
        if (e == nullptr) continue;
        double dist = e->getDistance();

        if (!destVertex->getVisited() && currSum + dist < bestSum) {
            destVertex->setVisited(true);
            thisSum = tspBacktracking(path, v.first, currSum + dist, bestSum, step + 1);
            if (thisSum < bestSum) {
                bestSum = thisSum;
                path[step] = v.first;
            }
            destVertex->setVisited(false);
        }
    }

    return bestSum;
}
