
#include <string>
#include <algorithm>
#include "article.h"
#include "newsgroup.h"

using namespace std;

Newsgroup::Newsgroup(int id, string name)
	: id_{id}
	, name_{name}
{

}

int
Newsgroup::id()
{
	return id_;
}

string
Newsgroup::name()
{
	return name_;
}

vector<Article>
Newsgroup::getArticle(const string& sought_article) const
{
    vector<Article> vec;
    for (auto a : articles_) {
        if (a.title() == sought_article) {
            vec.push_back(a);
        }
    }
    return vec;
}

vector<Article>
Newsgroup::listNewsgroup() const
{
	return articles_;
}

bool
Newsgroup::deleteArticle(string article_name)
{
	auto itr = remove_if(articles_.begin(), articles_.end(),
		[article_name](Article a) {
		return article_name == a.title();
	});
	if (itr == articles_.end()) {
		return false;
	}
	articles_.erase(itr, articles_.end());
	return true;
}

void
Newsgroup::createArticle(Article a)
{
	articles_.push_back(a);
}
