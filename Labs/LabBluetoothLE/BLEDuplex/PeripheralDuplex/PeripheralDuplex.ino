/*

  Peripheral duplex communication.

  This example waits for a connection from a central device.
  Once discovered and connected, the LED changes when the ledCharacteristic
  is written from by central device and the buttonCharacteristic changes
  when the local pushbutton is pressed.
  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
  - Button with pull-down resistor connected to pin 2.
  - LED connected to built-in LED pin.

  You can use it with another board that is compatible with this library
  and running the CentralDuplex example.

  created 27 Aug 2019
  by Tom Igoe
  based on Sandeep Mistry's examples
*/

#include <ArduinoBLE.h>

// variables for button:
const int buttonPin = 2;
int oldButtonState = LOW;

// create service
BLEService duplexService("473da924-c93a-11e9-a32f-2a2ae2dbcce4");
// create button characteristic and allow remote device to get notifications
BLEByteCharacteristic buttonCharacteristic("473dab7c-c93a-11e9-a32f-2a2ae2dbcce4",
    BLERead | BLENotify);
// create LED characteristic and allow remote device to read and write
BLEByteCharacteristic ledCharacteristic("473dacc6-c93a-11e9-a32f-2a2ae2dbcce4",
                                        BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT); // use the LED as an output
  pinMode(buttonPin, INPUT_PULLUP); // use button pin as an input

  // begin initialization
  BLE.begin();

  // set the local name that the peripheral advertises
  BLE.setLocalName("duplexPeripheral");
  // set the UUID for the service the peripheral advertises:
  BLE.setAdvertisedService(duplexService);

  // add the characteristics to the service
  duplexService.addCharacteristic(ledCharacteristic);
  duplexService.addCharacteristic(buttonCharacteristic);

  // add the service
  BLE.addService(duplexService);

  ledCharacteristic.writeValue(0);
  buttonCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();
  Serial.println("Peripheral is running");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Got a central");
    while (central.connected()) {
      // read the current button pin state
      byte buttonValue = digitalRead(buttonPin);

      // if the button has changed since the last read:
      if (buttonCharacteristic.value() != buttonValue) {
        // update button characteristic:
        buttonCharacteristic.writeValue(buttonValue);
        Serial.println("writing to button char..");
      }

      if (ledCharacteristic.written()) {
        // update LED when central writes to characteristic:
        byte ledState = ledCharacteristic.value();
        digitalWrite(LED_BUILTIN, ledState);
        Serial.println("changing LED");
      }
    }

    // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
