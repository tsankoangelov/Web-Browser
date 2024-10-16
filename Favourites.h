#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


class Favourites
{
private:
    std::unordered_map<std::string, std::vector<std::string>> bookmarks;
    std::vector<std::string> bookmarks_in_main_folder;
public:

    void bookmark(const std::string&, const std::string&);
    void bookmark_on_main_folder(const std::string&);

    void viewBookmarks(const std::string&);
    void viewBookmarks_in_main_folder();

    void removeBookmark(const std::string &, const std::string&);
    void removeBookmark_in_main_folder(const std::string&);
};
