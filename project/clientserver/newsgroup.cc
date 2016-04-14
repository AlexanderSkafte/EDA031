
#include <string>
#include <algorithm>

using namespace std;

Newsgroup(int id, string name)
    : id_{id}
    , name_{name}
{ }

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

string
Newsgroup::getArticle(string sought_article)
{
	auto itr = find_if(articles_.begin, articles_.end,
			[sought_article](string current_article) {
			return current_article == sought_article;
			});
	if (itr != articles_.end) {
		string article = itr->title() + "\n"
			+ itr->author() + "\n"
			+ itr->text + "\n";
		return article;
	} else {
		//Probably faulty logic, fix this case
		return nullptr;
	}
}

vector<Article>
Newsgroup::listNewsgroup() const
{
	return articles_;
}

string
Newsgroup::deleteArticle(string article_name)
{
	auto itr = remove_if(articles_.begin, articles_.end,
			[article_name](Article a) {
			return article_name == a.title;
			});
	if (itr == articles_.end) {
		return "No article by this name to delete error";
	}
	articles_.erase(itr, articles_.end);
	return "Deleted article " + artName;
}

void
Newsgroup::addArticle(Article a)
{
	articles_.push_back(a);
}