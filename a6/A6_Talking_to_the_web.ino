/* A6: Talking to the web!
 *  Jocelyn Chen
 *  Monday 2.28.2022
 *  
 *  This program is
*/

int x = A1;    
int y = A0;
int xval = 0;
int yval = 0;

// pins for red, green, and blue LEDs (red = pin3, green = pin5, blue = pin6)
const int leds_pins[] = {3, 5, 6};

// pins for the RGB LED ( red = pin9, green = pin10, blue = pin11)
const int rgb_led_pin[] = {9, 10, 11};

// number of total LEDs that a user can choose a color from (red, green, or blue)
const int num_leds = 3;

int led_value = 514;
int led_brightness = 10;


void setup() {
  Serial.begin(9600);
  
  // initialize pins for the red, green, blue, and RGB LEDs as outputs
  for (int i = 0; i < num_leds; i++) {
    // pins for red, green, and blue LEDs
    pinMode(leds_pins[i], OUTPUT);
    // pins for RGB LED
    pinMode(rgb_led_pin[i], OUTPUT);
  }  
}

void loop() {  
  xval = analogRead(x);
  yval = analogRead(y);

  if (xval < 500) {
    led_brightness--;
    if (led_brightness <= 0) {
      led_brightness = 0;
    }
  } else if (xval > 550) {
    led_brightness++;
    if (led_brightness >= 255) {
      led_brightness = 225;
    }
  }
  //delay(300);
  //Serial.println(led_value);
  if (yval < 500) {
    led_value = led_value - 10;  
    if (led_value >= 1023) {
      led_value = 1023;     
    }
  } else if (yval > 550) {
    led_value = led_value + 10;      
    if (led_value <= 0) {
      led_value = 0;     
    }      
  }

  Serial.print("led val: ");
  Serial.println(led_value);
  Serial.print("brightness: ");
  Serial.println(led_brightness);
  
  if (led_value < 350) {
    analogWrite(leds_pins[0], led_brightness);
    analogWrite(leds_pins[1], 0);
    analogWrite(leds_pins[2], 0);     
  } else if (led_value > 670) {
    analogWrite(leds_pins[0], 0);
    analogWrite(leds_pins[1], 0);
    analogWrite(leds_pins[2], led_brightness);     
  } else {
    analogWrite(leds_pins[0], 0);
    analogWrite(leds_pins[1], led_brightness);
    analogWrite(leds_pins[2], 0);     
  }

  //int y_input = map(yval, 0, 1023, 0, 255);
  //led_brightness = constrain(yval, 0, 255);
  //analogWrite(leds_pins[0], led_brightness);
  
  Serial.print("x = ");
  Serial.println(xval);
  Serial.print("y = ");
  Serial.println(yval);
  Serial.println(); 

  //xval = map(xval, 0, 1023, 0, 180);

  delay(15);
}
