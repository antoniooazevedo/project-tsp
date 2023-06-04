#ifndef PROJECT_TSP_SCRAPER_H
#define PROJECT_TSP_SCRAPER_H

#include <iostream>
#include "Graph.h"

using namespace std;

class Scraper {
public:

    /// Defines the type of graph to be scraped.
    enum type_of_graph{
        real,
        medium,
        toy
    };

    /**
     * Scrapes a graph from a file.
     * Complexity: O(L*V) in toy and medium graphs where L is the number of lines of the file and V is the number of vertexes,
     * and O(L+E) in real graphs, where L is the number of lines of the nodes file and E is the number of lines of the edges file.
     * @param file_name - the name of the file to be scraped;
     * @param gh - the graph to be populated;
     * @param type - the type of graph to be scraped;
     */
    static void scrape_graph(string file_name, Graph &gh, enum type_of_graph type);

    /**
     * Function to scrape the edges for the real graphs.
     * Complexity: O(L) where L is the number of lines of the file.
     * @param file_name - the name of the file to be scraped;
     * @param gh - the graph to be populated;
     */
    static void scrape_graph_edges(string file_name, Graph &gh);
};


#endif //PROJECT_TSP_SCRAPER_H
