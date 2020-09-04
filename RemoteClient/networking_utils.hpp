#include <WiFiClientSecure.h>


const uint16_t PORT = 8000;
const uint16_t STARTING_IP_END = 100;


void print_wifi_status()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

/*
 * Test whether the current ip address is the base ip address.
 */
bool is_base_ip_address(WiFiClient &client, const char *host)
{
  if (!client.connect(host, PORT))
  {
#ifdef DEBUG
    Serial.print("connection to ");
    Serial.print(host);
    Serial.print(":");
    Serial.print(PORT);
    Serial.println(" failed.");
#endif
    client.stop();
    return false;
  }
  return true;
}

/*
 * Find the base ip address from a starting ip address.
 */
const char *find_base_ip_address(WiFiClient &client, const char *starting_ip, int starting_ip_end)
{
  std::string starting_ip_str(starting_ip);
  for (int i = starting_ip_end; i < starting_ip_end + 100; ++i)
  {
    std::string current_ip = (starting_ip) + helper::long_to_string(i);
    bool success = is_base_ip_address(client, current_ip.c_str());
    if (success)
    {
      Serial.print("Valid ip address: ");
      Serial.println(current_ip.c_str());
      return current_ip.c_str();
    }
  }
  return NULL;
}

bool request_get(WiFiClient &client, const char *path)
{
#ifdef DEBUG
  Serial.print("Sending request to: \"");
  Serial.print(path);
  Serial.println("\"");
#endif // DEBUG
  std::string full_request = std::string("GET ") + std::string(path) + std::string(" HTTP/1.1");
  client.println(full_request.c_str());
  client.println("Connection: close");
  client.println();
  delay(500);
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }
  return false;
}