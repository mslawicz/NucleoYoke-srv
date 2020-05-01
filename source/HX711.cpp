#include "HX711.h"

/*
create HX711 object and set interrupt
*/
HX711::HX711(PinName clockPin, PinName dataPin, EventQueue& eventQueue, uint8_t totalPulses) :
    clock(clockPin, 0),
    data(dataPin, PullUp),
    eventQueue(eventQueue),
    totalPulses(totalPulses)
{

    data.fall(eventQueue.event(callback(this, &HX711::read)));
}

/*
read data from the HX711 chip
it should be called in a separate low priority thread
*/
void HX711::read(void)
{
    // disable data signal interrupts until the data is read
    data.fall(nullptr);

    uint32_t dataBuffer = 0;
    // generate clock pulses and read data bits
    for(uint8_t pulse = 0; pulse < totalPulses; pulse++)
    {
        // the pulse mustn't be interrupted (maximum length 50 us)
        CriticalSectionLock lock;
        clock = 1;
        if(pulse < 24)      // read 24 bits of data
        {
            dataBuffer = (dataBuffer << 1) | data.read();
        }
        clock = 0;
    }

    dataRegister = dataBuffer;
    // enable interrupt
    data.fall(eventQueue.event(callback(this, &HX711::read)));
}