/*
Seesaw Simpualtor


*/

import java.io.*;

import java.util.*;

public class Simulator {
	private static double wilmaH = 7.0;
	private static double fredH = 1.0;

	public static class Mutex {
		public int who;
		public int count;


		public Mutex(int timeCount, int person) {
			who = timeCount;
			count = person;
		}

			public synchronized void Change() {
				if(who == 0) {
					++who;
				}
				else if(who ==1) {
					--who;
				}
				notifyAll();
				}
				public synchronized void notTurn(int id) throws InterruptedException {
					while(who != id) {
						wait();
					}
				}
			}
			static private class FredsTurn extends Thread implements Runnable {
				private static Mutex MUT_ID;
				private static int THIS_ID;

				public FredsTurn(int id, Mutex MUT_IDtwo) {
					THIS_ID = id;
					MUT_ID = MUT_IDtwo;
				}
				static private class WilmasTurn extends Thread implements Runnable {
					private static Mutex MUT_ID;
					private static int THIS_ID;

					public WilmasTurn(Mutex m, int num) {
						MUT_ID = m;
						THIS_ID = num;
					}
					public void wilmaSaw() {
						for(int i = 0; i < 10; ++i) {
							try {
								MUT_ID.notTurn(THIS_ID);
								System.out.println("Wilma: Up");
								while(wilmaH < 7.0) {
									System.out.println("Wilmas Height is at: " + wilmaH);
									System.out.println("Freds Height is at : " + fredH);
									wilmaH += 1.5;
									fredH -= 1.5;
								}
								System.out.println("Wilmas Height after increment: " +wilmaH);
								System.out.println("Freds Height after decriment : " +fredH);
								Thread.sleep(1000);
								MUT_ID.Change();
							}
							catch(InterruptedException e) {
								e.printStackTrace();
							}
						}
					}
					public void run() {
						wilmaSaw();
					}
				}

				public void fredSee() {
					for(int j = 0; j < 10; ++j) {
						try {
							MUT_ID.notTurn(THIS_ID);
							System.out.println("Fred: Up");
							while(fredH < 7.0) {
								System.out.println("Wilmas Height is at: " + wilmaH);
									System.out.println("Freds Height is at : " + fredH);
									--wilmaH;
									++fredH;

							}
							System.out.println("Wilmas Height after decriment: " +wilmaH);
								System.out.println("Freds Height after increment: " +fredH);
								Thread.sleep(1000);
								MUT_ID.Change();

						}
						catch(InterruptedException e) {
							e.printStackTrace();
						}
					}
				}
				public void run() {
					fredSee();
				}
			}
			public static void main(String args[]) {
				ArrayList<Thread> threads = new ArrayList<>();
				Mutex myLock = new Mutex(0, 2);

				Thread tA = new Thread(new FredsTurn(0, myLock));
				Thread tB = new Thread(new WilmasTurn(1, myLock));

				threads.add(new Thread(tA));
				threads.add(new Thread(tB));

				try {
					for(Thread t : threads) {
						t.start();
					}
				}
				catch(Exception e) {
					System.out.println("Error, not starting. please try again");

				}
				try {
					for(Thread t : threads) {
						t.join();
					}
				}
				catch(InterruptedException e) {
					e.printStackTrace();
				}
			}
			}