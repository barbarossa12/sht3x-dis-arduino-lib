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
        Serial.println("Device in 4Hz Data acquisition mode");
        sht3x.art_4_hz_measurements();
        for (size_t i = 0; i < 5; i++) {
            sht3x.fetch_data();
            temperature = sht3x.get_temperature();
            rh = sht3x.get_rh();
            print_data(temperature, rh);
            delay(5000);
        }
        
        Serial.println("Sending break command and putting device in single shot mode");
        sht3x.send_break_command();
        Serial.println("Device now in single shot mode");
        delay(1000);

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
