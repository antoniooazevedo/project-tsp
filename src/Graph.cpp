
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
    if (vertexSet.empty()) {
        return;
    }

    MutablePriorityQueue<Vertex> q;

    for (auto v: vertexSet) {
        v.second->setPath(nullptr);
        v.second->setPrimDist(DBL_MAX);
        v.second->setVisited(false);
        q.insert(v.second);
    }

    auto s = this->findVertex(0);
    s->setPrimDist(0);
    q.decreaseKey(s);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto &e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getDistance() < w->getPrimDist()) {
                w->setPrimDist(e->getDistance());
                w->setPath(e);
                q.decreaseKey(w);
            }
        }
    }
}

void Graph::dfsMst(Vertex *v, vInt &path, int &count) {
    v->setVisited(true);
    path[count++] = v->getId();
    for (auto &e: v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited() && e == w->getPath()) {
            dfsMst(w, path, count);
        }
    }
}

double Graph::calculateTahTotalDistance(vInt &path) {
    double totalDistance = 0;
    auto s = this->findVertex(0);
    int count = 0;

    mstBuild();

    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    dfsMst(s, path, count);

    path.push_back(0);

    for (auto i = 0; i < path.size() - 1; i++) {
        auto v = findVertex(path[i]);
        auto w = findVertex(path[i + 1]);
        auto e = v->findEdge(w->getId());
        if (e == nullptr) {
            totalDistance += haversineCalculator(v->getLatitude(), v->getLongitude(), w->getLatitude(),
                                                 w->getLongitude());
        } else {
            totalDistance += e->getDistance();
        }
    }

    return totalDistance;
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

double Graph::nearestNeighbourRouteTsp(vInt &path) {
    for (auto v : vertexSet){
        v.second->setVisited(false);
}

    Vertex *currVertex = findVertex(0);
    path[0] = 0;
    Vertex *nextVertex;
    currVertex->setVisited(true);
    double totalDistance = 0;
    int numVisited = 1;

    while (numVisited < vertexSet.size()){
        auto minDistance = DBL_MAX;
        for (auto e : currVertex->getAdj()){
            if (e->getDistance() < minDistance && !e->getDest()->getVisited()){
                minDistance = e->getDistance();
                nextVertex = e->getDest();
            }
        }

        if(currVertex == nextVertex){
            nextVertex = findNearestHaversine(currVertex);
            minDistance = haversineCalculator(currVertex->getLatitude(), currVertex->getLongitude(), nextVertex->getLatitude(), nextVertex->getLongitude());
        }

        totalDistance += minDistance;
        path[numVisited] = nextVertex->getId();
        numVisited++;
        nextVertex->setVisited(true);
        currVertex = nextVertex;
    }

    totalDistance += currVertex->findEdge(0) == nullptr ? haversineCalculator(currVertex->getLatitude(), currVertex->getLongitude(), findVertex(0)->getLatitude(), findVertex(0)->getLongitude()) : currVertex->findEdge(0)->getDistance();
    path.push_back(0);

    return totalDistance;
}

Vertex* Graph::findNearestHaversine(Vertex* currentV){
    auto minDistance = DBL_MAX;
    Vertex* nearestV;
    for (auto v : vertexSet){
        if (currentV->findEdge(v.second->getId()) || v.second->getVisited()){
            continue;
        }
        double distance = haversineCalculator(currentV->getLatitude(), currentV->getLongitude(), v.second->getLatitude(), v.second->getLongitude());
        if (distance < minDistance){
            minDistance = distance;
            nearestV = v.second;
        }
    }

    return nearestV;
}
