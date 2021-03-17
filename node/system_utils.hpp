#include <ESP8266WiFi.h>

void blink_led(int count, int delay_value)
{
  for (int i=0; i<count; ++i) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(delay_value);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void fail(const char* fail_message)
{
  Serial.print("ERROR: \"");
  Serial.print(fail_message);
  Serial.println("\"");
  while(true) {
    blink_led(3, 200);
    delay(5000);
  }
}
