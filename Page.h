#pragma once

#include <iostream>
#include <string>

class Page
{
private:
    std::string url;
    std::string content;

public:
    Page();
    Page(const std::string&, const std::string&);

    std::string getURL() const { return url; }
    std::string getContent() const { return content; }
};
