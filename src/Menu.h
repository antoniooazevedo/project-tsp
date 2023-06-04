#ifndef PROJECT_TSP_MENU_H
#define PROJECT_TSP_MENU_H

#include <cstdlib>
#include <iostream>
#include <stack>
#include <limits>
#include "Scraper.h"

using namespace std;

class Menu {
public:
    Menu();

private:
    stack<int> menuStack; /**< Stack to keep track of the menus. */
    int currentMenu; /**< Current menu. */
    Graph* gh; /**< Pointer to the graph. */
    Graph loadedGraph; /**< Graph to be loaded. */
    Scraper::type_of_graph type; /**< Type of the graph. */
    string group; /**< Group of the graph. */
    string graph; /**< Name of the graph. */

    /**
     * Enum to define the menus.
     */
    enum menus{
        main_menu = 1,
        specific_graphs = 2,
        choose_algorithm = 3,
    };

    /**
     * Draws the main menu.
     */
    void drawMainMenu();

    /**
     * Draws the specific graphs menu.
     */
    void drawSpecificGraphs();

    /**
     * Function that draws the menu from the top of the stack.
     */
    void drawMenu();

    /**
     * Function to change the menu.
     * @param newMenu - the new menu.
     */
    void changeMenu(int newMenu);

    /**
     * Function to go back to the previous menu.
     */
    void back();

    /**
     * Function to get the option from the user.
     * @param option - the option to be returned.
     */
    void getOption(string &option);

    /**
     * Function to load a graph.
     * @param group - the group of the graph.
     * @param graph - the name of the graph.
     * @return true if the graph was loaded, false otherwise.
     */
    bool loadGraph(int group, string graph);

    /**
     * Function to draw the choose algorithm menu.
     */
    void drawChooseAlgorithm();
};


#endif //PROJECT_TSP_MENU_H
