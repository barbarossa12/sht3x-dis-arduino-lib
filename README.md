# SHT3X-DIS Arduino 
Arduino library for SHT3x-DIS humidity and temperature sensor by Sensirion.

## Hardware
This code has been tested with generic SHT3x-DIS breakout board and does not support the CRC error detection and correction and the ALERT pin is not used.

This library was written and tested with an ESP32 Dev module and utilized Wire and Serial libraries.
The default device address is DEVICE_ADDRESS_A 0x44 and if you attach the ADDR pin of the sensor to VDD address changes to DEVICE_ADDRESS_B 0x45.

This device supports 7bit I2C addresses.
Schematic diagram to connect the sensor to the ESP-32 dev module or an Arduino is shown below.



## Examples
```Cpp
Sht3x(const uint8_t device_address)
```
Constructor creates the sensor object with the given device address which is either ```0x44``` or  ```0x45```.

To measure the temperature and humidity you need to call the function
```Cpp
void perform_single_shot_measurement(uint8_t mode)
```

```Mode``` value ranges from 1-6 and these enumerate the combinations of clock stretching and measurement repeatability as mentioned in the table 8 of datasheet. ```Mode``` numbers are values added to each row for ease of reference.

More information can be found on ```example/read_temperature_humidity.ino```


Enables periodic measurements from the sensor as explained in the datasheet table 9. Similar to the  perform single shot measurement as above, mode enumerates the possible valid combinations of repeatability and measurements per seconds.

```Cpp
void set_periodic_data_acquisition(uint8_t mode)
```
In this mode sensor performs periodic measurements and data is acquired through fetch command. In order to read the sensor readings, you first call this function with a valid mode number and then call void ```void fetch_data()``` and subsequently call ```float get_temperature()``` and ```float get_rh()``` methods.

However at High MPS (Measurements per second) values the sensor is prone to
self heating.
Refer to ```examples/periodic_data_acquisition.ino``` for more details

This sensor has a heater and to control the heater following methods could be used.

```Cpp
void enable_heater()
void disable_heater()
```
More information on ```examples/enable_disable_heater.ino```

```Cpp
void art_4Hz_measurements();

```
In this mode the sensor starts acquiring data at a 4Hz rate and data could be read using the fetch command similar to the periodic data acquisition.

More information on how to perform 4Hz measurements are on ```examples/fourHz_Measurement.ino```

To soft reset the sensor ```void soft_reset()``` can be used and to read the status register of the sensor ```void read_device_status()``` can be used.

More information on examples ```void soft_reset_sensor()``` can be found at ```examples/soft_reset_sensor.ino```

