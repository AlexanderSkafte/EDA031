#ifndef DISK_MEMORY_DATA_BASE_H
#define DISK_MEMORY_DATA_BASE_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <fstream>

#include "database.h"
#include "article.h"
#include "newsgroup.h"


class DiskMemoryDataBase : public DataBase {
	public:
        DiskMemoryDataBase();
    
		std::vector<std::pair<std::string, unsigned int>>
			listNewsgroups();

		int
			addNewsgroup(
				std::string);
		
		int
			deleteNewsgroup(
				std::string newsgroup_title);

		std::vector<Article>
			getArticles(
				std::string newsgroup_title);

		void 
			addArticle(
				std::string newsgroup_title,
				std::string article_name,
				std::string author,
				std::string text);

		int
			deleteArticle(
				std::string newsgroup_title,
				std::string article_name);

		std::string
			getArticle(
				std::string newsgroup_title,
				std::string article_name);


	private:
        std::string root_directory_path;
        std::vector<Newsgroup> newsgroups;
        int newsgroup_id;
        int article_id;
};

#endif
