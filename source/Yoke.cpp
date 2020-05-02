#include "Yoke.h"

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    tensometerThread(osPriorityBelowNormal),
    pitchTensometer(PD_1, PD_0, eventQueue),
    pitchServo(PC_6, 1e-3, 2e-3, 0.5f),
    propellerPotentiometer(PC_3)
{
    printf("Yoke object created\r\n");
    // tensometer queue will be dispatched in another thread
    tensometerThread.start(callback(&tensometerQueue, &EventQueue::dispatch_forever));

    handlerTimer.start();

    //Yoke handler is executed every 10 ms
    eventQueue.call_every(10, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically every 10 ms
*/
void Yoke::handler(void)
{
    counter++;
    float dt = handlerTimer.read();
    handlerTimer.reset();

    // LED heartbeat
    systemLed = ((counter & 0x68) == 0x68);

    float pot = propellerPotentiometer.read();
    float force = -1.0f * pitchTensometer.getValue() * pot;
    float feedback = 0.03f * yokePitch;
    yokePitch += force - feedback;
    pitchServo.setValue(0.5f + yokePitch);

    if(counter % 50 == 0)
    {
        printf("pot=%f  fo=%f  fe=%f  pi=%f\r\n", pot, force, feedback, yokePitch);
    }
}