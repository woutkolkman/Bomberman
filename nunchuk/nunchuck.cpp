#include <Nunchuk.h>
#include <avr/io.h>
#include <Wire.h>
#include <util/delay.h>

#define ADDRESS 0x52 // address Nunchuk

int main(void) {

//  Serial.begin(9600);
    Wire.begin();

  while (1) {

  Nunchuk.begin(ADDRESS); // start communication between Nunchuk 1 and Arduino
  Nunchuk.getState(ADDRESS); // get states of joystick and buttons (defined in .h & .cpp file)
  Nunchuk._getid(ADDRESS); // get ID of Nunchuk 1

    if (Nunchuk._read(ADDRESS, 0x00)) { // if Nunchuk 1 is being read --> print states
      Nunchuk.printStates();
    }
    _delay_ms(500);
  }
}
