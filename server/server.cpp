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

#include <thread>
#include <stdexcept>
#include "request.h"

int main(int argc, char** argv)
{
  request r;
  if(argc > 1){
    string init = "init";
    if(argv[1] == init){
      printf("%s\n", "initializing main server.....");
      if(r.indexServer(1)){
        printf("%s\n", "Main server successfully initialized");
        if(r.setMainServer()){
          printf("%s\n", "Listening for connections...");
        }else{
          printf("%s\n", "file answer.ans could not open");
        }
      }
    }else{
      printf("%s\n", "wrong input");
      exit(0);
    }
  }else{
    printf("%s\n", "Listening for connections...");
  }

  
  TCPStream* stream = NULL;
  TCPAcceptor* acceptor = NULL;

  acceptor = new TCPAcceptor(81);

  if (acceptor->start() == 0) {
      while (1) {
          // thread t(newConnection, acceptor->accept());
          // t.detach();
        r.newConnection(acceptor->accept());
      }
  }
  exit(0);
}
