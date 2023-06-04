#include "VertexEdge.h"

using namespace std;

/************************* Vertex  **************************/

Vertex::Vertex(int id, double longitude, double latitude)
        : id(id), latitude(latitude), longitude(longitude) {}

Vertex::Vertex(int id) : id(id) {
    this->latitude = 0;
    this->longitude = 0;
}

int Vertex::getId() const {
    return this->id;
}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}


std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

Edge *Vertex::getPath() const {
    return this->path;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

double Vertex::getPrimDist() const {
    return this->primDist;
}

void Vertex::setPrimDist(double dist) {
    this->primDist = dist;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->primDist < vertex.primDist;
}

double Vertex::getLatitude() const {
    return latitude;
}

double Vertex::getLongitude() const {
    return longitude;
}

Edge *Vertex::findEdge(int dest) {
    for (Edge *e: this->adj) {
        if (e->getDest()->getId() == dest)
            return e;
    }

    return nullptr;
}

int Vertex::getOutdegree() const {
    return this->outdegree;
}

void Vertex::setOutdegree(int outdegree) {
    this->outdegree = outdegree;
}

/********************** Edge  ****************************/


Edge::Edge(Vertex *orig, Vertex *dest, double distance): orig(orig), dest(dest), distance(distance) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getDistance() const {
    return this->distance;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}


void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

bool Edge::getSelected() const {
    return this->selected;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setIsDouble(bool isDouble) {
    this->isDouble = isDouble;
}

bool Edge::getIsDouble() const {
    return this->isDouble;
}

