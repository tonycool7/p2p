#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <memory>
#include <array>
#include "tcpacceptor.h"
#include "serverContainer.h"

class request{
	char *request_code;
public:
	string exec(const char* cmd);
	string sendingIndexNumber(string ip);
	string AmITheMainServer();
	bool setMainServer();
	string synchronizeAllServers();
	string requestManager(string req_code, string ip);
	string backup(const char* query);
	void newConnection(TCPStream* stream);
	bool indexServer(int i);
	request();
	~request();
};