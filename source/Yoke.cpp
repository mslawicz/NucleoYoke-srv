#include "Yoke.h"

//XXX global variables for test
float g_pitchForce;
float g_rollForce;

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED2),
    tensometerThread(osPriorityBelowNormal),
    pitchTensometer(PD_0, PD_1, tensometerQueue),
    rollTensometer(PF_8, PF_9, tensometerQueue),
    pitchForceFilter(20),
    propellerPotentiometer(PC_3)
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
    joystickGainPotentiometer(PA_2),
    tinyJoystickX(PC_3),
    tinyJoystickY(PC_2),
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
    float dt = 1e-3 * handlerTimer.elapsed_time().count();
    float deltaT = std::chrono::duration<float>(handlerTimer.elapsed_time()).count();
    handlerTimer.reset();


    // request new tensometer readouts
    leftPedalTensometer.readRequest();
    rightPedalTensometer.readRequest();
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
