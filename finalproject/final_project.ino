/* HCDE 439 Final Project!
 *  Jocelyn Chen
 *  Thursday 3.10.2022
 *  
 *  Program: Make LED strip light up along staircase if motion is detected (when it is dark).
 *  
*/

const int led_pin = 9;            // pin for red LED (used to indicate that motion sensor is active)
const int pir_pin = 5;            // pin for PIR motion sensor module output pin (read HIGH or LOW)
const int leds_pin = 3;           // pin for LED Strip
const int pr_pin = A0;            // pin for photoresistor sensor (detect if it is dark)
int pir_value = 0;                // status of PIR motion sensor
int pr_value = 0;                 // status of photoresistor

/// SETUP FUNCTION ///
// the setup function runs once when you press reset or power the arduino
void setup() {
  // set pin for red LED as OUTPUT
  pinMode(led_pin, OUTPUT);
  // set pin for LED strip as OUTPUT
  pinMode(leds_pin, OUTPUT);
  // set pin for PIR motion sensor as INPUT
  pinMode(pir_pin, INPUT);
  // intialize LED strip as off (analog value to 0)
  analogWrite(leds_pin, 0);
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
}

/// COUNT THIRTY FUNCTION ///
// Blinks red LED on and off 30 times (as a time indicator for showing thirty seconds have passed)
void countThirty() {
  // integer for counting the number of seconds
  int num_sec = 0;
  // loop 15 times
  for (int i = 0; i < 15; i++) {
    // turn red LED off (set analog value to 0)
    analogWrite(led_pin, 0);
    // wait 1 second
    delay(1000);
    // increment num_sec variable up by one
    num_sec++;
    // for debugging: print out current number of seconds to serial monitor
    Serial.print(num_sec);
    Serial.println(" sec");
    // turn red LED on (set analog value to 100)
    analogWrite(led_pin, 100);
    // wait 1 second
    delay(1000);
    // increment num_sec variable up by one
    num_sec++;
    // for debugging: print out current number of seconds to serial monitor
    Serial.print(num_sec);
    Serial.println(" sec");
  }
}

/// LOOP FUNCTION ///
// the loop function runs over and over again forever
void loop(){ 
  // read the analog in value of the photoresistor
  pr_value = analogRead(pr_pin);

  // for debugging: print out photoresistor values to the serial monitor
  Serial.print("photoresistor value in: ");
  Serial.println(pr_value); 

  // if analog in from photoresistor is less than 100 (detects that it is dark)
  if (pr_value < 100) {
    // turn red LED on (set analog value to 100)
    analogWrite(led_pin, 100);
    // read the digital in value of the PIR motion sensor (detect if there is motion; 1 if motion, 0 if no motion)
    pir_value = digitalRead(pir_pin); 
    // if motion is detected
    if (pir_value == HIGH) {
      // turn LED strip on (set analog value to 100);
      analogWrite(leds_pin, 100);
      // print out PIR motion sensor value to serial monitor
      Serial.print(pir_value);
      // print out motion detected message to serial monitor
      Serial.println("Motion detected; turn on led!!!");
      // wait 30 seconds
      countThirty();
    } else { // no motion detected
      // turn LED strip off if there is no motion
      analogWrite(leds_pin, 0);
    }
  } else { // photoresistor value > 100 (not dark)
    // turn red LED off (set analog value to 0)
    analogWrite(led_pin, 0);
  }
} 
