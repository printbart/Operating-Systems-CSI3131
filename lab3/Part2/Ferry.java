class Ferry extends Thread{ // The ferry Class
  final static int MAXLOAD = 5;
  private int port=0;  // Start at port 0
  private int load=0;  // Load is zero
  private int numCrossings;  // number of crossings to execute
  private boolean ambulance_loaded = false;
  Logger logger;
  // Semaphores

  public Ferry(int prt, int nbtours, Logger logger)
  {
    this.port = prt;
    numCrossings = nbtours;
    this.logger = logger;
  }

  public void run() {
    System.out.println("Start at port " + port + " with a load of " + load + " vehicles");

    // numCrossings crossings in our day
    for(int i=0 ; i < numCrossings ; i++) {
      // The crossing
      System.out.println("Departure from port " + port + " with a load of " + load + " vehicles");
      System.out.println("Crossing " + i + " with a load of " + load + " vehicles");
      if (ambulance_loaded) {
        logger.check(load > 0 && load <= MAXLOAD, "error ferry leaving with less load! ");
      } 
      else {
        logger.check(load == MAXLOAD, "error ferry leaving with less load!, load is " + load + " ");
      }
      port = 1 - port;
      try {sleep((int) (100*Math.random()));} catch (Exception e) { }
      // Arrive at port
      System.out.println("Arrive at port " + port + " with a load of " + load + " vehicles");
      // Disembarkment et loading
    }
  }

  // methodes to manipulate the load of the ferry
  public int getLoad() { return(load); }
  public int getPort() { return(port); }
  public void addLoad() {
    logger.check(load < MAXLOAD, "error loadig in a full Ferry!");
    load = load + 1; 
    System.out.println ("added load, now " + load);
  }
  public void reduceLoad()  { 
    logger.check(load > 0, "error unloading an empty Ferry!");
    load = load - 1 ; 
    System.out.println ("removed load, now " + load);
  }
  public void loadAmbulance() {
    ambulance_loaded = true;
    addLoad();
  }
  public void unloadAmbulance(){
    ambulance_loaded = false;
    reduceLoad();
  }
}
