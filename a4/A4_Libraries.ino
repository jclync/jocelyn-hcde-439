/* A4: Libraries
 *  Jocelyn Chen
 *  Monday 2.14.2022
 *  
 *  This program is a color selector circuit which input is taken using a photoresistor to 
 *  choose a LED color to fade a RGB LED to the chosen color using a capacitive sensor.
 *  
*/

// include library for capacitive sensor
#include <CapacitiveSensor.h>

// capacitive sensor with 1 megaohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);

/// SET PINS FOR LEDs and PHOTORESISTOR ///

// pins for red, green, and blue LEDs (red = pin3, green = pin5, blue = pin6)
const int leds_pins[] = {3, 5, 6};

// pins for the RGB LED ( red = pin9, green = pin10, blue = pin11)
const int rgb_led_pin[] = {9, 10, 11};

// number of total LEDs that a user can choose a color from (red, green, or blue)
const int num_leds = 3;

// pin used for photoresistor sensor (will be used for choosing a LED color: red, green or blue)
const int sensor_pin = A0;

// the number LED chosen (corresponding to LED number in leds_pins[] and rgb_led_pin[] arrays)
int led = 0;

/// SETUP FUNCTION ///
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize pins for the red, green, blue, and RGB LEDs as outputs
  for (int i = 0; i < num_leds; i++) {
    // pins for red, green, and blue LEDs
    pinMode(leds_pins[i], OUTPUT);
    // pins for RGB LED
    pinMode(rgb_led_pin[i], OUTPUT);
  }
}

/// CHOOSE COLOR FUNCTION ///
// function to choose LED color (red, green, or blue) based on the analog in value from the photoresistor
//    Parameter:
//      - int sensor_in: the analog in value read in from the photoresistor
int choose_color(int sensor_in) {
  // change the LED color based on the analog in value
    // if analog in value >= 600 -> red LED on
    // if analog in value < 600 and >= 350 -> green LED on
    // if analog in value < 350 -> blue LED on
  if (sensor_in >= 600) {
    // turn red LED on (set pin to 255) and green and blue LEDs off (set pins to 0)
    analogWrite(leds_pins[0], 255);
    analogWrite(leds_pins[1], 0);
    analogWrite(leds_pins[2], 0);
    // set LED number to 0
    led = 0;
  } else if (sensor_in < 600 & sensor_in >= 350) {
    // turn green LED on (set pin to 255) and red and blue LEDs off (set pins to 0)
    analogWrite(leds_pins[0], 0);
    analogWrite(leds_pins[1], 255);
    analogWrite(leds_pins[2], 0);  
    // set LED number to 1
    led = 1;  
  } else { // sensor_in < 300
    // turn blue LED on (set pin to 255) and red and green LEDs off (set pins to 0)
    analogWrite(leds_pins[0], 0);
    analogWrite(leds_pins[1], 0);
    analogWrite(leds_pins[2], 255); 
    // set LED number to 2
    led = 2;
  }
  // return the LED number
  return led;
}

/// FADE RGB FUNCTION ///
// function to fade the RGB LED to the chosen LED color based on the capacitive sensor value
//    Parameters:
//      - int rgb_in: the capacitance value from the capacitive sensor
//      - int led_num: the chosen LED color
//      - int rgb_out: the constrained value 
void fade_rgb(int rgb_in, int led_num, int rgb_out) {
  // set color of the RGB LED based on the capacitive sensor reading
  //     if the capacitive sensor reading is &#60; 100, set the starting color and brightness of the RGB LED
  //     if the capacitive sensor reading is >= 100, set the RGB LED to the given color and calibrated brightness
  if (rgb_in < 100) {
    // set the starting color of the RGB LED, with red, green, and blue each at 10
    for (int i = 0; i < num_leds; i++) {
      analogWrite(rgb_led_pin[i], 10); 
    }
  } else { // rgb_in > 100
    // set the given color of the RGB LED to the given output value
    analogWrite(rgb_led_pin[led_num], rgb_out);
  }    
}


/// LOOP FUNCTION ///

// the loop function runs over and over again forever
void loop() {
  // set sensor resolution to 30
  long total1 =  cs_4_2.capacitiveSensor(30);
  
  // wait 100 millisec (delay) to limit data to serial port
  delay(100);
  
  // read the analog in value of the photoresistor:
  int sensor_value = analogRead(sensor_pin);

  // map the capacitive sensor reading to the range of the analog out to calibrate
      // read in a range 0 - 800 from the capacitive sensor
      // write out a range 0 - 255 (for the LED)
  int cs_value = map(total1, 0, 800, 0, 255);

  // constrain the output to be only from 0 to 255
  int cs_constrained = constrain(cs_value, 0, 255);

  // choose an LED color (red, green, or blue) based on the analog in reading from the photoresistor
  int chosen_led = choose_color(sensor_value);

  // fade the RGB LED to the given color (using the chosen_led variable) and brightness 
  // (using the capacitive sensor reading and its mapped constrained analog out value)
  fade_rgb(cs_value, chosen_led, cs_constrained);
}
