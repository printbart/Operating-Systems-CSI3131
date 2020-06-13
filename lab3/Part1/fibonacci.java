import java.util.Random;

interface fibonacci_seq{
    public double next_item();
}

class classic_fib implements fibonacci_seq
{
  double a = 0;
  double b = 1;
  public  double next_item() {
    double val = a + b;
    a = b;
    b = val;
    System.out.println("next item: " + val);
    return val;
  }
}
class fib_class  implements fibonacci_seq
{
  static double a = 0;
  static double b = 1;
  Random rand;
  fib_class () {
    rand = new Random(); //instance of random class
  }
  public  double next_item() {
      int upperbound = 100;
      double val = a + b;
      a = b;
      b = val;
      System.out.println("next item: " + val);
      return val;
   }
}

class fibonacci_thrd implements Runnable 
{
  fibonacci_seq fib;
  int id;
  fibonacci_thrd(fibonacci_seq _fib, int _id) {
    fib = _fib;
    id = _id;
  }
  public void run() {
    System.out.println("thrd " + id + " output: " + fib.next_item());
    try{
      Thread.sleep(100000);
    }
    catch(InterruptedException ie){

    }
  }
}

public class fibonacci
{   
  public static void main(String args[]) { 
    fibonacci_seq seq = new fib_class();
    classic_fib seq1 = new classic_fib();
    for (int i=0; i<100; i++) {
      seq1.next_item();
    }

    for (int i=0; i<100; i++) {
      Runnable fb = new fibonacci_thrd(seq, i);      
      Thread thrd = new Thread(fb);
      thrd.start();
    }

    System.out.println("main done");
  }
}

