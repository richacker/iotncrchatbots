#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SERVER      "broker.mqtt-dashboard.com"
#define SERVERPORT  1883
#define USERNAME    "airteldemo"

#define PIN 21
#define LED_COUNT 10

const char* ssid     = "Rishi";
const char* password = "Rishi1234";

char final_sub[40] = "";
char final_value[40] = "";

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_RGB + NEO_KHZ400);


WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  client.setServer(SERVER, SERVERPORT);
  client.setCallback(callback);
  leds.begin();
  leds.show();
  
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print((char)payload[0]);
  if((char)payload[0] == 'o'){
    colorWipe(leds.Color(153, 27, 226), 40);
  } else if((char)payload[0] == 'f'){
    colorWipe(leds.Color(0, 0, 0), 40);
  }else if((char)payload[0] == 'y'){
    colorWipe(leds.Color(255, 255, 0), 40);
  }
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(USERNAME, "", "")) {
      Serial.println("connected");
      client.subscribe(USERNAME);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
} 

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<leds.numPixels(); i++) {
    leds.setPixelColor(i, c);
    leds.show();
    delay(wait);
  }
}
