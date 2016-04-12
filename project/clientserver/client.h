#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "Newsgroup.h"

public class Client {
public:
    void menu();
    void choise();
    void listNewsgroup(const std::string name);
    void createNewsgroup(const std::string name);
private:
    
    // kanske är bättre med en hashmap?!?
    std::List<Newsgroup> newsgroups;
};

#endif
