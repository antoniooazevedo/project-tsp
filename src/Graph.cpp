#include "Graph.h"

std::unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex *Graph::findVertex(const int &id) const {
    auto v = vertexSet.find(id);
    if (v == vertexSet.end()) return nullptr;
    else return v->second;
}

bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getId()) != nullptr)
        return false;
    vertexSet.insert({v->getId(), v});
    return true;
}

Graph::~Graph() {
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
        v.second->setOutdegree(0);
        for (Edge *e: v.second->getAdj()) {
            e->setSelected(false);
            e->getReverse()->setSelected(false);
            e->setIsDouble(false);
            e->getReverse()->setIsDouble(false);
        }
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
                Edge *prevPath = w->getPath();
                if (prevPath != nullptr) {
                    prevPath->setSelected(false);
                    prevPath->getReverse()->setSelected(false);
                }

                w->setPrimDist(e->getDistance());
                w->setPath(e);
                q.decreaseKey(w);
                e->setSelected(true);
                e->getReverse()->setSelected(true);
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

    double bestDist = tspBacktracking(path, 0, 0, DBL_MAX, 1);
    path.push_back(0);
    return bestDist;

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

        if (destVertex->isVisited())
            continue;

        Edge *e = currVertex->findEdge(v.first);
        if (e == nullptr) continue;
        double dist = e->getDistance();

        if (currSum + dist < bestSum) {
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

vector<Vertex *> Graph::findOddDegreeVertexes() {
    vector<Vertex *> oddDegreeVertices;
    int outdegree;

    for (auto v: vertexSet) {
        outdegree = 0;
        for (Edge *e: v.second->getAdj()) {
            if (e->getSelected())
                outdegree++;
        }
        if (outdegree % 2 == 1)
            oddDegreeVertices.push_back(v.second);

        v.second->setOutdegree(outdegree);
    }

    return oddDegreeVertices;
}

void Graph::greedyPerfectMatching(vector<Vertex *> &oddDegreeVertexes) {
    Vertex *curr;
    double minDist;
    Edge *toAdd;
    vector<Vertex *>::iterator toRemove;

    while (!oddDegreeVertexes.empty()) {
        curr = oddDegreeVertexes.back();
        oddDegreeVertexes.pop_back();
        toAdd = nullptr;
        minDist = DBL_MAX;

        for (auto itr = oddDegreeVertexes.begin(); itr != oddDegreeVertexes.end(); itr++) {
            Edge *e = curr->findEdge((*itr)->getId());

            if (e->getDistance() < minDist) {
                minDist = e->getDistance();
                toAdd = e;
                toRemove = itr;
            }
        }

        if (toAdd->getSelected()) {
            toAdd->setIsDouble(true);
            toAdd->getReverse()->setIsDouble(true);
            toAdd->getOrig()->setOutdegree(toAdd->getOrig()->getOutdegree() + 1);
            toAdd->getDest()->setOutdegree(toAdd->getDest()->getOutdegree() + 1);
        }
        else {
            toAdd->setSelected(true);
            toAdd->getReverse()->setSelected(true);
            toAdd->getOrig()->setOutdegree(toAdd->getOrig()->getOutdegree() + 1);
            toAdd->getDest()->setOutdegree(toAdd->getDest()->getOutdegree() + 1);
        }

        oddDegreeVertexes.erase(toRemove);
    }
}

double Graph::nearestNeighbourRouteTsp(vInt &path) {
    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    Vertex *currVertex = findVertex(0);
    path[0] = 0;
    Vertex *nextVertex;
    currVertex->setVisited(true);
    double totalDistance = 0;
    int numVisited = 1;

    while (numVisited < vertexSet.size()) {
        double minDistance = DBL_MAX;
        for (auto e: currVertex->getAdj()) {
            if (e->getDistance() < minDistance && !e->getDest()->isVisited()) {
                minDistance = e->getDistance();
                nextVertex = e->getDest();
            }
        }

        if (currVertex == nextVertex) {
            nextVertex = findNearestHaversine(currVertex);
            minDistance = haversineCalculator(currVertex->getLatitude(), currVertex->getLongitude(),nextVertex->getLatitude(), nextVertex->getLongitude());
        }

        totalDistance += minDistance;
        path[numVisited] = nextVertex->getId();
        numVisited++;
        nextVertex->setVisited(true);
        currVertex = nextVertex;
    }

    totalDistance += currVertex->findEdge(0) == nullptr ? haversineCalculator(currVertex->getLatitude(),currVertex->getLongitude(),findVertex(0)->getLatitude(),findVertex(0)->getLongitude()): currVertex->findEdge(0)->getDistance();
    path.push_back(0);

    return totalDistance;
}

Vertex *Graph::findNearestHaversine(Vertex *currentV) {
    auto minDistance = DBL_MAX;
    Vertex *nearestV;
    for (auto v: vertexSet) {
        if (currentV->findEdge(v.second->getId()) || v.second->isVisited()) {
            continue;
        }
        double distance = haversineCalculator(currentV->getLatitude(), currentV->getLongitude(),v.second->getLatitude(), v.second->getLongitude());
        if (distance < minDistance) {
            minDistance = distance;
            nearestV = v.second;
        }
    }

    return nearestV;
}

double Graph::twoOpt(vInt &path, double bestDistance) {
    double newDistance = bestDistance;
    auto size = path.size();
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 1; i < size - 2; i++) {
            for (int k = i + 1; k < size - 1; k++) {
                int delta = -calculateTwoVerticesDist(findVertex(path[i]), findVertex(path[i + 1])) -
                            calculateTwoVerticesDist(findVertex(path[k]), findVertex(path[k + 1])) +
                            calculateTwoVerticesDist(findVertex(path[i]), findVertex(path[k])) +
                            calculateTwoVerticesDist(findVertex(path[i + 1]), findVertex(path[k + 1]));
                if (delta < 0) {
                    path = twoOptSwap(path, i, k);
                    bestDistance += delta;
                    improved = true;
                }
            }
        }
    }

    return bestDistance;
}

double Graph::calculateTwoVerticesDist(Vertex *v1, Vertex *v2) {
    Edge *e = v1->findEdge(v2->getId());
    return e == nullptr ? haversineCalculator(v1->getLatitude(), v1->getLongitude(),v2->getLatitude(), v2->getLongitude()): e->getDistance();
}

vInt Graph::twoOptSwap(vInt path, int i, int k) {
    vInt newPath;
    for (int j = 0; j <= i; j++) {
        newPath.push_back(path[j]);
    }
    for (int j = k; j > i; j--) {
        newPath.push_back(path[j]);
    }
    for (int j = k + 1; j < path.size(); j++) {
        newPath.push_back(path[j]);
    }
    return newPath;
}

vector<Vertex *> Graph::buildEulerianTour() {
    vector<Vertex *> eulerianTour;
    vector<vector<Vertex *>> eulerianPaths;
    vector<Vertex *> oneEulerianPath;
    Vertex *curr;
    bool finished;

    eulerianTour = getOneEulerianPath(findVertex(0));

    while (true) {
        finished = true;

        for (Vertex *v : eulerianTour) {
            if (v->getOutdegree() > 0) {
                curr = v;
                finished = false;
                break;
            }
        }

        if (finished) break;

        eulerianTour = mergePath(eulerianTour, getOneEulerianPath(curr));
    }

    return eulerianTour;
}

vector<Vertex *> Graph::getOneEulerianPath(Vertex *orig) {
    vector<Vertex *> eulerianPath;
    Vertex *curr = orig, *adjOrig, *adjDest;

    eulerianPath.push_back(orig);

    do {
        for (Edge *adj: curr->getAdj()) {
            adjOrig = adj->getOrig();
            adjDest = adj->getDest();

            if (adj->getIsDouble()) {
                adj->setIsDouble(false);
                adj->getReverse()->setIsDouble(false);
                adjOrig->setOutdegree(adjOrig->getOutdegree() - 1);
                adjDest->setOutdegree(adjDest->getOutdegree() - 1);
                eulerianPath.push_back(adj->getDest());
                curr = adj->getDest();

                break;
            }
            else if (adj->getSelected()) {
                adj->setSelected(false);
                adj->getReverse()->setSelected(false);
                adjOrig->setOutdegree(adjOrig->getOutdegree() - 1);
                adjDest->setOutdegree(adjDest->getOutdegree() - 1);
                eulerianPath.push_back(adj->getDest());
                curr = adj->getDest();

                break;
            }
        }
    } while(curr != orig);

    return eulerianPath;
}

vector<Vertex *> Graph::mergePath(vector<Vertex *> &eulerianTour, vector<Vertex *> path) {
    int i = 0;
    vector<Vertex *> newTour;

    while (eulerianTour[i] != path[0])
        newTour.push_back(eulerianTour[i++]);

    for (Vertex *v: path)
        newTour.push_back(v);

    for (; i < eulerianTour.size(); i++)
        newTour.push_back(eulerianTour[i]);

    return newTour;
}

vInt Graph::removeRepeatingVertexes(vector<Vertex *> path) {
    vInt unique_path;

    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    for (Vertex *v: path) {
        if (!v->isVisited()) {
            unique_path.push_back(v->getId());
            v->setVisited(true);
        }
    }

    unique_path.push_back(0);

    return unique_path;
}

double Graph::calculateChrisDistance(vector<Vertex *> eulerianTour) {
    unordered_set<Vertex *> visited;
    double dist = 0;
    int p1 = 0, p2 = 1, count = 0;

    visited.insert(eulerianTour[0]);

    while (p2 != eulerianTour.size()) {
        if (visited.find(eulerianTour[p2]) == visited.end() || p2 == eulerianTour.size() - 1) {
            visited.insert(eulerianTour[p2]);
            dist += eulerianTour[p1]->findEdge(eulerianTour[p2]->getId())->getDistance();
            cout << ++count << "- " << eulerianTour[p1]->getId() << " --> " << eulerianTour[p2]->getId() << endl;
            p1 = p2; p2++;
        }
        else
            p2++;
    }

    return dist;
}

double Graph::christofides(vInt &path) {
    mstBuild();

    vector<Vertex *> oddDegreeVertices = findOddDegreeVertexes();

    greedyPerfectMatching(oddDegreeVertices);

    vector<Vertex *> eulerianTour = buildEulerianTour();

    path = removeRepeatingVertexes(eulerianTour);

    return calculateChrisDistance(eulerianTour);
}
