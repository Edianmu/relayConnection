#include <Arduino.h>

void connectWiFi(); 
void connectionClientSub();
void callback(String topic, byte* message, unsigned int length);
void loopConnection();