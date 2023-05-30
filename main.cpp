#include <iostream>
#include "src/Scraper.h"
#include <chrono>
#include "src/Tah.h"

using namespace std;

int main(){
    Graph gh;

    auto start = chrono::high_resolution_clock::now();

    Scraper::scrape_graph("../src/data/real/graph1/nodes.csv", gh, Scraper::toy);

    Tah::mstBuild(&gh);


    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
