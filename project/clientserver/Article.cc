#include <string>

#include "Article.h"

Article::Article(int id, std::string author, std::string text) {
    this->id_ = id;
    this->author_ = author;
    this->text_ = text;
}

int
Article::id() {
    return this->id_;
}

std::string
Article::author() {
    return this->author_;
}

std::string
Article::text() {
    return this->text_;
}

