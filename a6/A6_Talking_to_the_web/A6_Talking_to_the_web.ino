/* A6: Talking to the web!
 *  Jocelyn Chen
 *  Monday 2.28.2022
 *  
 *  Program: pick a color for Rudolph's nose using the joystick! Plus added fun to blink and fade LEDs for party time!
 *  
 *  This program runs using a joystick, RGB LED, Red LED, Green LED, and Blue LED. This program creates a webpage with
 *  p5.js that interacts with the Arduino. 
*/

int x = A1;                              // pin for Xvalue of joystick
int y = A0;                              // pin for Yvalue of joystick
int xval = 0;                            // starting value for xvalue of joystick
int yval = 0;                            // starting value for yvalue of joystick
int led_brightness = 10;                 // starting value for LED brightness
const int leds_pins[] = {3, 5, 6};       // pins for red, green, and blue LEDs (red = pin3, green = pin5, blue = pin6)
const int rgb_led_pin[] = {9, 10, 11};   // pins for the RGB LED ( red = pin9, green = pin10, blue = pin11)
const int num_leds = 3;                  // number of total LEDs that a user can choose a color from (red, green, or blue)

/// SETUP FUNCTION ///
// the setup function runs once when you press reset or power the 
void setup() {
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600); 
  // set the timeout for parseInt
  Serial.setTimeout(10);  
  
  // initialize pins for the red, green, blue, and RGB LEDs as outputs
  for (int i = 0; i < num_leds; i++) {
    // pins for red, green, and blue LEDs
    pinMode(leds_pins[i], OUTPUT);
    // pins for RGB LED
    pinMode(rgb_led_pin[i], OUTPUT);
  }
}

/// LOOP FUNCTION ///
// the loop function runs over and over again forever
void loop() {  
  /// ARDUINO TO p5 ///
  // read in the xvalue of the joystick
  xval = analogRead(x);
  // read in the yvalue of the joystick
  yval = analogRead(y);

  // print out the values that were read in to the console in the form [xval, yval]
  Serial.print("[");
  Serial.print(xval);
  Serial.print(",");
  Serial.print(yval);
  Serial.println("]");

  // wait 100 ms
  delay(100);

  /// WEB to ARDUINO ///
  // if there's serial data 
  if (Serial.available() > 0) {
    // read the serial data
    int inByte = Serial.read();
    // send the serial data back out as raw binary data
    Serial.write(inByte);

    // blink the red, green, and blue LEDs 10 times in a circuit if 'b' is pressed
    if (inByte == 98) { // b pressed
      // for 10 times
      for (int i = 0; i < 10; i++) {
        // for each LED
        for (int j = 0; j < num_leds; j++) {
          // turn the LED on at brightness value of 10
          analogWrite(leds_pins[j], led_brightness);
          // wait 200 ms
          delay(200);
          // turn the LED off
          analogWrite(leds_pins[j], 0);
          // wait 200 ms
          delay(200);
        }
      }   
      // turn all LEDs (red, blue, green, and RGB) off if space is pressed
    } else if (inByte == 32) { // space pressed
      // for each LED
      for (int i = 0; i < num_leds; i++) {
        // turn off given RGB LED color
        analogWrite(rgb_led_pin[i], 0);
        // turn off given red, green, or blue LED
        analogWrite(leds_pins[i], 0);
      }
      // fade all LEDs 5 times if 'p' is pressed
    } else if (inByte == 112) { // p pressed
      // for 5 times
      for (int i = 0; i < 5; i++) {
        // fade out from min to max in increments of 5 points (with max being 100 and min being 0)
        for (int fadeValue = 0 ; fadeValue <= 100; fadeValue += 5) {
          // for each LED
          for (int j = 0; j < num_leds; j++) {
            // set the given RGB LED color to the given fade value
            analogWrite(rgb_led_pin[j], fadeValue);
            // set the given red, green, or blue LED to given fade value
            analogWrite(leds_pins[j], fadeValue);
            // wait 20 ms
            delay(20);
          }
        }

        // fade out from max to min in increments of 5 points (with max being 100 and min being 0)
        for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 5) {
          // for each LED
          for (int j = 0; j < num_leds; j++) {
            // set the given RGB LED color to given fade value
            analogWrite(rgb_led_pin[j], fadeValue);
            // set the given red, green, or blue LED to given fade value
            analogWrite(leds_pins[j], fadeValue);
            // wait 20 ms
            delay(20);
          }
        }
      }
    }
  }  
}
