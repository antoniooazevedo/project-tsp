#include <iostream>
#include "src/Scraper.h"
#include "src/Menu.h"
#include <chrono>

using namespace std;

int main(){
    auto start = chrono::high_resolution_clock::now();

    vector<Graph*> graphs;

    auto *ghShipping = new Graph;
    Scraper::scrape_graph("../src/data/toy/shipping.csv", *ghShipping, Scraper::toy);
    graphs.push_back(ghShipping);

    auto *ghStadiums = new Graph;
    Scraper::scrape_graph("../src/data/toy/stadiums.csv", *ghStadiums, Scraper::toy);
    graphs.push_back(ghStadiums);

    auto *ghTourism = new Graph;
    Scraper::scrape_graph("../src/data/toy/tourism.csv", *ghTourism, Scraper::toy);
    graphs.push_back(ghTourism);

    auto *ghMedium25 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_25.csv", *ghMedium25, Scraper::medium);
    graphs.push_back(ghMedium25);

    auto *ghMedium50 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_50.csv", *ghMedium50, Scraper::medium);
    graphs.push_back(ghMedium50);

    auto *ghMedium75 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_75.csv", *ghMedium75, Scraper::medium);
    graphs.push_back(ghMedium75);

    auto *ghMedium100 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_100.csv", *ghMedium100, Scraper::medium);
    graphs.push_back(ghMedium100);

    auto *ghMedium200 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_200.csv", *ghMedium200, Scraper::medium);
    graphs.push_back(ghMedium200);

    auto *ghMedium300 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_300.csv", *ghMedium300, Scraper::medium);
    graphs.push_back(ghMedium300);

    auto *ghMedium400 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_400.csv", *ghMedium400, Scraper::medium);
    graphs.push_back(ghMedium400);

    auto *ghMedium500 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_500.csv", *ghMedium500, Scraper::medium);
    graphs.push_back(ghMedium500);

    auto *ghMedium600 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_600.csv", *ghMedium600, Scraper::medium);
    graphs.push_back(ghMedium600);

    auto *ghMedium700 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_700.csv", *ghMedium700, Scraper::medium);
    graphs.push_back(ghMedium700);

    auto *ghMedium800 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_800.csv", *ghMedium800, Scraper::medium);
    graphs.push_back(ghMedium800);

    auto *ghMedium900 = new Graph;
    Scraper::scrape_graph("../src/data/medium/edges_900.csv", *ghMedium900, Scraper::medium);
    graphs.push_back(ghMedium900);

    auto *ghReal1 = new Graph;
    Scraper::scrape_graph("../src/data/real/graph1/nodes.csv", *ghReal1, Scraper::real);
    graphs.push_back(ghReal1);

    auto *ghReal2 = new Graph;
    Scraper::scrape_graph("../src/data/real/graph2/nodes.csv", *ghReal2, Scraper::real);
    graphs.push_back(ghReal2);

    auto *ghReal3 = new Graph;
    Scraper::scrape_graph("../src/data/real/graph3/nodes.csv", *ghReal3, Scraper::real);
    graphs.push_back(ghReal3);

    Menu menu(graphs);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
