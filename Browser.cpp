#include "Browser.h"

Browser::Browser() : currentTab(new Tab()), current_index_of_browser_tab(0)
{
    tabs.push_back(currentTab);
}

Browser::~Browser()
{
    delete currentTab;

    for (Tab *&tab : tabs)
    {
        delete tab;
    }
}

std::vector<std::pair<std::string, std::string>> Browser::readFromFile()
{
    std::vector<std::pair<std::string, std::string>> startUpPages;
    std::string line, temp1, temp2;

    std::ifstream file("test.csv");

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::size_t locate_index = line.find(',');
            temp1 = line.substr(0, locate_index);
            line.erase(locate_index + 2, 1);
            temp2 = line.substr(locate_index + 2);
            temp2.erase(temp2.size() - 1);

            std::pair<std::string, std::string> temp(temp1, temp2);
            startUpPages.push_back(temp);
        }

        file.close();
    }
    else
    {
        std::cout << "Error" << std::endl;
        return startUpPages;
    }

    return startUpPages;
}

void Browser::newTab(const std::string &url, std::string &content)
{
    Tab *newTab = new Tab();
    newTab->go(url, content);
    tabs.push_back(newTab);
    currentTab = newTab;
    current_index_of_browser_tab = tabs.size() - 1;
    global_history.push_back(url);
}

void Browser::closeTab()
{
    if (tabs.size() > 1)
    {
        std::vector<Tab *>::iterator it = tabs.begin();
        for (int i = 0; i < current_index_of_browser_tab; i++)
        {
            it++;
        }

        tabs.erase(it);
        delete currentTab;
        current_index_of_browser_tab--;

        if (current_index_of_browser_tab == -1)
        {
            currentTab = tabs.back();
            current_index_of_browser_tab = tabs.size() - 1;

            global_history.push_back(currentTab->getCurrent()->getURL());
        }
        else
        {
            currentTab = tabs[current_index_of_browser_tab];

            global_history.push_back(currentTab->getCurrent()->getURL());
        }
    }
    else
    {
        std::cout << "Can not close the only tab!" << std::endl;
    }
}

void Browser::switchTab(int& index)
{
    if (index >= 0 && index < tabs.size())
    {
        tabs[current_index_of_browser_tab] = currentTab;
        currentTab = tabs[index];
        current_index_of_browser_tab = index;

        global_history.push_back(currentTab->getCurrent()->getURL());
    }
    else
    {
        std::cout << "Invalid tab index!" << std::endl;
    }
}

void Browser::menu()
{
    pages = readFromFile();
    std::string command;
    std::size_t size_of_pages = pages.size();
    SlowWeb slowWeb(pages);

    while (true)
    {
        std::cin >> command;
        if (command == "go")
        {
            std::string url;
            std::cin >> url;
            bool temp = false;

            for (std::size_t i = 0; i < size_of_pages; i++)
            {
                if (pages[i].first == url)
                {
                    temp = true;

                    currentTab->go(url, pages[i].second);
                    std::cout << slowWeb.getContent(url) << std::endl;
                }
            }

            if (temp == false)
            {
                std::string str = "404: Not Found";
                currentTab->go(url, str);
                std::cout << str << std::endl;
            }

            global_history.push_back(url);
        }
        else if (command == "back")
        {

            currentTab->back();

            std::cout << slowWeb.getContent(currentTab->getCurrent()->getURL()) << std::endl;

            global_history.push_back(currentTab->getCurrent()->getURL());
        }
        else if (command == "forward")
        {
            currentTab->forward();

            std::cout << slowWeb.getContent(currentTab->getCurrent()->getURL()) << std::endl;

            global_history.push_back(currentTab->getCurrent()->getURL());
        }
        else if (command == "newtab")
        {
            std::string url;
            std::cin >> url;
            bool temp = false;

            for (std::size_t i = 0; i < size_of_pages; i++)
            {
                if (pages[i].first == url)
                {
                    temp = true;
                    newTab(url, pages[i].second);
                    std::cout << slowWeb.getContent(url) << std::endl;
                }
            }

            if (temp == false)
            {
                std::string str = "404: Not Found";
                newTab(url, str);
                std::cout << str << std::endl;
            }
        }
        else if (command == "closetab")
        {
            closeTab();
            std::cout << slowWeb.getContent(currentTab->getCurrent()->getURL()) << std::endl;
        }
        else if (command == "switchtab")
        {
            int index;
            std::cin >> index;
            switchTab(index);
            std::cout << slowWeb.getContent(currentTab->getCurrent()->getURL()) << std::endl;
        }
        else if (command == "bookmark")
        {
            std::string line, name, folder;
            std::cin.ignore();
            std::getline(std::cin, line);

            line.erase(0, 1);
            std::size_t locate_index = line.find('"');
            name = line.substr(0, locate_index);
            std::size_t size = line.size();
            if (locate_index + 2 < size)
            {
                folder = line.substr(locate_index + 2);
            }

            if (folder.empty())
            {
                favourite_pages.bookmark_on_main_folder(name);
            }
            else
            {
                favourite_pages.bookmark(name, folder);
            }
        }
        else if (command == "viewbookmarks")
        {
            std::string line, folder;
            std::getline(std::cin, line);

            if (!line.empty())
            {
                folder = line.substr(1);
            }

            if (folder.empty())
            {
                favourite_pages.viewBookmarks_in_main_folder();
            }
            else
            {
                favourite_pages.viewBookmarks(folder);
            }
        }
        else if (command == "removebookmark")
        {
            std::string line, name, folder;
            std::cin.ignore();
            std::getline(std::cin, line);

            line.erase(0, 1);
            std::size_t locate_index = line.find('"');
            name = line.substr(0, locate_index);

            if (locate_index + 2 < line.size())
            {
                folder = line.substr(locate_index + 2);
            }

            if (folder.empty())
            {
                favourite_pages.removeBookmark_in_main_folder(name);
            }
            else
            {
                favourite_pages.removeBookmark(name, folder);
            }
        }
        else if (command == "quit")
        {
            return;
        }
        else
        {
            std::cout << "Invalid command" << std::endl;
        }
    }
}

void Browser::print_history()
{
    for (std::string str : global_history)
    {
        std::cout << str << std::endl;
    }

    return;
}