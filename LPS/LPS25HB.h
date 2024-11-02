#include "main.h"
#include "i2c.h"

#define 	LPS22HB_DEVICE_ADDRESS_0				0xB9
#define 	LPS22HB_DEVICE_ADDRESS_1				0xBB

#define 	LPS22HB_WHO_AM_I_VALUE					0xB1
#define 	LPS22HB_WHO_AM_I_ADDRESS				0x0F

#define 	LPS22HB_ADDRESS_CONTROL_R				0x10

#define 	LPS22HB_ADDRESS_PRESS_OUT_XL			0x28
#define 	LPS22HB_ADDRESS_PRESS_OUT_L				0x29
#define 	LPS22HB_ADDRESS_PRESS_OUT_H				0x2A

#define     LPS22HB_ADDRESS_TEMP_OUT_L				0x2B
#define     LPS22HB_ADDRESS_TEMP_OUT_H				0x2C

uint8_t lps22hb_init(void);
void lps22hb_readArray(uint8_t reg, uint8_t *data, uint8_t length);
void lps22hb_writeArray(uint8_t reg, uint8_t *data, uint8_t length);

float lps22hb_get_pressure();
float lps22hb_get_temperature();
