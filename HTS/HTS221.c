#include "hts221.h"
#include "i2c.h"

#define HTS221_DEVICE_ADDRESS 0x5F  // Replace with actual I2C address

// Device address for the HTS221 sensor
uint8_t address = HTS221_DEVICE_ADDRESS;

// Function to read an array of bytes from the HTS221 sensor
void hts221_readArray(uint8_t reg, uint8_t *data, uint8_t length)
{
    I2C_ReadData(address, reg, data, length);
}

// Function to write an array of bytes to the HTS221 sensor
void hts221_writeArray(uint8_t reg, uint8_t *data, uint8_t length)
{
    I2C_WriteData(address, reg, data, length);
}

// Function to initialize the HTS221 sensor
uint8_t hts221_init(void)
{
    uint8_t status = 1;
    LL_mDelay(100);

    uint8_t who_am_i = 0;
    hts221_readArray(HTS221_WHO_AM_I_ADDRES, &who_am_i, 1);

    if (who_am_i != HTS221_WHO_AM_I_VALUE)
    {
        status = 0;
    }

    uint8_t ctrl1 = 0;
    hts221_readArray(HTS221_ADDRESS_CTRL1, &ctrl1, 1);
    ctrl1 &= 0x78;
    ctrl1 |= 0x81;
    hts221_writeArray(HTS221_ADDRESS_CTRL1, &ctrl1, 1);

    return status;
}

// Function to get the humidity value
int8_t hts221_get_humidity(void)
{
    uint8_t humidity_array[2];
    hts221_readArray(HTS221_ADDRESS_HUMIDITY_L, humidity_array, 2);
    int16_t humidity = (humidity_array[1] << 8) | humidity_array[0];

    uint8_t calibration_val_x0_array[2];
    hts221_readArray(HTS221_ADDRESS_H0_T0_OUT_L, calibration_val_x0_array, 2);
    int16_t calibration_x0 = (calibration_val_x0_array[1] << 8) | calibration_val_x0_array[0];

    uint8_t calibration_val_x1_array[2];
    hts221_readArray(HTS221_ADDRESS_H1_T0_OUT_L, calibration_val_x1_array, 2);
    int16_t calibration_x1 = (calibration_val_x1_array[1] << 8) | calibration_val_x1_array[0];

    uint8_t calibration_y0 = 0;
    uint8_t calibration_y1 = 0;
    hts221_readArray(HTS221_ADDRESS_H0_rH_x2, &calibration_y0, 1);
    hts221_readArray(HTS221_ADDRESS_H1_rH_x2, &calibration_y1, 1);

    float k = (float)(calibration_y1 - calibration_y0) / (calibration_x1 - calibration_x0);
    float q = (float)(calibration_y1 - k * calibration_x1);
    int8_t total = (int8_t)((k * humidity + q) / 2);

    return total;
}



