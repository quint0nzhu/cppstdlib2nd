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
#include <limits>
#include <fstream> //for file I/O
#include <sstream>
#include <tuple>
#include <utility>
#include <strstream>
#include <vector>
#include <iterator>
#include <memory>
#include <algorithm>
#include <cstring> //for std::memmove()


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

template <typename charT,typename traits>
inline
std::basic_istream<charT,traits>&
ignoreLine(std::basic_istream<charT,traits>& strm)
{
  //skip until end-of-file
  strm.ignore(std::numeric_limits<std::streamsize>::max(),
              strm.widen('\n'));

  //return stream for concatenation
  return strm;
}

class ignoreLinen
{
private:
  int num;
public:
  explicit ignoreLinen(int n=1):num(n){}

  template<typename charT,typename traits>
  friend std::basic_istream<charT,traits>&
  operator>>(std::basic_istream<charT,traits>& strm,
             const ignoreLinen& ign)
  {
    //skip until end-of-line num times
    for(int i=0;i<ign.num;++i){
      strm.ignore(std::numeric_limits<std::streamsize>::max(),
                  strm.widen('\n'));
    }

    //return stream for concatenation
    return strm;
  }
};

void writeCharsetToFile(const std::string& filename)
{
  //open output file
  std::ofstream file(filename);

  //file opened?
  if(!file){
    //NO, abort program
    std::cerr<<"can't open output file \""<<"\""
             <<std::endl;
    exit(EXIT_FAILURE);
  }

  //write character set
  for(int i=32;i<256;++i){
    file<<"value: "<<std::setw(3)<<i<<" "
        <<"char:  "<<static_cast<char>(i)<<std::endl;
  }
}//close file automatically

void outputFile(const std::string& filename)
{
  //open input file

  std::ifstream file(filename);

  //file opened?
  if(!file){
    //NO, abort program
    std::cerr<<"can't open input file \""<<filename<<"\""
            <<std::endl;
    exit(EXIT_FAILURE);
  }

  //copy file contents to cout
  char c;
  while(file.get(c)){
    std::cout.put(c);
  }

  //another method for copy file contents to cout
  std::cout<<file.rdbuf();

}//close file automatically

std::ofstream openFile(const std::string& filename)
{
  std::ofstream file(filename);

  return file;
}

void printFileTwice(const char* filename)
{
  //open file
  std::ifstream file(filename);

  //print contents the first time
  std::cout<<file.rdbuf();

  //seek to the beginning
  file.seekg(0);

  //print contents the second time
  char c;
  while(file.get(c)){
    std::cout.put(c);
  }
  std::cout<<std::endl;
}

std::tuple<std::string,std::string,std::string> parseName(std::string name)
{
  std::string s1,s2,s3;
  std::istringstream(name)>>s1>>s2>>s3;
  if(s3.empty()){
    return std::tuple<std::string,std::string,std::string>(std::move(s1),"",std::move(s2));
  }
  else{
    return std::tuple<std::string,std::string,std::string>(std::move(s1),std::move(s2),std::move(s3));
  }
}

void foo(const char* s)
{
  std::cout<<s<<std::endl;
}

class Fraction{
private:
  int num;
  int den;
public:
  Fraction(int n=0,int d=1):num(n),den(d){}
  int numerator()const{return num;}
  int denominator()const{return den;}

  void setNumerator(int n){num=n;}
  void setDenominator(int d){
    if(d!=0){
      den=d;
    }
    else{
      std::cout<<"Denominator could not be 0!"<<std::endl;
    }
  }

  virtual void printOn(std::ostream& strm)const{//output
    strm<<num<<'/'<<den;
  }

  virtual void scanFrom(std::istream& strm){
    //assign values directly to the components
    strm>>num;
    strm.ignore();
    strm>>den;
  }
};

//get index for new ostream data
static const int iword_index=std::ios_base::xalloc();

inline
std::ostream& operator<<(std::ostream& strm,const Fraction& f)
{
  //query the ostream data
  //-if true, use spaces between numerator and denominator
  //-if false, use no spaces between numerator and denominator
  if(strm.iword(iword_index)){
    strm<<f.numerator()<<" / "<<f.denominator();
  }
  else{
    strm<<f.numerator()<<'/'<<f.denominator();
  }
  return strm;
}

template<typename charT,typename traits>
inline
std::basic_ostream<charT,traits>&
operator<<(std::basic_ostream<charT,traits>& strm,
           const Fraction& f)
{
  //string stream
  //-with same format
  //-without special field width
  std::basic_ostringstream<charT,traits> s;
  s.copyfmt(strm);
  s.width(0);

  //fill string stream
  s<<f.numerator()<<'/'<<f.denominator();

  //print string stream
  strm<<s.str();

  return strm;
}

template<typename T1,typename T2>
std::ostream& operator<<(std::ostream& strm,const std::pair<T1,T2>& p)
{
  return strm<<"["<<p.first<<","<<p.second<<"]";
}

inline
std::istream& operator>>(std::istream& strm,Fraction& f)
{
  int n,d;

  strm>>n;//read value of the numerator
  strm.ignore();//skip '/'
  strm>>d;//read value of the denominator

  f=Fraction(n,d);//assign the whole fraction

  return strm;
}

template<typename charT,typename traits>
inline
std::basic_istream<charT,traits>&
operator>>(std::basic_istream<charT,traits>& strm,Fraction& f)
{
  int n,d;

  //read value of numerator
  strm>>n;

  //if available
  //-read '/' and value of denominator
  if(strm.peek()=='/'){
    strm.ignore();
    strm>>d;
  }
  else{
    d=1;
  }

  //if denominator is zero
  //-set failbit as I/O format error
  if(d==0){
    strm.setstate(std::ios::failbit);
    return strm;
  }

  //if everything is fine so far
  //-change the value of the fraction
  if(strm){
    f=Fraction(n,d);
  }

  return strm;
}

//std::ostream& operator<<(std::ostream& strm,const Fraction& f)
//{
//  f.printOn(strm);
//  return strm;
//}

//std::istream& operator>>(std::istream& strm,Fraction& f)
//{
//  f.scanFrom(strm);
//  return strm;
//}

//define manipulator that sets this data
std::ostream& fraction_spaces(std::ostream& strm)
{
  strm.iword(iword_index)=true;
  return strm;
}

void hexMultiplicationTable(std::streambuf* buffer,int num)
{
  std::ostream hexout(buffer);
  hexout<<std::hex<<std::showbase;

  for(int i=1;i<=num;++i){
    for(int j=1;j<=10;++j){
      hexout<<i*j<<' ';
    }
    hexout<<std::endl;
  }
}//does NOT close buffer

void redirect(std::ostream& strm)
{
  //save output buffer of the stream
  //-use unique pointer with deleter that ensures to restore
  // the original output buffer at the end of the function
  auto del=[&](std::streambuf* p){
    strm.rdbuf(p);
  };
  std::unique_ptr<std::streambuf,decltype(del)> origBuffer(strm.rdbuf(),del);

  //redirect output into the file redirect.txt
  std::ofstream file("redirect.txt");
  strm.rdbuf(file.rdbuf());

  file<<"one row for the file"<<std::endl;
  strm<<"one row for the stream"<<std::endl;
}//closes file AND its buffer automatically

class outbuf1:public std::streambuf
{
protected:
  //central output function
  //-print characters in uppercase mode
  virtual int_type overflow(int_type c){
    if(c!=EOF){
      //convert lowercase to uppercase
      c=std::toupper(c,getloc());

      //and write the character to the standard output
      if(std::putchar(c)==EOF){
        return EOF;
      }
    }
    return c;
  }
};

template<typename charT,
         typename traits=std::char_traits<charT> >
class basic_outbuf:public std::basic_streambuf<charT,traits>
{
protected:
  //central output function
  //-print characters in uppercase mode
  virtual typename traits::int_type
  overflow(typename traits::int_type c){
    if(!traits::eq_int_type(c,traits::eof())){
      //convert lowercase to uppercase
      c=std::toupper(c,this->getloc());

      //convert the character into a char(default:'?')
      char cc=std::use_facet<std::ctype<charT> >
        (this->getloc()).narrow(c,'?');

      //and write the character to the standard output
      if(std::putchar(cc)==EOF){
        return traits::eof();
      }
    }
    return traits::not_eof(c);
  }
};

typedef basic_outbuf<char> outbuf;
typedef basic_outbuf<wchar_t> woutbuf;

//for write():
#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

class fdoutbuf:public std::streambuf{
protected:
  int fd;//file descriptor

public:
  //constructor
  fdoutbuf(int _fd):fd(_fd){}
protected:
  //write one character
  virtual int_type overflow(int_type c){
    if(c!=EOF){
      char z=c;
      if(write(fd,&z,1)!=1){
        return EOF;
      }
    }
    return c;
  }
  //write multiple characters
  virtual std::streamsize xsputn(const char* s,
                                 std::streamsize num){
    return write(fd,s,num);
  }
};

class fdostream:public std::ostream{
protected:
  fdoutbuf buf;
public:
  fdostream(int fd):std::ostream(0),buf(fd){
    rdbuf(&buf);
  }
};

class outbuf2:public std::streambuf{
protected:
  static const int bufferSize=10;//size of data buffer
  char buffer[bufferSize];//data buffer

public:
  //constructor
  //-initialize data buffer
  //-one character less to let the bufferSizeth character cause a call of overflow()
  outbuf2(){
    setp(buffer,buffer+(bufferSize-1));
  }

  //destructor
  //-flush data buffer
  virtual ~outbuf2(){
    sync();
  }

protected:
  //flush the characters in the buffer
  int flushBuffer(){
    int num=pptr()-pbase();
    if(write(1,buffer,num)!=num){
      return EOF;
    }
    pbump(-num);//reset put pointer accordingly
    return num;
  }

  //buffer full
  //-write c and all previous characters
  virtual int_type overflow(int_type c){
    if(c!=EOF){
      //insert character into the buffer
      *pptr()=c;
      pbump(1);
    }
    //flush the buffer
    if(flushBuffer()==EOF){
      //ERROR
      return EOF;
    }
    return c;
  }

  //synchronize data with file/destination
  //-flush the data in the buffer
  virtual int sync(){
    if(flushBuffer()==EOF){
      //ERROR
      return -1;
    }
    return 0;
  }
};

class fdoutbuf1:public outbuf2{
protected:
  int fd;//file descriptor

public:
  //constructor
  fdoutbuf1(int _fd):fd(_fd){}
protected:
  //write one character
  virtual int_type overflow(int_type c){
    if(c!=EOF){
      char z=c;
      if(write(fd,&z,1)!=1){
        return EOF;
      }
    }
    return c;
  }
  //write multiple characters
  virtual std::streamsize xsputn(const char* s,
                                 std::streamsize num){
    return write(fd,s,num);
  }
};

class fdostream1:public std::ostream{
protected:
   fdoutbuf1 buf;
public:
  fdostream1(int fd):std::ostream(0),buf(fd){
    rdbuf(&buf);
  }
};

class inbuf:public std::streambuf{
protected:
  //data buffer:
  //-at most, four characters in putback area plus
  //-at most, six characters in ordinary read buffer
  static const int bufferSize=10;//size of the data buffer
  char buffer[bufferSize];//data buffer

public:
  //constructor
  //-initialize empty data buffer
  //-no putback area
  //=>force underflow()
  inbuf(){
    setg(buffer+4,//beginning of putback area
         buffer+4,//read position
         buffer+4);//end position
  }

protected:
  //insert new characters into the buffer
  virtual int_type underflow(){
    if(gptr()<egptr()){
      return traits_type::to_int_type(*gptr());
    }

    //process size of putback area
    //-use number of characters read
    //-but at most four
    int numPutback;
    numPutback=gptr()-eback();
    if(numPutback>4){
      numPutback=4;
    }

    //copy up to four characters previously read into
    //the putback buffer(area of first four characters)
    std::memmove(buffer+(4-numPutback),gptr()-numPutback,numPutback);

    //read new characters
    int num;
    num=read(0,buffer+4,bufferSize-4);
    if(num<=0){
      //ERROR or EOF
      return EOF;
    }

    //reset buffer pointers
    setg(buffer+(4-numPutback),//beginning of putback area
         buffer+4,//read position
         buffer+4+num);//end of buffer

    //return next character
    return traits_type::to_int_type(*gptr());
  }
};


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
  while(std::cin>>a>>b){
    //output a and b
    std::cout<<"a: "<<a<<" b: "<<b<<std::endl;
  }

  std::cin.clear();

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
  std::cin.clear();
  std::cout.clear();

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

  //15.5.4 sentry对象（岗哨）

  //15.6 操控器(Manipulator)
  //15.6.1 操控器概览
  //15.6.2 操控器如何运作
  //std::endl(std::cout)
  //带有实参的操控器，使用前要包含<iomanip>
  //15.6.3 用户自定义的操控器

  //ignore the rest of the line
  std::cin>>ignoreLine;

  //ignore two lines
  std::cin>>ignoreLine>>ignoreLine;

  //ignore another two lines
  std::cin>>ignoreLinen(2);

  std::string s3;
  std::cin>>s3;
  std::cout<<s3<<std::endl;

  //15.7 格式化(Formatting)
  //15.7.1 Format Flag（格式标志）

  //set flags showpos and uppercase
  std::cout.setf(std::ios::showpos | std::ios::uppercase);
  std::cout<<34<<std::endl;

  //set only the flag hex in the group basefield
  std::cout.setf(std::ios::hex,std::ios::basefield);
  std::cout<<0x12f<<std::endl;

  //clear the flag uppercase
  std::cout.unsetf(std::ios::uppercase);
  std::cout<<0x12f<<std::endl;

  //save current format flags
  std::ios::fmtflags oldFlags=std::cout.flags();

  //do some changes
  std::cout.setf(std::ios::showpos|std::ios::showbase|std::ios::uppercase);
  std::cout.setf(std::ios::internal,std::ios::adjustfield);
  std::cout<<34<<std::endl;
  std::cout<<std::oct<<34<<std::endl;

  //restore saved format flags
  std::cout.flags(oldFlags);
  std::cout<<34<<std::endl;

  std::cout.unsetf(std::ios::hex);
  std::cout.unsetf(std::ios::showpos);
  std::cout<<34<<std::endl;

  std::cout<<resetiosflags(std::ios::adjustfield)//clear adjustm.flags
           <<setiosflags(std::ios::left);//left-adjust values
  std::cout<<34<<std::endl;
  std::cout.unsetf(std::ios::left);

  //15.7.2 Boolean的I/O格式

  bool b1;

  std::cout<<std::noboolalpha<<b1<<" == "
           <<std::boolalpha<<b1<<std::endl;

  //15.7.3 栏位宽度、填充字符、位置调整

  std::cout<<std::setw(8)<<std::setfill('_')<<-3.14
           <<' '<<42<<std::endl;
  std::cout<<std::setw(8)<<"sum: "
           <<std::setw(8)<<42<<std::endl;

  char buffer1[81];

  //read, at most, 80 characters:
  std::cin>>std::setw(sizeof(buffer1))>>buffer1;

  //char* s1;
  //std::cin>>std::setw(sizeof(s1))>>s1;//RUNTIME ERROR

  std::string s1;
  std::cin>>s1;//OK
  std::cout<<s1<<std::endl;

  //15.7.4 正号与大写

  std::cout<<12345678.9<<std::endl;

  std::cout.setf(std::ios::showpos|std::ios::uppercase);
  std::cout<<12345678.9<<std::endl;

  std::cout<<std::noshowpos<<std::nouppercase;
  std::cout<<12345678.9<<std::endl;

  //15.7.5 数值基数(Numeric Base)

  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex);

  std::cout.setf(std::ios::hex,std::ios::basefield);

  int x1=10,y1=20,z=30;

  std::cout<<std::hex<<x1<<std::endl;
  std::cout<<y1<<' '<<std::dec<<z<<std::endl;

  std::cout<<127<<' '<<255<<std::endl;

  std::cout<<std::hex<<127<<' '<<255<<std::endl;

  std::cout.setf(std::ios::showbase);
  std::cout<<127<<' '<<255<<std::endl;

  std::cout.setf(std::ios::uppercase);
  std::cout<<127<<' '<<255<<std::endl;

  std::cout<<std::nouppercase<<std::noshowbase<<std::dec;
  std::cout<<234<<std::endl;

  //15.7.6 浮点数(Floating-Point)表示法

  std::cout<<0.123456789<<std::endl;

  std::cout<<std::scientific<<std::showpoint
           <<std::setprecision(8)
           <<0.123456789<<std::endl;

  //15.7.7 一般格式(General Formatting)定义

  //cerr和wcerr预先设置了ios::unitbuf（每次输出后，刷清output缓冲区）

  //15.8 国际化(Internationalization)

  std::cout<<std::cout.widen('\n');

  //15.9 文件访问(File Access)
  //15.9.1 File Stream Class

  writeCharsetToFile("charset.out");
  outputFile("charset.out");

  //15.9.2 File Stream的Rvalue和Move语义

  //write string to a temporarily created file stream(since C++11)
  std::string s2("hello");
  std::ofstream("fstream2.tmp")<<s2<<std::endl;

  //write C-string to a temporarily created file stream
  //-NOTE:wrote a pointer value before C++11
  std::ofstream("fstream2.tmp",std::ios::app)<<"world"<<std::endl;

  std::ofstream file;
  file=openFile("xyz.tmp");//use returned file stream(since C++11)
  file<<"hello, world"<<std::endl;

  //15.9.3 File Flag（文件标志）

  //for all filenames passed as command-line arguments
  //-open, print contents, and close file

  std::ifstream file1;

  //for all command-line arguments
  for(int i=1;i<argc;++i){

    //open file
    file1.open(argv[i]);

    //write file contents to cout
    char c;
    while(file1.get(c)){
      std::cout.put(c);
    }

    //another write file contents to cout
    std::cout<<file1.rdbuf()<<std::endl;

    //clear eofbit and failbit set due to end-of-file
    file1.clear();

    //close file
    file1.close();
  }
  std::cout.clear();

  //15.9.4 随机访问(Random Access)

  //save current file position
  //std::ios::pos_type pos=file.tellg();

  //seek to file position saved in pos
  //file.seekg(pos);

  //seek to the beginning of the file
  //file.seekg(0,std::ios::beg);

  //seek 20 characters forward
  //file.seekg(20,std::ios::cur);

  //seek 10 characters before the end
  //file.seekg(-10,std::ios::end);

  //print all files passed as a command-line argument twice
  for(int i=1;i<argc;++i){
    printFileTwice(argv[i]);
  }

  //15.9.5 使用文件描述器(File Descriptor)

  //15.10 为String而设计的Stream Class
  //15.10.1 String Stream Class

  std::ostringstream os;

  //decimal and hexadecimal value
  os<<"dec: "<<15<<std::hex<<" hex: "<<15<<std::endl;
  std::cout<<os.str()<<std::endl;

  //append floating value and bitset
  std::bitset<15> b2(5789);
  os<<"float: "<<4.67<<" bitset: "<<b2<<36<<std::endl;

  //overwrite with octal value
  os.seekp(0);
  os<<"oct: "<<std::oct<<15;
  std::cout<<os.str()<<std::endl;

  os.str("");
  std::cout<<"new os: "<<os.str()<<std::endl;

  int x2;
  float f3;
  std::string s4="3.7";

  std::istringstream is(s4);
  is>>x2>>f3;

  std::cout<<x2<<" "<<f3<<std::endl;

  std::string s5("vlaue: ");

  std::ostringstream os1(s5,std::ios::out|std::ios::ate);//pos is s5's last letter
  os1<<77<<" "<<std::hex<<77<<std::endl;
  std::cout<<os1.str();//writes:value:77 4d, it's a copy of s5+
  std::cout<<s5;//writes:value:
  std::cout<<std::endl;

  //15.10.2 String Stream的Move语义

  auto t1=parseName("Nicolai M. Josuttis");
  std::cout<<"firstname: "<<std::get<0>(t1)<<std::endl;
  std::cout<<"middle:    "<<std::get<1>(t1)<<std::endl;
  std::cout<<"lastname:  "<<std::get<2>(t1)<<std::endl;

  auto t2=parseName("Nico Josuttis");
  std::cout<<"firstname: "<<std::get<0>(t2)<<std::endl;
  std::cout<<"middle:    "<<std::get<1>(t2)<<std::endl;
  std::cout<<"lastname:  "<<std::get<2>(t2)<<std::endl;

  std::cin.clear();

  //15.10.3 char* Stream Class

  char buffer2[1000];//buffer for at most 999 characters

  //read line
  std::cin.get(buffer2,sizeof(buffer2));

  //read/process line as stream
  std::istrstream input(buffer2);

  std::string s6;

  input>>s6;

  std::cout<<s6<<std::endl;
  std::cout<<input.str()<<std::endl;

  float x3=1.2345;

  //create and fill char* stream
  //-don't forget ends or '\0'!!!
  std::ostrstream buffer3;//dynamic stream buffer
  buffer3<<"float x: "<<x3<<std::ends;

  //pass resulting C-string to foo() and return memory to buffer
  char* s7=buffer3.str();
  foo(s7);
  buffer3.freeze(false);

  float x4=2.34567;

  std::ostrstream buffer4;//dynamic char* stream

  //fill char* stream
  buffer4<<"float x: "<<x4<<std::ends;

  //pass resulting C-string to foo()
  //-freezes the char* stream
  foo(buffer4.str());

  //unfreeze the char* stream
  buffer4.freeze(false);

  //seek writing position to the beginning
  buffer4.seekp(0,std::ios::beg);

  //refill char* stream
  buffer4<<"once more float x: "<<x4<<std::ends;

  //pass resulting C-string to foo() again
  //-freezes the char* stream
  foo(buffer4.str());

  //return memory to buffer
  buffer4.freeze(false);

  //15.11 “用户自定义类型”之I/O操作符
  //15.11.1 实现一个Output操作符

  Fraction vat(19,100);//I'm German and we have a uniform VAT of 19%
  std::cout<<"VAT: \""<<std::left<<std::setw(8)
           <<vat<<'"'<<std::endl;

  std::pair<int,long> p(42,77777);
  std::cout<<p<<std::endl;//OK

  std::vector<std::pair<int,long>> v({p});

  //std::copy(v.begin(),v.end(),std::ostream_iterator<std::pair<int,long>>(std::cout,"\n"));//ERROR:doesn't compile:

  //15.11.2 实现一个Input操作符

  Fraction f4;
  std::cin>>f4;
  std::cout<<f4<<std::endl;

  //15.11.3 以辅助函数完成I/O
  //15.11.4 用户自定义之Format Flag（格式标志）

  Fraction f5;
  std::cin>>f5;
  std::cout<<fraction_spaces<<f5<<std::endl;

  Fraction f6(1,7);
  std::cout<<f6<<std::endl;

  //15.11.5 用户自定义I/O操作符的规约(Convention)

  //15.12 连接Input和Output Stream
  //15.12.1 以tie()完成松耦合(Loose Coupling)

  //predefined connections:
  std::cin.tie(&std::cout);
  //std::wcin.tie(&std::wcout);

  int x5;

  std::cout<<"Please enter x: ";
  std::cin>>x5;
  std::cout<<x5<<std::endl;

  //decouple cin from any output stream
  std::cin.tie(nullptr);

  //tieing cout to cerr
  std::cerr.tie(&std::cout);

  //15.12.2 以Stream缓冲区完成紧耦合(Tight Coupling)

  //stream for hexadecimal standard output
  std::ostream hexout(std::cout.rdbuf());
  hexout.setf(std::ios::hex,std::ios::basefield);
  hexout.setf(std::ios::showbase);

  //switch between decimal and hexadecimal output
  hexout<<"hexout: "<<177<<" ";
  std::cout<<"cout: "<<177<<" ";
  hexout<<"hexout: "<<-49<<" ";
  std::cout<<"cout: "<<-49<<" ";
  hexout<<std::endl;

  int num=5;

  std::cout<<"We print "<<num
           <<" lines hexadecimal"<<std::endl;

  hexMultiplicationTable(std::cout.rdbuf(),num);

  std::cout<<"That was the output of "<<num
           <<" hexadecimal lines"<<std::endl;

  //15.12.3 将标准Stream重定向(Redirecting)

  std::streambuf* oldcout;

  std::ofstream file2("cout.txt");
  oldcout=std::cout.rdbuf(file2.rdbuf());

  std::cout<<"Hello Fuck You!"<<std::endl;

  std::cout<<std::hex<<std::showbase;

  std::ofstream file3("cout1.txt");
  file3.copyfmt(std::cout);
  std::cout.rdbuf(file3.rdbuf());

  std::cout<<"hello fuck you!"<<34<<std::endl;

  std::cout.rdbuf(oldcout);
  std::cout.clear();

  std::cout<<"the first row"<<std::endl;

  redirect(std::cout);

  std::cout<<"the last row"<<std::endl;

  //15.12.4 可读可写的Stream

  std::fstream file4("example.txt",std::ios::in|std::ios::out);

  std::ofstream out("example.txt",std::ios::in|std::ios::out);
  std::istream in(out.rdbuf());

  std::filebuf buffer5;
  std::ostream out1(&buffer5);
  std::istream in1(&buffer5);
  buffer5.open("example.txt",std::ios::in|std::ios::out);

  //open file "example.dat" for reading and writing
  std::filebuf buffer6;
  std::ostream output(&buffer6);
  std::istream input1(&buffer6);

  buffer6.open("example.dat",std::ios::in|std::ios::out|std::ios::trunc);

  for(int i=1;i<=4;++i){
    //write one line
    output<<i<<". line"<<std::endl;

    //print all file contents
    input1.seekg(0);//seek to the beginning
    char c;
    while(input1.get(c)){
      std::cout.put(c);
    }
    std::cout<<std::endl;
    input1.clear();//clear eofbit and failbit
  }

  //15.13 Stream Buffer Class
  //15.13.1 Stream缓冲区接口
  //15.13.2 Stream缓冲区的Iterator

  //create iterator for buffer of output stream cout
  std::ostreambuf_iterator<char> bufWriter(std::cout);

  std::string hello("hello, world\n");
  copy(hello.begin(),hello.end(),//source:string
       bufWriter);//destination:output buffer of cout

  //input stream buffer iterator for cin
  std::istreambuf_iterator<char> inpos(std::cin);

  //end-of-stream iterator
  std::istreambuf_iterator<char> endpos;

  //output stream buffer iterator for cout
  std::ostreambuf_iterator<char> outpos(std::cout);

  //while input iterator is valid
  while(inpos!=endpos){
    *outpos=*inpos;//assign its value to the output iterator
    ++inpos;
    ++outpos;
  }

  std::cout.rdbuf(oldcout);

  std::cout<<count(std::istreambuf_iterator<char>(std::cin),
                        std::istreambuf_iterator<char>(),
                   '\n')<<std::endl;

  std::cout.clear();

  //15.13.3 用户自定义之Stream缓冲区

  outbuf ob;//create special output buffer
  std::ostream out2(&ob);//initialize output stream with that output buffer

  out2<<"31 hexadecimal: "<<std::hex<<31<<std::endl;

  fdostream out3(1);//stream with buffer writing to file descriptor 1

  out3<<"31 hexadecimal: "<<std::hex<<31<<std::endl;

  fdostream1 out4(1);
  out4<<"hello stream and buffer"<<std::hex<<36<<std::endl;

  inbuf ib;//create special stream buffer
  std::istream in2(&ib);//initialize input stream with that buffer

  char c3;
  for(int i=1;i<=20;i++){
    //read next character(out of the buffer)
    in2.get(c3);

    //print that character(and flush)
    std::cout<<c3<<std::flush;

    //after eight characters, put two characters back into the stream
    if(i==8){
      in2.unget();
      in2.unget();
      in2.unget();
      in2.unget();
      in2.unget();
      in2.unget();
    }
  }
  std::cout<<std::endl;

  //15.14 关于效能(Performance)
  //15.14.1 与C标准串流同步(Synchronization with C's Standard Streams)

  std::ios::sync_with_stdio(false);//disable synchronization
  std::ios::sync_with_stdio(true);//enable synchronization

  //15.14.2 Stream缓冲区内的缓冲机制
  //15.14.3 直接使用Stream缓冲区

  //copy all standard input to standard output
  std::cout<<std::cin.rdbuf();

  std::cout.clear();

  //copy all standard input to standard output
  std::cin>>std::noskipws>>std::cout.rdbuf();
  std::cout<<std::endl;

  return 0;
}
