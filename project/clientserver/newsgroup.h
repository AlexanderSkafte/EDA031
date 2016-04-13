#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include "Article.h"

class Newsgroup {
public:
    Newsgroup(int id, std::string name);

    int id();
    std::string name();
    string getArticle(std::string artName) const;
    string getNG() const;
    std::string deleteArticle(std::string artName);
    void addArticle(Article a);

private:
    std::string name_;
    std::string id_;
    std::list<Article> articles_;
};

#endif
