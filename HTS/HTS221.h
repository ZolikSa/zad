
#include "main.h"
#include "i2c.h"

#define     HTS221_DEVICE_ADDRESS					0xBF

#define     HTS221_WHO_AM_I_VALUE					0xBC
#define     HTS221_WHO_AM_I_ADDRESS					0x0F

#define 	HTS221_ADDRESS_CONTROL_R				0x20

#define 	HTS221_ADDRESS_HUMIDITY_L				0x28
#define 	HTS221_ADDRESS_HUMIDITY_H				0x29

/*calibration points*/
#define 	HTS221_ADDRESS_H0_T0_OUT_L 				0x36
#define 	HTS221_ADDRESS_H0_T0_OUT_H 				0x37
#define 	HTS221_ADDRESS_H1_T0_OUT_L 				0x3A
#define 	HTS221_ADDRESS_H1_T0_OUT_H 				0x3B

/*calibration values*/
#define     HTS221_ADDRESS_H0_rH_x2                 0x30
#define     HTS221_ADDRESS_H1_rH_x2                 0x31

#define 	HTS221_ADDRESS_TEMP_OUT_L				0x2A
#define 	HTS221_ADDRESS_TEMP_OUT_H				0x2B

#define 	HTS221_ADDRESS_T0_OUT_L 				0x3C
#define 	HTS221_ADDRESS_T0_OUT_H 				0x3D

#define     HTS221_ADDRESS_T1_OUT_L                 0x3E
#define     HTS221_ADDRESS_T1_OUT_H                 0x3F

#define 	HTS221_ADDRESS_T0_degC_x8  				0x32
#define 	HTS221_ADDRESS_T1_degC_x8               0x33
#define 	HTS221_ADDRESS_T1T0_msb                 0x35

uint8_t hts221_init(void);
void hts221_readArray(uint8_t reg, uint8_t *data, uint8_t length);
void hts221_writeArray(uint8_t reg, uint8_t *data, uint8_t length);

float hts221_get_temperature();
int8_t hts221_get_humidity();
