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
    enum type_of_graph{
        real,
        medium,
        toy
    };

    static void scrape_graph(string file_name, Graph &gh, enum type_of_graph type);
    static void scrape_graph_edges(string file_name, Graph &gh);
};


#endif //PROJECT_TSP_SCRAPER_H
