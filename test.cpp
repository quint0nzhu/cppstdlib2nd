/*
  author: Quinton
  date: 2018-11-27
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 15
*/


#include <iostream>
#include <bitset>
#include <complex>
#include <iomanip>
#include <chrono>



int main(int argc, char* argv[])
{
  //第15章 以Stream完成I/O
  //15.1 I/O Stream的共通基础
  //15.1.1 Stream对象
  //15.1.2 Stream Class
  //15.1.3 全局的Stream对象
  //15.1.4 Stream操作符

  int a,b;

  //as long as input of a and b is successful
  //while(std::cin>>a>>b){
    //output a and b
  //  std::cout<<"a: "<<a<<" b: "<<b<<std::endl;
  //}

  //15.1.5 操控器(Manipulator)
  //15.1.6 一个简单例子

  double x,y;//operands

  //print header string
  std::cout<<"Multiplication of two floating point values"<<std::endl;

  //read first operand
  std::cout<<"first operand: ";
  if(!(std::cin>>x)){
    //input error
    //=>error message and exit program with error status
    std::cerr<<"error while reading the first floating value"<<std::endl;
    return EXIT_FAILURE;
  }

  //read second operand
  std::cout<<"second operand: ";
  if(!(std::cin>>y)){
    //input error
    //=>error message and exit program with error status
    std::cerr<<"error while reading the second floating value"<<std::endl;
    return EXIT_FAILURE;
  }

  //print operands and result
  std::cout<<x<<" times "<<y<<" equals "<<x*y<<std::endl;

  //15.2 基本Stream Class和其对象
  //15.2.1 Class及其层次体系
  //15.2.2 全局性的Stream对象
  //15.2.3 头文件

  //15.3 标准的Stream操作符<<和>>
  //15.3.1 Output操作符<<

  int i=7;
  std::cout<<i<<std::endl;//outputs:7

  float f=4.5;
  std::cout<<f<<std::endl;//outputs:4.5

  std::string s("hello");
  s+=", world";
  std::cout<<s<<std::endl;//outputs: hello, world

  std::bitset<10> flags(7);
  std::cout<<flags<<std::endl;//outputs:0000000111

  std::complex<float> c(3.1,7.4);
  std::cout<<c<<std::endl;//outputs:(3.1,7.4)

  //15.3.2 Input操作符>>

  int i1;
  std::cin>>i1;//reads an int from standard input and stores it in i1

  float f1;
  std::cin>>f1;//reads a float from standard input and stores it in f1

  float f2;
  std::complex<double> c1;

  std::cin>>f2>>c1;

  std::cout<<i1<<std::endl;
  std::cout<<f1<<std::endl;
  std::cout<<f2<<std::endl;
  std::cout<<c1<<std::endl;

  //15.3.3 特殊类型的I/O

  char* cstring="hello";

  std::cout<<"string \""<<cstring<<"\" is located at address: "
           <<static_cast<void*>(cstring)<<std::endl;

  //process and print current date and time:
  auto now=std::chrono::system_clock::now();
  time_t t=std::chrono::system_clock::to_time_t(now);
  tm* nowTM=localtime(&t);
  std::cout<<std::put_time(nowTM,"date: %x\ntime: %X\n")<<std::endl;

  //read date:
  tm* date;
  std::cout<<"new date: ";
  std::cin>>std::get_time(date,"%x");//read date
  if(!std::cin){
    std::cerr<<"invalid format read"<<std::endl;
  }

  //15.4 Stream的状态(State)
  //15.4.1 表示“Stream状态”的常量
  //15.4.2 用来“处理Stream状态”的成员函数

  //check whether failbit is set
  if(std::cin.rdstate()&std::ios::failbit){
    std::cout<<"failbit was set"<<std::endl;

    //clear only failbit
    std::cin.clear(std::cin.rdstate()&~std::ios::failbit);
  }

  //clear all error flags(including eofbit):
  std::cin.clear();

  //15.4.3 Stream状态与Boolean条件测试

  //while the standard input stream is OK
  if(std::cin){
    std::cout<<"cin is ok!"<<std::endl;
  }

  if(std::cin>>i){
    //reading i was successful
    std::cout<<i<<std::endl;
  }

  //as long as i can be read
  while(std::cin>>i){
    //process i(in this case, simply output it)
    std::cout<<i<<std::endl;
  }

  std::cin>>i;
  if(std::cin.fail()){
    std::cout<<"read i error!"<<std::endl;
  }

  //15.4.4 Stream的状态和异常



  return 0;
}
