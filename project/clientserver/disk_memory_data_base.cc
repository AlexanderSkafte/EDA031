#include <iostream>

using namespace std;

DiskMemoryDataBase()
{
    //Create ptr to directory
    //Read
    vector<string> files;
    DIR *dp;
    struct dirent *dirp,
    if ((dp = opendir(root_directory_path.c_str())) == NULL) {
        int status;
        status = mkdir(root_directory_path, S_IRWXU);
        if (status != 0) {
            cout << "Error(" << errno << ") creating " << root_directory_path << endl;
            return errno;
        } else {
            dp = opendir(root_directory_path.c_str());
        }
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        //Create newsgroup object
        //Open newsgroup directory
        //read files in newsgroup directory
        //create article objects from files
        files.push_back(string(dirp->name));
    }
    closedir(dp);
    return 0;
}

vector<pair<string, unsigned int>>
DiskMemoryDataBase::listNewsgroups()
{
    
}

int
DiskMemoryDataBase::addNewsgroup(
             string newsgroup_title)
{
    
}

int
DiskMemoryDataBase::deleteNewsgroup(
                string newsgroup_title);

vector<Article>
DiskMemoryDataBase::getArticles(
            string newsgroup_title);

void
DiskMemoryDataBase::addArticle(
           string newsgroup_title,
           string article_name,
           string author,
           string text);

int
DiskMemoryDataBase::deleteArticle(
              string newsgroup_title,
              string article_name);

string
DiskMemoryDataBase::getArticle(
           string newsgroup_title,
           string article_name);