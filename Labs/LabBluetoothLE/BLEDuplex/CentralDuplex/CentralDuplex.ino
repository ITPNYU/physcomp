/*
  Central duplex communication.

  This example scans for BLE peripherals until one with  the advertised service
  UUID is found. Once discovered and connected, this device
  will monitor the peripheral's button characteristic and use it to set a local LED,
  and will change the peripheral's LED characteristic from a local button.
  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button with pull-down resistor connected to pin 2.
  - LED connected to built-in LED pin.

  You can use it with another board that is compatible with this library
  and running the PeripheralDuplex example.

  created 27 Aug 2019
  by Tom Igoe
  based on Sandeep Mistry's examples
*/

#include <ArduinoBLE.h>

// variables for button:
const int buttonPin = 2;
int oldButtonState = LOW;

BLECharacteristic ledCharacteristic;
BLECharacteristic buttonCharacteristic;

// peripheral characteristic flags:
bool ledAvailable = false;
bool buttonSubscribed = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  // configure the button pin as input:
  pinMode(buttonPin, INPUT_PULLUP);
  // configure the built-in LED as an output:
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the BLE hardware
  BLE.begin();

  // start scanning for peripherals
  BLE.scanForUuid("473da924-c93a-11e9-a32f-2a2ae2dbcce4");
  Serial.println("central is scanning");
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.println("Got a peripheral");
    // peripheral detected, see if it's the right one:
    if (peripheral.localName() == "duplexPeripheral") {
      Serial.println("Got the right peripheral");
      // If so, stop scanning and start communicating with it:
      BLE.stopScan();
      communicateWith(peripheral);
    }
    // when the peripheral disconnects, resume scanning:
    // reset the peripheral characteristic flags:
    ledAvailable = false;
    buttonSubscribed = false;
    // start scanning again:
    BLE.scanForUuid("473da924-c93a-11e9-a32f-2a2ae2dbcce4");
  }
}

void communicateWith(BLEDevice peripheral) {
  // connect to the peripheral
  Serial.println("Connecting ...");
  // if you can't connect, go back to the main loop:
  if (!peripheral.connect()) {
    Serial.println("Can't connect");
    return;
  }
  // If you can't discover peripheral attributes
  // go back to the main loop:
  if (!peripheral.discoverAttributes()) {
    Serial.println("Didn't discover attributes");
    peripheral.disconnect();
    return;
  }
  // if you don't know the UUIDs of the characteristics you want
  // you can loop over the service and explore each service
  // to see if it matches what you need:
  //  // loop the services of the peripheral and explore each
  //  for (int i = 0; i < peripheral.serviceCount(); i++) {
  //    BLEService service = peripheral.service(i);
  //    exploreService(service);
  //  }

  // when you know the UUIDs of the characteristics you want,
  // you can just pull them out of the remote peripheral like this:
  buttonCharacteristic = peripheral.characteristic("473dab7c-c93a-11e9-a32f-2a2ae2dbcce4");
  ledCharacteristic = peripheral.characteristic("473dacc6-c93a-11e9-a32f-2a2ae2dbcce4");

  if (buttonCharacteristic.canSubscribe()) {
    Serial.println("can subscribe");
    if (buttonCharacteristic.subscribe()) {
      Serial.println("button subscribed");
    }
  }
  // this while loop will run as long as you're connected to the peripheral:
  while (peripheral.connected()) {
    // while the peripheral is connected,
    // read the button pin:
    byte buttonState = digitalRead(buttonPin);
    // if the button has changed:
    //    if (oldButtonState != buttonState) {
    // if the LED characteristic is available, change it:
    if (ledCharacteristic) {
      // change the peripheral's LED:
      ledCharacteristic.writeValue(buttonState);
      Serial.println("writing to remote LED");
    }
    // save current button state for next check:
    oldButtonState = buttonState;
  }

  if (buttonCharacteristic) {
    // check the peripheral's button characteristic:
    if (buttonCharacteristic.valueUpdated()) {
      // if it's changed, read it:
      byte value = 0;
      buttonCharacteristic.readValue(value);
      Serial.println("remote button changed");
      // set the local LED to the state of the peripheral button characteristic:
      digitalWrite(LED_BUILTIN, value);
    }
  }  // end of while peripheral connected
  // turn the LED off for good measure:
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Peripheral disconnected");
}

// these functions ar for exploring a remote peripheral's
// services and characteristics:
void exploreService(BLEService service) {
  // loop the characteristics of the service and explore each
  for (int i = 0; i < service.characteristicCount(); i++) {
    BLECharacteristic characteristic = service.characteristic(i);
    exploreCharacteristic(characteristic);
  }
}

void exploreCharacteristic(BLECharacteristic characteristic) {
  // check if the characteristic is readable
  String thisUuid = String(characteristic.uuid());
  if (characteristic.canSubscribe() &&
      // does it match the UUID you care about?
      thisUuid == "473dab7c-c93a-11e9-a32f-2a2ae2dbcce4") {
    Serial.println("can subscribe");
    // read the characteristic value
    buttonCharacteristic = characteristic;
    if (buttonCharacteristic.subscribe()) {
      Serial.println("button subscribed");
    }
  }
  // Check if it's writable:
  if (characteristic.canWrite() &&
      // does it match the UUID you care about?
      thisUuid == "473dacc6-c93a-11e9-a32f-2a2ae2dbcce4") {
    ledCharacteristic = characteristic;
    Serial.println("led available");
  }
}
