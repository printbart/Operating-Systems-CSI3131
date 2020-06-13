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
  
      // Board
      System.out.println("Auto " + id_auto + " boards on the ferry at port " + port);
      logger.check (fry.getPort() == port, "error loading at wrong port");
      fry.addLoad();  // increment the ferry load
      
      // Arrive at the next port
      port = 1 - port ;   
      
      // disembark    
      System.out.println("Auto " + id_auto + " disembarks from ferry at port " + port);
      logger.check (fry.getPort() == port, "error unloading at wrong port");
      fry.reduceLoad();   // Reduce load
  
      // Terminate
      if(isInterrupted()) break;
    }
    System.out.println("Auto "+id_auto+" terminated");
  }
}
