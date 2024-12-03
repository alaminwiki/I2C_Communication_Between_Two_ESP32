#include <Wire.h>

#define SLAVE_ADDR 0x09 // Address of the slave device
#define MSG_TO_SLAVE "Hello from Master!" // Message to send to the slave

void setup() {
  Serial.begin(115200);        // Start serial communication at 115200 baud
  Wire.begin();                // Initialize I2C as master (default SDA and SCL pins)
  delay(2000);                 // Wait for the slave to initialize properly

  Serial.println("I2C Master started...");
}

void loop() {
  // Start communication with slave at address SLAVE_ADDR
  Wire.beginTransmission(SLAVE_ADDR); 

  // Send the string message character by character
  for (int i = 0; i < strlen(MSG_TO_SLAVE); i++) {
    Wire.write(MSG_TO_SLAVE[i]); // Send each byte (character)
  }

  // End transmission and check if the slave is responding
  byte error = Wire.endTransmission();

  if (error == 0) {
    // Success: The slave has acknowledged the data
    Serial.println("Data sent successfully to slave.");
  } else {
    // Error: Failed to communicate with the slave
    Serial.print("Error sending data to slave. Error code: ");
    Serial.println(error);
  }

  // Optionally, request data from the slave (if needed in the future)
  // Wire.requestFrom(SLAVE_ADDR, 16); // Request 16 bytes from slave
  // while (Wire.available()) {
  //   char received = Wire.read();
  //   Serial.print(received);  // Print the received byte from slave
  // }

  delay(1000);  // Wait 1 second before sending data again
}
