#include "sht3x-dis.h"

// Setup Serial communications
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    while(!Serial){};
}


void loop() {
    // Create an instance of the sht3x sensor with Address B
    Sht3x sht3x(DEVICE_ADDRESS_B);

    while(true) {
        /* read the status register of the device*/
        sht3x.read_device_status();

        /*Perform a soft reset on the device*/
        sht3x.soft_reset();

        /*Read the device status again*/
        sht3x.read_device_status();
        delay(5000);
    }
}
