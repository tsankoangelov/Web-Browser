#include "Tab.h"

Tab::Tab() : current(nullptr) {}

Tab::~Tab()
{
    delete current;

    while (!backward_pages.empty())
    {
        Page *curr = backward_pages.top();
        backward_pages.pop();
        delete curr;
    }

    while (!forward_pages.empty())
    {
        Page *curr = forward_pages.top();
        forward_pages.pop();
        delete curr;
    }
}

void Tab::go(const std::string &url, std::string &content)
{
    Page *page = new Page(url, content);
    backward_pages.push(page);
    current = page;
}

void Tab::back()
{
    if (backward_pages.size() > 1)
    {
        forward_pages.push(current);
        backward_pages.pop();

        current = backward_pages.top();
    }
    else
    {
        std::cout << "No page available to go back!" << std::endl;
    }
}

void Tab::forward()
{
    if (!forward_pages.empty())
    {
        backward_pages.push(current);
        current = forward_pages.top();
        forward_pages.pop();
    }
    else
    {
        std::cout << "No page available to go forward!" << std::endl;
    }
}