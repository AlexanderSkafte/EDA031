#include <stdio>

#include "client.h"

using namespace std;

void
client::menu()
{
    cout << "Options:" << endl << "1: List newsgroups" << endl << "2: Create newsgroup" << endl << "3: Delete newsgroup" << endl << "4: List articles in a newsgroup" << endl << "5: Read articles in a newsgroup" << endl << "6: Write article" << endl << "7: Delete Article" << endl; 
}

void 
client::choise()
{
    int ch;
    string name;
    cout << "Enter your option: " << endl;
    cin >> ch;
    switch (ch) 
        case(1):
            listNewsgroups();
        case(2):
            cout << "Enter name of new newsgroup:" << endl;
            cin >> name;
            createNewsgroup(name);
        case(3):
            cout << "Enter name of newsgroup you want to delete:" << endl;
            cin >> name;
            deleteNewsgroup(name);
        case(4):
            ListArticles();
        case(5):
            readAtricles();
        case(6):
            cout << "Enter nae of new Article
            cout << "Enter nae of new Article"
            writeArticle();
        case(7):
            deleteArticle();
        default: 
            cerror << "Non existant choise" << endl;
            exit(1);
}

void 
client::listNewsgroups()
{
    cout << newsgroups: << endl;
    for(auto ng: newsgroups){
        cout << ng.name() << endl;
    }
}

void 
client::createNewsgroup(const string name)
{
    // id behöver tas hand om på något sätt...
    newsgroups.insert(new newsgroup(id, name));
}

void 
client::deleteNewsgroup(const string name)
{
    newsgroups.remove(name);
}

void
client::listArticles(const string name){
    // en for each sats för varje artikel i name..
}

void 
readArticle(string name)
{
    // liknande funktionen ovan
}

void writeArticle(
