/**
 *David Jensen, Fred - Wilma Seesaw Simulator, using 2 semephore and 2 Threads.
 *
 */

import java.util.concurrent.*;



/**
 *Declaring the doubles as well as semephores for the seesaw to run.
 */

public class Simulator {
  private static int runningTime;
  private static double wilmaH;
  private static double fredH;

  static Semaphore thisisWilma = new Semaphore(0);
  static Semaphore thisisFred = new Semaphore(1);


  /**
   *Wilmas turn to run, she will aquire her semephore, and release Freds.
   */


  static class WilmaSaw implements Runnable {

    public void run() {

      while (runningTime < 100) {

        try {
          thisisWilma.acquire();
          while (fredH > 1) {
            ++runningTime;
            wilmaH += 1.5;
            fredH -= 1.5;

            if (runningTime > 100) 
              break;
            
              System.out.println("The Current time in seconds is:" + runningTime);
              System.out.println("Wilmas Height is: " + wilmaH);
              System.out.println("Freds Height is: " + fredH);
            

            if (runningTime % 10 == 0) 
              System.out.println();
              Thread.sleep(1050);
            //run
             // while
          } //try
        } catch (InterruptedException e) { //exception
          System.out.println("Error, Please try again: " + e);
        }
        thisisFred.release();


      } //while
    } // if
  } // if

  /**
   * Freds turn to run, he will aquire his semephore, and release wilmas.
   */

  static class FredSee implements Runnable {

    public void run() {
      while (runningTime < 100) {
        try {
          thisisFred.acquire();
          while (fredH < 7) {
            ++runningTime;
            ++fredH;
            --wilmaH;

            if (runningTime > 100) 
              break;
            
              System.out.println("The Current time in seconds is:" + runningTime);
              System.out.println("Wilmas Height is: " + wilmaH);
              System.out.println("Freds Height is: " + fredH);

              if (runningTime % 10 == 0) 
                System.out.println();
                Thread.sleep(1050);
              
            
          }
        } catch (InterruptedException e) {
          System.out.println("Error, Please try again: " + e);
        }
        thisisWilma.release();
      }
    }
  }

  /**
   * This is outside the main function, this required javadoc [comment].
   */
  public static void main(String[] args) {  /* require jdoc comment/*
     /**
      * inside the main function, this will run in run threaded with everything else
      */

    wilmaH = 7.0;
    fredH = 1.0; 
    runningTime = 0;

    System.out.println("Time of program starting is" + runningTime + "Seconds");
    System.out.println("Wilmas Height before starting is " + wilmaH + "Feet");
    System.out.println("Freds Height before starting is " + fredH + "Feet");
    Thread throughputWilma = new Thread(new WilmaSaw());
    Thread throughputFred = new Thread(new FredSee());
    throughputWilma.start();
    throughputFred.start();
  }
}












 