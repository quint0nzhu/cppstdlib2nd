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











  return 0;
}
