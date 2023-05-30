// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Edge;

#define INF std::numeric_limits<int>::max()

/************************* Vertex  **************************/

class Vertex {
public:

    /**
     * Constructor for the Vertex class;
     * @param id - the id of the vertex;
     */
    Vertex(int id);

    /**
     * Constructor for the Vertex class;
     * @param id - the id of the vertex;
     */
    Vertex(int id, double longitude, double latitude);
    /**
     * Returns the id of the vertex;
     */
    int getId() const;

    /**
     * Returns a vector containing all the adjacent edges of the vertex;
     */
    vector<Edge *> getAdj() const;

    /**
     * Retrieves the path of the vertex;
     * @return the edge path of the vertex;
     */
    Edge *getPath() const;

    void setPath(Edge *path);

    /**
     * Retrieves the incoming edges of the vertex;
     * @return a vector containing all the incoming edges of the vertex;
     */
    vector<Edge *> getIncoming() const;

    /**
     * Adds an edge from the vertex (this) to the destination vertex, with a given weight;
     * @param dest - the destination vertex;
     * @param w - the weight of the edge;
     * @return the edge created;
     */
    Edge * addEdge(Vertex *dest, double w);

    /**
     * Auxiliary function to remove an outgoing edge (with a given destination (d))
     * from a vertex (this).
     * Returns true if successful, and false if such edge does not exist.
     */
    bool removeEdge(int destID);

    /**
     * Removes all the outgoing edges of the vertex from the adjacency vector;
     * Time Complexity: O(E), where E is the number of edges;
     */
    void removeOutgoingEdges();

protected:
    int id; /**< The id of the vertex */
    vector<Edge *> adj; /**< The adjacency vector of the vertex */
    Edge *path = nullptr; /**< Edge path of the vertex */
    double latitude, longitude; /**< Latitude and longitude of the vertex */

    vector<Edge *> incoming; /**< Vector of incoming edges of the vertex */

    /**
     * Removes an edge from both its origin and destination vertices;
     * @param edge - the edge to be removed;
     */
    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    /**
     * Constructs an edge with a given origin, destination and capacity;
     * @param orig - the origin vertex of the edge;
     * @param dest - the destination vertex of the edge;
     * @param c - the capacity of the edge;
     */
    Edge(Vertex *orig, Vertex *dest, double distance);

    /**
     * Gets the destination vertex of the edge;
     * @return the destination vertex of the edge;
     */
    Vertex * getDest() const;

    /**
     * Gets the origin vertex of the edge;
     * @return the origin vertex of the edge;
     */
    Vertex * getOrig() const;

    /**
     * Gets the reverse edge of the edge;
     * @return the reverse edge of the edge;
     */
    Edge *getReverse() const;

    /**
     * Sets the reverse attribute of the edge;
     * @param reverse - the reverse edge of the edge;
     */
    void setReverse(Edge *reverse);

protected:
    Vertex * dest; /**< Destination vertex of the edge */
    Vertex *orig; /**< Origin vertex of the edge */
    Edge *reverse = nullptr; /**< Reverse edge of the edge */
    double distance; /**< Distance of the edge */
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */