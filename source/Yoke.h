#ifndef YOKE_H_
#define YOKE_H_

#include "HX711.h"
#include "Filter.h"
#include "Servo.h"
#include <mbed.h>

class Yoke
{
public:
    Yoke(events::EventQueue& eventQueue);
private:
    void handler(void);
    events::EventQueue& eventQueue;     // event queue of the main thread
    DigitalOut systemLed;               // yoke heartbeat LED
    HX711 pitchTensometer;              // pitch force tensometer object
    HX711 rollTensometer;               // roll force tensometer object
    FilterSMA pitchForceFilter;         // filter of the pitch force values
    uint32_t counter{0};                // counter of handler execution
    Timer handlerTimer;                 // measures time between handler calls
    float yokePitch{0.0f};              // yoke pitch deflection from refference position
    DigitalIn flapsUpSwitch;
    DigitalIn flapsDownSwitch;
    DigitalIn gearUpSwitch;
    DigitalIn gearDownSwitch;
    DigitalIn redPushbutton;
    DigitalIn greenPushbutton;
    DigitalIn leftToggle;
    DigitalIn rightToggle;
    AnalogIn throttlePotentiometer;
    AnalogIn propellerPotentiometer;
    AnalogIn mixturePotentiometer;
    AnalogIn joystickGainPotentiometer;
    Servo pitchServo;
};

#endif /* YOKE_H_ */