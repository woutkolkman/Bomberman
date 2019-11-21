/*
 * nunchuk library
 */
#ifndef NUNCHUK_H_
#define NUNCHUK_H_

#include <inttypes.h>

// response length of nuncheck
#define FRAMELEN 6

struct ncState {
	uint8_t joy_x_axis;
	uint8_t joy_y_axis;
	uint16_t accel_x_axis;
	uint16_t accel_y_axis;
	uint16_t accel_z_axis;
	uint8_t	z_button;
	uint8_t	c_button;
};

class NunChuk {
	public:
		NunChuk();
		void begin(uint8_t address);
		static uint8_t id[];
		uint8_t getState(uint8_t address);
		ncState state;

	private:
		static uint8_t response[];
		uint8_t _read(uint8_t address, uint8_t offset);
		void _getid(uint8_t address);
};

// Nunchuk globaly declared in Nunchuk.cpp
extern NunChuk Nunchuk;

#endif
