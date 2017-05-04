#include "node.h"

class ServerContainer{
private:
    node* root;//    size++;

public:
    ServerContainer();
    ~ServerContainer(){}
    void insert(string ip);
    node *createNewNode(string ip, int index_val);
    node *top();
    void display();
    bool serverRegistered(string ip);
    int index(string ip);
    static int size;
};
