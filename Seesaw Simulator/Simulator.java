/*
Seesaw Simpualtor

Works fine, didnt get to fully debug a few minor checkstyle issues


*/
import java.io.*;

import java.util.*;

import java.util.concurrent.locks.*;



public class Simulator { 
  private static double wilmaHeight = 7.0;
  private static double fredHeight = 1.0;

  //setting both fred and wilma as a double to meet specification requiremtns

  public static class Mutex {
    public int round;
    public int count;

    public Mutex(int person, int timeCount) { //pass mutex varibles into constructor
      round = person;
      count = timeCount;
    }
    


    /**
    * this synchronized roundPause passed the variable into id to catch exception e
    */


    public synchronized void roundPause(int id) throws InterruptedException {
      while (round != id) { // 
        wait();
      }
    }
  

    /**
     * this synchronized roudswap synchronizes with previous
     */

   
    public synchronized void roundSwap() { //System.out.println("Inside turnswitch");


      if (round == 0) {
        ++round;
      }   else if (round == 1) {
        --round;
      } 
      notifyAll();
    }
  }
  /**
  * The Sychronized constructuors and keywords in java come in hand for this situation most
  * because it means the method can not be executed by two threads at the same time, which ultimately
  * will allow the program to run and synchronize.
  */
  
  private static class WilmasTurn extends Thread implements Runnable {
    private static int THIS_ID;
    private static Mutex MUTEX_DOUBLE;

    public WilmasTurn(int id, Mutex Mt) {
      THIS_ID = id;
      MUTEX_DOUBLE = Mt;
    } 

    public void wilmaSaw() {
      for (int i = 0; i < 10; ++i) {
        try { 
          MUTEX_DOUBLE.roundPause(THIS_ID);
          System.out.println("Wilma: Up");
          while (wilmaHeight < 7.0) { 
            System.out.println("Wilmas Height is at: " + wilmaHeight);
            System.out.println("Freds Height is at: " + fredHeight);
            wilmaHeight += 1.5;
            fredHeight -= 1.5;
          }
          System.out.println("Wilmas Height after incriment: " + wilmaHeight);
          System.out.println("Freds Height after decriment: " + fredHeight);
          Thread.sleep(1000);
          MUTEX_DOUBLE.roundSwap();
        }  catch (InterruptedException e) { 
          e.printStackTrace(); 
        } 
      } 
    }

    public void run() { 
      wilmaSaw();
    }
  }

  private static class FredsTurn extends Thread implements Runnable {
    private static int THIS_ID;
    private static Mutex MUTEX_DOUBLE;
   
  
    public FredsTurn(int n, Mutex m) {
      THIS_ID = n; 
      MUTEX_DOUBLE = m;
    }


    public void fredSee() {
      for (int j = 0; j < 10; ++j) {
        try {
          MUTEX_DOUBLE.roundPause(THIS_ID);
          System.out.println("Fred: Up");
          while (fredHeight < 7.0) {
            System.out.println("Wilmas Height is at: " + wilmaHeight);
            System.out.println("Freds Height is at: " + fredHeight);
            --wilmaHeight;
            ++fredHeight;
          }
          System.out.println("Wilmas Height after decriment: " + wilmaHeight);
          System.out.println("Freds Height after incriment: " + fredHeight);
          Thread.sleep(1000);
          MUTEX_DOUBLE.roundSwap();
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
    }

    public void run() {
      fredSee();
    }
  }
  /**
  * this public static void main funciton.
  */

  public static void main(String args[]) {
    //general set up for threads and arrays
    ArrayList<Thread> funstuff = new ArrayList<>();
    Mutex myLock = new Mutex(0, 2);
   //using two threads

    Thread a1 = new Thread(new WilmasTurn(0, myLock));
    funstuff.add(new Thread(a1));
    Thread a2 = new Thread(new FredsTurn(1, myLock));
    funstuff.add(new Thread(a2));

    try {
      for (Thread a : funstuff) {
        a.start();
      }
    } catch (Exception e) {
      System.out.println("Error, not starting. please try again");

    }
    try {
      for (Thread a : funstuff) {
        a.join();
      }
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }
}