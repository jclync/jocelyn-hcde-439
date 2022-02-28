var serial; // variable to hold an instance of the serialport library
var portName = '/dev/tty.usbmodem14101' //rename to the name of your port
var dataarray = []; // data coming in over serial
var datastring = ""; // data read in from serial
var colorpicked = ""; // color picked using joystick


function setup() {
  serial = new p5.SerialPort();       // make a new instance of the serialport library
  serial.on('list', printList);       // set a callback function for the serialport list event
  serial.on('connected', serverConnected); // callback for connecting to the server
  serial.on('open', portOpen);        // callback for the port opening
  serial.on('data', serialEvent);     // callback for when new data arrives
  serial.on('error', serialError);    // callback for errors
  serial.on('close', portClose);      // callback for the port closing
 
  serial.list();                      // list the serial ports
  serial.open(portName);              // open a serial port
  createCanvas(1200, 700);
  background(0x08, 0x16, 0x40);
}
 
// get the list of ports:
function printList(portList) {
 // portList is an array of serial port names
 for (var i = 0; i < portList.length; i++) {
 // Display the list the console:
   print(i + " " + portList[i]);
 }
}

function serverConnected() {
  print('connected to server.');
}
 
function portOpen() {
  print('the serial port opened.')
}
 
function serialError(err) {
  print('Something went wrong with the serial port. ' + err);
}
 
function portClose() {
  print('The serial port closed.');
}

function serialEvent() {
  if (serial.available()) {
	  datastring = serial.readLine(); // readin some serial
	  var newarray;
	try {
  	  newarray = JSON.parse(datastring); // can we parse the serial
  	} catch(err) {
      	  //console.log(err);
	}
	if (typeof(newarray) == 'object') {
  	dataarray = newarray;
	}
	console.log("got back " + datastring);
  }
}

function graphData(newData) {
  // map the range of the input to the window height and width for x position and y position of joystick:
  var yPos = map(newData[1], 0, 1023, height, 0);
  var xPos = map(newData[0], 0, 1023, 0, width)

  background(0x08, 0x16, 0x40); // background navy
  createColors(); // create rectangles for the different colors to choose from (red, blue, green, purple, white)

  circle(xPos, yPos, 20, 20); // circle for joystick pointer

  // change the circle's color (Rudolph's nose) based on where the joystick pointer is located:
  // - change the fill color, then change the circle to the chosen color
  //    if joystick is pointing at red square -> change circle to red
  //    if joystick is pointing at blue square -> change circle to blue
  //    if joystick is pointing at green square -> change circle to green
  //    if joystick is pointing at pink square -> change circle to pink 
  //    if joystick is pointing at yellow square -> change circle to yellow
  //    if joystick is pointing at white square -> change circle to white
  //
  // joystick pointing at red square     
  if (xPos >= 100 && xPos <= 300 && yPos >= 50 && yPos <= 250) {
    fill('red');
    circle(605, 355, 20, 20);
    colorpicked = "red";
    // joystick pointing at blue square
  } else if (xPos >= 500 && xPos <= 700 && yPos >= 50 && yPos <= 250) {
    fill('blue');
    circle(605, 355, 20, 20);
    colorpicked = "blue";
    // joystick pointing at green square
  } else if (xPos >= 900 && xPos <= 1100 && yPos >= 50 && yPos <= 250) {
    fill('rgb(0, 230, 64)'); // green
    circle(605, 355, 20, 20);
    colorpicked = "green";
    // joystick pointing at pink square
  } else if (xPos >= 100 && xPos <= 300&& yPos >= 450 && yPos <= 650) {
    fill('rgb(255,0,255)'); // pink
    circle(605, 355, 20, 20);
    colorpicked = "pink";
    // joystick pointing at yellow square
  } else if (xPos >= 500 && xPos <= 700 && yPos >= 450 && yPos <= 650) {
    fill('yellow');
    circle(605, 355, 20, 20);
    colorpicked = "yellow";
    // joystick pointing at white square
  } else if (xPos >= 900 && xPos <= 1100 && yPos >= 450 && yPos <= 650) {
    fill('white');
    circle(605, 355, 20, 20);
    colorpicked = "white";
  }
}

// create the squares on the page, setting the color, coordinates, size (220 by 200), and radius 20
function createColors() {
  fill('red'); // red
  rect(100, 50, 220, 200, 20);

  fill('blue'); // blue
  rect(500, 50, 220, 200, 20);

  fill('rgb(0, 230, 64)'); // green
  rect(900, 50, 220, 200, 20);

  fill('rgb(255,0,255)'); // pink
  rect(100, 450, 220, 200, 20);

  fill('rgb(255,255,51)'); // yellow
  rect(500, 450, 220, 200, 20);

  fill('rgb(255, 255, 255)'); // white
  rect(900, 450, 220, 200, 20);   

  // draw Rudolph using circles, points, and lines
  circle(605, 355, 60, 60); // Rudolph's head
  strokeWeight(5);
  point(595, 345); // Rudolph's eye
  point(615, 345); // Rudolph's eye
  line(590, 335, 560, 310); // Rudolph's antler
  line(615, 335, 645, 310); // Rudolph's antler
  circle(605, 355, 20, 20); // Rudolph's nose
  text("Pick a color for Rudolph's nose!", 525, 420); // place text under Rudolph
}

function draw() {
  graphData(dataarray);
  text("key pressed: " + key, 30, 30); // text showing what key has been pressed
  text("color chosen: " + colorpicked, 30, 50); // text showing what color has been chosen
}

function keyPressed() {
	//console.log("writing key");
	serial.write(key);
}
