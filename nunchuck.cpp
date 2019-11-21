#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <Nunchuk.h>
#include <Arduino.h>

// function prototypes
void getID(uint8_t address);
uint8_t read(uint8_t address, uint8_t offset);
void begin(uint8_t address); 
uint8_t joy_x_axis_state();
uint8_t joy_y_axis_state();
uint8_t accel_x_axis_state();
uint8_t accel_y_axis_state(); 
uint8_t accel_z_axis_state();
uint8_t z_button_state();
uint8_t c_button_state();
uint8_t getState(uint8_t address);

#define ADDRESS 0x52 // address white nunchuk
#define FRAMELENGTH 6

// variables
uint8_t response[FRAMELENGTH];
uint8_t ID[FRAMELENGTH];

void begin(uint8_t address) {
     
   Wire.beginTransmission(address);
   Wire.write(0x40);
   Wire.write(0x00);
   Wire.endTransmission();

   // get ID nunchuk(s)
   getID(address);
}

uint8_t read(uint8_t address, uint8_t offset) {
  
    uint8_t i = 0;

    // send offset
    Wire.beginTransmission(address); // nunchuk address
    Wire.write(offset);
    Wire.endTransmission();

    // request FRAMELENGTH bytes
    Wire.requestFrom(address, FRAMELENGTH);

    // read bytes
    while (Wire.available() && i < FRAMELENGTH) {
         response[i++] = Wire.read();
  }
   return (i); // return bytes
} 

void getID(uint8_t address) {

   read(address, 0xFA); // read address and offset 
   // copy response buffer to ID
   for (uint8_t i = 0; i < FRAMELENGTH; i++) {
      ID[i] = response[i];
  }
}

uint8_t joy_x_axis_state() {
    return response[0];
}

uint8_t joy_y_axis_state() {
    return response[1];
}

uint8_t accel_x_axis_state() {
    return (response[2] << 2) | ((response[5] & 0x0C) >> 2);
}

uint8_t accel_y_axis_state() {
    return (response[3] << 2) | ((response[5] & 0x30) >> 4);
}

uint8_t accel_z_axis_state() {
    return (response[4] << 2) | ((response[5] & 0xC0) >> 6);
} 

uint8_t z_button_state() {
    return !(response[5] & 0x01);
}

uint8_t c_button_state() {
    return !((response[5] & 0x02) >> 1);
}  

uint8_t getState(uint8_t address) {
   
   uint8_t b = 0;

   // read response for next byte
   b = read(address, 0x00);
   
   // states
   joy_x_axis_state();
   joy_y_axis_state();
   accel_x_axis_state();
   accel_y_axis_state(); 
   accel_z_axis_state();
   z_button_state();
   c_button_state();

   return (b); // return byte
}

int main() {

   Wire.begin(); // enable communication nunchuk and arduino
   Serial.begin(9600); 

   while (1) {
    
   // read and display statuses 
   

  }
  return 0;
}