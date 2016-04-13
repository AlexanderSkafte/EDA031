#include <stdio>

#include "client.h"
#include "connection.h"
#include <iostream>
#include <string>
#include <map>

using namespace protocol;
using namespace std;

client::client() {
	inmemorydb db = new inmemorydb();
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
client::createNewsgroup(messagehandler mh)
{
	string newsgroup_name = mh.recvString();
	unsigned char resp = 

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
