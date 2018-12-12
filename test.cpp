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
#include <list>


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

void task1()
{
  //endless insertion and memory allocation
  //-will sooner or later raise an exception
  //-BEWARE:this is bad practice

  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  throw std::exception();
  //std::list<int> v;
  //while(true){
  //  for(int i=0;i<1000000;++i){
  //    v.push_back(i);
  //  }
  //  std::cout.put('.').flush();
  //}
}

int quickComputation()
{
  //process result "quick and dirty"
  std::cout<<"quick and dirty"<<std::endl;

  return -1;
}

int accurateComputation()
{
  //process result "accurate but slow"
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  std::cout<<"accurate but slow"<<std::endl;

  return 1;
}

std::future<int> f0;//outside declared because lifetime of accurateComputation() might exceed lifetime of bestResultInTime()

int bestResultInTime()
{
  //std::future<int> f0;//this func will be block for accurateComputation()
  //define time slot to get the answer:
  auto tp=std::chrono::system_clock::now()+std::chrono::seconds(5);

  //start both a quick and an accurate computation:
  f0=std::async(std::launch::async,accurateComputation);
  int guess=quickComputation();

  //give accurate computation the rest of the time slot:
  std::future_status s=f0.wait_until(tp);

  //return the best computation result we have:
  if(s==std::future_status::ready){
    return f0.get();
  }
  else{
    return guess;//accurateComputation() continues
  }
}

int doOtherthing(const char& c)//pass character by reference
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

class X
{
public:
  void mem(int num){std::cout<<num<<std::endl;}
};

int queryNumber()
{
  //read number
  std::cout<<"read number: ";
  int num;
  std::cin>>num;

  //throw exception if none
  if(!std::cin){
    throw std::runtime_error("no number read");
  }

  return num;
}

void doAnotherthing(char c,std::shared_future<int> f)
{
  try{
    //wait for number of characters to print
    int num=f.get();//get result of queryNumber()

    for(int i=0;i<num;++i){
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout.put(c).flush();
    }
  }
  catch(const std::exception& e){
    std::cerr<<"EXCEPTION in thread "<<std::this_thread::get_id()
             <<": "<<e.what()<<std::endl;
  }
}

void doSomeOtherthing(int num,char c)
{
  try{
    //random-number generator(use c as seed to get different sequences)
    std::default_random_engine dre(42*c);
    std::uniform_int_distribution<int> id(10,1000);
    for(int i=0;i<num;++i){
      std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
      std::cout.put(c).flush();
    }
  }
  //make sure no exception leaves the thread and terminates the program
  catch(const std::exception& e){
    std::cerr<<"THREAD-EXCEPTION (thread "
             <<std::this_thread::get_id()<<"): "<<e.what()<<std::endl;
  }
  catch(...){
    std::cerr<<"THREAD-EXCEPTION (thread "
             <<std::this_thread::get_id()<<")"<<std::endl;
  }
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

  //force func1() to start asynchronously now or throw std::system_error
  std::future<int> result3=std::async(std::launch::async,func1);

  int result4=func2();

  std::cout<<result3.get()+result4<<std::endl;

  std::future<int> f(std::async(std::launch::deferred,func1));//defer func1 until get()

  std::cout<<func2()<<std::endl;

  //auto f1=std::async(std::launch::deferred,task1);
  //auto f2=std::async(std::launch::deferred,task2);
  //...;
  //auto val=thisOrThatIsTheCase()?f1.get():f2.get();

  std::cout<<"starting 2 tasks"<<std::endl;
  std::cout<<"-task1: process endless loop of memory consumption"<<std::endl;
  std::cout<<"-task2: wait for <return> and then for task1"<<std::endl;

  auto f1=std::async(task1);//start task1() asynchronously(now or later or never)
  std::cin.get();//read a character(like getchar())

  std::cout<<"\nwait for the end of task1: "<<std::endl;
  try{
    f1.get();//wait for task1() to finish(raises exception if any)
  }
  catch(const std::exception& e){
    std::cerr<<"EXCEPTION: "<<e.what()<<std::endl;
  }

  //std::future<..> f(std::async(func));//try to call func asynchronously
  //...;
  //f.wait();//wait for func to be done(might start background task)
  //f.wait_for(std::chrono::seconds(10));//wait at most 10 seconds for func
  //f.wait_until(std::system_clock::now()+std::chrono::minutes(1));

  //do something while task has not finished(might never happen!)
  //while(f.wait_for(std::chrono::seconds(0))!=std::future_status::ready){
  //  ...;
  //}

  //check whether task was deferred:
  //if(f.wait_for(std::chrono::seconds(0))!=std::future_status::deferred){
    //do something while task has not finished
  //  while(f.wait_for(std::chrono::seconds(0))!=std::future_status::ready){
  //    ...;
  //  }
  //}
  //...;
  //auto r=f.get();//force execution of task and wait for result(or exception)

  //std::this_thread::yield();//hint to reschedule to the next thread

  std::cout<<bestResultInTime()<<std::endl;
  std::cout<<"bestResultInTime is done!"<<std::endl;

  //18.1.2 实例：等待两个Task

  std::cout<<"starting 2 operations asynchronously"<<std::endl;

  //start two loops in the background printing characters . or +
  auto f2=std::async([](){doSomething('.');});
  auto f3=std::async([](){doSomething('+');});

  //if at least one of the background tasks is running
  if(f2.wait_for(std::chrono::seconds(0))!=std::future_status::deferred||
     f3.wait_for(std::chrono::seconds(0))!=std::future_status::deferred){
    //poll until at least one of the loops finished
    while(f2.wait_for(std::chrono::seconds(0))!=std::future_status::ready&&
          f3.wait_for(std::chrono::seconds(0))!=std::future_status::ready){
      //...;//std::cout<<"foo!"<<std::endl;
      std::this_thread::yield();//hint to reschedule to the next thread
    }
  }
  std::cout.put('\n').flush();

  //wait for all loops to be finished and process any exception
  try{
    f2.get();
    f3.get();
  }
  catch(const std::exception& e){
    std::cout<<"\nEXCEPTION: "<<e.what()<<std::endl;
  }
  std::cout<<"\ndone"<<std::endl;

  char c='@';
  auto f4=std::async([=](){//=:can access objects in scope by value
      doSomething(c);//pass copy of c to doSomething()
    });
  c='*';
  auto f5=std::async(doSomething,c);//call doSomething(c) asynchronously
  c='/';
  auto f6=std::async([&](){doOtherthing(c);});//pass c by reference

  try{
    f4.get();
    f5.get();
    f6.get();//needs lifetime of c until here
  }
  catch(const std::exception& e){
    std::cout<<"\nEXCEPTION: "<<e.what()<<std::endl;
  }
  std::cout<<std::endl;

  //char c='@';
  //auto f=std::async([&](){doSomething(c);});//risky! c may be over!
  //auto f=std::async(doSomething,std::ref(c));//risky!c may be over!

  c='$';
  auto f7=std::async([&](){doOtherthing(c);});//pass c by reference
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  c='_';//switch output of doOtherthing() to underscores, if it still runs
  try{
    f7.get();//needs lifetime of c until here
  }
  catch(const std::exception& e){
    std::cout<<"\nEXCEPTION: "<<e.what()<<std::endl;
  }
  std::cout<<std::endl;

  X x;
  auto a=std::async(&X::mem,x,42);//try to call x.mem(42) asynchronously
  try{
    a.get();
  }
  catch(const std::exception& e){
    std::cout<<"\nEXCEPTION: "<<e.what()<<std::endl;
  }

  //18.1.3 Shared Future

  try{
    //start one thread to query a number
    std::shared_future<int> f=std::async(queryNumber);
    //auto f=std::async(queryNumber).share();

    //start three threads each processing this number in a loop
    auto f1=std::async(std::launch::async,doAnotherthing,'.',f);
    auto f2=std::async(std::launch::async,doAnotherthing,'+',f);
    auto f3=std::async(std::launch::async,doAnotherthing,'*',f);

    //wait for all loops to be finished
    f1.get();
    f2.get();
    f3.get();
  }
  catch(const std::exception& e){
    std::cout<<"\nEXCEPTION: "<<e.what()<<std::endl;
  }
  std::cout<<"\ndone"<<std::endl;

  //void doSomething(char c,const std::shared_future<int>& f);//risky! not good!
  //auto f1=std::async(std::launch::async,doSomething,'.',std::ref(f));//risky! not good!

  //18.2 低层接口：Thread和Promise
  //18.2.1 Class std::thread

  std::thread t(doSomething,'~');//start doSomething() in the background

  t.join();//wait for t to finish(block until doSomething() ends)
  std::cout<<std::endl;

  try{
    std::thread t1(doSomeOtherthing,5,'.');//print five dots in separate thread
    std::cout<<"-started fg thread "<<t1.get_id()<<std::endl;

    //print other characters in other background threads
    for(int i=0;i<5;++i){
      std::thread t(doSomeOtherthing,10,'a'+i);//print 10 chars in separate thread
      std::cout<<"-detach started bg thread "<<t.get_id()<<std::endl;
      t.detach();//detach thread into the background
    }

    std::cin.get();//wait for any input(return)
    std::cout<<"-join fg thread "<<t1.get_id()<<std::endl;
    t1.join();//wait for t1 to finish
  }
  catch(const std::exception& e){
    std::cerr<<"EXCEPTION: "<<e.what()<<std::endl;
  }
  std::cout<<std::endl;

  std::cout<<"ID of \"no thread\": "<<std::thread::id()
           <<std::endl;

  std






  return 0;
}
