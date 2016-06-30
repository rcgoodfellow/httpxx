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
  cout << "hewow" << endl; 
  atomic<bool> server_ready{false};
  
  thread t{[&server_ready](){
    SSLContextConfig sslc;
    sslc.setCertificate(
        "leaf_cert.pem",
        "leaf_key.pem",
        "" //no password on cert
    );

    HttpsServer srv("localhost", 4433, sslc);
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

  while(!server_ready) usleep(50);

  HttpRequest req{
    HTTPMethod::POST,
    "https://localhost:4433/ding",
    "hewow"
  };

  cout << req.response().get().bodyAsString() << endl;

}
