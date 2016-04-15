#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include <list>
#include <map>

class Article;

class Newsgroup {
public:
    Newsgroup                       (int id, const std::string& name);

    int             id              () const;
    std::string     name            () const;
    std::vector<Article>
                    articles        () const;
    void            createArticle   (const Article& a);
    std::string     deleteArticle   (const std::string& title);
    std::string     getArticle      (const std::string& title) const;

private:
    std::string name_;
    std::string id_;
    std::list<Article> articles_;
};

#endif
