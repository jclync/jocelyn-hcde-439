/* A5: High(er) Voltage and Transistors
 *  Jocelyn Chen
 *  Monday 2.21.2022
 *  
 *  This program is a pick-all-the-worms-without-picking-the-infected-worm game (inspired by Operation and Let's Go Fishin games) 
 *  This program includes a capacitive sensor, RGB LED, N-MOSFET Transistor, and LED strip.
 *  Some code in this program references Arduino example codes (fading the LED uses the Arduino Fade Example Code).
*/

// include library for capacitive sensor
#include <CapacitiveSensor.h>

// capacitive sensor with 1 megaohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);

const int nt_pin = 10;         // pin for n-mostfet transistor
const int buzzer = 7;          // pin for passive buzzer
const int red_pin = 5;         // pin for red color in RGB LED
const int green_pin = 6;       // pin for green color in RGB LED
const int blue_pin = 9;        // pin for blue color in RGB LED

/// SETUP FUNCTION ///
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);          // Initialize serial communication at 9600 bits per second:
  pinMode(nt_pin, OUTPUT);     // Set pin for N-MOSFET transistor as OUTPUT
  analogWrite(nt_pin, 0);      // Set LED strip initial state to off (0)
  pinMode(buzzer, OUTPUT);     // Set pin for buzzer set as OUTPUT
  pinMode(red_pin, OUTPUT);    // Set pin for red color in RGB LED as OUTPUT
  pinMode(green_pin, OUTPUT);  // Set pin for green color in RGB LED as OUTPUT
  pinMode(blue_pin, OUTPUT);   // Set pin for blue color in RGB LED as OUTPUT
}

/// ALARM FUNCTION ///
// the alarm function sounds the buzzer and flashes the LED strip and RGB LED (red color) using fade
void alarm() {  
  // fade out from max to min in increments of 3 points (with max being 100 and min being 0)
  for (int fadeValue = 100 ; fadeValue >= 0; fadeValue -= 3) {
    // map the RGB LED fade value to the range of frequency for the buzzer to calibrate
    //    - read in a range 0 to 100 (fade value for the LED)
    //    - write out a range 900 to 1000 (for buzzer frequency)  
    int frequency = map(fadeValue, 0, 100, 900, 1000); 
    // set buzzer with the mapped frequency value
    tone(buzzer, frequency);
    // set red color for RGB LED with the fade value
    analogWrite(red_pin, fadeValue);
    // sets LED strip with fade value
    analogWrite(nt_pin, fadeValue);
    // wait 20 ms
    delay(20);
  }
      
  // fade in from min to max in increments of 3 points (with max being 100 and min being 0)
  for (int fadeValue = 0; fadeValue <= 100; fadeValue += 3) {
    // map the RGB LED fade value to the range of frequency for the buzzer to calibrate
    //    - read in a range 0 to 100 (fade value for the LED)
    //    - write out a range 900 to 1000 (for buzzer frequency)    
    int frequency = map(fadeValue, 0, 100, 900, 1000); 
    // set buzzer with the mapped frequency value
    tone(buzzer, frequency);
    // set red color for RGB LED with the fade value
    analogWrite(red_pin, fadeValue);
    // sets LED strip with fade value
    analogWrite(nt_pin, fadeValue);
    // wait 20 ms
    delay(20);
  }
}

/// GET READING FUNCTION ///
// function to read in the capacitive sensor value as a parameter and either:
//    - do nothing if a normal worm was picked (reading < 1600)
//    - sound the alarm and fade LEDs if the infected worm was picked (reading > 1600) 
// 1600 was chosen as the capacitive sensor read in values from around 0-1800, so I used 1600 as the threshold value
void getReading(int led_in) {
  // if the capacitive sensor reading is less than 1600
  if (led_in < 1600) {
    // wait 100 ms
    delay(100);
    // Set LED strip to off (0)
    analogWrite(nt_pin, 0);
    // Set red color in RGB LED to 20
    analogWrite(red_pin, 20);
    // Set green color in rgb LED to 20
    analogWrite(green_pin, 20); 
    // Set blue color in rgb LED to 20
    analogWrite(blue_pin, 20); 
    // Stop buzzer sound
    noTone(buzzer);
  } else { // led_in >= 1600 (capacitive sensor reading is greater than equal to 1600)
    for (int i = 0; i < 5; i++) {
      // Set green color in rgb LED to 0
      analogWrite(green_pin, 0);
      // Set blue color in rgb LED to 0
      analogWrite(blue_pin, 0);
      // sound the buzzer and fade the LED strip and red color in RGB led
      alarm();
    }
  }
}

/// LOOP FUNCTION ///
// the loop function runs over and over again forever
void loop() {
  // set sensor resolution to 30
  long total1 =  cs_4_2.capacitiveSensor(30);
  // wait 100 ms (delay) to limit data to serial port
  delay(100);
  // get capacitive sensor reading and either:
  //    - do nothing if a normal worm was picked (reading < 1600)
  //    - sound the alarm if the infected worm was picked (reading >= 1600)
  getReading(total1);
}
