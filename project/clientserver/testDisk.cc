
#include <iostream>
#include <sstream>
#include "disk_memory_data_base.h"

using namespace std;

int main() {
	cout << "Testing dmdb: " << endl;
    string root_path = "/Users/Andreas/downloads/cppProject/eda031/project/clientserver/root";
	DiskMemoryDataBase dmdb(root_path);
    cout << "First init of DMDB successful!" << endl;
    
    cout << "Testing addNewsgroup fcn..." << endl;
    cout << dmdb.createNewsgroup("Newsgroup 1") << endl;
    cout << "addNewsgroup successful!" << endl;
    
    cout << "Testing addArticle..." << endl;
    dmdb.createArticle("Newsgroup 2", "Article 2", "Andreas", "Text...");
    cout << "addArticle successful!" << endl;
    
    cout << "Testing getArticle..." << endl;
    cout << dmdb.getArticle("Newsgroup 2", "Article 2") << endl;
    cout << "getArticle successful!" << endl;
    
    cout << "Testing getArticles..." << endl;
    auto vec = dmdb.listArticles("Newsgroup 2");
    for (auto a : vec) {
        cout << "Title: " << a.title() << endl;
        //cout << "ID: " << a.id() << endl;
    }
    cout << "getArticles successful!" << endl;
    
    cout << "Testing deleteNewsgroup..." << endl;
    cout << dmdb.deleteNewsgroup("Newsgroup 1") << endl;
    cout << "deleteNewsgroup successful!" << endl;
    
    cout << "Testing listNewsgroups..." << endl;
    dmdb.listNewsgroups();
    cout << "listNewsgroups successful!" << endl;
    
    cout << "Testing deleteArticle..." << endl;
    //cout << dmdb.deleteArticle("Newsgroup 2", "Article 2") << endl;
    cout << "deleteArticle successful!" << endl;
}
