/*
 * Nicholas Grout
 * 9/4/2020
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "secrets.h"
#include "helper.hpp"
#include "system_utils.hpp"
#include "networking_utils.hpp"

#define DEBUG

void setup()
{
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(STASSID);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup blinking LED
  pinMode(LED_BUILTIN, OUTPUT);
  led_off();
}

void loop()
{
  while (true)
  {
    WiFiClient client;
    find_base_ip_address(client, "192.168.1.", STARTING_IP_END);
    led_on();
    print_wifi_status();
    request_get(client, "/nick");
    led_off();
    fail("Finished");
  }
}
