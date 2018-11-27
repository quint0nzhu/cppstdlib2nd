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


namespace MyLib{
  double readAndProcessSum(std::istream& strm)
  {
    using std::ios;
    double value,sum;

    //save current state of exception flags
    ios::iostate oldExceptions=strm.exceptions();

    //let failbit and badbit throw exceptions
    //-NOTE:failbit is also set at end-of-file
    strm.exceptions(ios::failbit|ios::badbit);

    try{
      //while stream is OK
      //-read value and add it to sum
      sum=0;
      while(strm>>value){
        sum+=value;
      }
    }
    catch(...){
      //if exception not caused by end-of-file
      //-restore old state of exception flags
      //-rethrow exception
      if(!strm.eof()){
        strm.exceptions(oldExceptions);//restore exception flags
        throw;//rethrow
      }
    }

    //restore old state of exceptions flags
    strm.exceptions(oldExceptions);

    //return sum
    return sum;
  }
}

namespace MyLib1{
  double readAndProcessSum(std::istream& strm)
  {
    double value,sum;

    //while stream is OK
    //-read value and add it to sum
    sum=0;
    while(strm>>value){
      sum+=value;
    }

    if(!strm.eof()){
      throw std::ios::failure("input error in readAndProcessSum()");
    }

    //return sum
    return sum;
  }
}



int main(int argc, char* argv[])
{
  //第15章 以Stream完成I/O
  //15.1 I/O Stream的共通基础
  //15.1.1 Stream对象
  //15.1.2 Stream Class
  //15.1.3 全局的Stream对象
  //15.1.4 Stream操作符
  /*
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

  //throw exceptions for all "errors"
  //strm.exceptions(std::ios::eofbit|std::ios::failbit|std::ios::badbit);

  //do not generate exceptions
  //strm.exceptions(std::ios::goodbit);

  //this call throws an exception if failbit is set on entry
  //strm.exceptions(std::ios::failbit);

  //throw an exception(even if failbit was already set)
  //strm.setstate(std::ios::failbit);

  double sum=0;
  double sum1=0;
  try{
    sum=MyLib::readAndProcessSum(std::cin);
    sum1=MyLib1::readAndProcessSum(std::cin);
  }
  catch(const std::ios::failure& error){
    std::cerr<<"I/O exception: "<<error.what()<<std::endl;
    return EXIT_FAILURE;
  }
  catch(const std::exception& error){
    std::cerr<<"standard exception: "<<error.what()<<std::endl;
    return EXIT_FAILURE;
  }
  catch(...){
    std::cerr<<"unknown exception"<<std::endl;
    return EXIT_FAILURE;
  }

  //print sum
  std::cout<<"sum: "<<sum<<std::endl;
  std::cout<<"sum: "<<sum1<<std::endl;

  //15.5 标准I/O函数
  //15.5.1 Input相关函数

  //int istream::get()
  //读取下一字符
  //返回读取的字符，或EOF
  //通常返回类型是traits::int_type。traits::eof()会返回EOF。对istream而言，返回类型是int，EOF则为常量EOF。因此对istream来说，此函数对应于C语言的getchar()或getc()
  //注意，返回值不一定是字符类型，可以是范围更大的数值类型，否则就无法根据相应实值区分EOF和一般字符

  //istream& istream::get(char& c)
  //把下一字符赋值给实参c
  //返回stream；其状态可说明是否读取成功

  //istream& istream::get(char* str,streamsize count)
  //istream& istream::get(char* str,streamsize count,char delim)
  //两种形式均可读取多达count-1个字符，并存入str所指的字符序列中
  //第一形式的读取终止条件是，下一字符是相应字符集中的换行符，例如'\n'之于istream，wchar_t('\n')之于wistream。一般而言，用的是widen('\n')
  //第二形式的读取终止条件是：下一字符是delim
  //不会读取终止符delim
  //读取的字符序列以一个代表结束的null字符为结尾
  //调用者必须保证str足够存入count个字符

  //istream& istream::getline(char* str,streamsize count)
  //istream& istream::getline(char* str,streamsize count,char delim)
  //两种形式和先前对应的get()完全一样，只除了一点：终止读取时，读取内容包括换行符或delim，而非在两者之前就终止
  //因此当换行符或delim位于count-1个字符内时，它们会被读取，但不被存储于str内

  //istream& istream::read(char* str,streamsize count)
  //读取count个字符，并存入str中
  //返回stream。Stream的状态可以说明读取是否成功
  //str内的string不会自动以“终止符null”结束
  //调用者必须确保str有足够空间存储count个字符
  //读入过程中如遇到end-of-file会出错，则failbit会被设置（当然eofbit也有份）

  //streamsize istream::readsome(char* str,streamsize count)
  //可读取多达count个字符，存入str中
  //返回读取的字符个数
  //str内的string不会自动以“终止符null“结束
  //调用者必须确保str有足够空间存储count个字符
  //与read()相反，readsome()会读入stream buffer内的所有有效字符（利用buffer的成员函数in_avail()完成）。当我们不希望等待输入时，这很有用，因为输入来自键盘或其他进程(process)。遭遇end-of-file并不算错，不会因此设置eofbit或failbit

  //streamsize istream::gcount()const
  //返回上一次”非格式化读取操作“所读的字符个数

  //istream& istream::ignore()
  //istream& istream::ignore(streamsize count)
  //istream& istream::ignore(streamsize count,int delim)
  //所有形式均提取(extract)字符并舍弃不用
  //第一形式忽略(ignore)一个字符
  //第二形式可忽略多达count个字符
  //第三形式可忽略多达count个字符，直到提取并舍弃delim
  //如果count的值等于std::numeric_limits<std::streamsize>::max()（这是类型std::streamsize的最大值），那么delim或end-of-file之前的所有字符均被舍弃
  //上述形式均返回stream
  //举例：
  //-以下动作会弃置当前这一行的剩余部分：
  // cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
  //-以下动作会弃置cin的所有剩余内容：
  // cin.ignore(numeric_limits<std::streamsize>::max());

  //int istream::peek()
  //返回stream之内”下一个将被读取的字符“，但不真的把它读出来。下一次读取结果便是该字符（除非改变了读取位置）
  //如果不再能够读入任何字符，返回EOF
  //EOF即traits::eof()的返回值；对istream来说就是常量EOF

  //istream& istream::unget()
  //istream& istream::putback(char c)
  //两者均把上一次读取字符放回stream，使之可被下次读取（除非改变了读取位置）
  //两者的区别在于putback()会检查传入的c是否确是上一次读取字符
  //如果无法放回字符，或者putback()发现待放字符不正确，就设置badbit，相应的异常可能因此被抛出
  //两函数可放回的最大字符数，由实现版本决定。C++ standard保证在两次读取之间允许你调用上述任一函数一次，并且具有可携性

  //15.5.2 Output相关函数

  //ostream& ostream::put(char c)
  //将实参c写至stream
  //返回stream。Stream的状态可说明涂写是否成功

  //ostream& ostream::write(const char* str,streamsize count)
  //把str中的count个字符写入stream
  //返回stream。Stream的状态可说明涂写动作是否成功
  //终止符null并不会终止涂写动作，它本身也会被写进stream
  //调用者必须确保str的确包含至少count个字符，否则可能导致无法预期的行为

  //ostream& ostream::flush()
  //刷新(flush)stream的缓冲区，也就是把所有缓冲数据强制写入其所属的设备或I/O通道

  //15.5.3 实例

  char c2;

  //while it is possible to read a character
  while(std::cin.get(c2)){
    //print it
    std::cout.put(c2);
  }
  */

  //15.5.4 sentry对象（岗哨）

  //15.6 操控器(Manipulator)
  //15.6.1 操控器概览
  //15.6.2 操控器如何运作




  return 0;
}
