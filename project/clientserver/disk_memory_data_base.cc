#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <regex>
#include <sstream>
#include <cstring>

#include "database.h"
#include "article.h"
#include "newsgroup.h"
#include "disk_memory_data_base.h"
#include "protocol.h"

using namespace std;



DiskMemoryDataBase::DiskMemoryDataBase(const string& root_path)
    : root_directory_path{root_path}
{
    DIR     *root_dp;
    struct  dirent *root_dirp;
    string  newsgroup_path, article_path;
    string  article_author, article_text = "", article_title;
    int     article_id;
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
    
    //Create init_file if it doesn't exist, read it otherwise
    ifstream init_stream;
    init_stream.open(root_directory_path + "/init_file");
    if (!init_stream.good()) {
        newsgroup_id    = 0;
        article_id      = 0;
        write_to_init(article_id, newsgroup_id);
    } else {
        read_init();
    }
    
    while ((root_dirp = readdir(root_dp)) != NULL) {
        //Create newsgroup object from directory
        if (!strcmp(root_dirp->d_name, ".")         ||
            !strcmp(root_dirp->d_name, "..")        ||
            !strcmp(root_dirp->d_name, ".DS_Store") ||
            !strcmp(root_dirp->d_name, "init_file"))
        {
            continue;
        }
        
        //Save newsgroup as object
        int current_newsgroup_id        = get_id(root_dirp->d_name);
        string current_newsgroup_name   = get_name(root_dirp->d_name);
        Newsgroup newsgroup(current_newsgroup_id, current_newsgroup_name);
        
        //Open newsgroup directory
        DIR             *newsgroup_dp;
        struct dirent   *newsgroup_dirp;
        newsgroup_path  = root_directory_path + "/" + root_dirp->d_name;
        newsgroup_dp    = opendir(newsgroup_path.c_str());
        
        //read files in newsgroup directory
        while ((newsgroup_dirp = readdir(newsgroup_dp)) != NULL) {
            
            if (!strcmp(newsgroup_dirp->d_name, ".")    ||
                !strcmp(newsgroup_dirp->d_name, "..")   ||
                !strcmp(root_dirp->d_name, ".DS_Store"))
            {
                continue;
            }
            article_title   = get_name(newsgroup_dirp->d_name);
            article_id      = get_id(newsgroup_dirp->d_name);
            article_path    = newsgroup_path + "/" + newsgroup_dirp->d_name;
            article_stream.open(article_path.c_str());
            
            string line;
            getline(article_stream, article_author); //First line = author
            while (getline(article_stream, line)) {
                article_text += line + "\n";
            }
            Article article(article_title, article_author, article_text);
            article_stream.close();
            newsgroup.createArticle(article);
        }
        closedir(newsgroup_dp);
        newsgroups.push_back(newsgroup);
    }
    closedir(root_dp);
}

vector<pair<string, unsigned int>>
DiskMemoryDataBase::listNewsgroups()
{
    vector<pair<string, unsigned int>> vec;
    for (Newsgroup newsgroup : newsgroups) {
        vec.push_back(make_pair(newsgroup.name(), newsgroup.id()));
    }
    return vec;
}

int
DiskMemoryDataBase::createNewsgroup(
             const string& newsgroup_title)
{
    auto itr = find_if(newsgroups.begin(), newsgroups.end(),
             [newsgroup_title](Newsgroup ng) {
                 return ng.name() == newsgroup_title;
             });
    
    if (itr == newsgroups.end()) {
        ostringstream           newsgroup_id_string;
        newsgroup_id_string <<  newsgroup_id;
        
        string  newsgroup_path  = root_directory_path + "/" + newsgroup_id_string.str()
                                    + "_" + newsgroup_title;
        int     status          = mkdir(newsgroup_path.c_str(), S_IRWXU);
        
        if (status != 0) {
            cout << "Error(" << errno << ") creating " << newsgroup_path << endl;
            //Borde returnera ett error här. Vet dock inte vad det skulle vara...
        }
        
        Newsgroup newsgroup(newsgroup_id, newsgroup_title);
        newsgroups.push_back(newsgroup);
        write_to_init(article_id, newsgroup_id);
        ++newsgroup_id;
        
        return Protocol::ANS_ACK;
    } else {
        return Protocol::ERR_NG_ALREADY_EXISTS;
    }
}

int
DiskMemoryDataBase::deleteNewsgroup(
                const string& newsgroup_title)
{
    for (auto itr = newsgroups.begin(); itr != newsgroups.end(); ++itr) {
        if (itr->name() == newsgroup_title) {
            ostringstream           newsgroup_id_string;
            newsgroup_id_string <<  itr->id();
            string newsgroup_path = root_directory_path + "/" + convert.str()
                                    + "_" + itr->name();
            remove(newsgroup_path.c_str());
            newsgroups.erase(itr);
            
            return Protocol::ANS_ACK;
        }
    }
    return Protocol::ERR_NG_DOES_NOT_EXIST;
}

vector<Article>
DiskMemoryDataBase::listArticles(
            const string& newsgroup_title)
{
    vector<Article> vec;
    for (Newsgroup newsgroup : newsgroups) {
        if (newsgroup.name() == newsgroup_title) {
            vec = newsgroup.listNewsgroup();
            return vec;
        }
    }
    return vec;
}

void
DiskMemoryDataBase::createArticle(
           const string& newsgroup_title,
           const string& article_name,
           const string& author,
           const string& text)
{
    
    string current_newsgroup_id;
    Article article(article_id, article_name, author, text);
    auto itr = find_if(newsgroups.begin(), newsgroups.end(),
                       [newsgroup_title](Newsgroup ng) {
                           return ng.name() == newsgroup_title;
                       });
    
    if (itr != newsgroups.end()) {
        itr->createArticle(article);
        current_newsgroup_id = itr->id();
    } else {
        createNewsgroup(newsgroup_title);
        auto& newsgroup = newsgroups.back();
        newsgroup.createArticle(article);
        current_newsgroup_id = newsgroup.id();
    }
    
    string newsgroup_path = root_directory_path + "/" + current_newsgroup_id +
                            "_" + newsgroup_title;
    ofstream article_file;
    ostringstream stringed_article_id;
    stringed_article_id << article_id;
    article_file.open(newsgroup_path + "/" + stringed_article_id.str() + "_" + article_name);
    article_file << article_id << "\n";
    article_file << author + "\n";
    article_file << text;
    ++article_id;
    write_to_init(article_id, newsgroup_id);
    
    article_file.close();
}

int
DiskMemoryDataBase::deleteArticle(
              const string& newsgroup_title,
              const string& article_name)
{
    auto newsgroup_itr = find_if(newsgroups.begin(), newsgroups.end(),
                       [newsgroup_title](Newsgroup ng) {
                           return newsgroup_title == ng.name();
                       });
    if (newsgroup_itr != newsgroups.end()) {
        vector<Article> article_vec = newsgroup_itr->listNewsgroup();
        
        auto itr = find_if(article_vec.begin(), article_vec.end(),
                           [article_name](Article a) {
                               return article_name == a.title();
                           });
        
        if (itr != article_vec.end()) {
            ostringstream newsgroup_id_string, article_id_string;
            newsgroup_id_string << itr->art_id();
            article_id_string << itr->art_id();
            
            string article_path = root_directory_path + "/" + newsgroup_id_string.str() + "_" +
                                    newsgroup_itr->name() + "/" + article_id_string.str() + "_" +
                                    article_name;
            
            newsgroup_itr->deleteArticle(article_name);
            remove(article_path.c_str());
            return Protocol::ANS_ACK;
        } else {
            return Protocol::ERR_ART_DOES_NOT_EXIST;
        }
    } else {
        return Protocol::ERR_NG_DOES_NOT_EXIST;
    }
}

vector<Article>
DiskMemoryDataBase::getArticle(
           const string& newsgroup_title,
           const string& article_name)
{
    vector<Article> vec;
    auto itr = find_if(newsgroups.begin(), newsgroups.end(),
                       [newsgroup_title](Newsgroup ng) {
                           return newsgroup_title.compare(ng.name()) == 0;
                       });
   
    if (itr != newsgroups.end()) {
        vec = itr->getArticle(article_name);
        return vec;
    } else {
        return vec;
    }
}

void
DiskMemoryDataBase::write_to_init(
            int article_id,
            int newsgroup_id)
{
    ofstream init_file;
    init_file.open(root_directory_path + "/init_file");
    init_file << article_id << "\n";
    init_file << newsgroup_id << "\n";
    init_file.close();
}
            
int
DiskMemoryDataBase::get_id(const string& filename)
{
    regex rgx("^(\\d+)_.*$");
    smatch match;
    
    if (regex_search(filename, match, rgx)) {
        return stoi(match[1]);
    }
}
            
string
DiskMemoryDataBase::get_name(const string& filename)
{
    regex rgx("^\\d+_(.*)$");
    smatch match;
    
    if (regex_search(filename, match, rgx)) {
        return match[1];
    }
}

void
DiskMemoryDataBase::read_init()
{
    ifstream init_stream;
    init_stream.open(root_directory_path + "/init_file");
    string stringed_article_id;
    getline(init_stream, stringed_article_id);
    article_id = stoi(stringed_article_id); //First line = articles_id
                
    string stringed_newsgroup_id;
    getline(init_stream, stringed_newsgroup_id);
    newsgroup_id = stoi(stringed_newsgroup_id); //Second line = newsgroups_id
    init_stream.close();
}
            
            
