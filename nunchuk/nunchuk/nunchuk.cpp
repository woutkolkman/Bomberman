#include <avr/io.h>
#include <Wire.h>
#include <Nunchuk.h>
#include <Arduino.h>
#include <util/delay.h>

#define ADDRESS 0x52

int main(void) {

  // initialize Nunchuk
  init();

  Serial.begin(9600); // set baudrate
  Wire.begin(); // enable I2C communication

  Nunchuk.begin(ADDRESS); // start communication with Arduino and Nunchuk
  Serial.print("ID: "); // retrieve ID Nunchuk and display
  for (uint8_t i = 0; i < FRAMELEN; i++) {
    Serial.print(Nunchuk.id[i], HEX);
  }
  Serial.println("");

  _delay_ms(500); // wait

  while (1) {

    Nunchuk.getState(ADDRESS); // get states (defined in .h and .cpp)
    Nunchuk.printStates(); // print states of joystick and buttons

    _delay_ms(500); // wait
    
  }
  return(0);
}
