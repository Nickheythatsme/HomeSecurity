/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "secrets.h"
#include "helper.hpp"
#include "ipscanner.h"

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.205";
const uint16_t PORT = 8080;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

bool try_ip(const char* host, int port=PORT) {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(500);
    return false;
  }
  return true;
}

std::string make_ip_address(const char *ip_address) {
  Serial.println((std::string("Incrementing ip address: ") + ip_address).c_str());
  std::string ip_add(ip_address);
  int last_period = ip_add.rfind('.');
  std::string first_ip_section(ip_add.substr(0, last_period));
  std::string last_ip_section(ip_add.substr(last_period));
  int last_ip_section_int = strtol(last_ip_section.c_str(), NULL, 10);
  ++last_ip_section_int;

  std::string new_ip = first_ip_section + "." + helper::long_to_string(last_ip_section_int);
  Serial.println(("New ip: " + new_ip).c_str());
  return new_ip;
}

bool try_ip_address(const char *host) {
  #ifdef DEBUG
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(PORT);
  #endif

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, PORT)) {
    #ifdef DEBUG
    Serial.print("connection to ");
    Serial.print(host);
    Serial.println(" failed.");
    delay(5000);
    #endif
    return false;
  }
  return true;
}

void f() {
  /*
  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    //client.println("hello from ESP8266");
    client.print(String("GET ") + "/" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return false;
    }
  }
  Serial.print("connection to ");
  Serial.print(host);
  Serial.println(" suceeded.");
  return true;
  */
}

std::string try_ip_addresses(const char *starting_ip, int starting_ip_end) {
  std::string starting_ip_str(starting_ip);
  for (int i=starting_ip_end; i<starting_ip_end + 100; ++i) {
    std::string current_ip = (starting_ip) + helper::long_to_string(i);
    bool success = try_ip_address(current_ip.c_str());
    if (success) {
      Serial.print("Valid ip address: ");
      Serial.println(current_ip.c_str());
      return current_ip;
    }
  }
  return std::string();
}

void loop() {
  /*
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(PORT);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, PORT)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    //client.println("hello from ESP8266");
    client.print(String("GET ") + "/" + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }
  */

  /*
  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  */
  while(true) {
    try_ip_addresses("192.168.1.", 0);
    delay(3000); // execute once every 5 minutes, don't flood remote service
  }
}
