#ifndef CLIENT_H
#define CLIENT_H

class MessageHandler;

class Client {
public:
         client             ();
    void listNewsgroups     (MessageHandler mh);
    void createNewsgroup    (MessageHandler mh);
    void deleteNewsgroup    (MessageHandler mh);
    void listArticles       (MessageHandler mh);
    void writeArticle       (MessageHandler mh);
    void deleteArticle      (MessageHandler mh);
//    void getArticle         (MessageHandler mh);
private:
    // Empty for now
#endif
