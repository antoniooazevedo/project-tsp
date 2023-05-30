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
    auto e1 = v1->addEdge(v2, dist);
    auto e2 = v2->addEdge(v1, dist);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}