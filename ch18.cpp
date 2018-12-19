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
#include <queue>



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

std::thread::id masterThreadID;

void doAnotherSomething()
{
  if(std::this_thread::get_id()==masterThreadID){
    std::cout<<"This is masterThreadID: "<<masterThreadID<<std::endl;
  }
}

void doYetAnotherThing(std::promise<std::string>& p)
{
  try{
    //read character and throw exception if 'x'
    std::cout<<"read char('x' for exception): ";
    char c=std::cin.get();
    if(c=='x'){
      throw std::runtime_error(std::string("char ")+c+" read");
    }
    std::string s=std::string("char ")+c+" processed";
    p.set_value(std::move(s));//store result
    //p.set_value_at_thread_exit(std::move(s));//when thread end set value
  }
  catch(...){
    p.set_exception(std::current_exception());//store exception
    //p.set_exception_at_thread_exit(std::current_exception());//when thread end set exception
  }
}

double compute(int x,int y)
{
  std::cout<<"compute is done!"<<std::endl;
  return x+y;
}

void foo(int val)
{
  std::cout<<val<<std::endl;
}

std::mutex printMutex;//enable synchronized output with print()

void print(const std::string& s)
{
  std::lock_guard<std::mutex> l(printMutex);
  for(char c:s){
    std::cout.put(c).flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  std::cout<<std::endl;
}

class DatabaseAccess
{
private:
  std::mutex dbMutex;
  //...state of database access

public:
  void createTable()
  {
    std::lock_guard<std::mutex> lg(dbMutex);
    std::cout<<"call createTable"<<std::endl;
  }
  void insertData()
  {
    std::lock_guard<std::mutex> lg(dbMutex);
    std::cout<<"call insertData"<<std::endl;
  }
  //...

  void createTableAndInsertData()
  {
    std::lock_guard<std::mutex> lg(dbMutex);
    //...
    //createTable();//ERROR:deadlock because dbMutex is locked again
    std::cout<<"call createTableAndInsertData"<<std::endl;
  }
};

class DatabaseAccess1
{
private:
  std::recursive_mutex dbMutex;
  //...state of database access

public:
  void insertData()
  {
    std::lock_guard<std::recursive_mutex> lg(dbMutex);
    std::cout<<"call insertData"<<std::endl;
  }
  void createTable()
  {
    std::lock_guard<std::recursive_mutex> lg(dbMutex);
    std::cout<<"call createTable"<<std::endl;
  }
  void createTableAndInsertData()
  {
    std::lock_guard<std::recursive_mutex> lg(dbMutex);
    //...
    createTable();//OK:no deadlock
    std::cout<<"call createTableAndInsertData no deadlock"<<std::endl;
  }
};

void doSomeOtherStuff()
{
  std::cout<<"call doSomeOtherStuff"<<std::endl;
}

void couldNotGetTheLock()
{
  std::cout<<"call couldNotGetTheLock"<<std::endl;
}

bool readyFlag;
std::mutex readyFlagMutex;

void thread1()
{
  //do something therad2 needs as preparation
  //...
  std::cout<<"call thread1"<<std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  std::lock_guard<std::mutex> lg(readyFlagMutex);
  readyFlag=true;
  std::cout<<"thread1 is done!"<<std::endl;
}

void thread2()
{
  //wait until readyFlag is true(thread1 is done)
  {
    std::unique_lock<std::mutex> ul(readyFlagMutex);
    while(!readyFlag){
      ul.unlock();
      std::this_thread::yield();//hint to reschedule to the next thread
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      std::cout<<"thread2 is waiting"<<std::endl;
      ul.lock();
    }
  }//release lock

  //do whatever shall happen after thread1 has prepared things
  std::cout<<"call thread2"<<std::endl;
}

void initialize()
{
  std::cout<<"call initialize"<<std::endl;
}

static std::vector<std::string> staticData;

std::vector<std::string> initializeStaticData()
{
  std::vector<std::string> vs{"hello","world","!"};
  std::cout<<"initializing..."<<std::endl;
  return vs;
}

void bar()
{
  if(staticData.empty()){
    staticData=initializeStaticData();
  }
  std::cout<<"call bar"<<std::endl;
}

void foo1()
{
  static std::once_flag oc1;
  std::call_once(oc1,[](){
      staticData=initializeStaticData();
    });
  std::cout<<"call foo1"<<std::endl;
}

class Y{
private:
  mutable std::once_flag initDataFlag;
  void initData()const
  {
    std::cout<<"call Y::initData"<<std::endl;
  }
public:
  std::vector<std::string> getData()const
  {
    std::call_once(initDataFlag,&Y::initData,this);
    std::vector<std::string> vs{"haha","world","!"};
    return vs;
  }
};

bool readyFlagVar;
std::mutex readyMutexVar;
std::condition_variable readyCondVar;

void threadA()
{
  //do something threadB needs as preparation
  std::cout<<"<return>"<<std::endl;
  std::cin.get();

  //signal that threadA has prepared a condition
  {
    std::lock_guard<std::mutex> lg(readyMutexVar);
    readyFlagVar=true;
  }//release lock
  readyCondVar.notify_one();
}

void threadB()
{
  //wait until threadA is ready(readyFlagVar is true)
  {
    std::unique_lock<std::mutex> ul(readyMutexVar);
    readyCondVar.wait(ul,[](){return readyFlagVar;});//may lock unlock, so use unique_lock not lock_guard
  }//release lock

  //{
  //  std::unique_lock<std::mutex> ul(readyMutex);
  //  while(!readyFlag){
  //    readyCondVar.wait(ul);
  //  }
  //}//release lock

  //do whatever shall happen after threadA has prepared things
  std::cout<<"done"<<std::endl;
}

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
  //push different values(val til val+5 with timeouts of val milliseconds) into the queue
  for(int i=0;i<6;++i){
    {
      std::lock_guard<std::mutex> lg(queueMutex);
      queue.push(val+i);
    }//release lock
    queueCondVar.notify_one();

    std::this_thread::sleep_for(std::chrono::milliseconds(val));
  }
}

int count=0;

void consumer(int num)
{
  //pop values if available(num identifies the consumer)
  while(count!=18&&count!=17){
    int val;
    {
      std::unique_lock<std::mutex> ul(queueMutex);
      queueCondVar.wait(ul,[](){return !queue.empty();});
      val=queue.front();
      queue.pop();
      count++;
    }//release lock
    std::cout<<count<<": "<<"consumer "<<num<<": "<<val<<std::endl;
  }
}

std::atomic<bool> atomicReadyFlag(false);

void thread3()
{
  //do something thread4 needs as preparation
  std::cout<<"thread3 is doing for thread4"<<std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  atomicReadyFlag.store(true);

  //for C-style code:
  //std::atomic<bool> readyFlag;
  //...
  //std::atomic_init(&readyFlag,false);
}

void thread4()
{
  //wait until atomicReadyFlag is true(thread3 is done)
  while(!atomicReadyFlag.load()){
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  //do whatever shall happen after thread3 has prepared things
  std::cout<<"call thread4"<<std::endl;
}

long data;
std::atomic<bool> rFlag(false);

void provider1()
{
  //after reading a character
  std::cout<<"<return>"<<std::endl;
  std::cin.get();

  //provide some data
  data=42;

  //and signal readiness
  rFlag.store(true);//equal rFlag.store(true,std::memory_order_seq_cst)
  //or rFlag.store(true,std::memory_order_release)

  //ERROR: undefined behavior:
  //data=42;
  //rFlag.store(true,std::memory_order_relaxed);
}

void consumer1()
{
  //wait for readiness and do something else
  while(!rFlag.load()){//equal rFlag.load(std::memory_order_seq_cst)
    //or rFlag.load(std::memory_order_accquire)
    std::cout.put('.').flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  //and process provided data
  std::cout<<"\nvalue: "<<data<<std::endl;
}

std::atomic<long> data1(0);
std::atomic<bool> rFlag1(false);

void provider2()
{
  std::cout<<"<return>"<<std::endl;
  std::cin.get();

  //providing thread:
  data1.store(44,std::memory_order_relaxed);
  rFlag1.store(true,std::memory_order_relaxed);
}

void consumer2()
{
  //consuming thread:
  while(!rFlag1.load(std::memory_order_relaxed)){
    std::cout.put('*').flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  std::cout<<data1.load(std::memory_order_relaxed)<<std::endl;
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

  std::thread t1(doSomeOtherthing,5,'.');
  std::thread t2(doSomeOtherthing,5,'+');
  std::thread t3(doSomeOtherthing,5,'*');
  std::cout<<"t3 ID:       "<<t3.get_id()<<std::endl;
  std::cout<<"main ID:     "<<std::this_thread::get_id()<<std::endl;
  std::cout<<"nothread ID: "<<std::thread::id()<<std::endl;

  t1.join();
  t2.join();
  t3.join();
  std::cout<<std::endl;

  std::thread master(doAnotherSomething);
  masterThreadID=master.get_id();

  std::thread slave(doAnotherSomething);

  master.join();
  slave.join();

  //18.2.2 Promise

  try{
    //start thread using a promise to store the outcome
    std::promise<std::string> p;//hold string result or exception
    std::thread t(doYetAnotherThing,std::ref(p));
    t.detach();

    //create a future to process the outcome
    std::future<std::string> f(p.get_future());//can before thread started!

    //process the outcome
    std::cout<<"result: "<<f.get()<<std::endl;
  }
  catch(const std::exception& e){
    std::cerr<<"EXCEPTION: "<<e.what()<<std::endl;
  }
  catch(...){
    std::cerr<<"EXCEPTION "<<std::endl;
  }

  //18.2.3 Class packaged_task<>

  std::future<double> f8=std::async(compute,7,5);//try to start a background task

  double res=f8.get();//wait for its end and process result/exception

  std::cout<<res<<std::endl;

  std::packaged_task<double(int,int)> task(compute);//create a task
  std::future<double> f9=task.get_future();//get its future

  task(8,6);//start the task(typically in a separate thread)
  double res1=f9.get();//wait for its end and process result/exception
  std::cout<<res1<<std::endl;

  //18.3.1 细说async()

  //future async(std::launch::aync,F func,args...)
  //尝试启动func并给予实参args，形成一个异步任务（asynchronous task；一个并行线程）
  //如果以上办不到，就抛出std::system_error异常，带着差错码std::errc::resource_unavailable_try_again
  //被启动的线程保证在程序结束前完成，除非程序中途失败(abort)
  //以下情况会结束线程（完成工作）：
  //-对返回的future调用get()或wait()
  //-如果最后一个指向“返回之future所代表的shared state”的object被销毁
  //这意味着对async()的调用会造成停滞(block)直到func完成——如果async()的返回值未被使用的话

  //future async(std::launch::deferred,F func,args...)
  //传递func并夹带实参args，形成一个推迟任务(deferred task)。当我们对返回的future调用wait()或get()，那个推迟任务即被同步调用(synchronously called)
  //如果未曾如上调用wait()和get()，那个推迟任务(deferred task)绝不会启动

  //future async(F func,args...)
  //相当于调用async()并携带“std::launch::async和std::launch::deferred组合而成”的launch（发射）策略。系统会根据当前形势选择其中一个发射策略。也就是说，如果“立即发射”策略行不通的话，会造成func被推迟调用
  //也就是说，如果async()可以为func启动一个新线程，就那么做，否则func就会被推迟，直到我们对返回的future调用get()或wait()
  //这个调用的唯一保证是，一旦我们对返回的future调用get()或wait()，func就一定会被调用并且完成
  //如果没有对返回的future调用get()或wait()，func有可能永不被调用
  //注意，如果无法异步调用func，本形式的async()不会抛出system_error异常（但有可能因为其他原因而抛出system error）

  //18.3.2 细说Future
  //18.3.3 细说Shared Future

  //try{
  //  shared_future<void> sp=async(f);
  //  sp.get();
  //}
  //catch(E& e){
  //  e.modify();//risk of undefined behavior due to a data race
  //}

  //18.3.4 细说Class std::promise
  //18.3.5 细说Class std::packaged_task
  //18.3.6 细说Class std::thread

  //unsigned int std::thread::hardware_concurrency()
  //返回可能的线程数量
  //该数量只是个参考值，不保证准确
  //如果数量不可计算或不明确，返回值是0

  //18.3.7 Namespace this_thread

  //while(!readyFlag){//loop until data is ready
  //  std::this_thread::yield();
  //}

  //18.4 线程同步化与Concurrency（并发）问题
  //18.4.1 当心Concurrency（并发）
  //18.4.2 Concurrent Data Access为什么造成问题
  //18.4.3 什么情况下可能出错
  //18.4.4 解决问题所需要的性质(Feature)

  //18.5 Mutex和Lock
  //18.5.1 使用Mutex和Lock

  int val=1000;
  std::mutex valMutex;//control exclusive access to val

  valMutex.lock();//request exclusive access to val
  if(val>=0){
    foo(val);//val is positive
  }
  else{
    foo(-val);//pass negated negative val
  }
  valMutex.unlock();//release exclusive access to val

  //another thread may access to val
  valMutex.lock();//request exclusive access to val
  ++val;
  valMutex.unlock();//release exclusive access to val

  int val1=100;
  std::mutex valMutex1;//control exclusive access to val1

  std::lock_guard<std::mutex> lg(valMutex1);//lock and automatically unlock
  if(val1>=0){
    foo(val1);//val1 is positive
  }
  else{
    foo(-val1);//pass negated negative val1
  }

  int val2=10;
  std::mutex valMutex2;//control exclusive access to val2

  {
    std::lock_guard<std::mutex> lg(valMutex2);//lock and automatically unlock
    if(val2>=0){
      foo(val2);//val2 is positive
    }
    else{
      foo(-val2);//pass negated negative val2
    }
  }//ensure that lock gets released here

  {
    std::lock_guard<std::mutex> lg(valMutex2);//lock and automatically unlock
    ++val2;
    std::cout<<val2<<std::endl;
  }//ensure that lock gets released here

  auto f10=std::async(std::launch::async,
                      print,"Hello from a first thread");
  auto f11=std::async(std::launch::async,
                      print,"Hello from a second thread");
  print("Hello from the main thread");

  DatabaseAccess dba;
  dba.createTableAndInsertData();

  DatabaseAccess1 dba1;
  dba1.createTableAndInsertData();

  std::mutex m;

  //try to acquire a lock and do other stuff while this isn't possible
  while(m.try_lock()==false){
    doSomeOtherStuff();
  }
  std::lock_guard<std::mutex> lg1(m,std::adopt_lock);

  std::timed_mutex tm;

  //try for one second to acquire a lock
  if(tm.try_lock_for(std::chrono::seconds(1))){
    std::lock_guard<std::timed_mutex> lg(tm,std::adopt_lock);
    std::cout<<"have get the lock"<<std::endl;
  }
  else{
    couldNotGetTheLock();
  }

  std::mutex m1;
  std::mutex m2;
  //...
  {
    std::lock(m1,m2);//lock both mutexes(or none if not possible)
    std::lock_guard<std::mutex> lockM1(m1,std::adopt_lock);
    std::lock_guard<std::mutex> lockM2(m2,std::adopt_lock);
    //...
    std::cout<<"m1 m2 are both locked"<<std::endl;
  }//automatically unlock all mutexes

  std::mutex m3;
  std::mutex m4;

  int idx=std::try_lock(m1,m2);//try to lock both mutexes
  if(idx<0){//both locks succeeded
    std::lock_guard<std::mutex> lockM3(m3,std::adopt_lock);
    std::lock_guard<std::mutex> lockM4(m4,std::adopt_lock);
    //...
  }//automatically unlock all mutexes
  else{
    //idx has zero-based index of first failed lock
    std::cerr<<"could not lock mutex m"<<idx+1<<std::endl;
  }

  std::mutex m5;
  std::mutex m6;
  //...
  {
    std::lock(m5,m6);//lock both mutexes(or none if not possible)
    //no lock adopted
    //...
  }
  //... OOPS:mutexes are still locked!!!

  std::mutex m7;
  std::unique_lock<std::mutex> lock(m7,std::try_to_lock);
  //...
  if(lock){//if lock was successful
    std::cout<<"lock successful"<<std::endl;
  }

  std::timed_mutex m8;
  std::unique_lock<std::timed_mutex> lock1(m8,std::chrono::seconds(1));
  //...
  if(lock1){//if lock was successful
    std::cout<<"lock1 successful"<<std::endl;
  }

  std::mutex m9;
  std::unique_lock<std::mutex> lock2(m9,std::defer_lock);
  //...
  lock2.lock();//or(timed)try_lock();
  //...
  if(lock2){//if lock was successful
    std::cout<<"lock2 successful"<<std::endl;
  }

  std::mutex m10;
  std::mutex m11;

  std::unique_lock<std::mutex> lockM5(m10,std::defer_lock);
  std::unique_lock<std::mutex> lockM6(m11,std::defer_lock);
  //...
  std::lock(m10,m11);//lock both mutexes(or none if not possible)

  auto f12=std::async(thread1);
  auto f13=std::async(thread2);

  f12.get();
  f13.get();

  //18.5.2 细说Mutex和Lock

  //Class std::mutex，同一时间只可被一个线程锁定。如果它被锁住，任何其他lock()都会阻塞(block)，直到这个mutex再次可用，且try_lock()会失败
  //Class std::recursive_mutex，充许在同一时间多次被同一线程获得其lock。其典型应用是：函数捕获一个lock并调用另一函数而后者再次捕获相同的lock
  //Class std::timed_mutex，额外充许你传递一个时间段或时间点，用来定义多长时间内它可以尝试捕捉一个lock。为此它提供了try_lock_for()和try_lock_until()
  //Class std::recursive_timed_mutex 允许同一线程多次取得其lock，可指定期限

  //18.5.3 只调用一次

  bool initialized=false;//global flag
  //...
  if(!initialized){//initialize if not initialized yet
    initialize();
    initialized=true;
  }

  bar();

  std::once_flag oc;//global flag
  //...
  std::call_once(oc,initialize);//initialize if not initialized yet

  foo1();

  Y y;
  y.getData();

  //18.6 Condition Variable（条件变量）
  //18.6.1 Condition Variable（条件变量）的意图
  //18.6.2 Condition Variable（条件变理）的第一个完整例子

  auto f14=std::async(std::launch::async,threadA);
  auto f15=std::async(std::launch::async,threadB);

  f14.get();
  f15.get();
  //18.6.3 使用Condition Variable（条件变量）实现多线程Queue

  //start three providers for values 100+, 300+, and 500+
  auto p1=std::async(std::launch::async,provider,100);
  auto p2=std::async(std::launch::async,provider,300);
  auto p3=std::async(std::launch::async,provider,500);

  //start two consumers printing the values
  auto c1=std::async(std::launch::async,consumer,1);
  auto c2=std::async(std::launch::async,consumer,2);

  p1.get();
  p2.get();
  p3.get();
  c1.get();
  c2.get();

  //18.6.4 细说Condition Variable（条件变量）
  //18.7 Atomic
  //18.7.1 Atomic用例

  auto f16=std::async(std::launch::async,thread3);
  auto f17=std::async(std::launch::async,thread4);

  f16.get();
  f17.get();

  std::atomic<bool> ab(false);
  ab=true;
  if(ab){
    std::cout<<std::boolalpha<<ab<<std::endl;
  }

  std::atomic<int> ai(0);
  std::cout<<ai<<std::endl;
  int x1=ai;
  std::cout<<x1<<std::endl;
  ai=10;
  std::cout<<ai<<std::endl;
  ai++;
  std::cout<<ai<<std::endl;
  ai-=17;
  std::cout<<ai<<std::endl;

  //start provider and consumer
  auto p4=std::async(std::launch::async,provider1);
  auto c3=std::async(std::launch::async,consumer1);

  p4.get();
  c3.get();

  //18.7.2 细说Atomic及其高级接口
  //18.7.3 Atomic的C-Style接口

  std::atomic_bool ab1;//equivalent to: std::atomic<bool> ab
  std::atomic_init(&ab1,false);
  //...
  std::atomic_store(&ab1,true);//equivalent to: ab1.store(true);
  //...
  if(std::atomic_load(&ab1)){//equivalent to: if(ab1.load())
    std::cout<<std::boolalpha<<ab1<<std::endl;
  }

  //18.7.4 Atomic的低层接口

  auto p5=std::async(std::launch::async,provider2);
  auto c4=std::async(std::launch::async,consumer2);

  p5.get();
  c4.get();

  return 0;
}
