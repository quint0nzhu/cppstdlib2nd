/*
  author: Quinton
  date: 2018-4-24
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter4
*/

#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <bitset>
#include <complex>
#include <limits>
#include <functional>
#include <map>
#include <typeinfo> //for bad_cast and bad_typeid
#include <exception> //for classes exception and bad_exception
#include <stdexcept> //for most logic and runtime error classes
#include <system_error> //for system errors(since C++11)
#include <new> //for out-of-memory exceptions
#include <ios> //for I/O exceptions
#include <future> //for errors with async() and futures(since C++11),-lpthread


template <typename T>
void processCodeException(const T& e)
{
  using namespace std;
  auto c = e.code();
  cerr <<"- category:        " << c.category().name()<<endl;
  cerr <<"- value:           " << c.value()<<endl;
  cerr <<"- msg:             " << c.message()<<endl;
  cerr <<"- def category:    " << c.default_error_condition().category().name() << endl;
  cerr <<"- def value:       " << c.default_error_condition().value()<<endl;
  cerr <<"- def msg:         " << c.default_error_condition().message()<<endl;
}

void processException()
{
  using namespace std;
  try{
    throw;//rethrow exception to deal with here
  }
  catch (const ios_base::failure& e){
    cerr << "I/O EXCEPTION: " << e.what() << endl;
    processCodeException(e);
  }
  catch (const system_error& e){
    cerr << "SYSTEM EXCEPTION: " << e.what() << endl;
    processCodeException(e);
  }
  catch (const future_error& e){
    cerr << "FUTURE EXCEPTION: " << e.what() << endl;
    processCodeException(e);
  }
  catch (const bad_alloc& e){
    cerr << "BAD ALLOC EXCEPTION: " << e.what() << endl;
  }
  catch (const exception& e){
    cerr << "EXCEPTION: " << e.what() << endl;
  }
  catch (...) {
    cerr << "EXCEPTION (unknown)" << endl;
  }
}

std::exception_ptr eptr;//object to hold exceptions(or nullptr)

void foo()
{
  try {
    throw new std::exception();
  }
  catch(...){
    eptr = std::current_exception();//save exception for later processing
  }
}

void bar()
{
  if(eptr != nullptr){
    std::cout << "in bar() rethrow" << std::endl;
    std::rethrow_exception(eptr);//process saved exception
  }
}

class myexp : public std::exception{
public:
  const char* what()const noexcept{
    std::cout<<"This is myexp!" <<std::endl;
  }
};

int func(int x, int y)
{
  std::cout << "func(int x, int y) is called"<<std::endl;
  return x+y;
}

auto l = [](int x, int y)->int{
  std::cout<<"lambda [](int x, int y)->int is called" << std::endl;
  return x+y;
};

class C{
public:
  int operator()(int x, int y) const{
    std::cout<<"operator() is called"<<std::endl;
    return x+y;
  }
  int memfunc(int x, int y)const{
    std::cout<<"member function is called"<<std::endl;
    return x+y;
  }
};


int main()
{
  //4.1命名空间(Namespace) std
  //using declaration
  //using std::cout;
  //using directive
  //using namespace std;
  std::cout << std::hex << 15 << std::endl;

  //4.2头文件(Head File)
  //#include <cstdlib> // was:<stdlib.h>

  //4.3差错和异常(Error and Exception)的处理
  //4.3.1标准的Exception Class(异常类)


  //4.3.2异常类(Exception Class)的成员
  //what()或者code()
  try {
    throw std::exception();
  }
  catch(...){
    processException();
  }

  //4.3.3以Class exception_ptr传递异常

  try{
    foo();
  }
  catch(...){
    throw;
  }

  try{
    bar();
  }
  catch(...){
    processException();
  }

  //4.3.4抛出标准异常
  try{
    throw std::out_of_range("out_of_range at somewhere, somehow");
  }
  catch(...){
    processException();
  }

  try{
    throw std::system_error(std::make_error_code(std::errc::invalid_argument),
                            "argument ... is not valid");
  }
  catch(...){
    processException();
  }

  //4.3.5自标准异常类派生
  try{
    throw myexp();
  }
  catch(const myexp& e){
    e.what();
  }

  //4.4 Callable Object(可被调用的对象)
  C c;
  std::shared_ptr<C> sp(new C);

  //bind() uses callable objects to bind arguments:
  std::bind(func,77,33)();//calls:func(77,33)
  std::bind(l,66,22)();//calls:l(66,22)
  std::bind(C(),55,11)();//calls:C::operator()(55,11)
  std::bind(&C::memfunc,c,44,44)();//calls:c.memfunc(44,44)
  std::bind(&C::memfunc,sp,33,55)();//calls:sp->memfunc(33,55)

  //async() uses callable objects to start (background) tasks:
  std::async(func,42,77);//calls:func(42,77)
  std::async(l,32,77);//calls:l(32,77)
  std::async(c,22,77);//calls:c.operator()(22,77)
  std::async(&C::memfunc,&c,12,77);//calls:c.memfunc(12,77)
  std::async(&C::memfunc,sp,2,77);//calls:sp->memfunc(2,77)

  //4.5并发与多线程
  //标准库对象不是线程安全的，除非它被明确指定为sharable without data races，或加锁
  //并发的只读访问是允许的，并发处理同一容器内的不同元素是可以的(除了vector<bool>)
  //atexit()和at_quick_exit()的并发调用是同步的。
  //默认分配器的所有成员函数，除了析构函数，其并发处理都被同步(synchronized)

  //4.6分配器(Allocator)
  //default allocator调用new和delete操作符，决大多数情况下都使用它
  return 0;
}
