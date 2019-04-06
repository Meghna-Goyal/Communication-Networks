#ifndef QUEUE1_H_
#define QUEUE1_H_

class Token : public cSimpleModule
{
protected:
    virtual simtime_t startService(cMessage *msg);
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void endService(cMessage *msg);
    virtual void arrival(cMessage *msg) {}

    cMessage *msgServiced;
    cMessage *endServiceMsg;
    cQueue queue;
    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;
    int capacity =3;
    int nooftoken;
    int packetLength =500;
    int bucketsize = 2500;
    int tokentoadd = 825;
public :
    cOutVector ServiceTime,DropCount;
    Token();
    ~Token();
};



#endif /* QUEUE1_H_ */
