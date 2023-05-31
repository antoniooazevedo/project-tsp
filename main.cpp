#include <iostream>
#include "src/Scraper.h"
#include <chrono>

using namespace std;

int main(){
    Graph gh;

    auto start = chrono::high_resolution_clock::now();

    Scraper::scrape_graph("../src/data/real/graph1/nodes.csv", gh, Scraper::real);

    vector<int> path(gh.getVertexSet().size());
    cout << (gh.tspBT(path));

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
