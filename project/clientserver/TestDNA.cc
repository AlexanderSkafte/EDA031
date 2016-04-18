#include <iostream>
#include "in_memory_data_base.h"
#include "newsgroup.h"
#include "article.h"

using namespace std;

int main()
{
	//Test article class
	cout << "1. Test Article class: " << endl;
	Article a1("Author", "Text", "Title");
	cout << "Title: " << a1.title() << endl;
	cout << "Author: " << a1.author() << endl;
	cout << "Text: " << a1.text() << endl;
	cout << "Test successful! On to test 2..." << endl;
	cout << endl;

	//Test Newsgroup class
	cout << "2. Test Newsgroup class: " << endl;
	Newsgroup newsgroup(0, "Newsgroup");
	cout << "Newsgroup id: " << newsgroup.id() << endl;
	cout << "Newsgroup name: " << newsgroup.name() << endl;
	cout << "Adding article to newsgroup..." << endl;
	newsgroup.createArticle(a1);
	Article a2("Author 2", "Text 2", "Title 2");
	newsgroup.createArticle(a2);
	cout << "Adding successful!" << endl << endl;
	cout << "Newsgroup list: " << endl;
	vector<Article> vec = newsgroup.listNewsgroup();
	for (auto i = vec.begin(); i<vec.end(); ++i) {
		cout <<  i->author() << " " << i->text() << endl;
	}
	cout << "Testing delete function..." << endl;
	newsgroup.deleteArticle("Title 2");
	cout << "Delete function successful" << endl;
	cout << endl;

	//Test IMDB class
	cout << "3. Test IMDB class:" << endl;
	InMemoryDataBase imdb;
	cout << "testing createNewsgroup" << endl;
	imdb.createNewsgroup("apa");
	vector<pair<string, unsigned int>> veco = imdb.listNewsgroups();
	cout << veco.at(0).first << "does it work?" << endl;
	cout << "Testing createArticle..." << endl;
	imdb.createArticle("Newsgroup", "Article name", "Author 3", "Text 3");
	cout << "createArticle successful!" << endl;
	cout << "Testing createNewsgroup..." << endl;
	imdb.createNewsgroup("createNewsgroup test");
	cout << "createNewsgroup was successful!" << endl;
	cout << "Testing getNewsgroup: " << endl;
	//cout << "1. " << imdb.getArticles("createNewsgroup test") << endl;
	//cout << "2. " << imdb.getArticles("Newsgroup") << endl;
	cout << endl;
	cout << "Testing getArticle: " << imdb.getArticle("Newsgroup", "Article name") << endl;
	cout << "Testing deleteNewsgroup..." << endl;
	imdb.deleteNewsgroup("createNewsgroup test");
	cout << "Deletion successful!" << endl;
	cout << "Testing deleteArticle..." << endl;
	imdb.deleteArticle("Newsgroup", "Article name");
	cout << "Deletion successful!" << endl;
}
