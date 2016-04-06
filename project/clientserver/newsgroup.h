#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>

class Newsgroup {
public:
    Newsgroup(int id, std::string name);

    int id();
    std::string name();

private:
    std::string name_;
    std::string id_;
    std::list<Article> articles_;
};

#endif

