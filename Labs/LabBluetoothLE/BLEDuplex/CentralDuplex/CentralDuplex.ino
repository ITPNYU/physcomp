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

// peripheral characteristic flags:
bool ledAvailable = false;
bool buttonSubscribed = false;
void setup() {
  Serial.begin(9600);

  // configure the button pin as input:
  pinMode(buttonPin, INPUT);
  // configure the built-in LED as an output:
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the BLE hardware
  BLE.begin();

  // start scanning for peripherals
  BLE.scanForUuid("473da924-c93a-11e9-a32f-2a2ae2dbcce4");
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // peripheral detected, see if it's the right one:
    if (peripheral.localName() == "duplexPeripheral") {
      // If so, stop scanning and start communicating with it:
      BLE.stopScan();
      communicateWith(peripheral);
    }
    // if there's no perhpheral, keep scanning:
  } else {
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
    return;
  }
  // If you can't discover peripheral attributes
  // go back to the main loop:
  if (!peripheral.discoverAttributes()) {
    peripheral.disconnect();
    return;
  }
  // retrieve the characteristics:
  BLECharacteristic buttonCharacteristic =
    peripheral.characteristic("473dab7c-c93a-11e9-a32f-2a2ae2dbcce4");
  BLECharacteristic ledCharacteristic =
    peripheral.characteristic("473dacc6-c93a-11e9-a32f-2a2ae2dbcce4");

  if (ledCharacteristic) {
    if (ledCharacteristic.canWrite()) {
      // you're in business with the LED
      ledAvailable = true;
    }
  }

  // subscribe to the simple key characteristic
  Serial.println("Subscribing to simple key characteristic ...");
  if (buttonCharacteristic) {
    if (buttonCharacteristic.canSubscribe()) {
      if (buttonCharacteristic.subscribe()) {
        buttonSubscribed = true;
      }
    }
  }

  // this while loop will run as long as you're connected to the peripheral:
  while (peripheral.connected()) {
    // while the peripheral is connected,
    // read the button pin:
    byte buttonState = digitalRead(buttonPin);
    // if the button has changed:
    if (oldButtonState != buttonState) {
      // if the LED characteristic is available, change it:
      if (ledAvailable) {
        // change the peripheral's LED:
        ledCharacteristic.writeValue(buttonState);
      }
      // save current button state for next check:
      oldButtonState = buttonState;
    }


    if (buttonSubscribed) {
      // check the peripheral's button characteristic:
      if (buttonCharacteristic.valueUpdated()) {
        //if it's changed, read it:
        byte value = 0;
        buttonCharacteristic.readValue(value);
        // set the local LED to the state of the peripheral button characteristic:
        digitalWrite(LED_BUILTIN, value);
      }
    }  // end of while peripheral connected
    // turn the LED off for good measure:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Peripheral disconnected");
  }
}
