#include <string>

#include "Article.h"

using namespace std;

Article::Article(int id, string author, string text, string title)
    : id_{id}
    , author_{author}
    , text_{text}
    , title_{title}
{ }

int
Article::id()
{
    return id_;
}

string
Article::title()
{
	return title_;
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

