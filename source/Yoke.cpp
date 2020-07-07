#include "Yoke.h"

//XXX global variables for test
float g_pitchForce;
float g_rollForce;

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED2),
    pitchTensometer(PD_0, PD_1, eventQueue),
    rollTensometer(PF_8, PF_9, eventQueue),
    pitchForceFilter(20),
    flapsUpSwitch(PB_15, PullUp),
    flapsDownSwitch(PB_13, PullUp),
    gearUpSwitch(PF_4, PullUp),
    gearDownSwitch(PF_5, PullUp),
    redPushbutton(PB_11, PullUp),
    greenPushbutton(PB_2, PullUp),
    leftToggle(PG_5, PullUp),
    rightToggle(PG_8, PullUp),
    throttlePotentiometer(PC_5),
    propellerPotentiometer(PC_4),
    mixturePotentiometer(PB_1),
    joystickGainPotentiometer(PA_2)
{
    printf("Yoke object created\r\n");

    handlerTimer.start();

    //Yoke handler is executed every 10 ms
    eventQueue.call_every(10ms, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically every 10 ms
*/
void Yoke::handler(void)
{
    counter++;
    float dt = std::chrono::duration<float>(handlerTimer.elapsed_time()).count();
    handlerTimer.reset();


    // request new tensometer readouts
    pitchTensometer.readRequest();
    rollTensometer.readRequest();
    // LED heartbeat
    systemLed = ((counter & 0x68) == 0x68);

}
