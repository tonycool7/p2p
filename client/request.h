#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <thread>
#include "tcpconnector.h"
#include <fstream>
#include <iostream>

class request{
public:
	bool mainServerActive;
	string sendRequestToServer(TCPStream* stream, string message, string ip);
	bool setClientIndex(string i);
	void connectToServer(string ip);
	void chooseMainServer(string ip);
	request();
	~request();
};