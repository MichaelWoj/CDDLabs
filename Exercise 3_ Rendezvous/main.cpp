/* Author:       Michal Wojnowski
   Student Code: C00213963 
   Date:         24/11/19*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \class main
    \brief An Implementation of a Rendezvous using Semaphores and two tasks with varying delays

   Using mutex and condition variables to implement an example of a rendezvous for threads with the aid of two tasks, first one iwth a 5 sec delay 
   and second with a 1 sec delay

*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  //Relese firstSem to allow it to continue
  firstSem->Signal();
  //Set wait to allow taskTwo to finish
  secondSem->Wait();
  std::cout << "Task One has left!"<<std::endl;
}
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //Set the firstSem to wait to allow taskOne to arrive simultanoiusly
  firstSem->Wait();
  //THIS IS THE RENDEZVOUS POINT!
  //Release secondSem to allow taskOne to finish
  secondSem->Signal();
  std::cout << "Task Two has left "<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
