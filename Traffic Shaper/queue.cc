#include <omnetpp.h>
#include <queue.h>
#include <queue1.h>


using namespace omnetpp;
static int dropnumber;

Define_Module(Token);

Token::Token()
{
    msgServiced = endServiceMsg = NULL;
}

Token::~Token()
{
    delete msgServiced;
    cancelAndDelete(endServiceMsg);
}


simtime_t Token::startService(cMessage *msg)
{
    EV << "Starting service of " << msg->getName() << endl;
    return par("serviceTime");
}

void Token::endService(cMessage *msg)
{
    EV << "Completed service of " << msg->getName() << endl;
    send( msg, "out" );
}

void Token ::initialize()
{
    endServiceMsg = new cMessage("end-service");
    queue.setName("queue");
    ServiceTime.setName("Service Time(Seconds)");
    DropCount.setName("Drop count");
    qlenSignal = registerSignal("qlen");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingtime");
    emit(qlenSignal, queue.getLength());
    emit(busySignal, 0);

}

void Token::handleMessage(cMessage *msg)
{

    if (msg==endServiceMsg)
        {
            endService( msgServiced );
            if (queue.isEmpty())
            {
                msgServiced = NULL;
                emit(busySignal, 0);
            }
            else
            {
                if(packetLength <= bucketsize  && nooftoken >= packetLength)
                {
                    nooftoken = nooftoken - packetLength;

                    msgServiced = (cMessage *) queue.pop();
                    emit(qlenSignal, queue.getLength());
                    emit(queueingTimeSignal, simTime() - msgServiced->getTimestamp());
                    simtime_t serviceTime = startService( msgServiced );
                   // ServiceTime.record(serviceTime);
                    scheduleAt( simTime()+serviceTime, endServiceMsg );
                    ServiceTime.record(simTime()+serviceTime);

                }
                else
                {
                    bubble("no more space for new token..!!");
                    EV << "Bucket full.. please wait!!!";
                }
            }
        }
        else if (!msgServiced)
        {
            arrival( msg );
            msgServiced = msg;
            emit(queueingTimeSignal, 0.0);
            simtime_t serviceTime = startService( msgServiced );
            scheduleAt( simTime()+serviceTime, endServiceMsg );
            emit(busySignal, 1);
        }
        else
        {
           if (queue.getLength() >= capacity)
            {
               dropnumber++;
               DropCount.record(dropnumber);
                EV << "Capacity full! Job dropped.\n";
                 bubble("Dropped!");
                    delete msg;
                    return;
            }
            else
            {
                if(nooftoken < bucketsize && (nooftoken + tokentoadd) <=bucketsize )
                {
                    nooftoken= nooftoken + tokentoadd ;
                }
            arrival( msg );
            queue.insert( msg );

            msg->setTimestamp();
            emit(qlenSignal, queue.getLength());
            }


        }
}




