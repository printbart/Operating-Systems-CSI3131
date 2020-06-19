class Ambulance extends Thread { // the Class for the Ambulance thread

  private int id;
  private int port;
  private Ferry fry;
  Logger logger;

  public Ambulance(int id, int prt, Ferry ferry, Logger logger)
  {
    this.port = prt;
    this.fry = ferry;
    this.id = id;
    this.logger = logger;
  }

  public void run() {
     while (true) {
      // Attente
      try {sleep((int) (1000*Math.random()));} catch (Exception e) { break;}
      System.out.println("Ambulance " + id + " arrives at port " + port);

      try{
        fry.loadingSem[port].acquire();
        while(fry.getPort() != this.port || fry.finLoadSem.availablePermits() == 0){
          try{
            sleep(100);
          }
          catch (InterruptedException e){
            return;
          }
        }

  
        // Board
        System.out.println("Ambulance " + id + " boards the ferry at port " + port);
        logger.check (fry.getPort() == port, "error loading at wrong port"); 
        fry.loadAmbulance();  // increment the load 

        fry.loadingSem[port].release();
        
        // Arrive at the next port
        port = 1 - port ;   

        while(fry.getPort() != this.port){
          try{
            sleep(100);
          }
          catch(Exception e){
            break;
          }
        }
      }
      catch(InterruptedException ie){
        Thread.currentThread().interrupt();
        System.out.println("Thread terminated by interruption");
        break; 
      }
      
      try{
        fry.unloadSem[port].acquire();
        //Disembarkment    
        System.out.println("Ambulance " + id + " disembarks the ferry at port " + port);
        logger.check(fry.getPort() == port, "error unloading at wrong port");
        fry.unloadAmbulance();

        fry.unloadSem[port].release();
      }
      catch(InterruptedException ie){
        Thread.currentThread().interrupt();
        break;
      }
  
      // Terminate
      if(isInterrupted()) break;
    }
    System.out.println("Ambulance " + id + " terminated.");
  }
}
