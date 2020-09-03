#include "ipscanner.h"

IpScanner::IpScanner()
{
    this->starting_host = std::string(IP_SCANNER_HOST);
    this->port = IP_SCANNER_PORT;
}

IpScanner::IpScanner(std::string starting_host, int port):
    starting_host(starting_host), port(port)
{
}

bool IpScanner::try_ip()
{
    Serial.print("connecting to ");
    Serial.print(host);
    Serial.print(':');
    Serial.println(this->port);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(this->current_host, port)) {
        Serial.println("connection failed");
        delay(500);
        return false;
    }
    return true;
}
