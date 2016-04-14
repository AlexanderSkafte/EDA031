#include <string>
#include <algorithm>

using namespace std;

Newsgroup(int id, string name)
    : id_{id}
    , name_{name}
{ }

int
Newsgroup::id() const
{
    return id_;
}

string
Newsgroup::name() const
{
    return name_;
}

vector<Article>
Newsgroup::articles() const
{
	return articles_;
}

void
Newsgroup::createArticle(const Article& a)
{
	articles_.push_back(a);
}

string
Newsgroup::deleteArticle(const string& title)
{
	auto itr = remove_if(articles_.begin(), articles_.end(),
		[&title](const Article& a) {
			return title == a.title();
		});
	if (itr != articles_.end()) {
		articles_.erase(itr, articles_.end());
		return "Deleted article '" + artName + "'.";
	} else {
		return "No article by this name to delete error";
	}
}

string
Newsgroup::getArticle(const string& title) const
{
	auto itr = find_if(articles_.begin(), articles_.end(),
		[&title](const Article& a) {
			return title == a.title();
		});
	if (itr != articles_.end()) {
        return itr->title() + "\n" + itr->author() + "\n" + itr->text() + "\n";
	} else {
		//Probably faulty logic, fix this case
		return nullptr;
	}
}
