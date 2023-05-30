//
// Created by work on 13-05-2023.
//

#ifndef PROJECT_TSP_SCRAPER_H
#define PROJECT_TSP_SCRAPER_H

#include <iostream>
#include "Graph.h"

using namespace std;

class Scraper {
public:
    /**
     * Enum to define the type of graph to be scraped.
     */
    enum type_of_graph{
        real,
        medium,
        toy
    };

    /**
     * Scrapes a graph from a file.
     * Time Complexity: O(L) where L is the number of lines of the file, or O(L+E) if its the real graphs, where L is the number of lines of the nodes file and E is the number of lines of the edges file.
     * @param file_name - the name of the file to be scraped;
     * @param gh - the graph to be scraped;
     * @param type - the type of graph to be scraped;
     */
    static void scrape_graph(string file_name, Graph &gh, enum type_of_graph type);

    /**
     * Function to scrape the edges for the real graphs.
     * Time Complexity: O(L) where L is the number of lines of the file.
     * @param file_name - the name of the file to be scraped;
     * @param gh - the graph to be scraped;
     */
    static void scrape_graph_edges(string file_name, Graph &gh);
};


#endif //PROJECT_TSP_SCRAPER_H
