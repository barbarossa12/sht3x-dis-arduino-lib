#include "sht3x-dis.h"

void print_data(float temperature, float rh); /*Helper function to print the readings*/


// Setup the serial communications
void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    while(!Serial){};
}


void loop() {
    // create an instance of the sht3x sensor with the address B
    // ADDR pin connted to VDD
    Sht3x sht3x(DEVICE_ADDRESS_B);

    // Enable and disable the heater
    // Print the status register to see the heater status
    sht3x.enable_heater();
    sht3x.read_device_status();
    sht3x.disable_heater();
    sht3x.read_device_status();

    delay(5000);

}


void print_data(float temperature, float rh) {
    Serial.println("===================================================");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("C");
    Serial.print("rh:");
    Serial.print(rh);
    Serial.println("%");
    Serial.println("===================================================");
}
