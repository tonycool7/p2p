#include "request.h"

request::request(){
  mainServerActive = false;
}


request::~request(){}


string request::sendRequestToServer(TCPStream* stream, string message, string ip){
  int len;
  char line[256];
  if (stream) {
      stream->send(message.c_str(), message.size());
      printf("sent - %s %s\n", message.c_str(), ip.c_str());
      len = stream->receive(line, sizeof(line));
      line[len] = 0;
  }
  printf("%s\n", line);
  return line;
}

bool request::setClientIndex(string i){
  fstream file;
  file.open("index.in", fstream::out);
  if(file.is_open()){
    file << i;
    file.close();
    return true;
  }
  return false;
}

void request::connectToServer(string ip){
  TCPConnector* connector = new TCPConnector();
  TCPStream* stream = connector->connect(ip.c_str(), 81);
  if(sendRequestToServer(stream, "101", ip) == "yes"){
    mainServerActive = true;
    string index = sendRequestToServer(stream, "102", ip);
    setClientIndex(index);
    sendRequestToServer(stream, "mysqldump -hlocalhost -uroot -pdlords --databases backupSYS > ../backup/backupSYS.sql", ip);
    sendRequestToServer(stream, "103", ip);
  }
  delete stream;
}

void request::chooseMainServer(string ip){
  TCPConnector* connector = new TCPConnector();
  TCPStream* stream = connector->connect(ip.c_str(), 81);
  if(sendRequestToServer(stream, "101", ip) == "yes"){
    mainServerActive = true;
    string index = sendRequestToServer(stream, "102", ip);
    setClientIndex(index);
  }
  delete stream;
}
