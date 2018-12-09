/*
  author: Quinton
  date: 2018-12-9
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 18
*/


#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>


int doSomething(char c)
{
  //random-number generator(use c as seed to get different sequences)
  std::default_random_engine dre(c);
  std::uniform_int_distribution<int> id(10,1000);

  //loop to print character after a random period of time
  for(int i=0;i<10;++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
    std::cout.put(c).flush();
  }

  return c;
}

int func1()
{
  return doSomething('.');
}

int func2()
{
  return doSomething('+');
}



int main(int argc, char* argv[])
{
  //第18章 并发
  //18.1 高级接口：async()和Future
  //18.1.1 async()和Future的第一个用例

  std::cout<<"starting func1() in background"
           <<" and func2() in foreground:"<<std::endl;

  //start func1() asynchronously(now or later or never):
  std::future<int> result1(std::async(func1));

  int result2=func2();//call func2() synchronously(here and now)

  //print result(wait for func1() to finish and add its result to result2)
  int result=result1.get()+result2;

  //int result=func2()+result1.get();//might call func2() after func1() ends

  std::cout<<"\nresult of func1()+func2(): "<<result
           <<std::endl;

  //std::future<void> f(std::async(func));//try to call func asynchronously
  //f.get();//wait for func to be done(yields void)

  //std::async([]{...});//try to perform...asynchronously




  return 0;
}
