#include "Menu.h"

Menu::Menu(vector<Graph *> Graphs) {
    graphs = Graphs;
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
    cin >> option;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (option == "q" || option == "Q") {
        exit(0);
    }
}

void Menu::drawMenu() {
    switch (currentMenu) {
        case main_menu:
            drawMainMenu();
            break;
        case specific_graphs:
            drawSpecificGraphs();
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
    back();
    drawMenu();
}

bool Menu::loadGraph(int group, string graph) {

    try {
        stoi(graph);
    } catch (invalid_argument &e) {
        cout << "Invalid option!" << endl;
        drawMenu();
    }


    switch (group) {
        case 1:
            switch (stoi(graph)) {
                case 1:
                    gh = graphs[0];
                    gh->calculateTahTotalDistance();
                    break;
                case 2:
                    gh = graphs[1];
                    gh->calculateTahTotalDistance();
                    break;
                case 3:
                    gh = graphs[2];
                    gh->calculateTahTotalDistance();
                    break;
                default:
                    cout << "Invalid option. Try Again\n";
                    return false;
            }
            break;
        case 2:
            switch (stoi(graph)) {
                case 1:
                    gh = graphs[3];
                    gh->calculateTahTotalDistance();
                    break;
                case 2:
                    gh = graphs[4];
                    gh->calculateTahTotalDistance();
                    break;
                case 3:
                    gh = graphs[5];
                    gh->calculateTahTotalDistance();
                    break;
                case 4:
                    gh = graphs[6];
                    gh->calculateTahTotalDistance();
                    break;
                case 5:
                    gh = graphs[7];
                    gh->calculateTahTotalDistance();
                    break;
                case 6:
                    gh = graphs[8];
                    gh->calculateTahTotalDistance();
                    break;
                case 7:
                    gh = graphs[9];
                    gh->calculateTahTotalDistance();
                    break;
                case 8:
                    gh = graphs[10];
                    gh->calculateTahTotalDistance();
                    break;
                case 9:
                    gh = graphs[11];
                    gh->calculateTahTotalDistance();
                    break;
                case 10:
                    gh = graphs[12];
                    gh->calculateTahTotalDistance();
                    break;
                case 11:
                    gh = graphs[13];
                    gh->calculateTahTotalDistance();
                    break;
                case 12:
                    gh = graphs[14];
                    gh->calculateTahTotalDistance();
                    break;
                default:
                    cout << "Invalid option. Try Again\n";
                    return false;
            }
            break;
        case 3:
            switch (stoi(graph)) {
                case 1:
                    gh = graphs[15];
                    gh->calculateTahTotalDistance();
                    break;
                case 2:
                    gh = graphs[16];
                    gh->calculateTahTotalDistance();

                    break;
                case 3:
                    gh = graphs[17];
                    gh->calculateTahTotalDistance();
                    break;
                default:
                    cout << "Invalid option. Try Again\n";
                    return false;
            }
    }
    return true;
}

