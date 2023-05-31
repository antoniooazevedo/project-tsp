// By: Gonçalo Leão

#include "Graph.h"


std::unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex *Graph::findVertex(const int &id) const {
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

bool Graph::addBidirectionalEdge(Vertex *&v1, Vertex *&v2, double dist) {
    auto e1 = v1->addEdge(v2, dist);
    auto e2 = v2->addEdge(v1, dist);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::mstBuild() {
    if (vertexSet.empty()) {
        return;
    }
    for (auto v: vertexSet) {
        v.second->setAuxDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }

    auto s = this->findVertex(0);
    s->setAuxDist(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto &e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getAuxDist();
                if (e->getDistance() < oldDist) {
                    w->setAuxDist(e->getDistance());
                    w->setPath(e);
                    if (oldDist == INF) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }
}

void Graph::dfsMst(Vertex *v, vector<Vertex *> &res) {
    v->setVisited(true);
    res.push_back(v);
    for (auto &e: v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited() && e == w->getPath()) {
            dfsMst(w, res);
        }
    }
}

void Graph::calculateTotalDistance(bool real) {
    double totalDistance = 0;
    auto s = this->findVertex(0);
    mstBuild();
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }
    vector<Vertex *> res;
    dfsMst(s, res);
    res.push_back(s);

    for (auto i = 0; i < res.size() - 1; i++) {
        auto v = res[i];
        auto w = res[i + 1];
        double auxDistance = 0.0;
        if (!real) {
            for (auto &e: v->getAdj()) {
                if (e->getDest() == w) {
                    auxDistance = e->getDistance();
                }
            }
            totalDistance += min(auxDistance, haversineCalculator(v->getLatitude(), v->getLongitude(), w->getLatitude(), w->getLongitude())*1000);
        }
    }


    cout << "Total distance: " << totalDistance << endl;
}


double Graph::haversineCalculator(double lat1, double long1, double lat2, double long2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (long2 - long1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}