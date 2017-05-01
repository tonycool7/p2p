/*
   client.cpp
   Test client for the tcpsockets classes. 
   ------------------------------------------
   Copyright (c) 2013 Vic Hargrave
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   https://github.com/vichargrave/tcpsockets
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "tcpconnector.h"

using namespace std;

void areYouTheMainServer(TCPStream* stream, string message){
  int len;
  char line[256];
  if (stream) {
    while(1){
      stream->send(message.c_str(), message.size());
      printf("sent - %s\n", message.c_str());
      len = stream->receive(line, sizeof(line));
      line[len] = 0;
      printf("received - %s\n", line);
      // delete stream;
      sleep(10);
    }
  }
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("usage: %s <port> <ip>\n", argv[0]);
        exit(1);
    }
    TCPConnector* connector = new TCPConnector();
    TCPStream* stream = connector->connect(argv[2], atoi(argv[1]));

    areYouTheMainServer(stream, "Are you the main server");

    exit(0);
}