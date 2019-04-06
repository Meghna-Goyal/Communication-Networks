
#include <omnetpp.h>

using namespace omnetpp;

#ifndef SOURCE_H_
#define SOURCE_H_

class stationA : public cSimpleModule
{
  private:
    cMessage *sendMessageEvent;

  public:
    cOutVector interarrival;
    stationA();
     virtual ~stationA();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};



#endif /* SOURCE_H_ */
