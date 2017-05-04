#include "serverContainer.h"

int ServerContainer::size = 0;

ServerContainer::ServerContainer()
{
    root = NULL;
}

void ServerContainer::insert(string ip){
    size++; //cdfaszfa
	node *temp = createNewNode(ip, size);
    if(root == NULL){
        root = temp;
        size = 0;
    }else{
        node *cur = root;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = temp;
    }
}

node *ServerContainer::createNewNode(string ip, int index_val){
	node *temp = new node();
    temp->ip_Addr = ip;
    temp->index = index_val;
    temp->next = NULL;
    return temp;
}


node *ServerContainer::top(){
	return root;
}

void ServerContainer::display(){
	node *temp;
    temp = top();
    while(temp != NULL){
        printf("%s\n", temp->ip_Addr);
        printf("%d\n", temp->index);
        temp = temp->next;
    }
}

bool ServerContainer::serverRegistered(string ip){
	node *temp;
    temp = top();

    while(temp != NULL){
        if(temp->ip_Addr == ip){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int ServerContainer::index(string ip){
	node *temp;
    temp = top();
    int i;

    while(temp != NULL){
        if(temp->ip_Addr == ip){
            i = temp->index;
        }
        temp = temp->next;
        break;
    }
    return i;
}