/*
   server.cpp
   Test server for the tcpsockets classes which handles connections
   iteratively.
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
#include "tcpacceptor.h"
#include <thread>
   #include <string.h>
#include <fstream>

string answer(){
  fstream file;
  file.open("answer.ans");
  string line;
  if(file.is_open()){
    getline(file, line);
  }

  return line;
}

void newConnection(TCPStream* stream){
  if (stream != NULL) {
      ssize_t len;
      char line[256];
      while ((len = stream->receive(line, sizeof(line))) > 0) {
          line[len] = 0;
          printf("received - %s%s%u\n", line, "from Client ip: ", pthread_self());
          stream->send(answer().c_str(), strlen(answer().c_str()));
      }
      delete stream;
  }
}

int main(int argc, char** argv)
{

  TCPStream* stream = NULL;
  TCPAcceptor* acceptor = NULL;

  acceptor = new TCPAcceptor(81);

  if (acceptor->start() == 0) {
      while (1) {
          thread t(newConnection, acceptor->accept());
          t.detach();
      }
  }
  exit(0);
}
