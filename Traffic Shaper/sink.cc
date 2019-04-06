#include <omnetpp.h>
#include<sink.h>

using namespace omnetpp;

Define_Module( stationB );

void stationB::initialize()
{
    lifetimeSignal = registerSignal("lifetime");
}

void stationB::handleMessage(cMessage *msg)
{
    simtime_t lifetime = simTime() - msg->getCreationTime();
    EV << "Received " << msg->getName() << ", lifetime: " << lifetime << "s" << endl;
    emit(lifetimeSignal, lifetime);
    delete msg;
}
