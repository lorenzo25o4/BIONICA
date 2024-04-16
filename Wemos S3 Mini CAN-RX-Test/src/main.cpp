#include <Arduino.h>


#include <ESP32-TWAI-CAN.hpp>

// Simple sketch that transmits and receives CAN frames
// Showcasing simple use of ESP32-TWAI-CAN library driver.

// Default for ESP32
#define CAN_TX 5
#define CAN_RX 4

CanFrame rxFrame;

// transmit a test frame
void sendObdFrame(uint8_t obdId) {
  static byte data = 2;  // test value - increment every frame
  CanFrame obdFrame = { 0 };
  obdFrame.identifier = 0x7DF;  // Default OBD2 address;
  obdFrame.extd = 0;
  obdFrame.data_length_code = 8;
  obdFrame.data[0] = 'B';
  obdFrame.data[1] = 1;
  obdFrame.data[2] = '0';
  obdFrame.data[3] = 0xDE;  // Best to use 0xAA (0b10101010) instead of 0
  obdFrame.data[4] = 0xAD;  // CAN works better this way as it needs
  obdFrame.data[5] = 0xBE;  // to avoid bit-stuffing
  obdFrame.data[6] = 0xEF;
  obdFrame.data[7] = 0x01;
  // Accepts both pointers and references
  ESP32Can.writeFrame(obdFrame);  // timeout defaults to 1 ms
  data++;                         // increment for testing
  Serial.printf("Transmit frame: %03X: ", obdFrame.identifier);
  for (byte i = 0; i < 8; i++)
    Serial.printf(" 0x%.2X", obdFrame.data[i]);
  Serial.printf("\n");
}

void setup() {
  // Setup serial for debbuging.
  Serial.begin(115200);
  Serial.println("\n\nESP32-TWAI-CAN Send/Receive test -  Initialize");
  // Set pins
  ESP32Can.setPins(CAN_TX, CAN_RX);
  // You can set custom size for the queues - those are default
  ESP32Can.setRxQueueSize(5);
  ESP32Can.setTxQueueSize(5);
  // .setSpeed() and .begin() functions require to use TwaiSpeed enum,
  // but you can easily convert it from numerical value using .convertSpeed()
  ESP32Can.setSpeed(ESP32Can.convertSpeed(250));  //500));
  // You can also just use .begin()..
  if (ESP32Can.begin()) {
    Serial.println("CAN bus started!");
  } else {
    Serial.println("CAN bus failed!");
  }
  // or override everything in one command;
  // It is also safe to use .begin() without .end() as it calls it internally
  if (ESP32Can.begin(ESP32Can.convertSpeed(1000), CAN_TX, CAN_RX, 10, 10)) {
    Serial.println("CAN bus started!");
  } else {
    Serial.println("CAN bus failed!");
  }
}

void loop() {
  // transmit data when space entered on keyboard
  if (Serial.available()) {
    if (Serial.read() != ' ') return;
    sendObdFrame(5);  // For coolant temperature
  }

  // frame received?  You can set custom timeout, default is 1000
  if (ESP32Can.readFrame(rxFrame, 1)) {
    // print frame contents
    Serial.printf("Received frame: %03X: ", rxFrame.identifier);
    for (byte i = 0; i < 8; i++)
      Serial.printf(" 0x%.2X", rxFrame.data[i]);
    Serial.printf("\n");
  }
}
