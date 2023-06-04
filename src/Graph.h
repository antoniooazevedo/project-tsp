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
#include <climits>
#include <cfloat>
#include <cmath>
#include "VertexEdge.h"
#include "MutablePriorityQueue.h"
#include "Graph.h"
#include <unordered_set>


using namespace std;

typedef unsigned int uint;
typedef vector<int> vInt;

class Graph {
public:
    /**
     * Default constructor for the Graph class;
     */
    ~Graph();

    /**
     * Auxiliary function to find a vertex with a given ID.
     * Time Complexity: O(1
     * @param id - the id of the vertex;
     * @return the vertex with the given id;
    */
    Vertex *findVertex(const int &id) const;

    /**
     *  Adds a vertex with a given string id to a graph (this).
     *  Time Complexity: O(1)
     *  @param id - the id of the vertex;
     *  @return true - if successful
     *          false - if a vertex with that id already exists.
     */
    bool addVertex(const int &id);

    /**
     * Adds a vertex to a graph (this).
     * Time Complexity: O(1)
     * @param v - the vertex to be added;
     * @return true - if successful
     *         false - if a vertex with that id already exists.
     */
    bool addVertex(Vertex *v);


    /**
     * Removes a vertex with a given string id from a graph (this).
     * Time Complexity: O(V), where V is the number of vertices of the graph.
     * @param id - the id of the vertex;
     * @return true - if successful
     *         false - if a vertex with that id does not exist.
     */
    bool removeVertex(const int &id);

    /**
     * Removes a vertex from a graph (this).
     * Time Complexity: O(V), where V is the number of vertices of the graph.
     * @param v - the vertex to be removed;
     * @return true - if successful
     *         false - if a vertex with that id does not exist.
     */
    bool removeVertex(Vertex *v);

    /**
     * Gets the vertex set of a graph (this).
     * Time Complexity: O(1)
     * @return the vertex set.
     */
    unordered_map<int, Vertex *> getVertexSet() const;

    /**
     * Adds an edge to the graph between two vertexes with a given distance.
     * Time Complexity: O(1)
     * @param v1 - the first vertex
     * @param v2 - the second vertex
     * @param distance - the distance of the edge
     * @return true if successful, false otherwise
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
    bool addEdge(Vertex *v1, Vertex *v2, double distance);

    /**
     * Adds a bidirectional edge to the graph between two vertexes with a given distance.
     * Time Complexity: O(1)
     * @param v1 - the first vertex
     * @param v2 - the second vertex
     * @param distance - the distance of the edge
     * @return true if successful, false otherwise
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
    void calculateTahTotalDistance();

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

    /**
     * Calls the backtracking algorithm for the travelling salesman problem
     * @param path vector that keeps the vertexes in the order they were visited
     * @return distance travelled in the backtracking algorithm for the travelling salesman problem
     */
    double tspBT(vInt &path);

    /**
     * Recursive backtracking algorithm that gives the optimal solution to the traveling salesman problem
     * @param path vector that keeps the vertexes in the order they were visited
     * @param currVertexId id of the currently visited vertex
     * @param currSum distance travelled through the vertexes that were visited
     * @param bestSum least distance travelled through all the vertexes until now
     * @param step number of vertexes that were already visited
     * @return best distance travelled from all the sets that were already experimented
     */
    double tspBacktracking(vInt &path, int currVertexId, double currSum, double bestSum, uint step);

    void nearestNeighbourRouteTsp();

    double christofides();

    vector<Vertex *> findOddDegreeVertexes();

    void greedyPerfectMatching(vector<Vertex *> &oddDegreeVertexes);

    vector<Vertex *> buildEulerianTour();

    vector<Vertex *> getOneEulerianPath(Vertex *orig);

    vector<Vertex *> mergePath(vector<Vertex *> &eulerianTour, vector<Vertex *> path);

    double calculateChrisDistance(vector<Vertex *> eulerianTour);

protected:
    std::unordered_map<int, Vertex *> vertexSet; /**< The vertex set of the graph. */

};

#endif /** DA_TP_CLASSES_GRAPH */