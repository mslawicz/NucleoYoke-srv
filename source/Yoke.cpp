#include "Yoke.h"

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    tensometerThread(osPriorityBelowNormal),
    pitchTensometer(PD_1, PD_0, eventQueue),
    pitchServo(PC_6, 1e-3, 2e-3, 0.5f)
{
    printf("Yoke object created\r\n");
    // tensometer queue will be dispatched in another thread
    tensometerThread.start(callback(&tensometerQueue, &EventQueue::dispatch_forever));

    //Yoke handler is executed every 10 ms
    eventQueue.call_every(10, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically every 10 ms
*/
void Yoke::handler(void)
{
    counter++;

    // LED heartbeat
    systemLed = ((counter & 0x68) == 0x68);
}