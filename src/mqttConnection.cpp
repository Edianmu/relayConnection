#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "dataConnection.h"

const int d0 = 16;
const int portBroker = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(String topic, byte* message, unsigned int length){

  Serial.print("Mensaje llegó en el topico: ");
  Serial.print(topic);
  Serial.print(". Mensaje: ");
  String messageTemp = "";

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i]; 
  }
  Serial.println();

  if(topic == "battery_pct"){
    if (messageTemp == "connect")
    {
      digitalWrite(d0, HIGH);
      Serial.print("ON");
    }else if (messageTemp == "disconnect")
    {
      digitalWrite(d0, LOW);
      Serial.print("OFF");
    }
  }
  Serial.println("");  
}

void connectionClientSub(){
     
  pinMode(d0, OUTPUT);

  Serial.println("Conectando al servidor: ");
  client.setServer(mqttServer, portBroker);
  client.setCallback(callback);
  
  while ((!client.connected()))
  {
    Serial.print("Attemting MQTT connection...");
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str(), userName, password)){
      Serial.println("Connected");
    }
    else{
      Serial.print("Error ");
      Serial.print(client.state());
      Serial.println("\nIntentando reconectar en 5 segundos");
      delay(1000);
    }
      client.subscribe("battery_pct");
      client.publish("ClientMcu","Alive" );
  }
}

void loopConnection(){
  
    client.loop();
}
