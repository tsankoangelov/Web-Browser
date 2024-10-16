#include "Favourites.h"

void Favourites::bookmark(const std::string &name, const std::string &folder)
{
    if (bookmarks.find(folder) == bookmarks.end())
    {
        bookmarks[folder] = std::vector<std::string>();
    }

    bookmarks[folder].push_back(name);
}

void Favourites::bookmark_on_main_folder(const std::string &name)
{
    bookmarks_in_main_folder.push_back(name);
}

void Favourites::viewBookmarks(const std::string &folder)
{
    if (bookmarks.find(folder) != bookmarks.end())
    {
        if (bookmarks[folder].empty())
        {
            std::cout << std::endl;
            return;
        }

        for (std::string bookmark : bookmarks[folder])
        {
            std::cout << bookmark << std::endl;
        }
    }
    else
    {
        std::cout << folder << " doesn't exist." << std::endl;
    }
}

void Favourites::viewBookmarks_in_main_folder()
{
    if (bookmarks_in_main_folder.empty())
    {
        std::cout << std::endl;
        return;
    }

    for (std::string bookmark : bookmarks_in_main_folder)
    {
        std::cout << bookmark << std::endl;
    }
}

void Favourites::removeBookmark(const std::string &name, const std::string &folder)
{
    if (bookmarks.find(folder) != bookmarks.end())
    {
        std::vector<std::string> &folderBookmarks = bookmarks[folder];
        std::vector<std::string>::iterator it = folderBookmarks.begin();
        while (it != folderBookmarks.end())
        {
            if (*it == name)
            {
                folderBookmarks.erase(it);
                return;
            }
            else
            {
                it++;
            }
        }

        std::cout << "Bookmark: " << name << " not found in folder: " << folder << std::endl;
    }
    else
    {
        std::cout << "Folder: " << folder << " does not exist!" << std::endl;
    }
}

void Favourites::removeBookmark_in_main_folder(const std::string &name)
{
    std::vector<std::string>::iterator it = bookmarks_in_main_folder.begin();
    while (it != bookmarks_in_main_folder.end())
    {
        if (*it == name)
        {
            bookmarks_in_main_folder.erase(it);
            return;
        }
        else
        {
            it++;
        }
    }

    std::cout << "Bookmark: " << name << " not found in main folder: " << std::endl;
}