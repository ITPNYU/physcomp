/*
  Serial graphing application
  uses p5.js and p5.serialport and chart.js. 
  Requires p5.serialcontrol app to be open as well.

  This sketch assumes it will receive binary values 
  between 0 and 255.
  
  For more on chart.js, see https://www.chartjs.org/

  created 9 July 2021
  modified 4 Aug 2021
  by Tom Igoe
*/

// variable to hold an instance of the serialport library:
let serial;
// HTML Select option object:
let portSelector;

// array to put the readings from the sensors into:
let readings = new Array();
// number of data points you plan to show:
let dataSize;

// The chart.js chart:
let chart;

// data object for the chart:
const data = {
  // X axis labels
  labels: new Array(),
  datasets: [{
    label: 'Serial Input',  // chart label
    data: readings,         // the data to chart
    borderColor: '#B765FF', // line color (lavender)
    pointRadius: 0          // point size
  }]
};

const config = {
  type: 'line',         // type of chart
  data: data,           // the data
  options: {
    animation: false,   // remove animation to speed drawing up
    scales: {           // axis ranges:
      y: {
        type: 'linear',
        min: 0,
        max: 255
      }
    }
  }
};

function setup() {
  // set up the canvas:
  createCanvas(800, 600);
  // set the data size based on the window size:
  dataSize = width - 20;
  // new instance of the serialport library:
  serial = new p5.SerialPort();
  // callback function for serialport:
  serial.on('list', printList);
  serial.on('data', serialEvent);
  // list the serial ports:
  serial.list();

  // set up the labels for the chart:
  for (let i = 0; i < dataSize; i++) {
    data.labels.push(i + 1);
  }
  // instantiate the chart:
  chart = new Chart(
    this,   // context: this sketch
    config  // config from the global variables
  );

}

function draw() {
  // update the chart:
  chart.update();
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
  // if port selector is visible, hide it, else show it:
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

// if new serial data comes in, put it in the readings array:
function serialEvent() {
  // assume a binary value from 0-255:
  let inData = Number(serial.read());
  // if you have a valid reading, add it to the data set:
  if (inData) {
    // add the latest reading to the end of the array:
    readings.push(inData);
    // if the reading array's longer than the graph is wide,
    // remove the first reading:
    if (readings.length > dataSize) {
      readings.shift();
    }
  }
}