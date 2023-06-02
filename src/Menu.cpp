#include "Menu.h"

Menu::Menu() {
    menuStack.push(main_menu);
    currentMenu = main_menu;
    drawMenu();
}

void Menu::changeMenu(int newMenu) {
    menuStack.push(newMenu);
    currentMenu = menuStack.top();
    drawMenu();
}

void Menu::back() {
    menuStack.pop();
    if (menuStack.empty()) {
        exit(0);
    }
    currentMenu = menuStack.top();
}

void Menu::getOption(string &option) {
    cout << "\n>> ";
    getline(cin, option);

    if (option == "q" || option == "Q") {
        exit(0);
    }
}

void Menu::drawMenu() {
    system("clear");
    switch (currentMenu) {
        case main_menu:
            drawMainMenu();
            break;
        case specific_graphs:
            drawSpecificGraphs();
            break;
        case choose_algorithm:
            drawChooseAlgorithm();
            break;
        default:
            break;
    }
}

void Menu::drawMainMenu() {
    cout << "Choose which graph to load:" << endl;
    cout << "1 - Toy Graphs" << endl;
    cout << "2 - Medium Graphs" << endl;
    cout << "3 - Real Graphs" << endl;
    cout << "q - Exit" << endl;

    getOption(group);

    try {
        stoi(group);
    } catch (invalid_argument &e) {
        cout << "Invalid option!" << endl;
        drawMenu();
    }

    if (stoi(group) < 1 || stoi(group) > 3) {
        cout << "Invalid option!" << endl;
        drawMenu();
    }
    changeMenu(specific_graphs);
}

void Menu::drawSpecificGraphs() {
    switch (stoi(group)) {
        case 1:
            cout << "Choose which graph to load:" << endl;
            cout << "1 - Shipping" << endl;
            cout << "2 - Stadiums" << endl;
            cout << "3 - Tourism" << endl;
            cout << "b - Back" << endl;

            do {
                getOption(graph);
                if (graph == "b" || graph == "B") {
                    break;
                }
            } while (!loadGraph(1, graph));
            break;
        case 2:
            cout << "Choose which graph to load:" << endl
                 << "1 - 25 nodes" << endl
                 << "2 - 50 nodes" << endl
                 << "3 - 75 nodes" << endl
                 << "4 - 100 nodes" << endl
                 << "5 - 200 nodes" << endl
                 << "6 - 300 nodes" << endl
                 << "7 - 400 nodes" << endl
                 << "8 - 500 nodes" << endl
                 << "9 - 600 nodes" << endl
                 << "10 - 700 nodes" << endl
                 << "11 - 800 nodes" << endl
                 << "12 - 900 nodes" << endl
                 << "b - Back" << endl;

            do {
                getOption(graph);
                if (graph == "b" || graph == "B") {
                    break;
                }
            } while (!loadGraph(2, graph));
            break;
        case 3:
            cout << "Choose which graph to load:" << endl
                 << "1 - Graph 1 (1K nodes 500K edges)" << endl
                 << "2 - Graph 2 (5K nodes 3M edges)" << endl
                 << "3 - Graph 3 (10K nodes 10M edges)" << endl
                 << "b - Back" << endl;

            do {
                getOption(graph);
                if (graph == "b" || graph == "B") {
                    break;
                }
            } while (!loadGraph(3, graph));
            break;
        default:
            break;
    }
    changeMenu(choose_algorithm);
    drawMenu();
}

bool Menu::loadGraph(int group, string graph) {

    try {
        stoi(graph);
    } catch (invalid_argument &e) {
        cout << "Invalid option!" << endl;
        drawMenu();
    }

    string filename;
    Scraper::type_of_graph type;
    switch (group) {
        case 1:
            type = Scraper::toy;
            switch (stoi(graph)) {
                case 1:
                    filename = "../src/data/toy/shipping.csv";
                    break;
                case 2:
                    filename = "../src/data/toy/stadiums.csv";
                    break;
                case 3:
                    filename = "../src/data/toy/tourism.csv";
                    break;
                default:
                    cout << "Invalid option. Try Again\n";
                    return false;
            }
            break;
        case 2:
            type = Scraper::medium;
            switch (stoi(graph)) {
                case 1:
                    filename = "../src/data/medium/edges_25.csv";
                    break;
                case 2:
                    filename = "../src/data/medium/edges_50.csv";
                    break;
                case 3:
                    filename = "../src/data/medium/edges_75.csv";
                    break;
                case 4:
                    filename = "../src/data/medium/edges_100.csv";
                    break;
                case 5:
                    filename = "../src/data/medium/edges_200.csv";
                    break;
                case 6:
                    filename = "../src/data/medium/edges_300.csv";
                    break;
                case 7:
                    filename = "../src/data/medium/edges_400.csv";
                    break;
                case 8:
                    filename = "../src/data/medium/edges_500.csv";
                    break;
                case 9:
                    filename = "../src/data/medium/edges_600.csv";
                    break;
                case 10:
                    filename = "../src/data/medium/edges_700.csv";
                    break;
                case 11:
                    filename = "../src/data/medium/edges_800.csv";
                    break;
                case 12:
                    filename = "../src/data/medium/edges_900.csv";
                    break;
                default:
                    cout << "Invalid option. Try Again\n";
                    return false;
            }
            break;
        case 3:
            type = Scraper::real;
            switch (stoi(graph)) {
                case 1:
                    filename = "../src/data/real/graph1/nodes.csv";
                    break;
                case 2:
                    filename = "../src/data/real/graph2/nodes.csv";
                    break;
                case 3:
                    filename = "../src/data/real/graph3/nodes.csv";
                    break;
                default:
                    cout << "Invalid option. Try Again\n";
                    return false;
            }
    }
    Scraper::scrape_graph(filename, loadedGraph, type);
    gh = &loadedGraph;
    return true;
}

void Menu::drawChooseAlgorithm() {
    string option;
    cout << "Choose which algorithm to run:" << endl
        << "1 - Backtracking" << endl
        << "2 - Triangular Approximation" << endl
        << "3 - Nearest Neighbor" << endl
        << "4 - Christofides' Algorithm" << endl
        << "b - Back" << endl;

    getOption(option);

    if (stoi(option) < 1 || stoi(option) > 4) {
        cout << "Invalid option!" << endl;
        drawMenu();
    }

    vInt path;
    switch (stoi(option)) {
        case 1:
            gh->tspBT(path);
            break;
        case 2:
            gh->calculateTahTotalDistance();
            break;
        case 3:
            //gh->nearestNeighbourRouteTsp();
            break;
        case 4:
            break;
        default:
            break;
    }
    string dummy;
    cout << "Press anything to continue...\n";
    getline(cin, dummy);

    back(); back(); // to go back to main menu
    drawMenu();
}

