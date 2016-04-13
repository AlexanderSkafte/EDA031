#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
    Article(int id, std::string author, std::string text, std::string title);
    int id();
    std::string title();
    std::string author();
    std::string text();
private:
    int id_;
    std::string title_;
    std::string author_;
    std::string text_;
};

#endif

