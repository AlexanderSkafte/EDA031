#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "newsgroup.h"

public class Client {
public:
    void menu();
    void choise();
    void listNewsgroup(const std::string name);
    void createNewsgroup(const std::string name);
private:
    
    // kanske är bättre med en hashmap?!?
    std::string resp;
    std::List<Newsgroup> newsgroups;
};

#endif
