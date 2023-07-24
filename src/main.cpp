#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <esp_system.h>
#include <PubSubClient.h>
#include "credentials.h"
#include <HTTPClient.h>

#define RED_LED 4
#define GREEN_LED 17
#define BLUE_LED 16

const char *SSID = WIFI_SSID;
const char *password = WIFI_PASS;

const char *broker_pass = BROKER_PASS;
const char *broker_user = BROKER_USER;

IPAddress server(16, 16, 245, 116);

HTTPClient https;

void Connect(const char *SSID, const char *password)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, password);
}

void callback(char *topic, byte *payload, unsigned int length)
{

  String parsedPayload;

  for (int i = 0; i < length; i++)
  {
    // dobug
    // Serial.print((char)payload[i]);
    parsedPayload += (char)payload[i];
  }

  if (String(topic) == "CleverThing/G2WERGDS1REFRSG18/in/led")
  {
    if (parsedPayload == "on")
    {
      digitalWrite(RED_LED, HIGH);
    }
    else if (parsedPayload == "off")
    {
      digitalWrite(RED_LED, LOW);
    }
  }

  // dobug
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.print("] ");
  // for (int i = 0; i < length; i++)
  // {
  //   Serial.print((char)payload[i]);
  // }
  // Serial.println();
}

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("CleverThing", BROKER_USER, BROKER_PASS))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("CleverThing/out", "CleverThing G2WERGDS1REFRSG18 reconnected!");
      // ... and resubscribe
      client.subscribe("CleverThing/G2WERGDS1REFRSG18/in/led");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char randomNumberBuffer[64] = "";
void random(int lower, int upper, int divisor, char* strBuff)
{
    int temp = (rand() % (upper - lower + 1)) + lower;
    double num = (double)temp / (double)divisor;
    sprintf(strBuff, "%f", num);        
}

void setup()
{
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Connect(SSID, password);
  delay(500);
  // loopForInternet();

  
  Serial.print(WiFi.localIP());

  client.setServer(server, 1900);
  client.setCallback(callback);

  if (client.connect("CleverThing", BROKER_USER, BROKER_PASS))
  {
    client.publish("CleverThing/out", "CleverThing G2WERGDS1REFRSG18 connected!");
    client.subscribe("CleverThing/G2WERGDS1REFRSG18/in/led");
  }
  delay(1500);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  if (millis() % 5000 == 0){
    random(2050, 2080, 100, randomNumberBuffer);  
    client.publish("CleverThing/G2WERGDS1REFRSG17/out/temp", randomNumberBuffer);
    delay(1);
  }
}