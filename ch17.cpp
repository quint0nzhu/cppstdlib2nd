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
#include <typeinfo>



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

template<typename T>
bool operator<(const std::complex<T>& c1,
               const std::complex<T>& c2)
{
  return std::abs(c1)<std::abs(c2)||
                      (std::abs(c1)==std::abs(c2)&&
                       std::arg(c1)<std::arg(c2));
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

  std::uniform_int_distribution<int> dd;
  std::default_random_engine dre11;
  std::cout<<(dd(dre11))<<" ";
  std::default_random_engine dre22;
  std::cout<<(dd(dre22))<<" "<<std::endl;

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

  std::complex<float> cf;
  std::complex<double> cd;
  std::complex<long double> cld;

  std::complex<double> cd1=cf;//OK:safe conversion
  //std::complex<double> cd2=cld;//ERROR:no implicit conversion
  std::complex<double> cd3(cld);//OK:explicit conversion

  std::complex<double> cd4;
  std::complex<int> ci;

  //std::complex<double> cd5=ci;//ERROR:no implicit conversion
  //std::complex<double> cd6(ci);//ERROR:no explicit conversion
  std::complex<double> cd7(ci.real(),ci.imag());//OK

  cd=ci;//OK
  cd=cld;//OK

  std::complex<float> c9(std::polar(4.2,0.75));//OK
  //std::complex<float> c10=std::polar(4.2,0.75);//ERROR

  std::complex<double> c11;
  c11=std::complex<double>(c11.real(),3.7);//since C++11:c.imag(3.7)
  std::cout<<c11<<std::endl;

  c11.real(4.5);
  std::cout<<c11<<std::endl;

  std::complex<double> c12(2.3,2.5),c13(2.3,-2.6);
  std::cout<<std::boolalpha<<(c12<c13)<<std::endl;

  //17.2.4 细说Class complex<>

  //complex::value_type
  //实部和虚部的标量类型

  //complex::complex()
  //Default构造函数
  //构造一个复数，其实部和虚部的初值系通过调用实部和虚部的default构造函数而设定。因此，如果是基础类型，实部和虚部的初值为0

  //complex::complex(const T& re)
  //构造一个复数，实部为re，虚部则通过调用其default构造函数设定（基础类型的初值为0）
  //此构造函数同时定义了一个从T到complex的自动类型转换

  //complex::complex(const T& re,const T& im)
  //构造一个复数，实部初值为re，虚部初值为im

  //complex polar(const T& rho)
  //complex polar(const T& rho,const T& theta)
  //以上两种形式都建立并返回一个复数，其初值以极坐标形式设定
  //rho是大小(magnitude)
  //theta是相角，以弧度(radian)为单位，默认为0

  //complex conj(const complex& complx)
  //建立并返回一个复数；以复数cmplx的共轭复数初值。所谓共轭复数是指虚部与原复数的虚部互为反相(negated)

  //complex proj(const complex& cmplx)
  //根据cmplx在黎曼球面(Riemann sphere)上的投影，建立一个临时复数并返回
  //行为等同C函数cproj()
  //始自C++11

  //complex::complex(const complex& cmplx)
  //Copy构造函数
  //建立一个新复数，以cmplx为蓝本
  //复制实部和虚部
  //此函数通常同时提供non-template和template两种形式，因此具备对元素类型的自动转型能力
  //然而，float、double和long double等特化版本对copy构造函数有限制，所以不甚安全的转换（例如double或long double转为float，或是long double转为double）就必须显式进行

  //complex& complex::operator=(const complex& cmplx)
  //将复数cmplx赋值给*this
  //返回*this
  //此函数通常同时提供non-template和template两种形式，因此具备对元素类型的自动转型能力。C++标准库提供的特化版本也具备此能力

  //complex& complex::operator+=(const complex& cmplx)
  //complex& complex::operator-=(const complex& cmplx)
  //complex& complex::operator*=(const complex& cmplx)
  //complex& complex::operator/=(const complex& cmplx)
  //上述操作分别对*this和cmplx进行加、减、乘、除运算，并将结果存入*this
  //返回*this
  //此函数通常同时提供non-template和template两种形式。因此具备对元素类型的自动转型能力。C++标准库提供的特化版本也具备此能力
  //注意，赋值操作符是改变既有complex的唯一途径

  //T complex::real()const
  //T real(const complex& cmplx)
  //T complex::imag()const
  //T imag(const complex& cmplx)
  //上述函数分别返回实部和虚部
  //注意，返回值并不是个reference，所以你不能使用这些函数改变复数的实部和虚部。若要单独改变实部或虚部，必须赋予一个新的复数值

  //T complex::real(const T& re)
  //T complex::imag(const T& im)
  //这些函数分别对实部和虚部赋予新值
  //始自C++11。在C++11之前如果“只想改变实部”或“只想改变虚部”，必须赋予一个新的复数值

  //T abs(const complex& cmplx)
  //返回cmplx的绝对值（亦即大小）
  //计算公式：sqrt(cmplx.real()*cmplx.read()+cmplx.imag()*cmplx.imag())

  //T norm(const complex& cmplx)
  //返回cmplx绝对值的平方
  //计算公式：cmplx.real()*cmplx.real()+cmplx.imag()*cmplx.imag()

  //T arg(const complex& cmplx)
  //返回以弧度(radian)为单位的极坐标相角
  //计算公式：atan2(cmplx.imag(),cmplx.real())

  //ostream& operator<<(ostream& strm,const complex& cmplx)
  //将cmplx的值以(realpart,imagpart)的格式写入stream strm
  //返回strm

  //istream& operator>>(istream& strm,const complex& cmplx)
  //从strm中读一个新值至cmplx
  //合法的输入格式如下：
  //(realpart,imagpart)
  //(realpart)
  //realpart
  //返回strm

  //complex operator+(const complex& cmplx)
  //正号，返回cmplx

  //complex operator-(const complex& cmplx)
  //负号，将复数cmplx的实部和虚部都反相(negated)后返回

  //complex binary-op(const complex& cmplx1,const complex& cmplx2)
  //complex binary-op(const complex& cmplx,const T& value)
  //complex binary-op(const T& value,const complex& cmplx)
  //上述各项操作返回binary-op计算所得的复数
  //binary-op可以是下列四种运算之一：
  //operator+
  //operator-
  //operator*
  //operator/
  //如果传入一个元素类型标量值(scalar value)，它会被视为复数的实部，虚部则由其标量类型的默认初值决定（如果是基础类型则初值为0）

  //bool comparison(const complex& cmplx1,const complex& cmplx2)
  //bool comparison(const complex& cmplx,const T& value)
  //bool comparison(const T& value,const complex& cmplx)
  //返回两复数的比较结果，或是一个复数与一个标量(scalar value)的比较结果
  //comparison可以是下面两种运算之一：
  //operator==
  //operator!=
  //如果传入一个元素类型标量值(scalar value)，它会被视为复数的实部，虚部则由其类型的默认初值决定（如果是基础类型则初值为0）
  //注意，并没有定义<、<=、>和>=操作符

  //complex pow(const complex& base,const T& exp)
  //complex pow(const complex& base,const complex& exp)
  //complex pow(const T& base,const complex& exp)
  //上述所有形式都是计算“以base为底，exp为指数”的幂，定义如下：
  //exp(exp*log(base))
  //分支切割(branch cut)沿着负实数轴进行
  //pow(0,0)的结果由实现(implementation)自行定义

  //complex exp(const complex& cmplx)
  //返回“以e为底，cmplx为指数”的幂

  //complex sqrt(const complex& cmplx)
  //返回位于右半象限之cmplx平方根
  //如果实参是负实数，则运算结果位于正虚数轴上
  //分支切割(branch cut)沿着负实数轴进行

  //complex log(const complex& cmplx)
  //返回cmplx的自然对数（亦即以e为底的对数）
  //当cmplx是负实数时，imag(log(cmplx))的值为Pi
  //分支切割(branch cut)沿着负实数轴进行

  //complex log10(const complex& cmplx)
  //返回cmplx的（以10为底的）对数
  //相当于log(cmplx)/log(10)
  //分支切割(branch cut)沿着负实数轴进行

  //complex sin(const complex& cmplx)
  //complex cos(const complex& cmplx)
  //complex tan(const complex& cmplx)
  //complex sinh(const complex& cmplx)
  //complex cosh(const complex& cmplx)
  //complex tanh(const complex& cmplx)
  //complex asin(const complex& cmplx)
  //complex acos(const complex& cmplx)
  //complex atan(const complex& cmplx)
  //complex asinh(const complex& cmplx)
  //complex acosh(const complex& cmplx)
  //complex atanh(const complex& cmplx)
  //以上各操作函数分别对cmplx进行复数三角运算(complex trigonometric operation)
  //所有逆操作（名称以a开头者）都始自C++11

  //17.3 全局数值函数(Global Numeric Function)

  std::cout<<std::sqrt(9)<<" type: "<<typeid(std::sqrt(9)).name()<<std::endl;//AMBIGUOUS:sqrt(float), sqrt(double), or sqrt(long double)? return double
  std::cout<<std::sqrt(2.0)<<" type: "<<typeid(std::sqrt(2.0)).name()<<std::endl;//OK return double

  int x=16;
  std::cout<<std::sqrt(float(x))<<" type: "<<typeid(std::sqrt(float(x))).name()<<std::endl;//OK return float

  //17.4 Valarray

  return 0;
}
