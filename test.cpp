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

template<typename... Args>
void foofoo(const std::tuple<Args...> t)
{
  std::cout<<"call foofoo" <<std::endl;
}

std::tuple<int,int,int> barbar(){
  std::cout<<"call barbar"<<std::endl;
  return {1,2,3};//error,but now OK
}

std::vector<int> foobar(){
  std::cout<<"call foobar"<<std::endl;
  return {1,2,3};//OK
}

std::tuple<int,int,int> barfoo(){
  std::cout<<"call barfoo"<<std::endl;
  return std::make_tuple(1,2,3);
}





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

  f(std::make_pair(42,"empty"));//pass two values as pair
  g(std::make_pair(42,"chair"));//pass two values as pair with type conversions

  f({42,"empty"});//pass two values as pair
  g({42,"chair"});//pass two values as pair with type conversions

  std::pair<int,float>(42,7.77);//pair<int,float>
  std::make_pair(42,7.77);//pair<int,double>

  std::string s("hello");
  std::string t1("world");

  auto pp = std::make_pair(std::move(s),std::move(t1));
  //s and t1 are no longer used
  //auto pp = std::make_pair(s,t1);

  std::cout<<s<<std::endl<<t1<<std::endl;
  std::cout<<pp<<std::endl;

  int i = 0;
  auto ppp=std::make_pair(std::ref(i),std::ref(i));//creates pair<int&, int&>

  ++ppp.first;//increments i
  ++ppp.second;//increments i again
  std::cout << "i: " << i << std::endl;//print i:2

  std::pair<char,char> pt=std::make_pair('x','y');//pair of two chars
  char c;
  std::tie(std::ignore,c)=pt;//extract second value into c(ignore first one)
  std::cout << c <<std::endl;

  //5.1.2 Tuple(不定数的值组)
  //crate a four-element tuple
  //- elements are initialized with default value(0 for fundamental types)
  std::tuple<std::string, int, int, std::complex<double>> tt;

  //create and initialize a tuple explicitly
  std::tuple<int, float, std::string> tt1(41,6.3,"nico");

  //"iterate" over elements:
  std::cout<<std::get<0>(tt1)<<" ";
  std::cout<<std::get<1>(tt1)<<" ";
  std::cout<<std::get<2>(tt1)<<" ";
  std::cout<<std::endl;

  //crate tuple with make_tuple()
  //- auto declares tt2 with type of right-hand side
  //- thus, type of tt2 is tuple
  auto tt2 = std::make_tuple(22,44,"nico");//tuple<int,int,const char*)

  //assign second value in tt2 to tt1
  std::get<1>(tt1)=std::get<1>(tt2);

  //comparison and assignment
  //- include type conversion from tuple<int, int, const char*>
  // to tuple<int, float, string>
  if(tt1>tt2){//compares value for value
    tt1 = tt2;//OK, assigns value for value
  }
  std::string ss;
  std::make_tuple(std::ref(s));//yields type tuple<string&>, where the element refers to ss
  std::string s0("old value");
  std::cout << s0 << std::endl;

  auto x0=std::make_tuple(s0);//x0 is of type tuple<string>
  std::get<0>(x0) = "my value";//modifies x0 but not s0
  std::cout << s0 << std::endl;


  auto y0=std::make_tuple(std::ref(s0));//y0 is of type tuple<string&>, thus y0 refers to s0
  std::cout<<s0<<std::endl;
  std::get<0>(y0) = "my value";//modifies y0
  std::cout << s0 << std::endl;

  std::tuple<int,float,std::string> ttt(77,1.1,"more light");
  int iii;
  float fff;
  std::string sss;
  //assign values of ttt to iii, fff, and sss;
  auto z0=std::make_tuple(std::ref(iii),std::ref(fff),std::ref(sss))=ttt;
  

  iii = 11111;
  fff = 7.7777;
  sss = "less light";

  std::cout<<std::get<0>(z0)<<std::endl;
  std::cout<<std::get<1>(z0)<<std::endl;
  std::cout<<std::get<2>(z0)<<std::endl;

  auto w0=std::tie(iii,std::ignore,sss)=ttt;//assigns first and third value of ttt to iii and sss
  iii = 222;
  fff = 6.666;
  sss = "Hello world!";

  std::cout<<std::get<0>(w0)<<std::endl;
  //std::cout<<std::get<1>(w0)<<std::endl;
  std::cout<<std::get<2>(w0)<<std::endl;

  std::cout<<std::get<0>(z0)<<std::endl;
  std::cout<<std::get<1>(z0)<<std::endl;
  std::cout<<std::get<2>(z0)<<std::endl;

  //foofoo(42);//error: explicit conversion to tuple<> required
  foofoo(std::make_tuple(42));//OK

  std::tuple<int,double> xt1(42,3.14);//OK, old syntax
  std::tuple<int,double> xt2{42,3.14};//OK, new syntax
  std::tuple<int,double> xt3 = {42,3.14};//error,but now OK

  std::vector<std::tuple<int,float>> v{{1,1.0},{2,2.0}};//error, but now OK

  barbar();
  std::vector<std::pair<int,float>> v1{{1,1.1},{2,2.1}};//OK
  std::vector<std::vector<float>> v2{{1,1.1111},{2,2.2222}};//OK
  foobar();

  std::vector<std::tuple<int,float>> v3{std::make_tuple(1,1.13454),
      std::make_tuple(2,2.34435)};//OK
  barfoo();

  typedef std::tuple<int,float,std::string> TupleType;
  std::cout<<std::tuple_size<TupleType>::value<<std::endl;//yields 3
  std::cout<<typeid(std::tuple_element<1,TupleType>::type).name()<<std::endl;//yields float

  int nn=1000;
  auto tq=std::tuple_cat(std::make_tuple(42,7.7,"hello"),std::tie(nn));
  std::cout<<std::get<0>(tq)<<std::endl;
  std::cout<<std::get<1>(tq)<<std::endl;
  std::cout<<std::get<2>(tq)<<std::endl;
  std::cout<<std::get<3>(tq)<<std::endl;
  nn = 2000000;
  std::cout<<std::get<3>(tq)<<std::endl;

  //5.1.3 Tuple的输入/输出
  














  return 0;
}
