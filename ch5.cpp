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
#include <ios> //for I/O in exceptions
#include <future> //for errors with async() and futures(since C++11),-lpthread
#include <utility>
#include <memory> //for shared_ptr
#include <fstream>
#include <sys/mman.h> //for shared memory,-lrt
#include <fcntl.h>
#include <unistd.h>
#include <cstring> //for strerror()
#include <cerrno> //for errno
#include <atomic>
#include <dirent.h> //for opendir(),...
#include <algorithm>
#include <ratio>
#include <chrono>
#include <iomanip> // for setfill() setw()
#include <ctime>
#include <thread> //for this_thread


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
  return std::make_tuple(1,2,3);
  //return {1,2,3};//error,but now OK
}

std::vector<int> foobar(){
  std::cout<<"call foobar"<<std::endl;
  return {1,2,3};//OK
}

std::tuple<int,int,int> barfoo(){
  std::cout<<"call barfoo"<<std::endl;
  return std::make_tuple(1,2,3);
}

//
//helper: print element with index IDX of tuple with MAX elements
template<int IDX, int MAX, typename... Args>
struct PRINT_TUPLE{
  static void print(std::ostream& strm,
                    const std::tuple<Args...>& t){
    strm << std::get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");
    PRINT_TUPLE<IDX + 1, MAX, Args...>::print(strm, t);
  }
};

//partial specialization to end the recursion
template<int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...>{
  static void print(std::ostream& strm,
                    const std::tuple<Args...>& t){
  }
};

//output operator for tuples
template <typename... Args>
std::ostream& operator<<(std::ostream& strm,
                         const std::tuple<Args...>& t){
  strm << "[";
  PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
  return strm << "]";
}

class FileDeleter
{
private:
  std::string filename;
public:
  FileDeleter(const std::string& fn):filename(fn){}
  void operator()(std::ofstream* fp){
    fp->close();//close file
    std::remove(filename.c_str());;//delete file
  }
};

class SharedMemoryDetacher
{
public:
  void operator()(int* p){
    std::cout<<"unlink /tmp1234"<<std::endl;
    if(shm_unlink("/tmp1234")!=0){
      std::cerr<<"OOPS: shm_unlink() failed"<<std::endl;
    }
  }
};

std::shared_ptr<int> getSharedIntMemory(int num)
{
  void* mem;
  int shmfd = shm_open("/tmp1234",O_CREAT|O_RDWR,S_IRWXU|S_IRWXG);
  if(shmfd<0){
    throw std::string(strerror(errno));
  }

  if(ftruncate(shmfd, num*sizeof(int))==-1){
    throw std::string(strerror(errno));
  }

  mem = mmap(nullptr, num*sizeof(int),PROT_READ|PROT_WRITE,
             MAP_SHARED, shmfd,0);
  if(mem == MAP_FAILED){
    throw std::string(strerror(errno));
  }

  return std::shared_ptr<int>(static_cast<int*>(mem),
                              SharedMemoryDetacher());
}

class Person{
public:
  std::string name;
  std::shared_ptr<Person> mother;
  std::shared_ptr<Person> father;
  std::vector<std::shared_ptr<Person>> kids;

  Person(const std::string& n,
         std::shared_ptr<Person> m = nullptr,
         std::shared_ptr<Person> f = nullptr)
    : name(n),mother(m),father(f){}

  ~Person(){
    std::cout<<"delete "<<name <<std::endl;
  }
};

std::shared_ptr<Person> initFamily(const std::string& name)
{
  std::shared_ptr<Person> mom(new Person(name+"'s mom"));
  std::shared_ptr<Person> dad(new Person(name+"'s dad"));
  std::shared_ptr<Person> kid(new Person(name,mom,dad));
  mom->kids.push_back(kid);
  dad->kids.push_back(kid);

  return kid;
}

class Person1{
public:
  std::string name;
  std::shared_ptr<Person1> mother;
  std::shared_ptr<Person1> father;
  std::vector<std::weak_ptr<Person1>> kids;//weak pointer!!!
  Person1(const std::string& n,
         std::shared_ptr<Person1> m = nullptr,
         std::shared_ptr<Person1> f = nullptr)
    :name(n),mother(m),father(f){}
  ~Person1(){
    std::cout<<"Delete "<<name << std::endl;
  }
};


std::shared_ptr<Person1> initFamily1(const std::string& name)
{
  std::shared_ptr<Person1> mom(new Person1(name+"'s mom"));
  std::shared_ptr<Person1> dad(new Person1(name+"'s dad"));
  std::shared_ptr<Person1> kid(new Person1(name,mom,dad));
  mom->kids.push_back(kid);
  dad->kids.push_back(kid);

  return kid;
}

class Person2{
public:
  std::string name;
  std::shared_ptr<Person2> mother;
  std::shared_ptr<Person2> father;
  std::vector<std::shared_ptr<Person2>> kids;
  Person2(const std::string& n,
          std::shared_ptr<Person2> m = nullptr,
          std::shared_ptr<Person2> f = nullptr)
    :name(n), mother(m), father(f){}
  void setParentsAndTheirKids(std::shared_ptr<Person2> m = nullptr,
                              std::shared_ptr<Person2> f = nullptr){
    mother = m;
    father = f;
    if(m!=nullptr){
      m->kids.push_back(std::shared_ptr<Person2>(this));//Error
    }
    if(f!=nullptr){
      f->kids.push_back(std::shared_ptr<Person2>(this));//Error
    }
  }
};

class Person3 : public std::enable_shared_from_this<Person3>{
public:
  std::string name;
  std::shared_ptr<Person3> mother;
  std::shared_ptr<Person3> father;
  std::vector<std::shared_ptr<Person3>> kids;
  Person3(const std::string& n,
          std::shared_ptr<Person3> m = nullptr,
          std::shared_ptr<Person3> f = nullptr)
    :name(n), mother(m),father(f){}
  void setParentsAndTheirKids(std::shared_ptr<Person3> m = nullptr,
                              std::shared_ptr<Person3> f = nullptr){
    mother = m;
    father = f;
    if(m!=mother){
      m->kids.push_back(shared_from_this());//OK
    }
    if(f!=nullptr){
      f->kids.push_back(shared_from_this());//OK
    }
  }
};

class Person4 : public std::enable_shared_from_this<Person4>{
public:
  std::string name;
  std::shared_ptr<Person4> mother;
  std::shared_ptr<Person4> father;
  std::vector<std::shared_ptr<Person4>> kids;
  Person4(const std::string& n,
          std::shared_ptr<Person4> m = nullptr,
          std::shared_ptr<Person4> f = nullptr)
    :name(n), mother(m),father(f){
    mother = m;
    father = f;
    if(m!=mother){
      m->kids.push_back(shared_from_this());//OK
    }
    if(f!=nullptr){
      f->kids.push_back(shared_from_this());//OK
    }
  }
};

struct X
{
  int a;
  ~X(){std::cout<<"X is deleted!"<<std::endl;}
};

std::shared_ptr<X> global;//initially nullptr

void foooo()
{
  std::shared_ptr<X> local{new X};
  std::atomic_store(&global,local);
}

void test1()
{
  X* ptr = new X;//create an object explicitly
  //... perform some operations
  delete ptr;//clean up(destroy the object explicitly)
}

void test2()
{
  X* ptr = new X;//create an object explicity
  try{
    //... perform some operations
  }
  catch(...){//for any exception
    delete ptr;//- clean up
    throw;//- rethrow the exception
  }

  delete ptr;//clean up on normal end

}

void test3()
{
  //create and initialize an unique_ptr
  std::unique_ptr<X> ptr(new X);
  //.. perform some operations
}

void sink(std::unique_ptr<X> up)//sink() gets ownership
{

}

std::unique_ptr<X> source()
{
  std::unique_ptr<X> ptr(new X);//ptr owns the new object

  return std::move(ptr);//transfer ownership to calling function
  //c++11 can auto add std::move to ptr
}

class ClassA{
public:
  ClassA(){}
  ClassA(int n):x(n){}
private:
  int x;
};

class ClassB{
private:
  ClassA* ptr1;//pointer members
  ClassA* ptr2;
public:
  //constructor that initializes the pointers
  //- will cause resource leak if second new throws
  ClassB(int val1, int val2):ptr1(new ClassA(val1)),ptr2(new ClassA(val2)){}
  //copy constructor
  //- might cause resource leak if second new throws
  ClassB(const ClassB& x):ptr1(new ClassA(*x.ptr1)),ptr2(new ClassA(*x.ptr2)){}
  //assignment operator
  const ClassB& operator=(const ClassB& x){
    *ptr1=*x.ptr1;
    *ptr2=*x.ptr2;
    return *this;
  }
  ~ClassB(){
    delete ptr1;
    delete ptr2;
  }
};

class ClassC{
private:
  std::unique_ptr<ClassA> ptr1;//unique_ptr members
  std::unique_ptr<ClassA> ptr2;
public:
  //constructor that initializes the unique_ptrs
  //-no resource leak possible
  ClassC(int val1, int val2)
    : ptr1(new ClassA(val1)), ptr2(new ClassA(val2)){}
  //copy constructor
  //-no resource leak possible
  ClassC(const ClassC& x)
    :ptr1(new ClassA(*x.ptr1)), ptr2(new ClassA(*x.ptr2)){}
  //assignment operator
  const ClassC& operator=(const ClassC& x){
    *ptr1=*x.ptr1;
    *ptr2=*x.ptr2;
    return *this;
  }

  //no destructor necessary
  //(default destructor lets ptr1 and ptr2 delete their objects)
  //...
};

class ClassADeleter
{
public:
  void operator()(ClassA* p){
    std::cout<<"Call delete for ClassA object"<<std::endl;
    delete p;
  }
};

template<typename T>
using uniquePtr=std::unique_ptr<T,void(*)(T*)>;//alias template

class DirCloser
{
public:
  void operator()(DIR* dp){
    if(closedir(dp)!=0){
      std::cerr<<"OOPS: closedir() failed"<<std::endl;
      return;
    }
    std::cout<<"All files closed!"<<std::endl;
    return;
  }
};

extern "C" typedef int(*DIRDeleter)(DIR*);

class ClassDDeleter{
 public:
  void operator()(int* p){
    std::cout<<"ClassDDeleter is called"<<std::endl;
  }
};

//this is a bad example
template <typename T>
void bad_print(std::auto_ptr<T> p)//p gets ownership of passed argument
{
  //does p own an object?
  if(p.get()==NULL){
    std::cout<<"NULL"<<std::endl;
  }
  else{
    std::cout<<*p<<std::endl;
  }
}//Oops, exiting deletes the object to which p refers

template <typename T>
void good_print(std::unique_ptr<T> p)
{
  if(p.get()==nullptr){
    std::cout<<"NULL"<<std::endl;
  }
  else{
    std::cout<<*p<<std::endl;
  }
}

template<typename T>
void foo5(const T& val)
{
  if(std::is_pointer<T>::value){
    std::cout<<"foo5() called for a pointer"<<std::endl;
  }
  else{
    std::cout<<"foo5() called for a value"<<std::endl;
  }
}

template <typename T>
void foo6(const T& val)
{
  std::cout<<(std::is_pointer<T>::value ? *val : val)<<std::endl;
}

//foo() implementation for pointer types:
template <typename T>
void foo_impl(const T& val, std::true_type)
{
  std::cout<<"foo() called for pointer to  "<< *val<<std::endl;
}

//foo() implementation for non-pointer types:
template<typename T>
void foo_impl(const T& val, std::false_type)
{
  std::cout<<"foo() called for value to "<<val<<std::endl;
}

template<typename T>
void foo7(const T& val)
{
  foo_impl(val, std::is_pointer<T>());
}

template<typename T>
void foo8(const T& val)//general implementation
{
  std::cout<<"is value"<<val<<std::endl;
}

//template<typename T>
//void foo8<T*>(const T& val)//partial specialization for pointers
//{
//  std::cout<<"is pointer"<<*val<<std::endl;
//}

void xoo(short){}//provide integral version
void xoo(unsigned short){}
void xoo(int){}
void xoo(float){}//provide floating-point version
void xoo(double){}
void xoo(long double){}

template<typename T>
void xoo_impl(T val, std::true_type){}//provide integral version

template<typename T>
void xoo_impl(T val, std::false_type){}//provide floating-point version

template<typename T>
void xoo1(T val)
{
  xoo_impl(val, std::is_integral<T>());
}

template<typename T1, typename T2>
typename std::common_type<T1, T2>::type minmin(const T1& x, const T2& y)
{
  return x <= y ? x : y;
}

template<typename T>
void oof(T val)
{
  std::cout<<typeid(T).name()<<"  oof is called!"<<std::endl;
}

void cnuf(int x, int y)
{
  std::cout<<"call cnuf"<<std::endl;
  std::cout<<x+y<<std::endl;
}

class dac{
public:
  void memfunc(int x, int y) const { std::cout<<"call member function"<<std::endl<<x + y<<std::endl;}
};

//function that compares two pointers by comparing the values to which they point
bool int_ptr_less(int* a, int* b)
{
  return *a < *b;
}

class MyContainer{
private:
  int* elems;//dynamic array of elements
  int numElems;//number of elements
public:
  //implementation of swap()
  void swap(MyContainer& x){
    std::swap(elems,x.elems);
    std::swap(numElems,x.numElems);
  }
};

//overloaded global swap() for this type
inline void swap(MyContainer& c1,MyContainer& c2)
  noexcept(noexcept(c1.swap(c2)))
{
  c1.swap(c2);//calls implementation of swap()
}

class XX{
public:
  bool operator==(const XX& x)const{
    return false;
  }
  bool operator<(const XX& x)const{
    return false;
  }
};

template<typename V,typename R>
std::ostream& operator<<(std::ostream& s,const std::chrono::duration<V,R>& d)
{
  s<<"["<<d.count()<<" of "<<R::num<<"/"<<R::den<<"]";
  return s;
}

template <typename C>
void printClockData()
{
  std::cout<<"- precision: ";
  //if time unit is less or equal one millisecond
  typedef typename C::period P;//type of time unit
  if(std::ratio_less_equal<P, std::milli>::value){
    //convert to and print as milliseconds
    typedef typename std::ratio_multiply<P,std::kilo>::type TT;
    std::cout<< std::fixed << double(TT::num)/TT::den<<" milliseconds"<<std::endl;
  }
  else{
    //print as seconds
    std::cout<<std::fixed<<double(P::num)/P::den<<" seconds"<<std::endl;
  }
  std::cout<<"- is_steady: "<<std::boolalpha<<C::is_steady<<std::endl;
}

//convert timepoint of system clock to calendar time string
inline
std::string asString(const std::chrono::system_clock::time_point& tp)
{
  //convert to system time:
  std::time_t t = std::chrono::system_clock::to_time_t(tp);//convert to system time
  std::string ts = std::ctime(&t);//convert to calendar time
  //std::string ts = std::asctime(std::gmtime(&t));//universal, UTC
  ts.resize(ts.size()-1);//skip trailing newline
  return ts;
}

//convert calendar time to timepoint of system clock
inline
std::chrono::system_clock::time_point
makeTimePoint(int year, int mon, int day,
              int hour, int min, int sec=0)
{
  struct std::tm t;
  t.tm_sec = sec;//second of minute(0..59 and 60 for leap seconds)
  t.tm_min = min;//minute of hour(0..59)
  t.tm_hour=hour;//hour of day(0..23)
  t.tm_mday=day;//day of month(0..31)
  t.tm_mon=mon-1;//month of year(0..11)
  t.tm_year=year-1900;//year since 1900
  t.tm_isdst=-1;//determine whether daylight saving time
  std::time_t tt=std::mktime(&t);
  if(tt==-1){
    throw "no valid system time";
  }
  return std::chrono::system_clock::from_time_t(tt);

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
  //std::tuple<int,double> xt3 = {42,3.14};//error,but now OK

  //std::vector<std::tuple<int,float>> v{{1,1.0},{2,2.0}};//error, but now OK

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
  std::tuple<int,float,std::string> tu(77,1.1,"Hello Template");
  std::cout<<"io: "<<tu<<std::endl;

  //5.1.4 tuple和pair转换
  //5.2 Smart Pointer(智能指针)
  //5.2.1 Class shared_ptr

  //two shared pointers representing two persons by their name
  std::shared_ptr<std::string> pNico(new std::string("nico"));
  std::shared_ptr<std::string> pJutta(new std::string("jutta"));

  //capitalize person names
  (*pNico)[0] = 'N';
  pJutta->replace(0,1,"J");

  //put them multiple times in a container
  std::vector<std::shared_ptr<std::string>> whoMadeCoffee;
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pNico);
  whoMadeCoffee.push_back(pJutta);
  whoMadeCoffee.push_back(pNico);

  //print all elements
  for(auto ptr : whoMadeCoffee){
    std::cout<<*ptr<<" ";
  }
  std::cout<<std::endl;

  //overwrite a name again
  *pNico = "Nicolai";

  //print all elements again
  for(auto ptr : whoMadeCoffee){
    std::cout<<*ptr<<" ";
  }
  std::cout<<std::endl;

  //print some internal data
  std::cout<<"use_count: "<<whoMadeCoffee[0].use_count()<<std::endl;

  //std::shared_ptr<std::string> pABC=new std::string("ABC");//Error
  std::shared_ptr<std::string> pDEF{new std::string("DEF")};//OK

  std::shared_ptr<std::string> pGHI=std::make_shared<std::string>("GHI");
  std::shared_ptr<std::string> pJKL=std::make_shared<std::string>("JKL");

  std::shared_ptr<std::string> pNico4;
  //pNico4 = new std::string("nico");//Error: no assignment for ordinary pointers
  pNico4.reset(new std::string("nico"));//OK

  std::shared_ptr<std::string> pmmm(new std::string("mmmmmm"),
                                    [](std::string* p){
                                      std::cout<<"delete "<< *p <<std::endl;
                                      delete p;
                                    });
  pmmm = nullptr;//pmmm does not refer to the string any longer
  whoMadeCoffee.resize(2);//all copies of the string in pNico are destroyed

  std::shared_ptr<int> py(new int[10]);//Error, but compiles
  std::shared_ptr<int> pz(new int[10],
                          [](int* p){
                            std::cout<<"delete int[]"<<std::endl;
                            delete[] p;
                          });
  std::shared_ptr<int> pw(new int[10],
                          std::default_delete<int[]>());
  std::unique_ptr<int[]> ppx(new int[10]);//OK
  //std::shared_ptr<int[]> ppy(new int[10]);//Error: does not compile

  std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"),
                                    FileDeleter("tmpfile.txt"));

  //get and attach shared memory for 100 ints:
  std::shared_ptr<int> smp(getSharedIntMemory(100));

  //init the shared memory
  for(int i = 0; i<100; ++i){
    smp.get()[i]=i*42;
  }

  //deal with shared memory somewhere else:

  for(int i=0;i<100;++i){
    std::cout << smp.get()[i]<<" ";
  }
  std::cout<<std::endl;

  std::cout<<"<return>"<<std::endl;
  std::cin.get();

  //release shared memory here:
  smp.reset();

  //5.2.2 Class weak_ptr

  std::shared_ptr<Person> ppt=initFamily("nico");

  std::cout<<"nico's family exists"<<std::endl;
  std::cout<<"- nico is shared "<<ppt.use_count()<<" times"<<std::endl;
  std::cout<<"- name of 1st kid of nico's mom: "
           <<ppt->mother->kids[0]->name<<std::endl;

  ppt=initFamily("jim");
  std::cout<<"jim's family exists" << std::endl;

  std::cout<<"-------------------------"<<std::endl;


  std::shared_ptr<Person1> ppt1=initFamily1("nico");

  std::cout<<"nico's family exists"<<std::endl;
  std::cout<<"- nico is shared "<<ppt1.use_count()<<" times"<<std::endl;
  std::cout<<"- name of 1st kid of nico's mom: "
           <<ppt1->mother->kids[0].lock()->name<<std::endl;
  ppt1=nullptr;

  //ppt1=initFamily1("jim");
  //std::cout<<"jim's family exists" << std::endl;

  std::cout<<"-------------------------"<<std::endl;

  try{
    std::shared_ptr<std::string> sp(new std::string("hi"));//create shared pointer
    std::weak_ptr<std::string> wp = sp;//create weak pointer out of it
    sp.reset();//release object of shared pointer
    std::cout<<wp.use_count()<<std::endl;//prints: 0
    std::cout<<std::boolalpha<<wp.expired()<<std::endl;//prints: true
    std::shared_ptr<std::string> pppp(wp);//throws std::bad_weak_ptr
  }
  catch(const std::exception& e){
    std::cerr<<"exception: "<<e.what()<<std::endl;//prints: bad_weak_ptr
  }

  //5.2.3 误用Shared Pointer
  int* tp=new int;
  std::shared_ptr<int> sp1(tp);
  //std::shared_ptr<int> sp2(tp);//Error: two shared pointers manage allocated int
  std::shared_ptr<int> ssp1(new int);
  std::shared_ptr<int> ssp2(ssp1);//OK

  //5.2.4 细究Shared Pointer和Weak Pointer
  auto del = [](int* p){
    delete p;
  };
  std::shared_ptr<int> xp(new int, del);
  decltype(del)* pd =std::get_deleter<decltype(del)>(xp);

  std::shared_ptr<X> pxp(new X);
  std::shared_ptr<int> pip(pxp,&pxp->a);

  std::shared_ptr<X> sspp1(new X);
  //std::shared_ptr<X> sspp2(sspp1,new X);//Error: delete for this X will never be called

  ssp1.reset();//deletes first X; make ssp1 empty
  std::shared_ptr<X> sspp3(sspp1, new X);//use_count()==0, but get()!=nullptr
  std::shared_ptr<void> xxsp(new int);//shared pointer holds a void* internally
  //std::shared_ptr<int>(static_cast<int*>(xxsp.get()));//Error: undefined behavior
  std::static_pointer_cast<int*>(xxsp);//OK

  foooo();
  //5.2.5 Class unique_ptr

  //create and initialize (pointer to) string:
  std::unique_ptr<std::string> up(new std::string("nico"));
  (*up)[0]='N';//replace first character
  up->append("lai");//append some characters
  std::cout<<*up<<std::endl;//print whole string

  //std::unique_ptr<int> up1=new int;//Error
  std::unique_ptr<int> up2(new int);//OK

  std::unique_ptr<std::string> up4;
  up4=nullptr;
  up4.reset();

  std::unique_ptr<std::string> up5(new std::string("nico"));
  std::string* sp=up5.release();//up5 loses ownership
  if(up5){//if up5 is not empty
    std::cout<<*up5<<std::endl;
  }
  if(up5==nullptr){
    std::cout<<"is empty"<<std::endl;
  }
  if(up5.get()==nullptr){
    std::cout<<"is empty"<<std::endl;
  }

  std::string* spp1=new std::string("hello");
  std::unique_ptr<std::string> upp1(spp1);
  //std::unique_ptr<std::string> upp2(spp1);//Error: upp1 and upp2 own same data

  //initialize a unique_ptr with a new object
  std::unique_ptr<X> uup1(new X);
  //copy the unique_ptr
  //std::unique_ptr<X> uup2(uup1);//Error: not possible
  //transfer ownership of the unique_ptr
  std::unique_ptr<X> uup3(std::move(uup1));//OK
  if(!uup1){
    std::cout<<"uup1 is emtpy"<<std::endl;
  }

  //initialize a unique_ptr with a new object
  std::unique_ptr<X> uupp1(new X);
  std::unique_ptr<X> uupp2;//create another unique_ptr
  //uupp2=uupp1;//Error: not possible
  uupp2 = std::move(uupp1);//assign the unique_ptr
  //- transfers ownership from uupp1 to uupp2
  if(!uupp1){
    std::cout<<"uupp1 is empty"<<std::endl;
  }
  //initialize a unique_ptr with a new object
  std::unique_ptr<X> xup1(new X);
  //initialize another unique_ptr with a new object
  std::unique_ptr<X> yup1(new X);

  yup1=std::move(xup1);//move assign the unique_ptr
  //- delete object owned by yup1
  //- transfer ownership from xup1 to yup1

  std::unique_ptr<X> axx;//create a unique_ptr
  //axx = new X;//Error
  axx = std::unique_ptr<X>(new X);//OK, delete old object and own new
  axx = nullptr;//delete the associated object, if any

  std::unique_ptr<X> fuc(new X);
  sink(std::move(fuc));//fuc loses ownership

  std::unique_ptr<X> tpp;

  for(int i = 0; i < 10; ++i){
    tpp = source();//p gets ownership of the returned object
    //(previously returned object of f() gets deleted)
  }//last-owned object of tpp gets deleted when main() is end!

  //std::unique_ptr<std::string> uck(new std::string[10]);//runtime error!
  std::unique_ptr<std::string[]> ck(new std::string[10]);//OK

  //std::cout<<*ck<<std::endl;//Error: * not defined for arrays
  std::cout<< ck[0]<<std::endl;//OK
  std::cout<<"_____________"<<std::endl;

  std::unique_ptr<ClassA,ClassADeleter> fook(new ClassA());

  std::unique_ptr<int, void(*)(int*)> fuuk(new int[10],
                                           [](int* p){
                                             std::cout<<"call in lambda"<<std::endl;
                                             delete[] p;
                                           });
  std::unique_ptr<int,std::function<void(int*)>> fcck(new int[10],
                                                      [](int* p){
                                                        std::cout<<"call lambda by function<>"<<std::endl;
                                                        delete[] p;
                                                      });
  auto lll=[](int* p){
    std::cout<<"using auto"<<std::endl;
    delete[] p;
  };
  std::unique_ptr<int, decltype(lll)> fffk(new int[10],lll);


  uniquePtr<int> uuuk(new int[10],[](int* p){
      std::cout<<"Using alias template"<<std::endl;
      delete[] p;
    });

  //open current directory:
  std::unique_ptr<DIR,DirCloser> pDir(opendir("."));

  //process each directory entry:
  struct dirent *dp;
  while((dp=readdir(pDir.get()))!=nullptr){
    std::string filename(dp->d_name);
    std::cout<<"process " <<filename<<std::endl;
  }

  std::unique_ptr<DIR, int(*)(DIR*)> ppDir(opendir("."),
                                           closedir);//might not work

  std::unique_ptr<DIR,DIRDeleter> pppDir(opendir("."),
                                         closedir);//OK

  //5.2.6细究Class unique_ptr

  ClassDDeleter cd;//instance of the deleter type
  std::unique_ptr<int,ClassDDeleter> psp1(new int, ClassDDeleter());//ClassDDeleter must be MoveConstructible
  std::unique_ptr<int,ClassDDeleter> psp2(new int, cd);//ClassDDeleter must be CopyConstructible
  std::unique_ptr<int,ClassDDeleter&> psp3(new int,cd);//psp3 holds a reference to cd
  //std::unique_ptr<int,const ClassDDeleter&> psp4(new int,ClassDDeleter());//Error: rvalue deleter object can't have reference deleter type

  //5.2.7 Class auto_ptr
  std::auto_ptr<int> pxxp(new int);
  *pxxp=42;//change value to which pxxp refers
  bad_print(pxxp);//Oops, deletes the memory to which p refers
  //*pxxp=18;//RUNTIME ERROR


  std::unique_ptr<int> pgp(new int);
  *pgp=77842;
  good_print(std::move(pgp));
  //*pgp=18;//RUNTIME ERROR

  //5.2.8 Smart Pointer结语
  //1.shared_ptr用来共享拥有权
  //2.unique_ptr用来独占拥有权
  //3.auto_ptr已经不被推荐使用

  //5.3数值的极值(Numeric Limit)

  //use textual representation for bool
  std::cout<<std::boolalpha;

  //print maximum of integral types
  std::cout<<"max(short): "<<std::numeric_limits<short>::max()<<std::endl;
  std::cout<<"max(int): "<<std::numeric_limits<int>::max()<<std::endl;
  std::cout<<"max(long): "<<std::numeric_limits<long>::max()<<std::endl;
  std::cout<<std::endl;

  //print maximum of floating-point types
  std::cout<<"max(float): "
           <<std::numeric_limits<float>::max()<<std::endl;
  std::cout<<"max(double): "
           <<std::numeric_limits<double>::max()<<std::endl;
  std::cout<<"max(long double): "
           <<std::numeric_limits<long double>::max()<<std::endl;

  //print whether char is signed
  std::cout<<"is_signed(char): "
           <<std::numeric_limits<char>::is_signed<<std::endl;
  std::cout<<std::endl;

  //print whether numeric limits for type string exist
  std::cout<<"is_specialized(string): "
           <<std::numeric_limits<std::string>::is_specialized<<std::endl;

  //5.4 Type Trait和Type Utility
  //5.4.1 Type Trait的目的

  X* pX;
  foo5(pX);

  X x5;
  foo5(x5);

  foo5(1);

  //foo6(100);*100 can't be compiled!

  foo7(100);
  int jb = 123;
  int* pjb=&jb;
  foo8(jb);
  foo8(pjb);

  xoo(jb);
  xoo1(jb);


  int jbc=123;
  long long jbcc=13999;
  std::cout<<minmin(jbcc,jbc)<<std::endl;
  std::string astr("aHello");
  char* bstr="babc";
  std::cout<<minmin(astr,bstr)<<std::endl;

  //5.4.2细究Type Trait
  std::cout<<"_________________"<<std::endl;
  std::cout<<std::is_const<int>::value<<std::endl;//false
  std::cout<<std::is_const<const volatile int>::value<<std::endl;//true
  std::cout<<std::is_const<int* const>::value<<std::endl;//true
  std::cout<<std::is_const<const int*>::value<<std::endl;//false
  std::cout<<std::is_const<const int&>::value<<std::endl;//false
  std::cout<<std::is_const<int[3]>::value<<std::endl;//false
  std::cout<<std::is_const<const int[3]>::value<<std::endl;//true
  std::cout<<std::is_const<int[]>::value<<std::endl;//false
  std::cout<<std::is_const<const int[]>::value<<std::endl;//true
  //std::cout<<std::is_const<int[] const>::value<<std::endl;//Error!

  std::cout<<"*********************"<<std::endl;

  std::cout<<std::is_assignable<int,int>::value<<std::endl;//false
  std::cout<<std::is_assignable<int&,int>::value<<std::endl;//true
  std::cout<<std::is_assignable<int&&,int>::value<<std::endl;//false
  std::cout<<std::is_assignable<long&,int>::value<<std::endl;//true
  std::cout<<std::is_assignable<int&,void*>::value<<std::endl;//false
  std::cout<<std::is_assignable<void*,int>::value<<std::endl;//false
  std::cout<<std::is_assignable<const char*,std::string>::value<<std::endl;//false
  std::cout<<std::is_assignable<std::string,const char*>::value<<std::endl;//true
  std::cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<std::endl;
  std::cout<<std::is_assignable<int*,int>::value<<std::endl;//false
  std::cout<<std::is_assignable<int,int*>::value<<std::endl;//false
  std::cout<<std::is_assignable<int,int&>::value<<std::endl;//false
  std::cout<<std::is_assignable<int,int&&>::value<<std::endl;//false
  std::cout<<std::is_assignable<int&,int*>::value<<std::endl;//false
  std::cout<<std::is_assignable<int&&,int*>::value<<std::endl;//false
  std::cout<<std::is_assignable<int&,int&&>::value<<std::endl;//false
  std::cout<<std::is_assignable<int&&,int&>::value<<std::endl;//false

  std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
  std::cout<<std::is_constructible<int>::value<<std::endl;//true
  std::cout<<std::is_constructible<int,int>::value<<std::endl;//true
  std::cout<<std::is_constructible<long,int>::value<<std::endl;//true
  std::cout<<std::is_constructible<int,void*>::value<<std::endl;//false
  std::cout<<std::is_constructible<void*,int>::value<<std::endl;//false
  std::cout<<std::is_constructible<const char*,std::string>::value<<std::endl;//false
  std::cout<<std::is_constructible<std::string,const char*>::value<<std::endl;//true
  std::cout<<std::is_constructible<std::string,const char*,int,int>::value<<std::endl;//true

  typedef int T;
  std::cout<<typeid(std::add_const<T>::type).name()<<std::endl; //const int
  std::cout<<typeid(std::add_lvalue_reference<T>::type).name()<<std::endl;//int&
  std::cout<<typeid(std::add_rvalue_reference<T>::type).name()<<std::endl;//int&&
  std::cout<<typeid(std::add_pointer<T>::type).name()<<std::endl; //int*
  std::cout<<typeid(std::make_signed<T>::type).name()<<std::endl; //int
  std::cout<<typeid(std::make_unsigned<T>::type).name()<<std::endl; //unsigned int
  std::cout<<typeid(std::remove_const<T>::type).name()<<std::endl; //int
  std::cout<<typeid(std::remove_reference<T>::type).name()<<std::endl; //int
  std::cout<<typeid(std::remove_pointer<T>::type).name()<<std::endl; //int

  typedef const int& TT;
  std::cout<<typeid(std::add_const<TT>::type).name()<<std::endl; //const int&
  std::cout<<typeid(std::add_lvalue_reference<TT>::type).name()<<std::endl; //const int&
  std::cout<<typeid(std::add_rvalue_reference<TT>::type).name()<<std::endl; //const int& (yes, lvalue remains lvalue)
  std::cout<<typeid(std::add_pointer<TT>::type).name()<<std::endl; //const int*
  //std::cout<<typeid(std::make_signed<TT>::type).name()<<std::endl; //undefined behavior
  //std::cout<<typeid(std::make_unsigned<TT>::type).name()<<std::endl; //undefined behavior
  std::cout<<typeid(std::remove_const<TT>::type).name()<<std::endl; //const int&
  std::cout<<typeid(std::remove_reference<TT>::type).name()<<std::endl; //const int
  std::cout<<typeid(std::remove_pointer<TT>::type).name()<<std::endl; //const int&

  std::cout<<std::rank<int>::value<<std::endl;
  std::cout<<std::rank<int[]>::value<<std::endl;
  std::cout<<std::rank<int[5]>::value<<std::endl;
  std::cout<<std::rank<int[][7]>::value<<std::endl;
  std::cout<<std::rank<int[5][7]>::value<<std::endl;

  std::cout<<std::extent<int>::value<<std::endl;
  std::cout<<std::extent<int[]>::value<<std::endl;
  std::cout<<std::extent<int[5]>::value<<std::endl;

  std::cout<<std::extent<int[][7]>::value<<std::endl;
  std::cout<<std::extent<int[5][7]>::value<<std::endl;
  std::cout<<std::extent<int[][7],1>::value<<std::endl;
  std::cout<<std::extent<int[5][7],1>::value<<std::endl;
  std::cout<<std::extent<int[5][7],2>::value<<std::endl;

  std::cout<<typeid(std::remove_extent<int>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_extent<int[]>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_extent<int[5]>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_extent<int[][7]>::type).name()<<std::endl;//int[7]
  std::cout<<typeid(std::remove_extent<int[5][7]>::type).name()<<std::endl;//int[7]

  std::cout<<typeid(std::remove_all_extents<int>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_all_extents<int[]>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_all_extents<int[5]>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_all_extents<int[][7]>::type).name()<<std::endl;//int
  std::cout<<typeid(std::remove_all_extents<int[5][7]>::type).name()<<std::endl;//int

  //5.4.3 Reference Wrapper（外覆器）

  int oooo=999;
  oof(std::ref(oooo));//int&
  oof(std::cref(oooo));//const int&

  //std::vector<A&> ocll;//Error!
  std::vector<std::reference_wrapper<A>> lloc;//OK

  //5.4.4 Function Type Wrapper（外覆器）
  std::vector<std::function<void(int,int)>> tasks;
  tasks.push_back(cnuf);
  tasks.push_back([](int x, int y){
      std::cout<<"call lambda"<<std::endl;
      std::cout<<x-y<<std::endl;
    });

  for(std::function<void(int,int)> f : tasks){
    f(33, 66);
  }

  std::function<void(const dac&, int, int)> mmf;
  mmf = &dac::memfunc;
  mmf(dac(),42,77);

  std::function<void(int,int)> f4;
  //f4(44,44);//throws std::bad_functon_call
  f4=cnuf;
  f4(44,44);

  //5.5辅助函数
  //5.5.1挑选最小值和最大值

  int zhux=17;
  int zhuy=42;
  int zhuz=33;
  int* pzhux=&zhux;
  int* pzhuy=&zhuy;
  int* pzhuz=&zhuz;

  //call max() with special comparison function
  int* pmax=std::max(pzhux,pzhuy,int_ptr_less);
  std::cout<<*pmax<<std::endl;

  //call minmax() for initializer list with special comparison function
  std::pair<int*,int*> extremes=std::minmax({pzhux,pzhuy,pzhuz},int_ptr_less);
  std::cout<<*extremes.first<<std::endl;
  std::cout<<*extremes.second<<std::endl;

  auto extremes1 = std::minmax({pzhux,pzhuy,pzhuz},[](int* a,int* b){
      return *a<*b;
    });
  std::cout<<*extremes1.first<<std::endl<<*extremes1.second<<std::endl;

  int i4i=1;
  long l4l=2;

  //std::max(i4i,l4l);//ERROR:argument types don't match
  //std::max({i4i,l4l});//ERROR:argument types don't match

  std::cout<<std::max<long>(i4i,l4l)<<std::endl;//OK
  std::cout<<std::max<long>({i4i,l4l})<<std::endl;;//OK

  //5.5.2两值互换（Swapping）

  int i10=11;
  long l10=111;
  //std::swap(i10,l10);//ERROR:argument types don't match
  int aa1[10];
  int aa3[11];
  //std::swap(aa1,aa3);//ERROR:arrays have different types(different sizes)

  //5.5.3增补的"比较操作符"（Comparison Operator）

  using namespace std::rel_ops;//make !=,>,etc.,available
  XX xx1,xx2;
  if(xx1!=xx2){ //ok
    std::cout<<"xx1!=xx2"<<std::endl;
  }
  if(xx1>xx2){//ok
    std::cout<<"xx1>xx2"<<std::endl;
  }

  //5.6 Class ratio<>的编译期分数运算
  typedef std::ratio<5,3> FiveThirds;
  std::cout<<FiveThirds::num <<"/"<<FiveThirds::den<<std::endl;

  typedef std::ratio<25,15> AlsoFiveThirds;
  std::cout<<AlsoFiveThirds::num<<"/"<<AlsoFiveThirds::den<<std::endl;

  std::ratio<42,42> one;
  std::cout<<one.num<<"/"<<one.den<<std::endl;

  std::ratio<0> zero;
  std::cout<<zero.num<<"/"<<zero.den<<std::endl;

  typedef std::ratio<7,-3> Neg;
  std::cout<<Neg::num<<"/"<<Neg::den<<std::endl;

  std::ratio_add<std::ratio<2,7>,std::ratio<2,6>>::type thht;
  std::cout<<thht.num<<"/"<<thht.den<<std::endl;

  std::cout<<std::ratio_equal<std::ratio<5,3>,std::ratio<25,15>>::value<<std::endl;//yields true

  //typedef std::ratio_multiply<std::ratio<1,std::numeric_limits<long long>::max()>,
  //                    std::ratio<1,2>>::type bigden;
  //std::cout<<bigden.num<<"/"<<bigden.den<<std::endl;
  typedef std::ratio<0> Zero;

  //std::ratio_divide<FiveThirds,Zero>::type d0;
  //std::cout<<d0.num<<"/"<<d0.den<<std::endl;

  std::cout<<std::nano::num<<"/"<<std::nano::den<<std::endl;

  //5.7 Clock和Timer

  //5.7.1 Chrono程序库概观

  //5.7.2 Duration（时间段）
  std::chrono::duration<int> twentySeconds(20);
  std::chrono::duration<double,std::ratio<60>> halfMinute(0.5);
  std::chrono::duration<long,std::ratio<1,1000L>> oneMillisecond(1);

  std::chrono::seconds atwentySeconds(20);
  std::chrono::hours aDay(24);
  std::chrono::milliseconds oneMillisecond1(1);

  std::chrono::seconds dxd1(42);//42 seconds
  std::chrono::milliseconds dxd2(10); //10 milliseconds
  std::cout<<(dxd1-dxd2).count()<<std::endl;

  std::chrono::duration<int,std::ratio<1,3>> tmd1(1);//1 tick of 1/3 second
  std::chrono::duration<int,std::ratio<1,5>> tmd2(1);//1 tick of 1/5 second
  std::cout<<(tmd1+tmd2).count()<<std::endl;//8 ticks of 1/15 second
  std::cout<<(tmd1<tmd2)<<std::endl;//false

  std::chrono::seconds tss(20);//20 seconds
  std::chrono::hours adday(24);//24 hours

  std::chrono::milliseconds msms;//0 milliseconds
  msms=tss+adday;//86400000milliseconds
  --msms;//86399999;milliseconds
  msms*=2;///172839998milliseconds
  std::cout<<msms.count()<<" ms"<<std::endl;
  std::cout<<std::chrono::nanoseconds(msms).count()<<" ns"<<std::endl;

  std::chrono::milliseconds dada(42);
  std::cout<<dada<<std::endl;

  std::chrono::seconds sec(59);
  //std::chrono::minutes m1=sec;//ERROR
  std::chrono::minutes m2=std::chrono::duration_cast<std::chrono::minutes>(sec);//OK
  std::cout <<  m2 <<std::endl;
  std::chrono::duration<double, std::ratio<60>> ybmin(0.5);
  //std::chrono::seconds sss1=ybmin;//ERROR
  std::chrono::seconds sss2=std::chrono::duration_cast<std::chrono::seconds>(ybmin);//OK
  std::cout << sss2 << std::endl;

  std::chrono::milliseconds mmms(7255042);

  //split into hours, minutes, seconds, and milliseconds
  std::chrono::hours hh=std::chrono::duration_cast<std::chrono::hours>(mmms);
  std::chrono::minutes mm=std::chrono::duration_cast<std::chrono::minutes>(mmms % std::chrono::hours(1));
  std::chrono::seconds s4=std::chrono::duration_cast<std::chrono::seconds>(mmms % std::chrono::minutes(1));
  std::chrono::milliseconds msec=std::chrono::duration_cast<std::chrono::milliseconds>(mmms % std::chrono::seconds(1));

  //and print durations and values:
  std::cout << "raw: " << hh << "::" << mm << "::" << s4 << "::" << msec << std::endl;

  std::cout << "     " << std::setfill('0') << std::setw(2) << hh.count() << "::"
            <<std::setw(2)<<mm.count()<<"::"
            <<std::setw(2)<<s4.count()<<"::"
            <<std::setw(3)<<msec.count()<<std::endl;

  //5.7.3 Clock （时钟）和Timepoint（时间点）

  std::cout<<"system_clock: "<<std::endl;
  printClockData<std::chrono::system_clock>();
  std::cout<<"\nhigh_resolution_clock: "<<std::endl;
  printClockData<std::chrono::high_resolution_clock>();
  std::cout<<"\nsteady_clock: "<<std::endl;
  printClockData<std::chrono::steady_clock>();

  auto system_start=std::chrono::system_clock::now();
  //std::chrono::minutes onem(1);
  //if(std::chrono::system_clock::now() > (system_start+onem)){
  //  std::cout<<"time over 1 minutes!"<<std::endl;
  // }

  std::this_thread::sleep_for(std::chrono::seconds(15));
  auto diff=std::chrono::system_clock::now()-system_start;

  auto sec1=std::chrono::duration_cast<std::chrono::seconds>(diff);
  std::cout<<"this program runs: "<<sec1.count()<<" seconds"<<std::endl;

  //print the epoch of this system clock:
  std::chrono::system_clock::time_point tp100;
  std::cout <<"epoch: "<<asString(tp100)<<std::endl;

  //print current time:
  tp100=std::chrono::system_clock::now();
  std::cout<<"now: "<<asString(tp100)<<std::endl;

  //print minimum time of this system clock:
  tp100=std::chrono::system_clock::time_point::min();
  std::cout<<"min: "<<asString(tp100)<<std::endl;

  //print maximum time of this system clock:
  tp100=std::chrono::system_clock::time_point::max();
  std::cout<<"max: "<<asString(tp100)<<std::endl;

  //define type for durations that represent day(s):
  typedef std::chrono::duration<int, std::ratio<3600*24>> Days;

  //process the epoch of this system clock
  std::chrono::time_point<std::chrono::system_clock> tp007;
  std::cout<<"epoch: "<<asString(tp007)<<std::endl;

  //add one day, 23 hours, and 55 minutes
  tp007 += Days(1)+std::chrono::hours(23)+std::chrono::minutes(55);
  std::cout<<"later: "<<asString(tp007)<<std::endl;

  //process difference from epoch in minutes and days:
  auto diff007=tp007-std::chrono::system_clock::time_point();
  std::cout<<"diff:       "
           <<std::chrono::duration_cast<std::chrono::minutes>(diff007).count()
           <<" minute(s)"<<std::endl;
  Days ddays=std::chrono::duration_cast<Days>(diff007);
  std::cout<<"diff:       "
           <<ddays.count()<<" day(s)"<<std::endl;

  //subtract one year(hoping it is valid and not a leap year)
  tp007-=std::chrono::hours(24*365);
  std::cout<<"-1 year:  "<<asString(tp007)<<std::endl;

  //subtract 50 years(hoping it is valid and ignoring leap years)
  tp007-=std::chrono::duration<int, std::ratio<3600*24*365>>(50);
  std::cout<<"-50 years: "<<asString(tp007)<<std::endl;

  //subtract 50 years(hoping it is valid and ignoring leap years)
  tp007-=std::chrono::duration<int,std::ratio<3600*24*365>>(50);
  std::cout<<"-50 years: "<<asString(tp007)<<std::endl;

  //5.7.4 C和POSIX提供的Date/Time函数
  auto tp1=makeTimePoint(2010,01,01,00,00);
  std::cout<<asString(tp1)<<std::endl;

  auto tp2=makeTimePoint(2011,05,23,13,44);
  std::cout<<asString(tp2)<<std::endl;

  //5.7.5 以计时器停滞线程（Blocking with Timer）
  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout<<"Alread wait 10 seconds!"<<std::endl;
  std::this_thread::sleep_until(std::chrono::system_clock::now()+std::chrono::seconds(10));

  //5.8头文件<cstddef>、<cstdlib>和<cstring>
  //5.8.1<cstddef>内的各项定义
  //5.8.2<cstdlib>内的各种定义
  //5.8.3<cstring>中的定义式

  return 0;
}
