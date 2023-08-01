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

    float temperature = 0.0;
    float rh = 0.0;


    while(true) {
        // cycle through all 15 measurement modes
        // high mps values can cause the sensor to self heat
        for (size_t i = 1; i < 16; i++) {
            Serial.print("Periodic Acquisition:");
            Serial.println(i);
            sht3x.set_periodic_data_acquisition(i);
            sht3x.fetch_data();
            temperature = sht3x.get_temperature();
            rh = sht3x.get_rh();
            print_data(temperature, rh);
            delay(5000);
        }

        // send the break command to exit the periodic data acquisition
        sht3x.send_break_command();

        // device now in single shot measurement mode 
        temperature = sht3x.get_temperature();
        rh = sht3x.get_rh();                     
        print_data(temperature, rh);
    }

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
