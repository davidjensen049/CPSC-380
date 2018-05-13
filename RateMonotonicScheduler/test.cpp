/*
David Jensen assignment 3

I was really confused with this assignment so i have no idea if its running 
the way its supposed to.

c++ test.cpp -o a.out to to compile and run.

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <pthread.h>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
#include <semaphore.h>
#include <vector>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;
#define _GNU_SOURCE
#define NUM_THREAD 4

//global variables
int thread0count = 0;
int thread1count = 0;
int thread2count = 0;
int thread3count = 0;
int thread0failedC = 0;
int thread1failedC = 0;
int thread2failedC = 0;
int thread3failedC = 0;
void printOptions();
void welcomeScreen();
bool thread0completed = true;
bool thread1completed = true;
bool thread2completed = true;
bool thread3completed = true;
bool Finished = false;
double U = 10;
int arr[10][10];
sem_t thread0;
sem_t thread1;
sem_t thread2;
sem_t thread3;
sem_t stop; //wake up the scheduler
//Calc* avg = new Calc();

//


 class Calc {
	vector<long long int> thread0;
	vector<long long int> thread1;
	vector<long long int> thread2;
	vector<long long int> thread3;
	Calc();
	double calcAvg(vector<long long int> vec);

	};

	Calc::Calc(){}
	double Calc::calcAvg(vector<long long int> vec) {
	double sum;
	for(int i = 0; i < vec.size(); ++i) {
		sum += vec[i];
	}
	return (sum/vec.size());
}



// the printing statements for the work done

void printOptions() {

	cout << "Thead 0 has ran " << thread0count << " Times. " << endl;
	cout << "Thread 1 has ran " << thread1count << " Times. " << endl;
	cout << "Thead 2 has ran " << thread2count << " Times. " << endl;
	cout << "Thread 3 has ran " << thread3count << " Times. " << endl;
	cout << "" <<endl;
	cout << "Thread 0 overrn a total of " << thread0failedC << " times" << endl;
	cout << "Thread 1 overrn a total of " << thread1failedC << " times" << endl;
	cout << "Thread 2 overrn a total of " << thread2failedC << " times" << endl;
	cout << "Thread 3 overrn a total of " << thread3failedC << " times" << endl;
	//cout << "total time was " << time << endl;

}

void welcomeScreen() {
	cout << "welcome" << endl;
// just a testing window

}


//supposed to handle the timer and sleep fucntions 
void timer() {
	nanosleep((const struct timespec[]){{0, 10000000}}, NULL);
		sem_post(&stop);
}

//loading the array
void initArr() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			arr[i][j]=1;
		}
	}
}
//this indexses for skipping aray and nested for loop for runtime
void DoWork() {
	int column[] = {0,2,4,6,8,1,3,5,7,9};
	for(int x = 0; x < 10; ++x) {
		int temp = column[x];
		for (int y = 0; y < 10; ++y) {
			if (y == 9) {
				arr[y][temp] = arr[y][temp] * arr[0][temp];
			}
			arr[y][temp] = arr[y][temp] * arr[y][temp+1];
			for (int m = 0; m < 100; ++m) {

			}
		}
	}
}


//thread 3 handling 16, waits for the schedule to finish then runs
void *th3(void* arg) {
	while(!Finished) {
		sem_wait(&thread3);
		thread0completed = false;
		for (int x = 0; x < 16; ++x) {
			DoWork();
		}
		thread3completed = true;
	}	++thread3count;
		
}


void *th2(void* arg) {
	while(!Finished) {
		sem_wait(&thread2);
		thread2completed = false;
		for (int x = 0; x < 4; ++x) {
			DoWork();
		}
		thread2completed = true;
		++thread2count;
	
	}
}

void *th1(void* arg) {
	while(!Finished) {
		sem_wait(&thread1);
		thread1completed = false;
		for (int x = 0; x < 2; ++ x) {
			DoWork();
		}
		thread1completed = true;
		++thread1count;
	}
}


void *th0(void* arg) {
	while(!Finished) {
		sem_wait(&thread0);
		//auto start = std::chrono::high_resolution_clock::now();
		thread0completed = false;
		for (int x = 0; x < 5000; ++ x) {
			DoWork();
		}
		thread0completed = true;
		++thread0count;
		
		}
}





int main(int argc, char** argsv) {

	
	//time = (end - start);

 
pthread_t threads[NUM_THREAD]; //makes threads
initArr();



//starts at 0
sem_init(&thread0, 0, 0);
sem_init(&thread1, 0, 0);
sem_init(&thread2, 0, 0);
sem_init(&thread3, 0, 0);
sem_init(&stop, 0, 0);
int priority = 50;

//init priorities and attribues
pthread_attr_t attribute0;
pthread_attr_t attribute1;
pthread_attr_t attribute2;
pthread_attr_t attribute3;
pthread_attr_init(&attribute0);
pthread_attr_init(&attribute1);
pthread_attr_init(&attribute2);
pthread_attr_init(&attribute3);
struct sched_param paramater0;
struct sched_param paramater1;
struct sched_param paramater2;
struct sched_param paramater3;
	
//prioroty scheduling for the threads
paramater0.sched_priority = priority;
int sucess = pthread_attr_setschedparam(&attribute0, &paramater0);
if (sucess != 0) {
	cout << "attribute0 has sucessfully passed!" << endl;
}

priority = 30;
paramater1.sched_priority = priority;
sucess = pthread_attr_setschedparam(&attribute1, &paramater1);
if (sucess != 0) {
	cout << "attribute1 has failed" << endl;
}

priority = 20;
	paramater2.sched_priority=priority;
	pthread_attr_setschedparam(&attribute2, &paramater2);
	if (sucess != 0){
		cout << "attribute2 failed" << endl;
	}
	//schedule priority for thread 3
	priority = 10;
	paramater3.sched_priority=priority;
	pthread_attr_setschedparam(&attribute3, &paramater3);
	if (sucess != 0){
		cout << "attribute3 passed" << endl;
	}

//creating the threads
  pthread_create(&threads[0], &attribute0, th0, NULL);
  pthread_create(&threads[1], &attribute1, th2, NULL);
  pthread_create(&threads[2], &attribute2, th2, NULL);
  pthread_create(&threads[3], &attribute3, th3, NULL);

//scheduling
  int i = 0;
  //time_point<clock> start = clock::now();
  while(i < 160) {
  	timer();
  	sem_wait(&stop);
  	if(i == 0) { //resort to schduling all if 0
  		sem_post(&thread0);
  		sem_post(&thread1);
  		sem_post(&thread2);
  		sem_post(&thread3);
  	}

  	if(i%16==0){
  		if(thread3completed!=true){
  			++thread3failedC;
  		}
  		sem_post(&thread3);
  	}

  	if(i%4==0){
  		if(thread2completed!=true){
  			++thread2failedC;
  		}
  		sem_post(&thread2);
  	}

  	if(i%2==0){
  		if(thread1completed!=true){
  			++thread1failedC;
  		}
  		sem_post(&thread1);
  	}

  	if(i%1 ==0) {
  		if(thread0completed!=true){
  			++thread0failedC;
  		}
  		sem_post(&thread0);
  	}
  	++i;

  }
//time_point<clock> end = clock::now();
// return the printed statemnts
  Finished = true;
  sleep(5);
  printOptions();
 // string word2;
  //cin >> word2;


//cout << "Time took " << end-start << endl;
//deallocate memory

  pthread_attr_destroy(&attribute0);
  pthread_attr_destroy(&attribute1);
  pthread_attr_destroy(&attribute2);
  pthread_attr_destroy(&attribute3);
  sem_destroy(&thread0);
  sem_destroy(&thread1);
  sem_destroy(&thread2);
  sem_destroy(&thread3);

return 0;
}
