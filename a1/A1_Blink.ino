/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
// name the pins with corresponding LED colors
int red = 13;     // set red to 13
int yellow = 7;   // set yellow to 7
int green = 1;    // set green to 1


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin for each LED as an output.
  pinMode(red, OUTPUT);      // RED LED
  pinMode(yellow, OUTPUT);   // YELLOW LED
  pinMode(green, OUTPUT);    // GREEN LED
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(green, HIGH);    // turn the GREEN LED on (HIGH is the voltage level)
  digitalWrite(red, LOW);       // turn the RED LED off by making the voltage LOW
  digitalWrite(yellow, LOW);    // turn the YELLOW LED off by making the voltage LOW
  delay(1000);                      // wait for one second
  digitalWrite(green, LOW);     // turn the GREEN LED off by making the voltage LOW
  digitalWrite(yellow, HIGH);   // turn the YELLOW LED on (HIGH is the voltage level)
  delay(250);                       // wait for a quarter of a second
  digitalWrite(yellow, LOW);    // turn the YELLOW LED off by making the voltage LOW
  digitalWrite(red, HIGH);      // turn the RED LED on (HIGH is the voltage level)
  delay(500);                       // wait for half a second
}
