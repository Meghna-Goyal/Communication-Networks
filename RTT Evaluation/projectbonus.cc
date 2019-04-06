#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

//Declare variables for calculating RTT and Propagation delay.

simtime_t startTimeTic,endTimeTic,RTT_Tic;
simtime_t startTimeToc,endTimeToc,RTT_Toc;
double delayrr,delayrr1;
int i,counter;


class Txc1 : public cSimpleModule

{
  private:

    cOutVector totaltocround,totalticround;

  protected:

    // The following redefined virtual function holds the algorithm.

    virtual void initialize() override;

    virtual void handleMessage(cMessage *msg) override;

};



// The module class needs to be registered with OMNeT++

Define_Module(Txc1);



void Txc1::initialize()

{

    totaltocround.setName("Total Round trip of Station B");
    totalticround.setName("Total Round trip of Station A");
    delayrr = par("distance");
    if (strcmp("StationA", getName()) == 0) {

        cMessage *msg = new cMessage("EndToEndMsg");
        send(msg, "out");

    }

}


void Txc1::handleMessage(cMessage *msg)

{
    /* To use multiple delay of difference 50 each variable 'i' is used.
     * each time message recieved at any of the node difference 100 will add to the previous delay.
     */
    if (strcmp("StationA", getName()) == 0) {
        EV << "Packet No: " << counter <<"\n";
        startTimeTic =  msg->getArrivalTime();
        RTT_Tic = startTimeTic - endTimeTic;
        endTimeTic = startTimeTic;
        totalticround.record(RTT_Tic);
        cDelayChannel * channel = check_and_cast<cDelayChannel*>(gate("out")->getChannel());
        delayrr = par("distance");
        delayrr=delayrr+i;
        channel->setDelay(delayrr) ;
        i= i+50;
        send(msg, "out"); // send out the message
    } else {
        EV << "Packet No: " << counter <<"\n";
        startTimeToc =  msg->getArrivalTime();
        RTT_Toc = startTimeToc - endTimeToc;
        endTimeToc = startTimeToc;
        totaltocround.record(RTT_Toc);
        delayrr1=par("distance");
        cDelayChannel * channel = check_and_cast<cDelayChannel*>(gate("out")->getChannel());
        delayrr1 = delayrr1+i;
        channel->setDelay(delayrr1) ;
        send(msg, "out");
        i=i+50;
    }
    counter++;
}






