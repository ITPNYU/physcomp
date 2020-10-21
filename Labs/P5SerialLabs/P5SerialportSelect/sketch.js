/*
  Serial port selector
  uses DOM elements to make a serial port selector
  
  created 20 Oct 2020
  by Tom Igoe
*/

// variable to hold an instance of the serialport library:
let serial;
// HTML Select option object:
let portSelector;

function setup() {
  serial = new p5.SerialPort(); // new instance of the serialport library
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback function for serialport data event
  serial.list(); // list the serial ports
}

// make a serial port selector object:
function printList(portList) {
  // create a select object:
  portSelector = createSelect();
  portSelector.position(10, 10);
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // add this port name to the select object:
    portSelector.option(portList[i]);
  }
  // set an event listener for when the port is changed:
  portSelector.changed(mySelectEvent);
}


function mySelectEvent() {
  let item = portSelector.value();
  // give it an extra property for hiding later:
  portSelector.visible = true;
  // if there's a port open, close it:
  if (serial.serialport != null) {
    serial.close();
  }
  // open the new port:
  serial.open(item);
}

function keyPressed() {
  // if port selector is visible hide, else show:
  if (portSelector) {
    if (portSelector.visible) {
      portSelector.hide();
      portSelector.visible = false;
    } else {
      portSelector.show();
      portSelector.visible = true;
    }
  }
}

function serialEvent() {
  var inData = serial.readLine();
  console.log(inData);
}