#pragma once

#include <iostream>
#include <unordered_map>
#include <iterator>
#include <fstream>

#include "Tab.h"
#include "slow-web.h"
#include "Favourites.h"

class Browser
{
private:
    std::vector<Tab *> tabs;
    Tab *currentTab;
    int current_index_of_browser_tab;
    Favourites favourite_pages;
    std::vector<std::pair<std::string, std::string>> pages;
    std::vector<std::string> global_history;
    

public:
    Browser();
    ~Browser();
    std::vector<std::pair<std::string, std::string>> readFromFile();
    void newTab(const std::string&, std::string&);
    void closeTab();
    void switchTab(int&);
    void menu();
    void print_history();
};
