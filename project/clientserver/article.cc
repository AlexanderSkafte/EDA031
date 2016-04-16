#include <string>

#include "article.h"

using namespace std;

Article::Article(string title, string author, string text)
    : author_{author}
    , text_{text}
    , title_{title}
{ }

string
Article::title() const
{
	return title_;
}
string
Article::author() const
{
    return author_;
}

string
Article::text() const
{
    return text_;
}
