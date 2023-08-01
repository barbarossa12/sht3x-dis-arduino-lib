/*
MIT License

Copyright (c) 2023 barbarossa12

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef SHT3X_DIS_H
#define SHT3X_DIS_H
#include <Wire.h>
#include <Arduino.h>
#include "sht3x-dis-registers.h"

#define SERIAL_BAUD_RATE 115200
#define TWO_TO_THE_POWER_16 65536



class Sht3x {
    public:
        Sht3x(const uint8_t device_address);
        ~Sht3x() = default;
        void perform_single_shot_measurement(uint8_t mode);
        void send_break_command();
        float get_temperature();
        float get_rh();
        void soft_reset();
        void fetch_data();
        void set_periodic_data_acquisition(uint8_t mode);
        void read_device_status();
        void clear_status_register();
        void enable_heater();
        void disable_heater();
        void art_4_hz_measurements();
        MeasurementModesSingleShot single_shot_mode;
        MeasurementsPerSecondModes mps_modes;

    private:
        const uint8_t device_address;
        uint16_t device_status;
        uint16_t temperature_raw;
        uint16_t rh_raw;
        float temperature;
        float rh;
        bool heater_on;
        uint8_t i2c_data[6] = {0}; /*All the measurement results are 6 bytes*/
        uint8_t i2c_data_device_status[3] = {0}; /*Device status result is 3 bytes*/
        uint8_t cmd_size;
        uint8_t data_size;


        enum class I2C_STATUS {
            SUCCESS,
            DATA_TOO_LONG_FOR_TX_BUFFER,
            RECEIVED_NACK_AT_TX_ADDRESS,
            RECEIVED_NACK_ON_TX_DATA,
            OTHER_ERROR,
            TIMEOUT,
            WIRE_AVAILABLE_FALSE
        };



        I2C_STATUS read_i2c_device(uint8_t *tx_buffer, uint8_t tx_buffer_size, uint8_t *rx_buffer, uint8_t rx_buffer_size);
        I2C_STATUS write_i2c_device(uint8_t *tx_buffer, uint8_t tx_buffer_size);
        void read_temperature();
        void read_relative_humidity();

};

#endif
