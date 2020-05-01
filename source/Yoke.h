#ifndef YOKE_H_
#define YOKE_H_

#include "HX711.h"
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
};

#endif /* YOKE_H_ */