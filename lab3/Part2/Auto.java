class Auto extends Thread { // Class for the auto threads.

  private int id_auto;
  private int port;
  private Ferry fry;
  Logger logger;

  public Auto(int id, int prt, Ferry ferry, Logger logger)
  {
    this.id_auto = id;
    this.port = prt;
    this.fry = ferry;
    this.logger = logger;
  }

  public void run() {

    while (true) {
      // Delay
      try {sleep((int) (300*Math.random()));} catch (Exception e) { break;}
      System.out.println("Auto " + id_auto + " arrives at port " + port);
      

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
        fry.addLoad();  // increment the ferry load
        fry.loadingSem[port].release();
        System.out.println("Auto " + id_auto + " boards on the ferry at port " + port);
        logger.check (fry.getPort() == port, "error loading at wrong port");

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
        // handle the interrupt
        break; 
      }

      try{
        fry.unloadSem[port].acquire();
        // disembark    
        System.out.println("Auto " + id_auto + " disembarks from ferry at port " + port);
        logger.check (fry.getPort() == port, "error unloading at wrong port");
        fry.reduceLoad();   // Reduce load
        fry.unloadSem[port].release();
      }
      catch(InterruptedException ie){
        Thread.currentThread().interrupt();
        break;
      }
  
      // Terminate
      if(isInterrupted()) break;
    }
    System.out.println("Auto "+id_auto+" terminated");
  }
}
