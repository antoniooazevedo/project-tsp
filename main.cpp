#include <iostream>
#include "src/Scraper.h"
#include "src/Menu.h"
#include <chrono>

using namespace std;

int main(){
    auto *gh = new Graph();

    auto start = chrono::high_resolution_clock::now();

    Menu menu(*gh);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
