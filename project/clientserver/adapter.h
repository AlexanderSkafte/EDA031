#ifndef CLIENT_H
#define CLIENT_H

#include "in_memory_data_base.h"

class MessageHandler;

class Adapter {
public:
    Adapter                 ();
    void listNewsgroups     (MessageHandler mh);
    void createNewsgroup    (MessageHandler mh);
    void deleteNewsgroup    (MessageHandler mh);
    void listArticles       (MessageHandler mh);
    void writeArticle       (MessageHandler mh);
    void deleteArticle      (MessageHandler mh);
//    void getArticle         (MessageHandler mh);
private:
    InMemoryDataBase        db;
#endif
