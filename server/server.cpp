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
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <string.h>
#include <fstream>
#include "serverContainer.h"

ServerContainer *container = new ServerContainer();

string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
}

string sendingIndexNumber(string ip){
  if(!container->serverRegistered(ip)){
    container->insert(ip);
    return to_string(ServerContainer::size);
  }else{
    return to_string(container->index(ip));
  }
}

string AmITheMainServer(){
  fstream file;
  file.open("answer.ans");
  string line;
  if(file.is_open()){
    getline(file, line);
  }
  return line;
}

bool setMainServer(){
  fstream file;
  file.open("answer.ans");
  if(file.is_open()){
    file << "yes";
    return true;
  }
  return false;
}

string requestManager(string req_code, string ip){
  if(req_code == "101") return AmITheMainServer();
  else if(req_code == "102") return sendingIndexNumber(ip);
  else return "incorrect request";
}

void newConnection(TCPStream* stream){
  if (stream != NULL) {
      ssize_t len;
      char line[256];
      while ((len = stream->receive(line, sizeof(line))) > 0) {
          line[len] = 0;
          printf("received request - %s%s%s\n", line, " from Client ip: ", stream->getPeerIP());
          string answer = requestManager(line, stream->getPeerIP());
          stream->send(answer.c_str(), strlen(answer.c_str()));
          printf("sent reply - %s\n", answer.c_str());
      }
  }
  //container->display();
  delete stream;
}

bool indexServer(int i){
  fstream file;
  file.open("index.in", fstream::out);
  if(file.is_open()){
    file << i;
    file.close();
    return true;
  }
  return false;
}

int main(int argc, char** argv)
{
  if(argc > 1){
    string init = "init";
    if(argv[1] == init){
      printf("%s\n", "initializing main server.....");
      if(indexServer(1)){
        printf("%s\n", "Main server successfully initialized");
        if(setMainServer()){
          printf("%s\n", "Listening for connections...");
        }else{
          printf("%s\n", "file answer.ans could not open");
        }
      }
    }else{
      printf("%s\n", "wrong input");
      exit(0);
    }
  }

  
  TCPStream* stream = NULL;
  TCPAcceptor* acceptor = NULL;

  acceptor = new TCPAcceptor(81);

  if (acceptor->start() == 0) {
      while (1) {
          // thread t(newConnection, acceptor->accept());
          // t.detach();
        newConnection(acceptor->accept());
      }
  }
  exit(0);
}
