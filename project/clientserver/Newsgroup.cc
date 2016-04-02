
#include <string>

using namespace std;

Newsgroup(int id, string name)
    : id_{id}
    , name_{name}
{ }

int
Newsgroup::id()
{
    return id_;
}

string
Newsgroup::name()
{
    return name_;
}

