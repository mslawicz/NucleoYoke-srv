#ifndef HX711_H_
#define HX711_H_

#include <mbed.h>

class HX711
{
public:
    HX711(PinName clockPin, PinName dataPin, EventQueue& eventQueue, uint8_t totalPulses = 25);
private:
    void read(void);
    DigitalOut clock;
    InterruptIn data;
    EventQueue& eventQueue;
    uint8_t totalPulses;
};

#endif /* HX711_H_ */