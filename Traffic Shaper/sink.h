
#include <omnetpp.h>

using namespace omnetpp;

#ifndef SINK_H_
#define SINK_H_

class stationB : public cSimpleModule

{

  private:
    simsignal_t lifetimeSignal;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};



#endif /* SINK_H_ */
