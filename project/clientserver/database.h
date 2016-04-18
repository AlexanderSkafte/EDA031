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
                const std::string& newsgroup_title) = 0;
    
    virtual int
        deleteNewsgroup(
                const std::string& newsgroup_title) = 0;
    
    
    virtual std::vector<Article>
        listArticles(
                const std::string& newsgroup_title) = 0;
    
    virtual void
        createArticle(
               const std::string& newsgroup_title,
               const std::string& article_name,
               const std::string& author,
               const std::string& text) = 0;
    
    virtual int
        deleteArticle(
                  const std::string& newsgroup_title,
                  const std::string& article_name) = 0;
    
    
    
    virtual std::vector<Article>
        getArticle(
               const std::string& newsgroup_title,
               const std::string& article_name) = 0;

};

#endif
