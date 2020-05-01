#ifndef HX711_H_
#define HX711_H_

#include <mbed.h>

class HX711
{
public:
    HX711(PinName clockPin, PinName dataPin, EventQueue& eventQueue, uint8_t totalPulses = 25);
    uint32_t getData(void) const { return dataRegister; }
private:
    void read(void);            // reads data from HX711 chip
    DigitalOut clock;           // clock pin
    InterruptIn data;           // interrupt and data pin
    EventQueue& eventQueue;     // event queue for HX711 data readouts
    uint8_t totalPulses;        // number of pulses to generate <25-27>
    uint32_t dataRegister;      // data read from the chip
};

#endif /* HX711_H_ */