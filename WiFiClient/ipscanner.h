#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <string>
#include <cstring>

#ifndef HOME_SECURITY_IP_SCANNER_
#define HOME_SECURITY_IP_SCANNER_

#define IP_SCANNER_STARTING_HOST = "192.168.1.205";
#define IP_SCANNER_PORT = 8080;

class IpScanner {
  public:
    IpScanner();
    IpScanner(const char* starting_host, int port);
    bool try_ip();
  private:
    std::string starting_host;
    std::string current_host;
    int port;
};

#endif // HOME_SECURITY_IP_SCANNER_
