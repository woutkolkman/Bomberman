#include <avr/io.h>
#include <Wire.h>
#include <Nunchuk.h>
#include <Arduino.h>
#include <util/delay.h>

#define ADDRESS 0x52
#define RESETBS PORTB &= ~(1 << PORT5);
#define BS 	PORTB |= (1 << PINB5);

int main(void) { 
  // input & output
  DDRB |= (1 << DDB5) | (1 << DDB4) | (1 << DDB3) | (1 << DDB2) | (1 << DDB1); // set D13..D9 as output
  
  // initialize Nunchuk
  init();

  Serial.begin(9600); // set baudrate
  Wire.begin(); // enable I2C communication

  Nunchuk.begin(ADDRESS); // start communication with Arduino and Nunchuk
  
  Serial.print("ID: 0x"); // retrieve ID Nunchuk and display
  for (uint8_t i = 0; i < FRAMELEN; i++) {
    Serial.print(Nunchuk.id[i], HEX);
  }
  Serial.println("");

  _delay_ms(500); // wait

  while (1) {

    Nunchuk.getState(ADDRESS); // get states of joystick and buttons (defined in .h and .cpp)

  /* X-axis: left: 0 - middle: 127 - right: 255
     Y-axis: up: 255 - middle: 128 - down: 0
     Z-button: released: 0 - pressed: 1
     C-button: released: 0 - pressed: 1 */

    // check how LEDs (joystick and buttons) react to Nunchuk values
    // X-axis
    if (Nunchuk.X_Axis() == 255) { // right
      PORTB &= ~(1 << PINB1) & ~(1 << PINB3) & ~(1 << PINB4);
      PORTB |= (1 << PINB2);
    } else if (Nunchuk.X_Axis() == 0) { // up
      PORTB |= (1 << PINB3);
      PORTB &= ~(1 << PINB1) & ~(1 << PINB2) & ~(1 << PINB4);
    } else if (Nunchuk.Y_Axis() == 255) { // up
      PORTB |= (1 << PINB4);
      PORTB &= ~(1 << PINB1) & ~(1 << PINB2) & ~(1 << PINB3);
    } else if (Nunchuk.Y_Axis() == 0) { // down 
      PORTB |= (1 << PINB1);
      PORTB &= ~(1 << PINB4) & ~(1 << PINB2) & ~(1 << PINB3);
    }
  }
  return(0);
}