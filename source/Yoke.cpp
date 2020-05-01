#include "Yoke.h"

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    tensometerThread(osPriorityBelowNormal),
    pitchTensometer(PD_1, PD_0, eventQueue)
{
    printf("Yoke object created\r\n");
    // tensometer queue will be dispatched in another thread
    tensometerThread.start(callback(&tensometerQueue, &EventQueue::dispatch_forever));

    //XXX temporary heartbeat for test
    eventQueue.call_every(500, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically
*/
void Yoke::handler(void)
{
    systemLed = !systemLed;
    printf("F=0x%08X\r\n", pitchTensometer.getData());
}