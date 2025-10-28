const int STATE_PIN = 4;   // HC-08 STATE pin to D4
const int BT_RX = 2;       // HC-08 TX -> Arduino RX (SoftwareSerial)
const int BT_TX = 3;       // HC-08 RX -> Arduino TX (SoftwareSerial)

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(BT_RX, BT_TX);  // RX, TX

bool lastState = LOW;

void setup() {
  pinMode(STATE_PIN, INPUT);
  Serial.begin(9600);       // Serial Monitor
  BTSerial.begin(9600);     // HC-08 Bluetooth communication

  Serial.println("🔵 HC-08 Bluetooth Connection Monitor (Arduino R4)");
  Serial.println("--------------------------------------------------");
  Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
  bool currentState = digitalRead(STATE_PIN);

  // Detect Bluetooth connection state change
  if (currentState != lastState) {
    if (currentState == HIGH) {
      Serial.println("✅ Bluetooth Connected!");
    } else {
      Serial.println("⏳ Waiting for Connection...");
    }
    lastState = currentState;
  }

  // 🔹 Receive data from Bluetooth → Serial Monitor
  if (BTSerial.available()) {
    String btData = BTSerial.readStringUntil('\n');
    Serial.print("📥 Received via Bluetooth: ");
    Serial.println(btData);
  }

  // 🔹 Send data from Serial Monitor → Bluetooth device
  if (Serial.available()) {
    String serialData = Serial.readStringUntil('\n');
    BTSerial.println(serialData);
    Serial.print("📤 Sent to Bluetooth: ");
    Serial.println(serialData);
  }

  delay(50);
}
