/* Author:       Michal Wojnowski
   Student Code: C00213963 
   Date:         24/11/19*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \class main
    \brief Demonstration of semaphores using two tasks one of them being delayed  

   Using mutex and condition variables to implement Semaphores in thread functions and show semaphore uses with the use of a delayed task 

*/
/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  /*Increments the semaphore counter so taskTwo can take place*/
  theSemaphore->Signal();
}
/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  /*Decreases the semaphore counter as due to delay on taskOne this takes place first*/
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;

  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();

  return 0;
}
