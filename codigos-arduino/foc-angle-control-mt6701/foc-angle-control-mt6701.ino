#include <SimpleFOC.h>
#include <Wire.h>

bool system_ready;
const int SENSOR_SDA = 12; 
const int SENSOR_SCL = 13;

long int lastSend = 0;

MagneticSensorI2C sensor = MagneticSensorI2C(0x06, 14, 0x03, 8);
BLDCMotor motor = BLDCMotor(7, 19.6); 
BLDCDriver3PWM driver = BLDCDriver3PWM(18, 19, 20, 16);

float target_angle = 0;
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_angle, cmd); }
// Commander para actualizar parámetros del motor
void doMotor(char* cmd) { command.motor(&motor, cmd); }

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
  motor.voltage_limit = 9;       // Limit max voltage to avoid overheating
  motor.voltage_sensor_align = 4; // CRITICAL: Low voltage for calibration wiggle!
  
  // Controller PID
  motor.PID_velocity.P = 0.15f; 
  motor.PID_velocity.I = 0.6f; 
  motor.PID_velocity.D = 0.001f;
  motor.LPF_velocity.Tf = 0.05f;

  // 3. Angle Loop (The Outer Loop)
  motor.P_angle.P = 6.0f;
  //motor.P_angle.I = 0.5f;

  motor.velocity_limit = 20;     // Limit speed to 20 rad/s
  
  motor.init();
  
  // 4. Start FOC
if (motor.initFOC()) {
    Serial.println("MOT: Success! Calibration valid.");
    system_ready = true;
    command.add('T', doTarget, "target_angle");
    command.add('M', doMotor, "Motor Tuning");
    Serial.println(F("Ready, "));
    Serial.println(F("Commands: 'T 1.57' to move. 'M' to see settings."));
  } else {
    Serial.println("MOT: CRITICAL FAILURE. Pole Pair Check Failed!");
    Serial.println("Check magnet alignment or power supply.");
    system_ready = false;
  }
}

void loop() {
  if (!system_ready) {//Initialization not succesful
    // Print error every second
    static long lastError = 0;
    if (millis() - lastError > 1000) {
       Serial.println("SYSTEM HALTED: Calibration Failed");
       lastError = millis();
    }
    return; //Execution stops here
  }

  motor.loopFOC();
  motor.move(target_angle);
  command.run();

  if (millis() - lastSend > 100) {
    Serial.print(target_angle);
    Serial.print("\t");
    Serial.println(sensor.getAngle(),6);
  }
}