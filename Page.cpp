#include "Page.h"

Page::Page() : url(nullptr), content(nullptr) {}
Page::Page(const std::string &url, const std::string &content) : url(url), content(content) {}