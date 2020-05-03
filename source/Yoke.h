#ifndef YOKE_H_
#define YOKE_H_

#include "HX711.h"
#include "Filter.h"
#include <mbed.h>

class Yoke
{
public:
    Yoke(events::EventQueue& eventQueue);
private:
    void handler(void);
    events::EventQueue& eventQueue;     // event queue of the main thread
    DigitalOut systemLed;               // yoke heartbeat LED
    EventQueue tensometerQueue;         // tensometer event queue
    Thread tensometerThread;            // low priority thread for readout tensometer data
    HX711 pitchTensometer;              // pitch force tensometer object
    FilterSMA pitchForceFilter;         // filter of the pitch force values
    uint32_t counter{0};                // counter of handler execution
    AnalogIn propellerPotentiometer;    // propeller potentiometer object 
    Timer handlerTimer;                 // measures time between handler calls
    float yokePitch{0.0f};              // yoke pitch deflection from refference position
};

#endif /* YOKE_H_ */