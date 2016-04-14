#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <iostream>
#include <string>
#include <list>

class Article;

class Newsgroup {
public:
    Newsgroup(int id, std::string name);

    int         id              ();
    std::string name            ();
    std::string getArticle      (std::string sought_article) const;
    std::string listNewsgroup   () const;
    std::string deleteArticle   (std::string article_name);
    void        addArticle      (Article a);

private:
    std::string name_;
    std::string id_;
    std::list<Article> articles_;
};

#endif
