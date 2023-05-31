//
// Created by work on 13-05-2023.
//

#include "Scraper.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void Scraper::scrape_graph(string file_name, Graph &gh, enum type_of_graph type) {
    ifstream file(file_name);
    string line;
    if (type != medium) getline(file,line);
    while (getline(file, line)) {
        istringstream iss(line);
        string id, lat, lon, dist, id1, id2;

        if (type==real){
            getline(iss,id,',');
            getline(iss,lon,',');
            getline(iss,lat,'\r');

            auto v = new Vertex(stoi(id), stod(lon), stod(lat));
            gh.addVertex(v);
        }
        else{
            getline(iss,id1,',');
            getline(iss,id2,',');
            getline(iss,dist,',');
            if (dist.back() == '\r') dist.substr(0,dist.size()-1);

            auto v1 = gh.findVertex(stoi(id1)) == nullptr ? new Vertex(stoi(id1)) : gh.findVertex(stoi(id1));
            auto v2 = gh.findVertex(stoi(id2)) == nullptr ? new Vertex(stoi(id2)) : gh.findVertex(stoi(id2));

            gh.addVertex(v1);
            gh.addVertex(v2);
            gh.addBidirectionalEdge(v1,v2,stod(dist));
        }
    }
    if (type == real){
        string edges_file_name = file_name.substr(0,file_name.find_last_of('/') + 1) + "edges.csv";
        scrape_graph_edges(edges_file_name, gh);
    }
}

void Scraper::scrape_graph_edges(std::string file_name, Graph &gh) {
    ifstream file(file_name);
    string line;
    getline(file,line);
    while (getline(file, line)) {
        istringstream iss(line);
        string id1, id2, dist;

        getline(iss,id1,',');
        getline(iss,id2,',');
        getline(iss,dist,'\r');

        auto v1 = gh.findVertex(stoi(id1));
        auto v2 = gh.findVertex(stoi(id2));

        gh.addVertex(v1);
        gh.addVertex(v2);
        gh.addBidirectionalEdge(v1,v2,stod(dist));
    }
}