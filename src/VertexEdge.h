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

    /**
     * Sets the path of the vertex;
     * @param path - the edge path of the vertex;
     */
    void setPath(Edge *path);

    /**
     * Retrieves the incoming edges of the vertex;
     * @return a vector containing all the incoming edges of the vertex;
     */
    vector<Edge *> getIncoming() const;

    /**
     * Returns whether the vertex is visited or not
     * @return true if vertex has been visited, false otherwise
     */
    bool getVisited() const;

    /**
     * Sets the visited attribute of the vertex
     * @param visited - whether the vertex has been visited or not
     */
    void setVisited(bool visited);

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

    /**
     * * Gets the primDist value of the vertex;
     * @return the primDist value of the vertex;
     */
    double getPrimDist() const;

    /**
     * Sets the primDist value of the vertex;
     * @param dist - the lowest distance a vertex is from a vertex currently chosen in Prim's algorithm;
     */
    void setPrimDist(double dist);

    /**
     * Checks if the vertex has been visited;
     * @return the visited value of the vertex;
     */
    bool isVisited() const;

    /**
     * Compares auxDist values of two vertices;
     * @param vertex - the vertex to be compared to;
     * @return true if the auxDist value of the vertex is smaller than the auxDist value of the vertex passed as argument;
     */
    bool operator<(Vertex & vertex) const;

    /**
     * Get the latitude of the vertex;
     * @return the latitude of the vertex;
     */
    double getLatitude() const;


    /**
     * Set the latitude of the vertex;
     * @param latitude - the latitude of the vertex;
     */
    void setLatitude(double latitude);

    /**
     * Get the longitude of the vertex;
     * @return the longitude of the vertex;
     */
    double getLongitude() const;

    /**
     * Set the longitude of the vertex;
     * @param longitude - the longitude of the vertex;
     */
    void setLongitude(double longitude);

    /**
     * Finds an edge that connects the current vertex (this) to the destination vertex
     * @param dest id of the destination vertex
     * @return a pointer to the selected edge or nullptr if there is no edge connecting the current vertex to dest
     */
    Edge * findEdge(int dest);

protected:
    int id; /**< The id of the vertex */
    vector<Edge *> adj; /**< The adjacency vector of the vertex */
    Edge *path = nullptr; /**< Edge path of the vertex */
    double latitude, longitude; /**< Latitude and longitude of the vertex */

protected:
    /**< Latitude and longitude of the vertex */
    double primDist; /**< Auxiliary distance to be used to build mst */
    bool visited = false; /**< Boolean to check if the vertex has been visited */
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
<<<<<<< HEAD
     * Gets the distance of the edge;
     * @return the distance of the edge;
=======
     * @return the distance between the two vertexes the edge connects
>>>>>>> 709bc2efc96836dd83922a9f020fccff9e58d214
     */
    double getDistance() const;

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