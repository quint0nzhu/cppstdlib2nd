/*
  author: Quinton
  date: 2018-12-7
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 17
*/


#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>
#include <complex>
#include <limits>


void printNumbers(std::default_random_engine& dre)
{
  for(int i=0;i<6;++i){
    std::cout<<dre()<<" ";
  }
  std::cout<<std::endl;
}

template<typename Distr,typename Eng>
void distr(Distr d,Eng e,const std::string& name)
{
  //print min, max and four example values
  std::cout<<name<<":"<<std::endl;
  std::cout<<"-min(): "<<d.min()<<std::endl;
  std::cout<<"-max(): "<<d.max()<<std::endl;
  std::cout<<"-values: "<<d(e)<<' '<<d(e)<<' '
           <<d(e)<<' '<<d(e)<<std::endl;

  //count the generated values(converted to integral values)
  std::map<long long,int> valuecounter;
  for(int i=0;i<200000;++i){
    valuecounter[d(e)]++;
  }

  //and print the resulting distribution
  std::cout<<"===="<<std::endl;
  for(auto elem:valuecounter){
    std::cout<<std::setw(3)<<elem.first<<": "
             <<elem.second<<std::endl;
  }
  std::cout<<"===="<<std::endl;
  std::cout<<std::endl;
}

int main(int argc, char* argv[])
{
  //第17章 数值
  //17.1 随机数及分布(Random Number and Distribution)
  //一个引擎和一个分布的组合

  //17.1.1 第一个例子

  //create default engine as source of randomness
  std::default_random_engine dre;

  //use engine to generate integral numbers between 10 and 20(both included)
  std::uniform_int_distribution<int> di(10,20);
  for(int i=0;i<20;++i){
    std::cout<<di(dre)<<" ";
  }
  std::cout<<std::endl;

  //use engine to generate floating-point numbers between 10.0 and 20.0
  //(10.0 included, 20.0 not included)
  std::uniform_real_distribution<double> dr(10,20);
  for(int i=0;i<8;++i){
    std::cout<<dr(dre)<<" ";
  }
  std::cout<<std::endl;

  //unsigned int seed=...;//process some value really random
  //std::default_random_engine dre(seed);//and use it for the initial engine state

  //use engine to shuffle elements
  std::vector<int> v={1,2,3,4,5,6,7,8,9};

  std::shuffle(v.begin(),v.end(),//range
               dre);//source of randomness
  for(int i=0;i<v.size();++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<std::endl;

  std::shuffle(v.begin(),v.end(),//range
               std::default_random_engine());//random-number generator
  for(int i=0;i<v.size();++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<std::endl;

  std::shuffle(v.begin(),v.end(),//range
               std::default_random_engine());//random-number generator
  for(int i=0;i<v.size();++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<std::endl;

  std::shuffle(v.begin(),v.end(),//range
               dre);//random-number generator
  for(int i=0;i<v.size();++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<std::endl;

  std::shuffle(v.begin(),v.end(),//range
               dre);//random-number generator
  for(int i=0;i<v.size();++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<std::endl;

  //17.1.2 引擎(Engine)

  //create engine and generate numbers
  std::default_random_engine dre1;
  printNumbers(dre1);

  //create equal engine and generate numbers
  std::default_random_engine dre2;//same initial state as dre
  printNumbers(dre2);

  //create engine with initial state specified by a seed
  std::default_random_engine dre3(42);
  printNumbers(dre3);

  //save state of engine dre1
  std::stringstream engineState;
  engineState<<dre1;

  //generate numbers according to current state of dre1
  printNumbers(dre1);

  //restore saved state of engine dre1 and create numbers again
  engineState>>dre1;
  printNumbers(dre1);

  //restore saved state of engine dre1, skip 2 numbers and create numbers again
  engineState.clear();//clear EOF bit
  engineState.seekg(0);//and move read position to the beginning
  engineState>>dre1;
  dre1.discard(2);
  printNumbers(dre1);

  //17.1.3 细说引擎(Engine)
  //17.1.4 分布(Distribution)

  std::uniform_int_distribution<> d(0,20);//initialize parameters "a" and "b"
  std::cout<<d.a()<<std::endl;//yields value of parameter "a"
  std::cout<<d.b()<<std::endl;//yields value of parameter "b"
  std::cout<<d.param().a()<<std::endl;//yields value of parameter "a"
  std::cout<<d.param().b()<<std::endl;//yields value of parameter "b"

  std::uniform_int_distribution<>::param_type pt(100,200);//other parametrization
  std::cout<<d(dre,pt)<<std::endl;//generates one value according to parametrization pt
  d.param(pt);//let all generated values use parametrization pt
  std::cout<<d(dre)<<std::endl;

  std::knuth_b e;

  std::uniform_real_distribution<> ud(0,10);
  distr(ud,e,"uniform_real_distribution");

  std::normal_distribution<> nd;
  distr(nd,e,"normal_distribution");

  std::exponential_distribution<> ed;
  distr(ed,e,"exponential_distribution");

  std::gamma_distribution<> gd;
  distr(gd,e,"gama_distribution");

  //17.1.5 细说分布(Distribution)

  //17.2 复数(Complex Number)
  //17.2.1 Class complex<> 一般性质
  //17.2.2 Class complex<> 运用实例

  //complex number with real and imaginary parts
  //-real part:4.0
  //-imaginary part:3.0
  std::complex<double> c1(4.0,3.0);

  //create complex number from polar coordinates
  //-magnitude:5.0
  //-phase angle:0.75
  std::complex<float> c2(std::polar(5.0,0.75));

  //print complex numbers with real and imaginary parts
  std::cout<<"c1: "<<c1<<std::endl;
  std::cout<<"c2: "<<c2<<std::endl;

  //print complex numbers as polar coordinates
  std::cout<<"c1: magnitude: "<<abs(c1)
           <<" (squared magnitude: "<<norm(c1)<<") "
           <<" phase angle: "<<arg(c1)<<std::endl;
  std::cout<<"c2: magnitude: "<<abs(c2)
           <<" (squared magnitude: "<<norm(c2)<<") "
           <<" phase angle: "<<arg(c2)<<std::endl;

  //print complex conjugates
  std::cout<<"c1 conjugated: "<<conj(c1)<<std::endl;
  std::cout<<"c2 conjugated: "<<conj(c2)<<std::endl;

  //print result of a computation
  std::cout<<"4.4+c1*1.8: "<<4.4+c1*1.8<<std::endl;

  //print sum of c1 and c2:
  //-note: different types
  std::cout<<"c1+c2: "
           <<c1+std::complex<double>(c2.real(),c2.imag())<<std::endl;

  //add square root of c1 to c1 and print the result
  std::cout<<"c1+=sqrt(c1): "<<(c1+=sqrt(c1))<<std::endl;

  std::complex<long double> c3,c4;
  std::cout<<"complex number c3: ";

  while(std::cin.peek()!=EOF){

    //read first complex number
    std::cin>>c3;
    if(!std::cin){
      std::cerr<<"input error"<<std::endl;
      return EXIT_FAILURE;
    }

    //read second complex number
    std::cout<<"complex number c4: ";
    std::cin>>c4;
    if(!std::cin){
      std::cerr<<"input error"<<std::endl;
      return EXIT_FAILURE;
    }

    if(c3==c4){
      std::cout<<"c3 and c4 are equal !"<<std::endl;
    }

    std::cout<<"c3 raised to the c4: "<<pow(c3,c4)
             <<std::endl<<std::endl;

    //skip rest of line
    std::cin.ignore(std::numeric_limits<int>::max(),'\n');
    std::cout<<"complex number c3: ";
  }
  std::cout<<std::endl;

  //17.2.3 复数的各项操作

  //create a complex number initialized from polar coordinates
  std::complex<double> c5(std::polar(4.2,0.75));

  std::complex<float> c6(std::polar(4.2,0.75));//OK
  //std::complex<float> c7=std::polar(4.2,0.75);//ERROR,double to float no!

  std::complex<double> c7(1.1,5.5);
  std::complex<double> c8(conj(c7));//initialize c8 with complex<double>(1.1,-5.5)
  std::cout<<c8<<std::endl;







  return 0;
}
