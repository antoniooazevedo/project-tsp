#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

using namespace std;

class Edge;
/************************* Vertex  **************************/

class Vertex {
public:

    int queueIndex; /**< Index of the vertex in the priority queue */

    /**
     * Constructor for the Vertex class
     * @param id - the id of the vertex
     */
    Vertex(int id);

    /**
     * Constructor for the Vertex class with latitude and longitude information
     * @param id - the id of the vertex
     * @param latitude - latitude of the vertex
     * @param longitude - longitude of the vertex
     */
    Vertex(int id, double longitude, double latitude);

    /**
     * Gets the id attribute of the vertex
     * @return the id of the vertex
     */
    int getId() const;

    /**
     * Gets the adj attribute from the vertex
     * @return a vector containing all the adjacent edges of the vertex
     */
    vector<Edge *> getAdj() const;

    /**
     * Gets the path attribute of the vertex
     * @return The edge that was used to get into this vertex
     */
    Edge *getPath() const;

    /**
     * Sets the path attribute of the vertex
     * @param path - the edge that was used to get into this vertex
     */
    void setPath(Edge *path);

    /**
     * Sets the visited attribute of the vertex
     * @param visited - whether the vertex has been visited or not
     */
    void setVisited(bool visited);

    /**
     * Adds an edge from the vertex (this) to the destination vertex, with a given weight
     * @param dest - the destination vertex
     * @param w - the weight of the edge
     * @return the edge created
     */
    Edge * addEdge(Vertex *dest, double w);

    /**
     * Removes all the outgoing edges of the vertex from the adjacency vector
     * Time Complexity: O(E²), where E is the number of edges
     */
    void removeOutgoingEdges();

    /**
     * Gets the primDist value of the vertex
     * @return the lowest distance this vertex is from a vertex currently chosen by Prim's algorithm
     */
    double getPrimDist() const;

    /**
     * Sets the primDist value of the vertex
     * @param dist - the lowest distance this vertex is from a vertex currently chosen by Prim's algorithm
     */
    void setPrimDist(double dist);

    /**
     * Checks if the vertex has been visited
     * @return the visited value of the vertex
     */
    bool isVisited() const;

    /**
     * Compares primDist values of two vertices to run Prim's algorithm with the mutable priority queue
     * @param vertex - the vertex to be compared to
     * @return true if the primDist value of the vertex is smaller than the primDist value of the vertex passed as an argument
     */
    bool operator<(Vertex & vertex) const;

    /**
     * Get the latitude attribute of the vertex
     * @return the latitude of the vertex
     */
    double getLatitude() const;

    /**
     * Get the longitude attribute of the vertex
     * @return the longitude of the vertex
     */
    double getLongitude() const;

    /**
     * Finds an edge that connects the current vertex (this) to the destination vertex
     * @param dest id of the destination vertex
     * @return a pointer to the selected edge or nullptr if there is no edge connecting the current vertex to dest
     */
    Edge * findEdge(int dest);

    /**
     * Returns the outdegree attribute
     * @return returns the number of outgoing edges from the current vertex
     */
    int getOutdegree() const;

    /**
     * Sets outdegree attribute
     * @param outdegree number of outgoing edges
     */
    void setOutdegree(int outdegree);

protected:
    int id; /**< The id of the vertex */
    vector<Edge *> adj; /**< The adjacency vector of the vertex */
    Edge *path = nullptr; /**< Edge path of the vertex */
    double latitude; /**< Latitude of the vertex */
    double longitude; /**< Longitude of the vertex */
    int outdegree /**< Number of outgoing edges **/;

protected:
    double primDist; /**< Auxiliary distance to be used to run Prim's algorithm */
    bool visited = false; /**< Boolean to check if the vertex has been visited */
    vector<Edge *> incoming; /**< Vector of incoming edges of the vertex */

    /**
     * Removes an edge from both its origin and destination vertices
     * Complexity: O(E) where E is the number of edges of the graph
     * @param edge - the edge to be removed
     */
    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    /**
     * Constructs an edge with a given origin, destination and length
     * @param orig - the origin vertex of the edge
     * @param dest - the destination vertex of the edge
     * @param distance - the length of the edge
     */
    Edge(Vertex *orig, Vertex *dest, double distance);

    /**
     * Gets the dest attribute of the edge
     * @return the destination vertex of the edge
     */
    Vertex * getDest() const;

    /**
     * Gets the orig attribute of the edge
     * @return the origin vertex of the edge
     */
    Vertex * getOrig() const;

    /**
     * Gets the distance attribute of the edge
     * @return the distance between the two vertexes the edge connects
     */
    double getDistance() const;

    /**
     * Gets the selected attribute of the edge
     * @return true if the edge is selected for the eulerian tour, false otherwise
     */
    bool getSelected() const;

    /**
     * Gets the isDouble attribute of the edge
     * @return true if this edge represents two edges between the two vertexes in the eulerian tour, false otherwise
     */
    bool getIsDouble() const;

    /**
     * Gets the reverse attribute of the edge
     * @return the reverse edge of the edge
     */
    Edge *getReverse() const;

    /**
     * Sets the reverse attribute of the edge
     * @param reverse - the reverse edge of the edge
     */
    void setReverse(Edge *reverse);

    /**
     * Sets the selected attribute of the edge
     * @param selected whether the vertex is selected for the eulerian tour
     */
    void setSelected(bool selected);

    /**
     * Sets the isDouble attribute of the edge
     * @param isDouble whether this edge represents two edges between the two vertexes in the eulerian tour
     */
    void setIsDouble(bool isDouble);


protected:
    Vertex * dest; /**< Destination vertex of the edge */
    Vertex *orig; /**< Origin vertex of the edge */
    Edge *reverse = nullptr; /**< Reverse edge of the edge */
    double distance; /**< Length of the edge */
    bool selected; /**< Edge selected to find eulerian path */
    bool isDouble; /**< True if this edge represents two edges between the two vertexes in the eulerian tour */
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */