#include "request.h"

ServerContainer *container = new ServerContainer();

request::request(){}
request::~request(){}

string request::exec(const char* cmd) {
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

string request::backup(const char* query){
	cout<< exec(query);
	return "backup successful";
}

string request::sendingIndexNumber(string ip){
  if(!container->serverRegistered(ip)){
    container->insert(ip);
    return to_string(ServerContainer::size);
  }else{
    return to_string(container->index(ip));
  }
}

string request::AmITheMainServer(){
  fstream file;
  file.open("answer.ans");
  string line;
  if(file.is_open()){
    getline(file, line);
  }
  return line;
}

bool request::setMainServer(){
  fstream file;
  file.open("answer.ans");
  if(file.is_open()){
    file << "yes";
    return true;
  }
  return false;
}


string request::synchronizeAllServers(){
  // node *temp;
  //   temp = container->top();
  //   while(temp != NULL){
  //       printf("ip of server :%s\n", temp->ip_Addr.c_str());
        
  //       temp = temp->next;
  //   }
    cout<< exec("rsync -avzh ../backup/ tony@192.168.1.224:~/diplom/p2p/backup");
    return "sync successful";
}

string request::requestManager(string req_code, string ip){
  if(req_code == "101") return AmITheMainServer();
  else if(req_code == "102") return sendingIndexNumber(ip);
  else if(req_code == "103") return synchronizeAllServers();
  else return backup(req_code.c_str());
}

void request::newConnection(TCPStream* stream){
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

bool request::indexServer(int i){
  fstream file;
  file.open("index.in", fstream::out);
  if(file.is_open()){
    file << i;
    file.close();
    return true;
  }
  return false;
}
