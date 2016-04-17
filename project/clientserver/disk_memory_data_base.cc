#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <fstream>

#include "database.h"
#include "article.h"
#include "newsgroup.h"
#include "disk_memory_data_base.h"

using namespace std;



DiskMemoryDataBase::DiskMemoryDataBase(const string& root_path)
    : root_directory_path{root_path}
{
    //root_directory_path = "/Users/Andreas/downloads/cppProject/eda031/project/clientserver";
    DIR *root_dp;
    struct dirent *root_dirp;
    string newsgroup_path, article_path;
    string article_author, article_text = "", article_title;
    int article_id;
    ifstream article_stream;
    
    //Read/create root directory
    if ((root_dp = opendir(root_directory_path.c_str())) == NULL) {
        int status;
        status = mkdir(root_directory_path.c_str(), S_IRWXU);
        if (status != 0) {
            cout << "Error(" << errno << ") creating " << root_directory_path << endl;
        }
        else {
            root_dp = opendir(root_directory_path.c_str());
        }
    }
    
    while ((root_dirp = readdir(root_dp)) != NULL) {
        //Create newsgroup object from directory
        Newsgroup newsgroup(root_dirp->d_ino, root_dirp->d_name);
        
        //Open newsgroup directory
        DIR *newsgroup_dp;
        struct dirent *newsgroup_dirp;
        newsgroup_path = root_directory_path + "/" + root_dirp->d_name;
        newsgroup_dp = opendir(newsgroup_path.c_str());
        
        //read files in newsgroup directory
        while ((newsgroup_dirp = readdir(newsgroup_dp)) != NULL) {
            article_title = newsgroup_dirp->d_name;
            article_id = newsgroup_dirp->d_ino;
            article_path = newsgroup_path + "/" + newsgroup_dirp->d_name;
            article_stream.open(article_path.c_str());
            
            string line;
            getline(article_stream, article_author); //First line is always author
            while (getline(article_stream, line)) {
                article_text += line + "\n";
            }
            Article article(article_id, article_author, article_text, article_title);
            article_stream.close();
            newsgroup.addArticle(article);
        }
        closedir(newsgroup_dp);
        newsgroups.push_back(newsgroup);
    }
    closedir(root_dp);
}

vector<pair<string, unsigned int>>
DiskMemoryDataBase::listNewsgroups()
{
    
}

int
DiskMemoryDataBase::addNewsgroup(
             string newsgroup_title)
{
    return 0;
}

int
DiskMemoryDataBase::deleteNewsgroup(
                string newsgroup_title)
{
    return 0;
}

vector<Article>
DiskMemoryDataBase::getArticles(
            string newsgroup_title)
{
    
}

void
DiskMemoryDataBase::addArticle(
           string newsgroup_title,
           string article_name,
           string author,
           string text)
{
    
}

int
DiskMemoryDataBase::deleteArticle(
              string newsgroup_title,
              string article_name)
{
    
}

string
DiskMemoryDataBase::getArticle(
           string newsgroup_title,
           string article_name)
{
    
}