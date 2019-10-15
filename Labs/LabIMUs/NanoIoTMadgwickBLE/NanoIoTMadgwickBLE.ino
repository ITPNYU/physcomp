/*
  Madgwick orientation calculation with BLE output
  Uses Arduino MadgwickAHRS library to calculate heading, pitch, and roll
  on an Arduino Nano 33 IoT, using the onboard LSM6DS3 IMU.
  Also makes the readings available as a BLE service

  For big fun, connect this to p5.js sketch MadgwickVisualizer

  created 13 Aug 2019
  modified 15 Oct 2019
  by Tom Igoe
*/
#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>
#include <ArduinoBLE.h>

BLEService orientationService("23ce3f92-be01-11e9-9cb5-2a2ae2dbcce4");
const char localName[] = "myNano33BLE";

// create characteristics for heading, pitch, roll
// and allow remote device to read and get notifications about them:
BLEFloatCharacteristic headingCharacteristic("23ce450a-be01-11e9-9cb5-2a2ae2dbcce4", BLERead | BLENotify);
BLEFloatCharacteristic pitchCharacteristic("23ce4276-be01-11e9-9cb5-2a2ae2dbcce4", BLERead | BLENotify);
BLEFloatCharacteristic rollCharacteristic("23ce43ca-be01-11e9-9cb5-2a2ae2dbcce4", BLERead | BLENotify);

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
  // begin IMU:
  if (!IMU.begin()) {
    Serial.println("Starting IMU failed.");
    // stop here if you can't access the IMU:
    while (true);
  }
  // start the Madgwick filter to run at the sample rate:
  filter.begin(sensorRate);

  // begin BLE:
  if (BLE.begin()) {
    // set advertised local name and service UUID:
    BLE.setLocalName(localName);
    BLE.setAdvertisedService(orientationService);

    // add the characteristics to the service:
    orientationService.addCharacteristic(headingCharacteristic);
    orientationService.addCharacteristic(pitchCharacteristic);
    orientationService.addCharacteristic(rollCharacteristic);

    // add service and start advertising:
    BLE.addService(orientationService);
    BLE.advertise();
  } else {
    Serial.println("starting BLE failed.");
    // stop here if you can't access the BLE radio:
    while (true);
  }
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to this peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      updateOrientation();
    }

    // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void updateOrientation() {
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
      // update the heading, pitch and roll:
      roll = filter.getRoll();
      pitch = filter.getPitch();
      heading = filter.getYaw();
      Serial.print("Orientation: ");
      Serial.print(heading);
      Serial.print(" ");
      Serial.print(pitch);
      Serial.print(" ");
      Serial.println(roll);

      // update the BLE characteristics with the orientation values:
      headingCharacteristic.writeValue(heading);
      pitchCharacteristic.writeValue(pitch);
      rollCharacteristic.writeValue(roll);
  }
}
