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

    // set single shot measurement mode 1
    sht3x.perform_single_shot_measurement(1);



    // vairables to hold the temperatture and the rh values
    float temperature = 0.0;
    float rh = 0.0;


    while(true) {
        // set single shot measurement mode 1
        sht3x.perform_single_shot_measurement(1);
        temperature = sht3x.get_temperature();
        rh = sht3x.get_rh();
        print_data(temperature, rh);
        delay(5000);
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
