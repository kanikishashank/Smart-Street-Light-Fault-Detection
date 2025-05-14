#define BLYNK_TEMPLATE_ID "TMP123abc456"
#define BLYNK_DEVICE_NAME "Street Light Fault Detection"
#define BLYNK_AUTH_TOKEN "YourAuthTokenHere"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

// LDR pins connected to A0, D1, D2, D3 (as analog or digital inputs)
#define LDR1 D1
#define LDR2 D2
#define LDR3 D3
#define LDR4 D4

void setup() {
  Serial.begin(9600);

  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  checkStreetLights();
  delay(2000); // Check every 2 seconds
}

void checkStreetLights() {
  int light1 = digitalRead(LDR1);
  int light2 = digitalRead(LDR2);
  int light3 = digitalRead(LDR3);
  int light4 = digitalRead(LDR4);

  Serial.print("L1: "); Serial.print(light1);
  Serial.print(" L2: "); Serial.print(light2);
  Serial.print(" L3: "); Serial.print(light3);
  Serial.print(" L4: "); Serial.println(light4);

  // Check for OFF (assume HIGH means no light falling = light OFF/faulty)
  if (light1 == HIGH) Blynk.logEvent("streetlight1_fault", "Street Light 1 Fault Detected!");
  if (light2 == HIGH) Blynk.logEvent("streetlight2_fault", "Street Light 2 Fault Detected!");
  if (light3 == HIGH) Blynk.logEvent("streetlight3_fault", "Street Light 3 Fault Detected!");
  if (light4 == HIGH) Blynk.logEvent("streetlight4_fault", "Street Light 4 Fault Detected!");
}
