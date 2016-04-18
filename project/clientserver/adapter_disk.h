#ifndef ADAPTER_DISK_H
#define ADAPTER_DISK_H

#include "messagehandler.h"
#include "disk_memory_data_base.h"

class AdapterDisk {
public:
    AdapterDisk                 (const std::string&);
    ~AdapterDisk();
    void listNewsgroups     (MessageHandler& mh);
    void createNewsgroup    (MessageHandler& mh);
    void deleteNewsgroup    (MessageHandler& mh);
    void listArticles       (MessageHandler& mh);
    void createArticle      (MessageHandler& mh);
    void deleteArticle      (MessageHandler& mh);
    void getArticle         (MessageHandler& mh);
private:
    DiskMemoryDataBase        db;
};

#endif
