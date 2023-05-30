#include <iostream>
#include "src/Scraper.h"

using namespace std;

int main(){
    Graph gh;

    Scraper::scrape_graph("../src/data/real/graph3/nodes.csv", gh, Scraper::real);
    return 0;
}
