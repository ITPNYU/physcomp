/*
   IMU and BLE example for LSM6DS3 IMU on the Nano 33 IoT

  created 9 Nov 2020
  by Tom Igoe
*/

#include <Arduino_LSM6DS3.h>
#include <ArduinoBLE.h>

BLEService imuService("DE778444-22F4-11EB-ADC1-0242AC120002"); // create service

// create switch characteristic and allow remote device to read and write
BLEFloatCharacteristic accelXCharacteristic("DE777C7E-22F4-11EB-ADC1-0242AC120002", BLERead | BLENotify);
BLEFloatCharacteristic accelYCharacteristic("DE778016-22F4-11EB-ADC1-0242AC120002", BLERead | BLENotify);
BLEFloatCharacteristic accelZCharacteristic("DE778124-22F4-11EB-ADC1-0242AC120002", BLERead | BLENotify);
BLEFloatCharacteristic gyroXCharacteristic("DE7781EC-22F4-11EB-ADC1-0242AC120002", BLERead | BLENotify);
BLEFloatCharacteristic gyroYCharacteristic("DE7782B4-22F4-11EB-ADC1-0242AC120002", BLERead | BLENotify);
BLEFloatCharacteristic gyroZCharacteristic("DE77837C-22F4-11EB-ADC1-0242AC120002", BLERead | BLENotify);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  // start the IMU:
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    // stop here if you can't access the IMU:
    while (true);
  }

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (true);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("IMU_BLE");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(imuService);

  // add the characteristics to the service
  imuService.addCharacteristic(accelXCharacteristic);
  imuService.addCharacteristic(accelYCharacteristic);
  imuService.addCharacteristic(accelZCharacteristic);
  imuService.addCharacteristic(gyroXCharacteristic);
  imuService.addCharacteristic(gyroYCharacteristic);
  imuService.addCharacteristic(gyroZCharacteristic);

  // add the service
  BLE.addService(imuService);

  // start advertising
  BLE.advertise();
  Serial.println("BLE peripheral advertising...");
}

void loop() {
  // values for acceleration & rotation:
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;
  // instance of BLE central to listen for connections:
  BLEDevice central = BLE.central();

  if (central) {
    // turn on LED to indicate connection:
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Got a central");
    Serial.println(central.address());
    while (central.connected()) {
      // if both accelerometer & gyrometer are ready to be read:
      if (IMU.accelerationAvailable() &&
          IMU.gyroscopeAvailable()) {
        // read accelerometer & gyrometer:
        IMU.readAcceleration(xAcc, yAcc, zAcc);
        IMU.readAcceleration(xGyro, yGyro, zGyro);
      }
      // update the sensor characteristics:
      accelXCharacteristic.writeValue(xAcc);
      accelYCharacteristic.writeValue(yAcc);
      accelZCharacteristic.writeValue(zAcc);
      gyroXCharacteristic.writeValue(xGyro);
      gyroYCharacteristic.writeValue(yGyro);
      gyroZCharacteristic.writeValue(zGyro);
    }

    // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
    // turn off LED:
    digitalWrite(LED_BUILTIN, LOW);
  }
}
