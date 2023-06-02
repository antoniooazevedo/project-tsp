#include <iostream>
#include "src/Menu.h"
#include <chrono>

using namespace std;

int main(){
    auto start = chrono::high_resolution_clock::now();

    Menu menu = Menu();

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}
