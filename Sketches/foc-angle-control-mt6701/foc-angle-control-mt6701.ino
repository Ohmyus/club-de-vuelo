#include <SimpleFOC.h>
#include <Wire.h>

// --- CHECK YOUR WIRING ---
// Make sure your physical wires match these numbers!
// GP12/13 are on the corner of the Pico. GP14/15 are slightly further down.
const int SENSOR_SDA = 12; 
const int SENSOR_SCL = 13;

long int lastSend = 0;

MagneticSensorI2C sensor = MagneticSensorI2C(0x06, 14, 0x03, 8);
BLDCMotor motor = BLDCMotor(7); 
BLDCDriver3PWM driver = BLDCDriver3PWM(18, 19, 20, 16);

float target_angle = 0;
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_angle, cmd); }

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial monitor to open so you see the debug!
  
  SimpleFOCDebug::enable(&Serial);
  Serial.println("Initializing...");

  // 1. Setup I2C Pins correctly
  Wire.setSDA(SENSOR_SDA);
  Wire.setSCL(SENSOR_SCL);
  Wire.begin();
  Wire.setClock(400000); 

  // 2. Initialize Sensor
  sensor.init();
  
  Serial.println(); // New line
  // ---------------------------------------------

  motor.linkSensor(&sensor);

  driver.voltage_power_supply = 9;
  driver.init();
  motor.linkDriver(&driver);

  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor.controller = MotionControlType::angle;

  // 3. CRITICAL SETTINGS FOR DRONE MOTORS
  motor.voltage_limit = 0.5;       // Limit max voltage to avoid overheating
  motor.voltage_sensor_align = 0.4; // CRITICAL: Low voltage for calibration wiggle!
  
  // Controller PID
  // We drop P from 4 to 0.2 to stop the shaking
  motor.PID_velocity.P = 0.3f;  
  motor.PID_velocity.I = 0.2f;  // Turn off 'I' for now to simplify tuning
  motor.PID_velocity.D = 0.0f;
  motor.LPF_velocity.Tf = 0.05f; // Slightly more filtering (0.01 -> 0.05)

  // 3. Angle Loop (The Outer Loop)
  motor.P_angle.P = 2.0f;       // A safe starting point
  motor.velocity_limit = 10; // I'm still missing what unit this is supposed to be

  motor.init();
  
  // 4. Start FOC
  motor.initFOC();

  command.add('T', doTarget, "target_angle");
  Serial.println(F("Motor ready. Send 'T 1.0' to turn."));
}

void loop() {
  motor.loopFOC();
  motor.move(target_angle);
  command.run();

  if (millis() - lastSend > 2000) {
    Serial.print("motor is holding: ");
    Serial.println(target_angle);
    lastSend = millis();
  }
}