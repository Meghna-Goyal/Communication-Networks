import ned.DatarateChannel;

simple stationA
{
    
    parameters:
		
   		@display("i=block/source,20");
   		volatile double sendIaTime @unit(s);
   		int limit = default(2);
    gates:
        //input in;
        output out;
}

simple Token
{
    parameters:

   		@display("i=block/queue;i2=status/busy");
   		volatile double serviceTime @unit(s);
   		@signal[qlen](type="long");
        @signal[busy](type="long");
        @signal[queueingtime](type="double");
        
   		
   		int limit = default(2);
    gates:
        input in[];
        output out;
} 

  

simple stationB
{
    
    parameters:
		//@display("i=block/routing");  // to add a default icon
   		@display("p=273,101");
   		volatile double delayTime @unit(s); // volatile variable is used to create processing delay
   		int limit = default(2);
   		@signal[lifetime](type="simtime_t");
    gates:
        input in[];
        //output out;
}
network tokenbuck
{         
    submodules:
        source: stationA
		{
			parameters:
            @display("i=,red");
		}
        sink: stationB
		{
			parameters:
			@display("i=,green");
			
		}
		
		queue : Token
		{
		    parameters:
            @display("i=,blue");
		}    
		
    connections:
        source.out --> queue.in++; // This delay is changed for 15 different simulations, datarate is kept constant
		queue.out --> sink.in++;


}

