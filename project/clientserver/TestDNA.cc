
#include <iostream>
#include "in_memory_data_base.h"
#include "database.h"
#include "newsgroup.h"
#include "article.h"

using namespace std;

int main()
{
	//Test article class
	cout << "1. Test Article class: " << endl;
	Article a1(1, "Author", "Text", "Title");
	cout << "ID: " << a1.id() << endl;
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
	newsgroup.addArticle(a1);
	Article a2(0, "Author 2", "Text 2", "Title 2");
	newsgroup.addArticle(a2);
	cout << "Adding successful!" << endl << endl;
	cout << "Newsgroup list: " << endl;
	cout << newsgroup.listNewsgroup() << endl;
	cout << "Testing delete function..." << endl;
	newsgroup.deleteArticle("Title 2");
	cout << "Delete function successful" << endl;
	cout << endl;

	//Test IMDB class
	cout << "3. Test IMDB class:" << endl;
	in_memory_data_base imdb;
	cout << "Testing addArticle..." << endl;
	imdb.addArticle("Newsgroup", "Article name", "Author 3", "Text 3");
	cout << "addArticle successful!" << endl;
	cout << "Testing addNewsgroup..." << endl;
	imdb.addNewsgroup("addNewsgroup test");
	cout << "addNewsgroup was successful!" << endl;
	cout << "Testing getNewsgroup: " << endl;
	//cout << "1. " << imdb.getArticles("addNewsgroup test") << endl;
	//cout << "2. " << imdb.getArticles("Newsgroup") << endl;
	cout << endl;
	cout << "Testing getArticle: " << imdb.getArticle("Newsgroup", "Article name") << endl;
	cout << "Testing deleteNewsgroup..." << endl;
	imdb.deleteNewsgroup("addNewsgroup test");
	cout << "Deletion successful!" << endl;
	cout << "Testing deleteArticle..." << endl;
	imdb.deleteArticle("Newsgroup", "Article name");
	cout << "Deletion successful!" << endl;
}
