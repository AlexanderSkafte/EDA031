#include <string>

#include "Article.h"

using namespace std;

Article::Article(int id, string author, string text)
    : id_{id}
    , author_{author}
    , text_{text}
{ }

int
Article::id()
{
    return id_;
}

string
Article::author()
{
    return author_;
}

string
Article::text()
{
    return text_;
}

