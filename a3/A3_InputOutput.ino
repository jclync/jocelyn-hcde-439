/// SET PINS FOR LEDs and VOLTAGE DIVIDERS ///

// set red LED to pin 3
const int red = 3;

// set green LED to pin 5
const int green = 5;

// set blue LED to pin 6
const int blue = 6;

// pins for the RGB LED
const int rgb_led_pin[] = {9, 10, 11};

// number of total leds that a user can choose a color from (red, green, or blue)
const int num_leds = 3;

// pin used for "sensor" using the photoresistor (will be used for rgb LED)
int rgb_sensor_pin = A0;

// pin used for potentiometer (will be used to choose color of red, green, blue LEDS)
int choose_color_pin = A5;


/// SETUP FUNCTION ///

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // initialize pins for the red, green, and blue LEDS as an output
  for (int i = 3; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }

  // initialize pins for the RGB LED as an output  
  for (int i = 0; i < num_leds; i++) {
    pinMode(rgb_led_pin[i], OUTPUT);
  }
}


// PRINT BRIGHTNESS STATUS MESSAGE FUNCTION //

// function to print out brightness status based on the analog in value from the photoresistor
//    Parameter:
//      - int sensor_value: the analog in value read in from the photoresistor
void rgbPrint(int sensor_value) {
  // print statements to serial monitor based on current brightness value
      // bright -> sensor value is at least 450
      // semi-bright -> sensor value is at least 220 and less than 450
      // dark -> sensor value is less than 220
  if (sensor_value >= 450) {
    // print message that it is bright outside
    Serial.println("Quite bright outside!");
    // print message that it is getting darker
  } else if (sensor_value < 450 & sensor_value >=220) {
    Serial.println("Getting kinda dark :/");
    // print message that it is too dark
  } else { // sensor_value < 220
    Serial.println("Too dark outside. Shine bright like a diamond! Time to turn the lights brighter!");
  }
}


/// SET RGB LED COLOR & BRIGHTNESS FUNCTION ///

// function to set the color and brightness of the RGB LED based on the value read in from the photoresistor
//    Parameters:
//      - int rgb_in: the analog in value read in from the photoresistor
//      - int rgb_out: the analog out value to write to the RGB LED
//      - int led_num: 0, 1, or 2 (corresponding to red, green, and blue of the RGB LED) 
void rgbSet(int rgb_in, int rgb_out, int led_num) {
  // if the analog in value is above 650, set the starting color of the RGB LED
  // else, set the brightness and color accordinglly using the given led_num and rgb_out values
  if (rgb_in > 650) {
    // set the starting color of the RGB LED, with red, green, and blue each at 10
    for (int i = 0; i < num_leds; i++) {
      analogWrite(rgb_led_pin[i], 10); 
    }
  } else { // rgb_in < 650
    // set the given color of the RGB LED to the given output value
    analogWrite(rgb_led_pin[led_num], rgb_out);
  }
}


/// LOOP FUNCTION ///

// the loop function runs over and over again forever
void loop() {  
  // read the analog in value of the photoresistor:
  int rgb_sensor_value = analogRead(rgb_sensor_pin);

  // map the rgb_sensor_value to the range of the analog out
      // read in a range 100 - 650
      // write out a range 255 - 0 (for the LED)
  int rgb_output_value = map(rgb_sensor_value, 100, 650, 255, 0);

  // constrain the rgb sensor output to be only from 0 to 255
  rgb_output_value = constrain(rgb_output_value, 0, 255);

  // read the analog in value of the potentiometer to choose a LED color
  int choose_sensor_value = analogRead(choose_color_pin);

  // print message based on the value read in from the photoresistor
  rgbPrint(rgb_sensor_value);
  
  // turn on a LED based on the analog in value read in from the potentiometer 
      // red LED -> 512 - 680
      // green LED -> 681 - 850
      // blue LED -> 851 - 1023
  if (choose_sensor_value <= 680) {
    // print message that the light is red
    Serial.println("~~ red as a rose ~~");
    // turn on red led (set value to 255)
    analogWrite(red, 255);
    // turn off green led (set value to 0)
    analogWrite(green, 0);
    // turn off blue led (set value to 0)
    analogWrite(blue, 0);
    // set red in RGB LED to the output value
    rgbSet(rgb_sensor_value, rgb_output_value, 0);
  } else if (choose_sensor_value > 680 & choose_sensor_value <= 850) {
    // print message that the light is green
    Serial.println("~~ green with envy ~~");
    // turn off red led (set value to 0)
    analogWrite(red, 0);
    // turn on green led (set value to 255)
    analogWrite(green, 255);
    // turn off blue led (set value to 0)
    analogWrite(blue, 0);
    // set green in RGB LED to the output value
    rgbSet(rgb_sensor_value, rgb_output_value, 1);
  } else { // chooseSensorValue > 850
    // print message that the light is blue
    Serial.println("~~ feeling the blues ~~");
    // turn off red led (set value to 0)
    analogWrite(red, 0);
    // turn off green led (set value to 0)
    analogWrite(green, 0);
    // turn on blue led (set value to 255)
    analogWrite(blue, 255);
    // set blue in RGB LED to the output value
    rgbSet(rgb_sensor_value, rgb_output_value, 2);
  }
}
