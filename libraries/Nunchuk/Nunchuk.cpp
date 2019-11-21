/*
 * nunchuk library
 * http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuk
 * http://create.arduino.cc/projecthub/infusion/using-a-wii-nunchuk-with-arduino-597254
 * https://www.robotshop.com/media/files/PDF/inex-zx-nunchuk-datasheet.pdf
 *
 * bRAM
 */
#include <Arduino.h>
#include <Wire.h>
#include "Nunchuk.h"

// nunchuk registers
#define NCNEXT	0x00	// request next state
#define NCID	0xFA	// request id
#define NCCAL	0x20	// calibration data (read 16 bytes)

/* ---- initialize variables --- */
uint8_t NunChuk::response[FRAMELEN];
uint8_t NunChuk::id[FRAMELEN];

/* ---- constructor ---- */
NunChuk::NunChuk() {
}

/* ---- public methods ---- */
 
/*
 * do the handschake
 */
void NunChuk::begin(uint8_t address) {
	Wire.beginTransmission(address);
        Wire.write(0xF0);
        Wire.write(0x55);
        Wire.endTransmission();
        Wire.beginTransmission(address);
        Wire.write(0xFB);
        Wire.write(0x00);
        Wire.endTransmission();

	/* old handshake
        Wire.beginTransmission(address);
        Wire.write(0x40);
        Wire.write(0x00);
        Wire.endTransmission();
	*/

	// init id
	_getid(address);
}

#if 0
/*
 * disable encoding
 */
void NunChuk::noencrypt(uint8_t address) {
	Wire.beginTransmission(address);
        Wire.write(0xF0);
        Wire.write(0x55);
        Wire.endTransmission();
        Wire.beginTransmission(address);
        Wire.write(0xFB);
        Wire.write(0x00);
        Wire.endTransmission();
}
#endif

/*
 * get current state
 * response encoding:
 *	byte 0: SX[7:0]
 *	byte 1: SY[7:0]
 *	byte 2: AX[9:2]
 *	byte 3: AY[9:2]
 *	byte 4: AZ[9:2]
 *	byte 5: AZ[1:0], AY[1:0], AX[1:0], BC, BZ
 */
uint8_t NunChuk::getState(uint8_t address) {
	uint8_t n = 0;

	// read response for next byte
	n = _read(address, 0x00);

	// set parameters
	state.joy_x_axis = response[0];
	state.joy_y_axis = response[1];
	state.accel_x_axis = (response[2] << 2) | ((response[5] & 0x0c) >> 2);
	state.accel_y_axis = (response[3] << 2) | ((response[5] & 0x30) >> 4);
	state.accel_z_axis = (response[4] << 2) | ((response[5] & 0xC0) >> 6);
	/* 0 = pressed */
	state.z_button = !(response[5] & 0x01);
	state.c_button = !((response[5] & 0x02) >> 1);

	return(n);
}

/* ---- private methods ---- */

/*
 * read response
 */
uint8_t NunChuk::_read(uint8_t address, uint8_t offset) {
	uint8_t i = 0;

	// send offset
        Wire.beginTransmission(address);
        Wire.write(offset);
        Wire.endTransmission();

	// request FRAMELEN bytes
	Wire.requestFrom(address, FRAMELEN);

	// read bytes
	while (Wire.available() && i < FRAMELEN) {
		response[i++] = Wire.read();
	}
	
	/* return nr bytes */
	return(i);
}

/*
 * get the device id (nunchuk should be 0xA4200000)
 */
void NunChuk::_getid(uint8_t address) {
	_read(address, 0xFA);
	// copy response buffer to id 
	for (uint8_t i = 0; i < FRAMELEN; i++) {
		id[i] = response[i];
	}
}

/*
 * preinstantiate object
 */
NunChuk Nunchuk = NunChuk();
