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
