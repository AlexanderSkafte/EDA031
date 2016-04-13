
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

string getArticle(string artName) {
	auto itr = find_if(articles_.begin, articles_.end, 
			[artName](string thisArt) {
			return thisArt == artName;
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

string getNG() const {
	string articles;
	for_each(articles_.begin, articles_.end, 
			[](Article a) {
			articles += a.title + "\n";
			});
	return articles;
}

string deleteArticle(string artName) {
	auto itr = remove_if(articles_.begin, articles_.end,
			[artName](Article a) {
			return artName == a.title;
			});
	if (itr == articles_.end) {
		return "No article by this name to delete error";
	}
	articles_.erase(itr, articles_.end);
	return "Deleted article " + artName;
}

void addArticle(Article a) {
	articles_.push_back(a);
}

