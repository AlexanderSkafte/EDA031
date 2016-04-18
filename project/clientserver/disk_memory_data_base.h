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
        DiskMemoryDataBase(const std::string& root_path);
    
		std::vector<std::pair<std::string, unsigned int>>
			listNewsgroups();

		int
			createNewsgroup(
				const std::string& newsgroup_title);
		
		int
			deleteNewsgroup(
				const std::string& newsgroup_title);

		std::vector<Article>
			listArticles(
				const std::string& newsgroup_title);

		void 
			createArticle(
				const std::string& newsgroup_title,
				const std::string& article_name,
				const std::string& author,
				const std::string& text);

		int
			deleteArticle(
				const std::string& newsgroup_title,
				const std::string& article_name);

		std::vector<Article>
			getArticle(
				const std::string& newsgroup_title,
				const std::string& article_name);


	private:
        void read_init();
        void write_to_init(int article_id, int newsgroup_id);
        int get_id(std::string filename);
        std::string get_name(std::string filename);
        std::string root_directory_path;
        std::vector<Newsgroup> newsgroups;
        int newsgroup_id;
        int article_id;
};

#endif
