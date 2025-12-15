#include <SimpleFOC.h>
#include <Wire.h>

MagneticSensorI2C mt6701 = MagneticSensorI2C(0x06, 14, 0x03, 8);

//angle setpoint variable
float target_angle = 0;

BLDCMotor drone_motor = BLDCMotor(7); // número de Pole-Pairs
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8); //pines para cada fase y "enable" pin.

Commander command = Commander(Serial);
void doTarget(char* cmd) {
  command.scalar(&target_angle, cmd);
}

void setup() {
  Wire.begin(115200);
  Wire.setClock(400000);
  SimpleFOCDebug::enable(&Serial);

  //inicialización del sensor:
  mt6701.init();
  //unión del motor al sensor
  drone_motor.linkSensor(&mt6701);

  //Configuración del driver:
  driver.voltage_power_supply = 12;
  driver.init();

  motor.linkDriver(&driver);

  //selección de la modulación FOC (opcional, pero conservado del ejemplo)
  drone_motor.foc_modulation = FOCModulationType::SpaceVectorPWM;

  //elegir el tipo de control para el motor:
  motor.controller = MotionControlType::angle;

  //configuración del controlador, parámetros por defecto en defaults.h

  //parámetros del controlador PID de la velocidad:
  motor.PID_velocity.P = 0.2f;
  motor.PID_velocity.I = 20;
  motor.PID_velocity.D = 0;

  //tensión máxima para el motor:
  motor.voltage_limit = 6;

    // velocity low pass filtering time constant
  // the lower the less filtered
  motor.LPF_velocity.Tf = 0.01f;

  // angle P controller
  motor.P_angle.P = 20;
  // maximal velocity of the position control
  motor.velocity_limit = 20;
  
  // comment out if not needed
  motor.useMonitoring(Serial);


  // initialize motor
  motor.init();
  // align sensor and start FOC
  motor.initFOC();

  // add target command T
  command.add('T', doTarget, "target angle");

  Serial.println(F("Motor ready."));
  Serial.println(F("Set the target angle using serial terminal:"));
  _delay(1000);

}

void loop() {

  // main FOC algorithm function
  // the faster you run this function the better
  // Arduino UNO loop  ~1kHz
  // Bluepill loop ~10kHz
  motor.loopFOC();

  // Motion control function
  // velocity, position or voltage (defined in motor.controller)
  // this function can be run at much lower frequency than loopFOC() function
  // You can also use motor.move() and set the motor.target in the code
  motor.move(target_angle);


  // function intended to be used with serial plotter to monitor motor variables
  // significantly slowing the execution down!!!!
  // motor.monitor();

  // user communication
  command.run();
}
