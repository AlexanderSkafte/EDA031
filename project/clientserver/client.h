#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class MessageHandler;

class Client {
public:
    int     parse_command   (std::string line);
    void    listNewsgroups  (MessageHandler mh);
    void    createNewsgroup (MessageHandler mh);
    void    deleteNewsgroup (MessageHandler mh);
    void    listArticles    (MessageHandler mh);
    void    createArticle   (MessageHandler mh);
    void    deleteArticle   (MessageHandler mh);
    void    getArticle      (MessageHandler mh);
};

#endif
