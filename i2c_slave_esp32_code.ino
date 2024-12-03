#include <Wire.h>

#define SLAVE_ADDR 0x09 // Address of the slave device

void setup() {
  Serial.begin(115200);  // Start serial communication for debugging
  Wire.begin(SLAVE_ADDR); // Initialize I2C as slave with address 0x09
  Wire.onReceive(receiveData);  // Register the function to handle data reception
  Wire.onRequest(sendData);    // Register the function to handle requests for data
  Serial.println("I2C Slave Started...");
}

void loop() {
  // The loop remains empty as the slave works asynchronously with interrupts
  delay(100);  // Delay to avoid excessive CPU usage
}

// This function is called when the master sends data
void receiveData(int byteCount) {
  Serial.print("Received data: ");
  while (Wire.available()) {
    char receivedChar = Wire.read();  // Read each byte sent by the master
    Serial.print(receivedChar);       // Print the received byte to the Serial Monitor
  }
  Serial.println();  // Print a new line after the received message
}

// This function is called when the master requests data from the slave
void sendData() {
  String message = "Data from Slave!";
  const char* msg = message.c_str();  // Convert the String to a C-string (char array)
  
  // Send the message byte by byte
  Wire.write((uint8_t*)msg, message.length());  // Send the message as bytes
}
