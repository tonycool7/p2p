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
   #include <pthread.h>

pthread_t thread_id[5];
int i =0;

void *newConnection(void* stream){
  TCPStream* new_stream;
  new_stream = (TCPStream*)stream;
  i++;
  if (new_stream != NULL) {
      ssize_t len;
      char line[256];
      while ((len = new_stream->receive(line, sizeof(line))) > 0) {
          line[len] = 0;
          printf("received - %s%s%u\n", line, "from Client ip: ", pthread_self());
          new_stream->send(line, len);
      }
      delete new_stream;
  }
}

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 4) {
        printf("usage: server <port> [<ip>]\n");
        exit(1);
    }

    TCPStream* stream = NULL;
    TCPAcceptor* acceptor = NULL;
    if (argc == 3) {
        acceptor = new TCPAcceptor(atoi(argv[1]), argv[2]);
    }
    else {
        acceptor = new TCPAcceptor(atoi(argv[1]));
    }

    if (acceptor->start() == 0) {
        while (1) {
            pthread_create(&thread_id[i],0,&newConnection, (void*)acceptor->accept());
            pthread_detach(thread_id[i]);
        }
    }
    exit(0);
}
