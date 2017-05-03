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
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include "tcpconnector.h"
#include <fstream>
#include <iostream>


using namespace std;

pthread_t thread_id[5];
int i =0;

void areYouTheMainServer(TCPStream* stream, string message){
  int len;
  char line[256];
  if (stream) {
    while(1){
      stream->send(message.c_str(), message.size());
      printf("sent - %s%s%u\n", message.c_str(), "thread id: ", pthread_self());
      len = stream->receive(line, sizeof(line));
      line[len] = 0;
      printf("received - %s\n", line);
      // delete stream;
      sleep(5);
    }
  }
}

void connectToServer(string ip){
  TCPConnector* connector = new TCPConnector();
  TCPStream* stream = connector->connect(ip.c_str(), 81);
  areYouTheMainServer(stream, "Are you the main server");
  i++;
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("usage: %s <port> <ip>\n", argv[0]);
        exit(1);
    }
    ifstream file("server.txt"); // pass file name as argment
    string linebuffer;
    while (file && getline(file, linebuffer)){
      if (linebuffer.length() == 0)continue;

      printf("%s\n", linebuffer);

   }
    

  file.close();
  TCPConnector* connector = new TCPConnector();
  TCPStream* stream = connector->connect(argv[2], atoi(argv[1]));

  fstream file;
  file.open("server.lst");
  string line;
  if(file.is_open()){
    while(getline(file, line)){
      thread newThread(connectToServer, line);
      newThread.join();
    }
  }else{
    cout<<"file could not open";
  }

  exit(0);
}