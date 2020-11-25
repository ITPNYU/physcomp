/*
  Serial port sender for mobile

  Sends touch Y value on a mobile phone to p5.serialcontrol to send out
  the serial port of your computer. Used to control the fade of an LED
  on a microcontroller (see fader.ino sketch in this folder).

  This sketch also generates a QR code so you can scan 
  the computer screen to get it on your phone.

  To open this on your laptop:
  * open the command line terminal application
  * cd to the directory of this sketch
  * Type: 
  python -m SimpleHTTPServer

  This will launch a local server on your computer. Then open the 
  IP address of your computer, port 8000, in the browser, like so:
  http://0.0.0.0:8000

  The page will load with a QR code. Scan the code with your phone
  in Chrome and the sketch should run on your phone.
  
  created 25 Nov 2020
  by Tom Igoe
*/

// variable to hold an instance of the serialport library:
let serial;
// HTML Select option object:
let portSelector;
// create HTML DIV elements for the text from serial and touch:
let serialInDiv, touchDiv;

// set the address of the computer on which you are running p5.serialControl here:
let myIPaddress = parent.location.hostname;

// a string to display in the QR code
// (the URL of this sketch):
let urlString = parent.location.href;
// an HTML div to display it in:
let tagDiv;

function setup() {
  // set up the canvas to be as big as the window:
  createCanvas(windowWidth, windowHeight);
  // initialize serial:
  serial = new p5.SerialPort(myIPaddress); // new instance of the serialport library
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback function for serialport data event
  serial.list(); // list the serial ports

  // create divs to put text in for serial in and touch:
  serialInDiv = createDiv('serial data will go here');
  serialInDiv.position(10, 80);
  touchDiv = createDiv('touch data will go here');
  touchDiv.position(10, 120);

  createCanvas(windowWidth, windowHeight);
  // make the HTML tag div:
  tagDiv = createDiv();

  // make a QR code from the URL
  // so you can scan your laptop screen to open it 
  // on your phone:
  let qr = qrcode(0, 'L');
  qr.addData(urlString);
  qr.make();
  // create an image from it:
  let qrImg = qr.createImgTag(10, 8, "qr code");
  // put the image and the URL string into the HTML div:
  tagDiv.html(urlString + '<br>' + qrImg);
  // position it:
  tagDiv.position(width/2, 10);
  // set a callback function for clicking on the tag
  // (this function will hide the tag when you tap on it):
  tagDiv.mousePressed(hideTag);
}

function draw() {
  // nothing happens in draw, it's all driven by touch input or serial
}

// make a serial port selector object:
function printList(portList) {
  // create a select object:
  portSelector = createSelect();
  portSelector.position(10, 40);
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // add this port name to the select object:
    portSelector.option(portList[i]);
  }
  // set an event listener for when the port is changed:
  portSelector.changed(mySelectEvent);
}

// this function is called when the serial port selector changes:
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

// when the person stops touching, send the touch Y value
// out the serial port:

function touchEnded() {
  // get the touch Y value, divide by window height and multiply
  // to get a 0-255 value:
  touchY = floor(mouseY / windowHeight * 255);
  // send it out the serial port as a binary value (not a string):
  serial.write(touchY);
  // put it onscreen too:
  touchDiv.html("touch Y: " + touchY);
}

function serialEvent() {
  // read the serial data in:
  var inData = serial.readLine();
  // if it's a valid value:
  if (inData !== null) {
    serialInDiv.html("Received serial data: " + inData);
  }
}

// This function hides the tag div when you click on it:
function hideTag() {
  tagDiv.hide();
}