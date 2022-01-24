const int fade_pin = 7;                 // pin used for "fade" button to fade the RGB LED
const int choose_color_pin = 1;         // pin used for "choose color" button to choose a color (red, green, or blue)

const int leds_pins[] = {3, 4, 5};      // pins for the red, green, green and blue LEDs
const int rgb_led_pin[] = {9, 10, 11};  // pins for the RGB LED
const int num_leds = 3;                 // number of total leds that a user can choose a color from (red, green, or blue)

int num_button_press = 0;               // the number of times the choose color button is pressed by the user 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins for the LEDS as an output
  for(int i = 0; i < num_leds; i++) {
    // pins for the red, green, and blue LEDs
    pinMode(leds_pins[i], OUTPUT);
    // pins for the RGB LED
    pinMode(rgb_led_pin[i], OUTPUT);
  }

  // initialize pins for the two buttons (fade button and choose color button) as an input
  pinMode(fade_pin, INPUT);
  pinMode(choose_color_pin, INPUT);
}

// the loop function runs over and over again forever
void loop() {  
  // USER CHOOSES A LED COLOR //

  // loop until the fade button is pressed
  while (digitalRead(fade_pin) == LOW) {
    // if choose color button is pressed
    if (digitalRead(choose_color_pin) == HIGH) {
      // increment number of times the button is pressed
      num_button_press++;
      // if number of presses reaches past the number of leds (3), restart at 0
          // this ensures that the value of num_button_press is either: 0, 1, or 2           
      num_button_press %= num_leds;
      // wait for 300ms
      delay(300);
    }

    // update the LEDs based on how many times the user has pressed the choose color button.
        // button pressed once -> green LED
        // button pressed twice -> blue LED
        // button pressed three times -> red LED
    for (int i = 0; i < num_leds; i++) {
      digitalWrite(leds_pins[i], num_button_press == i);
    }

    // set the starting color of the RGB LED
    analogWrite(rgb_led_pin[0], 10); // red color
    analogWrite(rgb_led_pin[1], 10); // green color
    analogWrite(rgb_led_pin[2], 10); // blue color
  }

  // FADE THE RGB LED //

  // if fade button is pressed
  if (digitalRead(fade_pin) == HIGH) {
    // fade the RGB LED from 0 to 255 to the corresponding color based on how many times the 
    // user pressed the choose color button 
    for(int i = 0; i < 256; i++) {
      analogWrite(rgb_led_pin[num_button_press], i);
      // wait 20ms
      delay(20);
    } 
    // wait 50ms
    delay(50);
  }
}
