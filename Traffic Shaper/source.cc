#include <omnetpp.h>
#include<source.h>

using namespace omnetpp;

double inter;

Define_Module(stationA);

stationA::stationA()
{
    sendMessageEvent = NULL;
}

stationA::~stationA()
{
    cancelAndDelete(sendMessageEvent);
}

void stationA::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);
    interarrival.setName("Inter Arrival Time");
}

void stationA::handleMessage(cMessage *msg)
{
    ASSERT(msg==sendMessageEvent);

    cMessage *job = new cMessage("job");
    send(job, "out");

    inter = par("sendIaTime");

    scheduleAt(simTime()+inter, sendMessageEvent);

    interarrival.record(inter);
}




