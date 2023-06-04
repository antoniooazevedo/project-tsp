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
#include "chrono"
#include <unordered_set>

using namespace std;

typedef unsigned int uint;
typedef vector<int> vInt;

class Graph {
public:
    /**
     * Graph's destructor
     */
    ~Graph();

    /**
     * Auxiliary function to find a vertex with a given id
     * Complexity: O(1)
     * @param id - the id of the vertex
     * @return the vertex with the given id or nullptr if it isn't found
    */
    Vertex *findVertex(const int &id) const;

    /**
     * Adds a vertex to a graph (this)
     * Complexity: O(1)
     * @param v - the vertex to be added
     * @return true - if successful
     *         false - if a vertex with that id already exists
     */
    bool addVertex(Vertex *v);

    /**
     * Gets the vertexSet of the graph
     * Time Complexity: O(1)
     * @return a map with all the vertexes of the graph.
     */
    unordered_map<int, Vertex *> getVertexSet() const;

    /**
     * Adds a bidirectional edge to the graph between two vertexes with a given distance
     * Time Complexity: O(1)
     * @param v1 - the first vertex
     * @param v2 - the second vertex
     * @param dist - the length of the edge
     * @return true if successful, false otherwise
     */
    bool addBidirectionalEdge(Vertex * &v1, Vertex * &v2, double dist);

    /**
     * Builds the minimum spanning tree of the graph using Prim's algorithm
     * Complexity: O(E*log(V)) where E is the number of edges and V the number of edges of the graph
     */
    void mstBuild();

    /**
     * Depth first search on the graph, which defines the route for the 2-approximate tsp algorithm
     * Complexity: O(V+E)
     * @param v - vertex to start the dfs
     * @param path - vector with the vertexes in the order visited in the dfs
     * @param count - number of vertexes that have already been assigned an order
     */
    void dfsMst(Vertex *v, vInt &path, int &count);

    /**
     * Computes the total distance of the route in the argument path
     * Complexity: O(V+E)
     */
    double calculateTahTotalDistance(vInt &path);

    /**
     * Computes the distance between two points using the haversine formula
     * Complexity: O(1)
     * @param lat1  - latitude of the first vertex
     * @param long1 - longitude of the first vertex
     * @param lat2 - latitude of the second vertex
     * @param long2 - longitude of the second vertex
     * @return distance between the two vertexes
     */
    double haversineCalculator(double lat1, double long1, double lat2, double long2);

    /**
     * Calls the backtracking algorithm for the travelling salesman problem
     * Complexity: O(V!) being V the number of vertexes in the graph
     * @param path vector that keeps the vertexes in the order they were visited
     * @return distance travelled in the backtracking algorithm for the travelling salesman problem
     */
    double tspBT(vInt &path);

    /**
     * Recursive backtracking algorithm that gives the optimal solution to the traveling salesman problem
     * Complexity: O(V!) being V the number of vertexes in the graph
     * @param path vector that keeps the vertexes in the order they were visited in a previous dfs call
     * @param currVertexId id of the currently visited vertex
     * @param currSum distance travelled through the vertexes that were visited
     * @param bestSum least distance travelled through all the vertexes until now
     * @param step number of vertexes that were already visited
     * @return best distance travelled from all the sets that were already tried
     */
    double tspBacktracking(vInt &path, int currVertexId, double currSum, double bestSum, uint step);

    /**
     * Computes the nearest neighbour route for the travelling salesman problem
     * Complexity: O(V^2 * E) where V is the number of vertexes and E the number of edges in the graph
     */
    double nearestNeighbourRouteTsp(vInt &path);

    /**
     * Find nearest vertex from currentV that isn't connected to it through a direct edge on the graph. The distance is determined with the Haversine formula
     * Complexity: O(V*E) where V is the number of vertexes and E is the number of edges of the graph
     * @param currentV vertex to compare to
     * @return the vertex with no edge directly connected to currentV that is the closest to currentV
     */
    Vertex * findNearestHaversine(Vertex *currentV);

    /**
     * Performs a swap in the 2-opt tour improvement algorithm
     * Complexity: O(V) being V the number of vertexes in the graph
     * @param path current order of the vertexes to compute the tsp distance
     * @param i index of the first vertex in path to be considered in the swap
     * @param k index of the second vertex in path to be considered in the swap
     * @return updated reordered path according to the swap
     */
    vInt twoOptSwap(vInt path, int i, int k);

    /**
     * Tour improvement algorithm to be ran after a solution has been found for the tsp problem
     * Complexity: the complexity of this algorithm isn't clear. However, the lower bound is Ω(E*V³) where V is the number
     * of vertexes and E the number of edges in the graph. The upper bound could be O(E*V³) as well, but a 2opt swap isn't
     * guaranteed to not for a new intersection between edges
     * @param path tour considered in the algorithm that gave the solution to the tsp
     * @param bestDistance distance that comes from a previous heuristic to find the solution for the tsp
     * @return the lowest distance of the path obtained with this algorithm
     */
    double twoOpt(vInt &path, double bestDistance);

    /**
     * Computes the distance between two vertexes. If there is an edge between the vertexes, the length of the edge is used.
     * Otherwise, the Haversine formula is used
     * Complexity: O(E) where E is the number of edges in the graph
     * @param v1 the first vertex to be considered
     * @param v2 the second vertex to be considered
     * @return the distance between v1 and v2
     */
    double calculateTwoVerticesDist(Vertex *v1, Vertex *v2);

    /**
     * Runs the christofides heuristic to solve the tsp problem. This version of the algorithm uses a greedy approach
     * instead of the blossom algorithm for the perfect matching step
     * Complexity: O(V²*E) where V is the number of vertixes and E the number of edges in the graph
     * @param path vector that will be filled with the eulerian path without repeated vertexes (excluding the starting vertex)
     * @return distance travelled in the christofides algorithm for the travelling salesman problem
     */
    double christofides(vInt &path);

    /**
     * Finds all the vertexes in a previously built MST that have an odd number of outgoing edges
     * Complexity: O(V*E) where V is the number of vertexes and E the number of edges in the graph
     * @return a vector with all the vertexes that follow the criteria above
     */
    vector<Vertex *> findOddDegreeVertexes();

    /**
     * Performs a greedy perfect matching between the vertexes in the oddDegreeVertexes vector
     * Complexity: O(V²*E) where V is the number of vertexes and E is the number of edges in the graph
     * @param oddDegreeVertexes vector of the vertexes that have an odd number of outgoing edges in a previously build MST
     */
    void greedyPerfectMatching(vector<Vertex *> &oddDegreeVertexes);

    /**
     * Builds an eurelian tour, that is, a tour that passes by each edge only once and that starts and ends in the same vertex
     * This tour passes by all the vertexes in the graph
     * Complexity: O((V+E) * V) where V is the number of vertexes and E the number of edges in the graph
     * @return the order in which the vertexes are traversed in the eulerian tour
     */
    vector<Vertex *> buildEulerianTour();

    /**
     * Builds one eulerian path, that is, a path that starts in the vertex orig and ends in that same vertex. The build path
     * does not have to traverse every edge and vertex of the graph
     * Complexity: O(V+E) where V is the number of vertexes and E is the number of edges in the graph
     * @param orig vertex to start the path
     * @return
     */
    vector<Vertex *> getOneEulerianPath(Vertex *orig);

    /**
     * Merges an eulerian path into the current eulerian tour
     * Complexity: O(V) where V is the number of vertexes in the graph
     * @param eulerianTour current eulerian tour
     * @param path eulerian path recently found
     * @return updated eulerian tour with the recently found path merged into it
     */
    vector<Vertex *> mergePath(vector<Vertex *> &eulerianTour, vector<Vertex *> path);

    /**
     * Computes the distance that takes to traverse the eulerian tour
     * Complexity: O(V) where V is the number of vertexes in the graph
     * @param eulerianTour order of the vertexes in the eulerian tour
     * @return total distance that was traversed
     */
    double calculateChrisDistance(vector<Vertex *> eulerianTour);

    vInt removeRepeatingVertexes(vector<Vertex *> path);

protected:
    std::unordered_map<int, Vertex *> vertexSet; /**< The map with all the vertexes of the graph */


};

#endif /** DA_TP_CLASSES_GRAPH */