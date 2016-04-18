#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include "article.h"
#include "newsgroup.h"

/*An interface for the Database classes*/
class DataBase {
public:
	virtual ~DataBase() {} //destructor for inherited class
	
    virtual std::vector<std::pair<std::string, unsigned int>>
		listNewsgroups() = 0;
    
    virtual int
        createNewsgroup(
                std::string) = 0;
    
    virtual int
        deleteNewsgroup(
                    std::string newsgroup_title) = 0;
    
    
    virtual std::vector<Article>
        listArticles(
                std::string newsgroup_title) = 0;
    
    virtual void
        createArticle(
               std::string newsgroup_title, std::string article_name,
               std::string author, std::string text) = 0;
    
    virtual int
        deleteArticle(
                  std::string newsgroup_title,
                  std::string article_name) = 0;
    
    
    
    virtual std::vector<Article>
        getArticle(
               std::string newsgroup_title,
               std::string article_name) = 0;

};

#endif
