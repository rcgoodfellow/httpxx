#include "http++.hxx"
#include <iostream>
#include <thread>
#include <atomic>

using Protocol = proxygen::HTTPServer::Protocol;
using wangle::SSLContextConfig;
using proxygen::HTTPMethod;
using namespace marina;
using namespace std;

int main()
{
  cout << "ding" << endl; 
  atomic<bool> server_ready{false};
  
  thread t{[&server_ready](){
    SSLContextConfig sslc;
    sslc.setCertificate(
        "door_cert.pem",
        "door_key.pem",
        "" //no password on cert
    );

    HttpsServer srv("127.0.0.1", 4433, sslc);
    srv.onPost("/ding", [](http::Message) {
        return http::Response{
          http::Status::OK(),
          "dong"
        };
    });

    server_ready = true;

    srv.run();
  }};
  t.detach();

  sleep(1);

  //TODO this dosen't actually work, need a real indication from
  //srv as to when it is ready
  while(!server_ready) usleep(50);

  HttpRequest req{
    HTTPMethod::POST,
    "https://127.0.0.1:4433/ding",
    "ding"
  };

  cout << req.response().get().bodyAsString() << endl;

}
