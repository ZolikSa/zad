#include "LPS25HB.h"
#include "i2c.h"

// Device address for the LPS22HB sensor
uint8_t address = LPS25HB_DEVICE_ADDRESS_0;

// Function to read an array of bytes from the LPS22HB sensor
void lps25hb_readArray(uint8_t reg, uint8_t *data, uint8_t length)
{
    I2C_ReadData(address, reg, data, length);
}

// Function to write an array of bytes to the LPS22HB sensor
void lps25hb_writeArray(uint8_t reg, uint8_t *data, uint8_t length)
{
    I2C_WriteData(address, reg, data, length);
}

// Function to initialize the LPS22HB sensor
uint8_t lps25hb_init(void)
{
    uint8_t status = 1;

    LL_mDelay(100);

    uint8_t who_am_i = 0;
    lps25hb_readArray(LPS25HB_WHO_AM_I_ADDRESS, &who_am_i, 1);

    if (who_am_i != LPS25HB_WHO_AM_I_VALUE)
    {
        address = LPS25HB_DEVICE_ADDRESS_1;
        lps25hb_readArray(LPS25HB_WHO_AM_I_ADDRESS, &who_am_i, 1);

        if (who_am_i != LPS25HB_WHO_AM_I_VALUE)
        {
            status = 0;  // Sensor identification failed
        }
    }

    uint8_t control = 0;
    lps25hb_readArray(LPS25HB_ADDRESS_CONTROL_R, &control, 1);
    control &= ~0xFF;
    control |= 0x18;
    lps25hb_writeArray(LPS25HB_ADDRESS_CONTROL_R, &control, 1);

    return status;
}

// Function to get the pressure value
float lps25hb_get_pressure(void)
{
    uint8_t pressure[3];
    lps25hb_readArray(LPS25HB_ADDRESS_PRESS_OUT_XL, pressure, 3);

    int32_t temp = ((int32_t)pressure[2] << 16) | ((int32_t)pressure[1] << 8) | pressure[0];
    float total_pressure = (float)temp / 4096;

    return total_pressure;
}

// Function to get the temperature value
float lps25hb_get_temperature(void)
{
    uint8_t temperature[2];
    lps25hb_readArray(LPS25HB_ADDRESS_TEMP_OUT_L, temperature, 2);

    int16_t total_t = ((int16_t)temperature[1] << 8) | temperature[0];
    float temp = (float)total_t / 100;

    return temp;
}
