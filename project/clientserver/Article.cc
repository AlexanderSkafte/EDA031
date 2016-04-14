#include <string>

#include "Article.h"

using namespace std;

Article::Article(string author, string text, string title)
    : author_{author}
    , text_{text}
    , title_{title}
{ }


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

