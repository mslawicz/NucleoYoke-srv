#include "Yoke.h"

//XXX global variables for test
float g_force;
float g_filteredForce;
float g_pitch;

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1),
    tensometerThread(osPriorityBelowNormal),
    pitchTensometer(PD_1, PD_0, eventQueue),
    pitchForceFilter(20),
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
    float alpha = 0.5f * pot;
    float force = -1.0f * pitchTensometer.getValue();
    pitchForceFilter.calculate(force);
    float filteredForce = pitchForceFilter.getValue();

    yokePitch = 10.0f * pot * filteredForce;
    pitchServo.setValue(0.5f + yokePitch);

    g_force = force;
    g_filteredForce = filteredForce;
    g_pitch = yokePitch;

    if(counter % 50 == 0)
    {
        printf("pot=%f  al=%f  fo=%f  fi=%f  pi=%f\r\n", pot, alpha, force, filteredForce, yokePitch);
        //printf("force=%f  filter=%f\r\n", force, filteredForce);
    }
}
