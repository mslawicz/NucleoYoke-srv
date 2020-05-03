#include "Yoke.h"

//XXX global variables for test
float g_pitchForce;
float g_rollForce;

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    tensometerThread(osPriorityBelowNormal),
    pitchTensometer(PD_0, PD_1, tensometerQueue),
    rollTensometer(PF_8, PF_9, tensometerQueue),
    pitchForceFilter(20),
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

    //float pot = propellerPotentiometer.read();
    float pitchForce = pitchTensometer.getValue();
    float rollForce = rollTensometer.getValue();

    g_pitchForce = pitchForce;
    g_rollForce = rollForce;

    if(counter % 50 == 0)
    {
        printf("pf=%f  rf=%f\r\n", pitchForce, rollForce);
    }
}
