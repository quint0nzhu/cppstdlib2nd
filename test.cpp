/*
  author: Quinton
  date: 2018-4-24
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter5
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
#include <utility>







//generic output operator for pairs(limited solution)
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& strm,
                         const std::pair<T1, T2>& p)
{
  return strm<<"["<<p.first<<","<<p.second<<"]";
}

void f(std::pair<int, const char*>)
{
}

void g(std::pair<const int, std::string>)
{
}

class A
{
public:
  A(){}
  A(A&){}//copy constructor with nonconstant reference
};

class Foo {
public:
  Foo(std::tuple<int, float>){
    std::cout<<"Foo::Foo(tuple)"<<std::endl;
  }
  template<typename... Args>
  Foo(Args... args){
    std::cout<<"Foo::Foo(args...)"<<std::endl;
  }
  Foo(int,float){
    std::cout<<"Foo:Foo(int,float)"<<std::endl;
  }
};











int main()
{
  //5通用工具
  //5.1Pair和Tuple
  //5.1.1 Pair
  typedef std::pair<int, float> IntFloatPair;
  IntFloatPair p(42,3.14);

  std::cout <<p<<std::endl;

  std::cout<<std::get<0>(p)<<std::endl;//yields p.first
  std::cout<<std::get<1>(p)<<std::endl;//yields p.second
  std::cout<<std::tuple_size<IntFloatPair>::value<<std::endl;//yields 2
  std::cout<<typeid(std::tuple_element<0,IntFloatPair>::type).name()<<std::endl;//yields int
  std::pair<int, float> p1;
  std::cout<<p1<<std::endl;

  std::pair<int, const char*> p2(42, "hello");
  f(p2);//OK:calls implicitly generated copy constructor
  g(p2);//OK:calls template constructor

  //std::pair<A,int> p3;//Error since C++11

  //create tuple t;
  std::tuple<int,float> t(1,2.22);

  //pass the tuple as a whole to the constructor of Foo:
  std::pair<int,Foo> p4(42,t);

  //pass the elements of the tuple to the constructor of Foo:
  std::pair<int,Foo> p5(std::piecewise_construct,std::make_tuple(42),t);


  return 0;
}
