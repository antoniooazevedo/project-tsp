
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
        v.second->setIndegree(0);
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

void Graph::dfsMst(Vertex *v, vector<Vertex *> &res) {
    for (auto vertex: vertexSet) {
        vertex.second->setVisited(false);
    }

    v->setVisited(true);
    res.push_back(v);
    for (auto &e: v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited() && e == w->getPath()) {
            dfsMst(w, res);
        }
    }
}

void Graph::calculateTahTotalDistance() {
    double totalDistance = 0;
    auto s = this->findVertex(0);
    vector<Vertex *> res;

    mstBuild();

    dfsMst(s, res);
    res.push_back(s);

    for (auto i = 0; i < res.size() - 1; i++) {
        auto v = res[i];
        auto w = res[i + 1];
        auto e = v->findEdge(w->getId());
        if (e == nullptr) {
            cout << "Error: edge not found" << endl;
            totalDistance += haversineCalculator(v->getLatitude(), v->getLongitude(), w->getLatitude(),
                                                 w->getLongitude());
        } else {
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

vector<Vertex *> Graph::findOddDegreeVertexes() {
    vector<Vertex *> oddDegreeVertices;
    int indegree;

    for (auto v: vertexSet) {
        indegree = 0;
        for (Edge *e: v.second->getAdj()) {
            if (e->getSelected())
                indegree++;
        }
        if (indegree % 2 == 1)
            oddDegreeVertices.push_back(v.second);

        v.second->setIndegree(indegree);
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
            toAdd->getOrig()->setIndegree(toAdd->getOrig()->getIndegree() + 1);
            toAdd->getDest()->setIndegree(toAdd->getDest()->getIndegree() + 1);
        }
        else {
            toAdd->setSelected(true);
            toAdd->getReverse()->setSelected(true);
            toAdd->getOrig()->setIndegree(toAdd->getOrig()->getIndegree() + 1);
            toAdd->getDest()->setIndegree(toAdd->getDest()->getIndegree() + 1);
        }

        oddDegreeVertexes.erase(toRemove);
    }
}

vector<Vertex *> Graph::buildEulerianTour() {
    vector<Vertex *> eulerianTour;
    vector<vector<Vertex *>> eulerianPaths;
    vector<Vertex *> oneEulerianPath;
    Vertex *curr;
    bool finished;

    for (auto v: vertexSet) {
        v.second->setVisited(false);
    }

    eulerianTour = getOneEulerianPath(findVertex(0));

    while (true) {
        finished = true;

        for (Vertex *v : eulerianTour) {
            if (v->getIndegree() > 0) {
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
                adjOrig->setIndegree(adjOrig->getIndegree() - 1);
                adjDest->setIndegree(adjDest->getIndegree() - 1);
                eulerianPath.push_back(adj->getDest());
                curr = adj->getDest();

                break;
            }
            else if (adj->getSelected()) {
                adj->setSelected(false);
                adj->getReverse()->setSelected(false);
                adjOrig->setIndegree(adjOrig->getIndegree() - 1);
                adjDest->setIndegree(adjDest->getIndegree() - 1);
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

double Graph::christofides() {
    mstBuild();

    vector<Vertex *> oddDegreeVertices = findOddDegreeVertexes();

    greedyPerfectMatching(oddDegreeVertices);

    vector<Vertex *> eulerianTour = buildEulerianTour();

    return calculateChrisDistance(eulerianTour);
}
