/*
 * Nicholas Grout
 * 3/15/2021
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "secrets.h"
#include "system_utils.hpp"

#define STARTING_IP_LAST_QUAD 73
#define MAX_HOST_IP_ATTEMPTS 200
#define DELAYTIME 500
#define PORT 8000

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
const uint8_t inPin = D5;

// Wi-Fi settings - replace with your Wi-Fi SSID and password, in quotes
String address;
bool door_is_open_prev;

// This is the setup section and will only run one time
void setup()
{

    // Configure status LED on NodeMCU board
    // Later, it will be programmed to blink every HTTP POST
    pinMode(LED_BUILTIN, OUTPUT);

    //Let the NodeMCU know inPin is an INPUT
    pinMode(inPin, INPUT_PULLUP);

    // Configure serial port for debug when NodeMCU board is connected
    // to your computer or laptop using USB port
    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    // Initiate Wi-Fi connection setup
    WiFi.begin(SECRET_SSID, SECRET_PASS);

    // Show status on serial monitor
    Serial.print("Connecting to ");
    Serial.print(SECRET_SSID);
    Serial.println(" ...");

    // Wait for Wi-Fi connection and show progress on serial monitor
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to network. IP address: ");
    Serial.println(WiFi.localIP());
    address = find_base_address();
    Serial.print("Using host address: ");
    Serial.println(address);
}

bool is_base_ip_address(WiFiClient &client, String host)
{
    Serial.print("Connecting to ");
    Serial.print(host + ":" + String(PORT));
    Serial.print(".....");
    if (!client.connect(host, PORT))
    {
        Serial.println("FAILED");
        return false;
    }
    Serial.println("SUCCEEDED");
    return true;
}

String find_base_address()
{
    // Starting ip address, used when trying to find host
    String base_ip = "192.168.1.";
    WiFiClient client;
    for (uint16_t i = STARTING_IP_LAST_QUAD; i < STARTING_IP_LAST_QUAD + MAX_HOST_IP_ATTEMPTS; ++i)
    {
        address = base_ip + String(i);
        if (is_base_ip_address(client, address))
        {
            return String("http://") + address + ":" + String(PORT);
        }
    }
    fail("Could not find host address");
}

// main loop
void loop()
{
    // This is the minimum amount of time to wait before
    // reading the sensor
    delay(DELAYTIME);

    // Store sensor state
    // State is "true" if door is open
    bool door_is_open;

    if (digitalRead(inPin) == LOW)
    {
        door_is_open = false;
    }
    else
    {
        door_is_open = true;
    }

    Serial.println("door_is_open: ");
    Serial.println(String(door_is_open));

    if (door_is_open != door_is_open_prev)
    {
        String post_data;

        // Make the payload response
        if (door_is_open) {
            post_data = "{\"context\":{\"target_id\":\"Entry_Sensor\"}, \"data\":{\"door_open\": true}}";
        } else {
            post_data = "{\"context\":{\"target_id\":\"Entry_Sensor\"}, \"data\":{\"door_open\": false}}";
        }
        WiFiClient client;
        HTTPClient http;

        http.begin(client, address);
        http.addHeader("Content-Type", "application/json");
        int httpCode = http.POST(post_data);

        // httpCode will be negative on error
        if (httpCode > 0)
        {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] POST... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK)
            {
                const String &payload = http.getString();
                Serial.print("received payload:  ");
                Serial.println(payload);
            }
        }
        else
        {
            Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end(); //Close connection
        // Blink the status LED
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
        digitalWrite(LED_BUILTIN, HIGH);
        // Store the new sensor value
        door_is_open_prev = door_is_open;
    }
}