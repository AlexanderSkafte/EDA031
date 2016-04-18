#ifndef ADAPTER_H
#define ADAPTER_H

#include "messagehandler.h"
#include "in_memory_data_base.h"

class Adapter {
public:
    Adapter                 ();
    void listNewsgroups     (MessageHandler& mh);
    void createNewsgroup    (MessageHandler& mh);
    void deleteNewsgroup    (MessageHandler& mh);
    void listArticles       (MessageHandler& mh);
    void createArticle      (MessageHandler& mh);
    void deleteArticle      (MessageHandler& mh);
    void getArticle         (MessageHandler& mh);
private:
    InMemoryDataBase        db;
};

#endif
