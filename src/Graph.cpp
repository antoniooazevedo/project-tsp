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
    if (v1 == nullptr || v2 == nullptr) return false;
    auto e1 = v1->addEdge(v2, dist);
    auto e2 = v2->addEdge(v1, dist);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::mstBuild() {
    if (vertexSet.empty()) return;
    for (auto v: vertexSet) {
        v.second->setAuxDist(INFINITY);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
    }

    Vertex *v = findVertex(0);
    v->setAuxDist(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(v);

    while (!q.empty()) {
        auto s = q.extractMin();
        s->setVisited(true);
        for (auto &e: s->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getAuxDist();
                if (e->getDistance() < oldDist) {
                    w->setAuxDist(e->getDistance());
                    w->setPath(e);
                    if (oldDist == INFINITY) {
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

void Graph::calculateTotalDistance() {
    double totalDistance = 0;
    auto s = this->findVertex(0);
    vector<Vertex *> res;

    mstBuild();

    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    dfsMst(s, res);
    res.push_back(s);

    for (auto i = 0; i < res.size() - 1; i++) {
        auto v = res[i];
        auto w = res[i + 1];
        auto e = v->findEdge(w->getId());
        if (e == nullptr) {
            totalDistance += haversineCalculator(v->getLatitude(), v->getLongitude(), w->getLatitude(),w->getLongitude());
        } else {
            cout << e->getDistance() << " " << v->getId() << " - " << w->getId() << endl;
            totalDistance += e->getDistance();
        }
    }

    cout << "Total distance: " << totalDistance << endl;
}

double convert_to_radians(double coordinate) {
    return coordinate * M_PI / 180;
}

double Graph::haversineCalculator(double lat1, double long1, double lat2, double long2) {
    lat1 = convert_to_radians(lat1);
    lat2 = convert_to_radians(lat2);
    long1 = convert_to_radians(long1);
    long2 = convert_to_radians(long2);

    double delta_lat = lat2 - lat1;
    double delta_long = long2 - long1;

    double aux = pow(sin(delta_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(delta_long / 2), 2);
    double c = 2.0 * atan2(sqrt(aux), sqrt(1 - aux));
    double earth_radius = 6371000.0;
    return earth_radius * c;
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
