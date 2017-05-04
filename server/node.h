#include <cstdio>
#include <iostream>

using namespace std;

class node{
public:
	string ip_Addr;
	int g;
	int index;
	node *next;
	node(){next = NULL;}
    ~node();
};