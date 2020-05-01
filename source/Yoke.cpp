#include "Yoke.h"

Yoke::Yoke(events::EventQueue& eventQueue) :
    eventQueue(eventQueue),
    systemLed(LED1)
{
    printf("Yoke object created\r\n");

    //XXX temporary heartbeat for test
    eventQueue.call_every(500, callback(this, &Yoke::handler));
}



/*
* yoke handler should be called periodically
*/
void Yoke::handler(void)
{
    systemLed = !systemLed;
}