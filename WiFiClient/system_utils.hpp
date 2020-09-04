#include <ESP8266WiFi.h>


void led_on()
{
  digitalWrite(LED_BUILTIN, LOW);
}

void led_off()
{
  digitalWrite(LED_BUILTIN, HIGH);
}

void led_blink(int count=5, int delay_value=500)
{
  for (int i=0; i<count; ++i) {
    led_on();
    delay(delay_value);
    led_off();
    delay(delay_value);
  }
  led_off();
}

void fail(const char* fail_message)
{
  Serial.print("ERROR: \"");
  Serial.print(fail_message);
  Serial.println("\"");
  while(true) {
    led_blink(3);
    delay(5000);
  }
}