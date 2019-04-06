simple Txc1

{
     parameters:
         volatile double distance ; 
    gates:

        input in;

        output out;

}


network StationAtoB

{
	
    submodules:

        StationA: Txc1;

        StationB: Txc1;

    connections:

        StationA.out --> {delay = 100ms;}  --> StationB.in;

        StationA.in <--  {delay = 130ms;}   <-- StationB.out;

}

