#include "HTS221.h"
#include "i2c.h"
// Device address for the HTS221 sensor
uint8_t addressh = HTS221_DEVICE_ADDRESS;

// Function to read an array of bytes from the HTS221 sensor
void hts221_readArray(uint8_t reg, uint8_t *data, uint8_t length)
{
    I2C_ReadData(addressh, reg, data, length);
}

// Function to write an array of bytes to the HTS221 sensor
void hts221_writeArray(uint8_t reg, uint8_t *data, uint8_t length)
{
    I2C_WriteData(addressh, reg, data, length);
}

// Function to initialize the HTS221 sensor
uint8_t hts221_init(void)
{
    uint8_t status = 1;
    LL_mDelay(100);

    uint8_t who_am_i = 0;
    hts221_readArray(HTS221_WHO_AM_I_ADDRESS, &who_am_i, 1);

    if (who_am_i != HTS221_WHO_AM_I_VALUE)
    {
        status = 0;
    }

    uint8_t control_r = 0;
    hts221_readArray(HTS221_ADDRESS_CONTROL_R, &control_r, 1);
    control_r &= 0x78;
    control_r |= 0x81;
    hts221_writeArray(HTS221_ADDRESS_CONTROL_R, &control_r, 1);

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

// Function to get the temperature value
float hts221_get_temperature(void)
{
    uint8_t temperature[2];
    hts221_readArray(HTS221_ADDRESS_TEMP_OUT_L, temperature, 2);
    int16_t total_t = (temperature[1] << 8) | temperature[0];

    uint8_t cal0[2], cal1[2];
    hts221_readArray(HTS221_ADDRESS_T0_OUT_L, cal0, 2);
    hts221_readArray(HTS221_ADDRESS_T1_OUT_L, cal1, 2);

    int16_t total_cal0 = (cal0[1] << 8) | cal0[0];
    int16_t total_cal1 = (cal1[1] << 8) | cal1[0];

    uint8_t cal0_y_temp = 0, cal1_y_temp = 0;
    hts221_readArray(HTS221_ADDRESS_T0_degC_x8, &cal0_y_temp, 1);
    hts221_readArray(HTS221_ADDRESS_T1_degC_x8, &cal1_y_temp, 1);

    uint8_t temp0 = 0, temp1 = 0;
    hts221_readArray(HTS221_ADDRESS_T1T0_msb, &temp0, 1);
    temp1 = temp0 >> 2 & 0x03;
    temp0 &= 0x03;

    int16_t cal0_y = (temp0 << 8) | cal0_y_temp;
    int16_t cal1_y = (temp1 << 8) | cal1_y_temp;

    float k = (float)(cal1_y - cal0_y) / (total_cal1 - total_cal0);
    float q = (float)(cal1_y - k * total_cal1);
    float total = (float)((k * total_t + q) / 8);

    return total;
}


