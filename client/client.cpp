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

#include "request.h"
#include <thread>

using namespace std;

int main(int argc, char** argv)
{
  request r;
  fstream file;
  file.open("server.lst");
  string line;
  if(file.is_open()){
    while(getline(file, line)){
      r.connectToServer(line);
    }
  }else{
    cout<<"file could not open";
  }

  exit(0);
}