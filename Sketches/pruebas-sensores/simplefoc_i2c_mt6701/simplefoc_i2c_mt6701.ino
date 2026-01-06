#include <SimpleFOC.h>
#include <Wire.h>

const int SENSOR_SDA = 12;
const int SENSOR_SCL = 13;

// MT6701 Config: Address 0x06, 14-bit, Start Register 0x03, 8-bit length
MagneticSensorI2C sensor = MagneticSensorI2C(0x06, 14, 0x03, 8);

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for the Serial Monitor to open

  // 2. Initialize I2C on specific Pico pins
  Wire.setSDA(SENSOR_SDA);
  Wire.setSCL(SENSOR_SCL);
  Wire.begin();
  Wire.setClock(400000); // 400kHz fast mode

  // 3. Initialize the Sensor
  Serial.println("Initializing Sensor...");
  sensor.init();
  
  Serial.println("Sensor Ready. Please rotate the magnet.");
}

void loop() {
  // 4. Update the sensor state
  sensor.update();

  // 5. Print the angle in Radians
  // You should see values from 0.00 to ~6.28
  Serial.print("Angle: ");
  Serial.println(sensor.getAngle());

  // Slow down the loop slightly so you can read the numbers
  delay(5); 
}