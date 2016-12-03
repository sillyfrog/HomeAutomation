/*
 * IMPORTANT: For this to work I needed to downgrade Homie to version 1.5.0.
 * To do this:
 *    - Go to your ".../Arduino/libraries/" folder
 *    - Run "git clone git@github.com:marvinroger/homie-esp8266.git" to get a copy of the code
 *    - Run "git checkout v1.5.0" to downgrade to version 1.5.0
 */

#include <Homie.h>

const int PIN_RELAY = D4;

HomieNode lightNode("light", "switch");

bool lightOnHandler(String value) {
  if (value == "true") {
    digitalWrite(PIN_RELAY, HIGH);
    Homie.setNodeProperty(lightNode, "on", "true"); // Update the state of the light
    Serial.println("Light is on");
  } else if (value == "false") {
    digitalWrite(PIN_RELAY, LOW);
    Homie.setNodeProperty(lightNode, "on", "false");
    Serial.println("Light is off");
  } else {
    return false;
  }

  return true;
}

void setup() {
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  Homie.setFirmware("awesome-light", "1.0.0");
  lightNode.subscribe("on", lightOnHandler);
  Homie.registerNode(lightNode);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
