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

    // 1 second LED heartbeat
    uint8_t phase = counter % 100;
    systemLed = (phase <= 10) || ((phase >= 20) && (phase <= 30)) ? 1 : 0;
}