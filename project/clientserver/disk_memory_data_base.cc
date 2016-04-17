#include <iostream>

using namespace std;



DiskMemoryDataBase()
{
    //Create ptr to directory
    //Read
    vector<string> files;
    DIR *dp;
    struct dirent *dirp,
    string newsgroup_path, article_path;
    ifstream fin;
    
    if ((dp = opendir(root_directory_path.c_str())) == NULL) {
        int status;
        status = mkdir(root_directory_path, S_IRWXU);
        if (status != 0) {
            cout << "Error(" << errno << ") creating " << root_directory_path << endl;
        } else {
            dp = opendir(root_directory_path.c_str());
        }
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        //Create newsgroup object
        Newsgroup newsgroup(dirp->d_ino, dirp->d_name);
        //Open newsgroup directory
        DIR *dp2;
        struct dirent *dirp2;
        newsgroup_path = root_directory_path + "/" + dirp->d_name;
        dp2 = opendir(filename);
        //read files in newsgroup directory
        while ((dirp2 = readdir(dp2)) != NULL) {
            string article_title = dirp2->d_name;
            int article_id = dirp2->d_ino;
            //Open .txt file
            article_path = newsgroup_path + "/" + dirp2->d_name;
            fin.open(article_path.c_str());
            string line, article_text = "";
            string article_author = getline(fin, line); //First line is always author
            while (getline(fin, line)) {
                //Save text in variable
                text += line + "\n";
            }
            Article article(article_id, article_author, article_text, article_title);
            fin.close();
        }
        files.push_back(string(dirp->name));
        //Close newsgroup directory
        closedir(dp2);
    }
    closedir(dp);
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