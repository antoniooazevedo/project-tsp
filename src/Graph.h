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

#include "VertexEdge.h"

using namespace std;

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

protected:
    std::unordered_map<int, Vertex *> vertexSet; /**< The vertex set of the graph. */

};

#endif /** DA_TP_CLASSES_GRAPH */