#include "main.h"
#include "i2c.h"

#define 	LPS25HB_DEVICE_ADDRESS_0				0xBA
#define 	LPS25HB_DEVICE_ADDRESS_1				0xBB

#define 	LPS25HB_WHO_AM_I_VALUE					0xBD
#define 	LPS25HB_WHO_AM_I_ADDRESS				0x0F

#define 	LPS25HB_ADDRESS_CONTROL_R				0x20

#define 	LPS25HB_ADDRESS_PRESS_OUT_XL			0x28
#define 	LPS25HB_ADDRESS_PRESS_OUT_L				0x29
#define 	LPS25HB_ADDRESS_PRESS_OUT_H				0x2A

#define     LPS25HB_ADDRESS_TEMP_OUT_L				0x2B
#define     LPS25HB_ADDRESS_TEMP_OUT_H				0x2C

uint8_t lps25hb_init(void);
void lps25hb_readArray(uint8_t reg, uint8_t *data, uint8_t length);
void lps25hb_writeArray(uint8_t reg, uint8_t *data, uint8_t length);

float lps25hb_get_pressure();
float lps25hb_get_temperature();
