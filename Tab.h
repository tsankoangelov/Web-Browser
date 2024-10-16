#pragma once

#include <iostream>
#include <stack>
#include "Page.h"

class Tab 
{
private:
    std::stack<Page*> backward_pages;
    std::stack<Page*> forward_pages;
    Page* current;

public:
    Tab();
    ~Tab();

    Page* getCurrent() const { return this->current; }

    void go(const std::string &url, std::string &content);
    void back();
    void forward();
};
