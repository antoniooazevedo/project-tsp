//
// Created by work on 13-05-2023.
//

#include "Scraper.h"
#include <fstream>
#include <sstream>

using namespace std;

void Scraper::scrape_graph_nodes(string file_name, Graph &gh, enum type_of_graph type) {
    ifstream file(file_name);
    string line;
    if (type != medium) getline(file,line);
    while (getline(file, line)) {
        istringstream iss(line);
        string id, lat, lon, dist, id1, id2;

        if (type==real){
            getline(iss,id,',');
            getline(iss,lon,',');
            getline(iss,lat,',');

            auto v = new Vertex(stoi(id), stod(lon), stod(lat));
            gh.addVertex(v);
        }
        else{
            getline(iss,id1,',');
            getline(iss,id2,',');
            getline(iss,dist,',');

            auto v1 = new Vertex(stoi(id1));
            auto v2 = new Vertex(stoi(id2));
            gh.addVertex(v1);
            gh.addVertex(v2);
            gh.addEdge(v1,v2,stod(dist));
        }
    }
}