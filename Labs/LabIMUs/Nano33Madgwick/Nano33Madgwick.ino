/*
  Madgwick orientation calculation
  Uses Arduino MadgwickAHRS library to calculate heading, pitch, and roll
  on an Arduino Nano 33 IoT, using the onboard LSM6DS3 IMU.

  For big fun, connect this to p5.js sketch MadgwickVisualizer

  created 4 Aug 2019
  updated 25 Aug 2019
  by Tom Igoe
*/

#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>

// initialize a Madgwick filter:
Madgwick filter;
// sensor's sample rate is fixed at 104 Hz:
const float sensorRate = 104.00;

// values for orientation:
float roll = 0.0;
float pitch = 0.0;
float heading = 0.0;

void setup() {
  Serial.begin(9600);
  // attempt to start the IMU:
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    // stop here if you can't access the IMU:
    while (true);
  }
  // start the filter to run at the sample rate:
  filter.begin(sensorRate);
}

void loop() {
  // values for acceleration & rotation:
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;

  // check if the IMU is ready to read:
  if (IMU.accelerationAvailable() &&
      IMU.gyroscopeAvailable()) {
    // read accelerometer & gyrometer:
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro);

    // update the filter, which computes orientation:
    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
  }

  // if you get a byte in the serial port,
  // send the latest heading, pitch, and roll:
  if (Serial.available()) {
    char input = Serial.read();   
    Serial.print(heading);
    Serial.print(",");
    Serial.print(pitch);
    Serial.print(",");
    Serial.println(roll);
  }
}
