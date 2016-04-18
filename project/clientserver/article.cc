#include <string>

#include "article.h"

using namespace std;

Article::Article(int art_id, string author, string text, string title)
    : id_{art_id}
    , author_{author}
    , text_{text}
    , title_{title}
{
    
}

Article::Article(string title, string author, string text)
    : author_{author}
    , text_{text}
    , title_{title}
{ }

int
Article::art_id()
{
    return id_;
}

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
