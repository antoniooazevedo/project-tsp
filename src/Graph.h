// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string>
#include <unordered_set>
#include <math.h>

#include "VertexEdge.h"
#include "MutablePriorityQueue.h"


using namespace std;

class Graph {
public:
    /**
     * Default constructor for the Graph class;
     */
    ~Graph();

    /**
     * Auxiliary function to find a vertex with a given ID.
     * @param id - the id of the vertex;
     * @return the vertex with the given id;
    */
    Vertex *findVertex(const int &id) const;

    /**
     *  Adds a vertex with a given string id to a graph (this).
     *  @param id - the id of the vertex;
     *  @return true - if successful
     *          false - if a vertex with that id already exists.
     */
    bool addVertex(const int &id);

    /**
     * Adds a vertex to a graph (this).
     * @param v - the vertex to be added;
     * @return true - if successful
     *         false - if a vertex with that id already exists.
     */
    bool addVertex(Vertex *v);


    /**
     * Removes a vertex with a given string id from a graph (this).
     * @param id - the id of the vertex;
     * @return true - if successful
     *         false - if a vertex with that id does not exist.
     */
    bool removeVertex(const int &id);

    /**
     * Removes a vertex from a graph (this).
     * @param v - the vertex to be removed;
     * @return true - if successful
     *         false - if a vertex with that id does not exist.
     */
    bool removeVertex(Vertex *v);

    /**
     * Gets the vertex set of a graph (this).
     * @return the vertex set.
     */
    unordered_map<int, Vertex *> getVertexSet() const;

    /**
     * Depth first search that gives each vertex the number of the connected component it is in
     * Time Complexity: O(V+E) where V is the number of vertexes and E the number of edges of the graph (this)
     * @param src - Vertex we are in
     * @param i - number of the connected component
     */
    void connectedComponentsDfs(Vertex *src, int i);

    /**
     * add an edge to the graph
     * @param v1 - first vertex
     * @param v2 - second vertex
     * @param distance - distance between the two vertexes
     */
    bool addEdge(Vertex *v1, Vertex *v2, double distance);

    /**
     * add a bidirectional edge to the graph
     * @param v1 - first vertex
     * @param v2 - second vertex
     * @param distance - distance between the two vertexes
     */
    bool addBidirectionalEdge(Vertex * &v1, Vertex * &v2, double dist);

    /**
     * builds the minimum spanning tree of the graph using Prim's algorithm
     * complexity: O(E*log(V))
     */
    void mstBuild();

    /**
     * dfs that build the route for the tsp
     *  complexity: O(V+E)
     * @param v - vertex to start the dfs
     * @param res - vector with the vertexes in the dfs order
     */
    void dfsMst(Vertex *v, vector<Vertex *> &res);

    /**
     * calculates the total distance of the route
     */
    void calculateTotalDistance(bool real);

    /**
     * calculate the distance between two points using the haversine formula
     * complexity: O(1)
     * @param lat1  - latitude of the first point
     * @param long1 - longitude of the first point
     * @param lat2 - latitude of the second point
     * @param long2 - longitude of the second point
     * @return distance between the two points
     */
    double haversineCalculator(double lat1, double long1, double lat2, double long2);

protected:
    std::unordered_map<int, Vertex *> vertexSet; /**< The vertex set of the graph. */

};

#endif /** DA_TP_CLASSES_GRAPH */