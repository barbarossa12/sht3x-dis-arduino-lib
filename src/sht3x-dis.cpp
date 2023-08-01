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


#include "sht3x-dis-registers.h"
#include "sht3x-dis.h"

/**
 * @brief function to read i2c data from sht3x
 *
 * @param tx_buffer i2c data buffer to transmit
 * @param tx_buffer_size i2c data buffer size
 * @param rx_buffer i2c buffer to receive data
 * @param rx_buffer_size i2c receive buffer size
 * @return Sht3x::I2C_STATUS status of the i2c comms
 */
Sht3x::I2C_STATUS Sht3x::read_i2c_device(uint8_t *tx_buffer,
    uint8_t tx_buffer_size,
    uint8_t *rx_buffer, uint8_t rx_buffer_size) {
    Wire.begin();
    Wire.beginTransmission(this->device_address);
    for (size_t i = 0; i < tx_buffer_size; i++) {
        Wire.write(tx_buffer[i]);
    }

    uint8_t status = Wire.endTransmission();
    I2C_STATUS STATUS;

    if(status == 0) STATUS = I2C_STATUS::SUCCESS;
    else if(status == 1) STATUS = I2C_STATUS::DATA_TOO_LONG_FOR_TX_BUFFER;
    else if(status == 2) STATUS = I2C_STATUS::RECEIVED_NACK_AT_TX_ADDRESS;
    else if(status == 3) STATUS = I2C_STATUS::RECEIVED_NACK_ON_TX_DATA;
    else if(status == 4) STATUS = I2C_STATUS::OTHER_ERROR;
    else if(status == 5) STATUS = I2C_STATUS::TIMEOUT;
    else {
      Serial.println("I2C error code unknown");
    }


    Wire.requestFrom(this->device_address, rx_buffer_size);
    if (Wire.available()) {
      for (size_t i = 0; i < rx_buffer_size; i++) {
        rx_buffer[i] = Wire.read();
      }
    } else {
      STATUS = I2C_STATUS::WIRE_AVAILABLE_FALSE;
    }

    Wire.end();
    return STATUS;
}


/**
 * @brief Function to write i2c data to sht3x
 *
 * @param tx_buffer i2c data transmit buffer
 * @param tx_buffer_size i2c data buffer size
 * @return Sht3x::I2C_STATUS
 */
Sht3x::I2C_STATUS Sht3x::write_i2c_device(uint8_t *tx_buffer,
    uint8_t tx_buffer_size) {
    Wire.begin();
    Wire.beginTransmission(this->device_address);

    for (size_t i = 0; i < tx_buffer_size; i++) {
        Wire.write(tx_buffer[i]);
    }
    uint8_t status = Wire.endTransmission();
    I2C_STATUS STATUS;

    if(status == 0) STATUS = I2C_STATUS::SUCCESS;
    else if(status == 1) STATUS = I2C_STATUS::DATA_TOO_LONG_FOR_TX_BUFFER;
    else if(status == 2) STATUS = I2C_STATUS::RECEIVED_NACK_AT_TX_ADDRESS;
    else if(status == 3) STATUS = I2C_STATUS::RECEIVED_NACK_ON_TX_DATA;
    else if(status == 4) STATUS = I2C_STATUS::OTHER_ERROR;
    else if(status == 5) STATUS = I2C_STATUS::TIMEOUT;
    else {
      Serial.println("I2C error code unknown");
    }


    Wire.end();
    return STATUS;
}


/**
 * @brief Construct a new Sht 3x:: Sht 3x object
 *
 * @param device_address 7bit address of sht3x
 */
Sht3x::Sht3x(const uint8_t device_address): device_address{device_address} {
}


/**
 * @brief Perform singleshot measurement
 *
 * @param mode clock streching and repeatability selection
 */
void Sht3x::perform_single_shot_measurement(uint8_t mode) {

    I2C_STATUS status;

    if(mode == 1) status = read_i2c_device(this->single_shot_mode.MODE1, 2, this->i2c_data, 6);
    else if(mode == 2) status = read_i2c_device(this->single_shot_mode.MODE2, 2, this->i2c_data, 6);
    else if(mode == 3) status = read_i2c_device(this->single_shot_mode.MODE3, 2, this->i2c_data, 6);
    else if(mode == 4) status = read_i2c_device(this->single_shot_mode.MODE4, 2, this->i2c_data, 6);
    else if(mode == 5) status = read_i2c_device(this->single_shot_mode.MODE5, 2, this->i2c_data, 6);
    else if(mode == 6) status = read_i2c_device(this->single_shot_mode.MODE6, 2, this->i2c_data, 6);
    else {
      Serial.println("single shot measurement mode not found.");
    }


    if(status != Sht3x::I2C_STATUS::SUCCESS) {
        Serial.println("Error in i2c communications");
    }

    this->read_temperature();
    this->read_relative_humidity();

}


/**
 * @brief Convert the i2c data to floating point
 *        temperature value
 */
void Sht3x::read_temperature() {
  this->temperature_raw = (this->i2c_data[0] << 8) | this->i2c_data[1];
  this->temperature = -45 + 175 * (this->temperature_raw)/(TWO_TO_THE_POWER_16 - 1);
}


/**
 * @brief Convert the i2c data to floating point
 *        rh value
 */
void Sht3x::read_relative_humidity() {
  this->rh_raw = (this->i2c_data[3] << 8) | this->i2c_data[4];
  this->rh = 100 * this->rh_raw/(TWO_TO_THE_POWER_16 - 1);
}


/**
 * @brief  Get current temperature from sht3x
 *
 * @return float temperature value
 */
float Sht3x::get_temperature() {
    return this->temperature;
}


/**
 * @brief Get current rh value from sht3x
 *
 * @return float
 */
float Sht3x::get_rh() {
    return this->rh;
}


/**
 * @brief Send the break command to end the perodic data
 *        Acquisition.
 *        After the successful execution of this command
 *        Device returns to singleshot mode
 */
void Sht3x::send_break_command() {
    uint8_t cmds[2] = {BREAK_CMD_MSB, BREAK_CMD_LSB};
    Serial.println("Sending break command");
    I2C_STATUS status =  write_i2c_device(cmds, 2);
    if (status != I2C_STATUS::SUCCESS) {
        Serial.println("Failed to send break command");
    }
}


/**
 * @brief Perform a soft reset on the device
 *
 */
void Sht3x::soft_reset() {
    uint8_t cmds[2] = {SOFT_RESET_MSB, SOFT_RESET_LSB};
    Serial.println("Sending soft-reset command");
    I2C_STATUS status =  write_i2c_device(cmds, 2);

    if (status != I2C_STATUS::SUCCESS) {
        Serial.println("Failed to send soft-reset command");
    }
}


/**
 * @brief Fetch results of the periodic measurements
 *
 */
void Sht3x::fetch_data() {
    uint8_t cmds[2] = {FETCH_DATA_MSB, FETCH_DATA_LSB};
    read_i2c_device(cmds, 2, this->i2c_data, 6);
    this->read_temperature();
    this->read_relative_humidity();
}


/**
 * @brief Perform periodic data acquisiton based on a
 *        measurements per second (mps) and repeatability
 *        configuration
 *
 * @param mode mode combinations of mps and repeatabilties.
 */
void Sht3x::set_periodic_data_acquisition(uint8_t mode) {
    /**At least give 10ms between this and calling fetch
     * to avoid i2c timeout errors
     * This delay is added at the end of this function
    */
    I2C_STATUS status;
    if(mode == 1)  write_i2c_device(mps_modes.MODE1,  2);
    else if(mode == 2)  write_i2c_device(mps_modes.MODE2,  2);
    else if(mode == 3)  write_i2c_device(mps_modes.MODE3,  2);
    else if(mode == 4)  write_i2c_device(mps_modes.MODE4,  2);
    else if(mode == 5)  write_i2c_device(mps_modes.MODE5,  2);
    else if(mode == 6)  write_i2c_device(mps_modes.MODE6,  2);
    else if(mode == 7)  write_i2c_device(mps_modes.MODE7,  2);
    else if(mode == 8)  write_i2c_device(mps_modes.MODE8,  2);
    else if(mode == 9)  write_i2c_device(mps_modes.MODE9,  2);
    else if(mode == 10) write_i2c_device(mps_modes.MODE10, 2);
    else if(mode == 11) write_i2c_device(mps_modes.MODE11, 2);
    else if(mode == 12) write_i2c_device(mps_modes.MODE12, 2);
    else if(mode == 13) write_i2c_device(mps_modes.MODE13, 2);
    else if(mode == 14) write_i2c_device(mps_modes.MODE14, 2);
    else if(mode == 15) write_i2c_device(mps_modes.MODE15, 2);
    else {
      Serial.println("Periodic data acquisition mode not found");
    }

    if(status != Sht3x::I2C_STATUS::SUCCESS) {
        Serial.println("Error in i2c communications");
    }
    delay(10);
}


/**
 * @brief Read the status registers of the device.
 *        Parses and prints values to the serial terminal.
 *
 */
void Sht3x::read_device_status() {
    uint8_t cmds[2] = {READ_STATUS_REGISTER_MSB, READ_STATUS_REGISTER_LSB};
    Serial.println("Reading device status");

    I2C_STATUS status = read_i2c_device(cmds, 2, i2c_data_device_status,2);

    if (status != I2C_STATUS::SUCCESS) {
        Serial.println("Error reading the i2c device");
    }

    /**Transfer the i2c data to the device status register*/
    this->device_status = (i2c_data_device_status[0] << 8) | i2c_data_device_status[1];

    if (device_status & (0x1 << 15)) {
      Serial.println("Pending alerts PRESENT");
    } else {
      Serial.println("Pending alerts NONE");
    }


    if (device_status & (0x1 << 13)) {
      Serial.println("Heater ON");
      this->heater_on  = true;
    } else {
      Serial.println("Heater OFF");
      this->heater_on = false;
    }


    if (device_status & (0x1 << 11)) {
      Serial.println("RH tracking alert");
    }
    else {
      Serial.println("RH tracking alert NONE");
    }


    if (device_status & (0x1 << 10)) {
      Serial.println("Temperature tracking alert");
    } else {
      Serial.println("Temperature tracking alert NONE");
    }


    if (device_status & (0x1 << 4)) {
      Serial.println("System reset detected");
    } else {
      Serial.println("System reset NONE");
    }

    if (device_status & (0x1 << 1)) {
      Serial.println("Last command did not execute");
    } else {
      Serial.println("Last command executed");
    }


    if (device_status & (0x1 << 0)) {
      Serial.println("Checksum failed");
    } else {
      Serial.println("Checksum passed");
    }

    Serial.println("=========================================================");

}


/**
 * @brief Clears the status register of the device.
 *
 */
void Sht3x::clear_status_register() {
    Serial.println("Clearing status register");
    uint8_t cmds[2] = {CLEAR_STATUS_REGISTER_MSB, CLEAR_STATUS_REGISTER_LSB};
    I2C_STATUS status =  write_i2c_device(cmds, 2);
    if (status != I2C_STATUS::SUCCESS) {
      Serial.println("I2C write error");
    } else {
      Serial.println("Complete clearing status register");
    }
}


/**
 * @brief Enables the device heater.
 *
 */
void Sht3x::enable_heater() {
    Serial.println("Enabling the heater");
    uint8_t cmds[2] = {HEATER_EN_MSB, HEATER_EN_LSB};
    I2C_STATUS status =  write_i2c_device(cmds, 2);
    if (status != I2C_STATUS::SUCCESS) {
      Serial.println("I2C write error");
    } else {
      Serial.println("Complete enabling the heater");
    }
}


/**
 * @brief Disables the device heater.
 *
 */
void Sht3x::disable_heater() {
    Serial.println("Disable heater");
    uint8_t cmds[2] = {HEATER_DIS_MSB, HEATER_DIS_LSB};
    I2C_STATUS status =  write_i2c_device(cmds, 2);
    if (status != I2C_STATUS::SUCCESS) {
      Serial.println("I2C write error");
    } else {
      Serial.println("Complete disabling the heater");
    }
}


/**
 * @brief Puts the device in a 4Hz measurement mode.
 *        Need to call the fetch command to read the data.
 *        Delay at least 10ms to avoid getting a NACK from
 *        Sensor
 *
 */
void Sht3x::art_4_hz_measurements() {
    Serial.println("Starting 4Hz measurements");
    uint8_t cmds[2] = {ART_4HZ_MSB, ART_4HZ_LSB};
    I2C_STATUS status =  write_i2c_device(cmds, 2);
    if (status != I2C_STATUS::SUCCESS) {
      Serial.println("I2C write error");
    } else {
      Serial.println("Complete configuring device for 4Hz measurements");
    }
    delay(10);
}
