/*
  author: Quinton
  date: 2018-4-19
  This code is the source code of The C++ Standary Library 2nd Edition.
*/




#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <bitset>
#include <complex>
#include <limits>
#include <functional>






void f(int)
{
  std::cout << "Call f(int)" << std::endl;
}

void f(void*)
{
  std::cout << "Call f(void*)" << std::endl;
}

double f1(){
  std::cout << "call f1()" << std::endl;
}

void print(std::initializer_list<int> vals)
{
  for(auto p=vals.begin(); p!=vals.end();++p){
    std::cout << *p << "\n";
  }
}

class P
{
public:
  P(int,int){}
  P(std::initializer_list<int>){}
};

class PP
{
public:
  PP(int,int){}
  explicit PP(int,int,int){}
};

void fp(const PP&)
{
  std::cout<< "call fp(const PP&)" << std::endl;
}

template <typename T>
void printElements(const T& coll)
{
  for(const auto& elem : coll){
    std::cout << elem << std::endl;
  }
}

class C
{
public:
  explicit C(const std::string& s){}//explicit type conversion from strings
};

class D
{
public:
  D(){std::cout<< "default constructor of D" << std::endl;}
  D(const D&){std::cout << "copy constructor of D" << std::endl;}
  D(D&&){std::cout << "move constructor of D" << std::endl;}
  D& operator=(const D&){std::cout<< "assign constructor of D"<< std::endl; return *this;}
  D& operator=(D&&){std::cout<< "move assignment operator"<<std::endl; return *this;}
  D& operator+(const D&){std::cout << "+" << std::endl; return  *this;}
};

void createAndInsert(std::vector<D>& coll)
{
  D d;
  coll.push_back(std::move(d));
}


template<typename T>
void swap(T& x ,T& y)noexcept(noexcept(x.swap(y)))
{
  x.swap(y);
}

class E
{
public:
  E(){}
  void swap(E&){}
};

constexpr int square(int x)
{
  return x * x;
}

void print()
{
  
}

template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
  std::cout << "the number of args" << sizeof...(args) << std::endl;
  std::cout << firstArg << std::endl; //print first argument
  print(args...);//call print() for remaining arguments
}


template<typename T>
using Vvec = std::vector<T>;

std::function<int(int,int)> returnLambda()
{
  return [](int x, int y){
    return x*y;
  };
}


int main()
{
  //1.右尖括号中间要空格的要求没有了，新的空指针类型有了明确的定义
  std::vector<std::list<int> > a;
  std::vector<std::list<int>> b;
  f(0);
  f((void*)NULL);
  f(nullptr);

  //2.以auto完成类型自动推导
  auto i = 42;
  auto ff = f1();
  static auto vat = 0.1;
  std::vector<int> v(100);
  auto pos = v.begin();

  auto l = [](int x) -> bool {
    std::cout << "This is a lambda express" << std::endl;
  };
  l(1);

  //3.一致性初始化与初值列
  int values[]{1,2,3};
  std::vector<int> v1{2,3,5,7,11,13,17};
  std::vector<std::string> cities{
    "Berlin","New York","London", "Braunschweig","Cairo","Cologna"
      };
  std::complex<double> c{4.0,3.0};
  int j{};//j=0
  int ii;//ii has undefine value
  int* p;//p has undefine value
  int* q{};//q is initialized by nullptr
  int x1(5.3);//x1 becomes 5;
  int x2 = 5.3; //x2 becomes 5;
  // int x3{5.0}; //error:narrowing
  //int x4={5.3};//error:narrowing
  char c1{7};//this is ok
  //char c2{99999};//error:narrowing(if 99999 doesn't fit into a char)
  std::vector<int> vv1{1,2,4,5};//ok
  //std::vector<int> vv2{1,2,3,4,5.6};//error:narrowing doubles to ints
  print({12,3,5,7,11,13,17});
  P pp(77,5);//calls P::P(int,int)
  P qq{77,5};//calls P::P(initializer_list)
  P r{77,5,42};//calls P::P(initializer_list)
  P s={77,5};//calls P:P(initializer_list)

  PP x(77,5);//OK
  PP y{77,5};//OK
  PP z{77,5,42};//OK
  PP u={77,5};//OK(implicit type conversion allowed)
  //PP w={77,5,42};//error:due to explicit(no implicit type conversion allowed)

  fp({47,11});//OK,implicit conversion of {47,11} into PP
  //fp({47,11,3});//error:due to explicit
  fp(PP{47,11});//OK,explicit conversion of {47,11} into PP
  fp(PP{47,11,3});//OK,explicit conversion of {47,11,3} into PP

  //4.Range-Based for 循环
  for(int i : {2,3,5,7,8,9,45,433,24}){
    std::cout << i << std::endl;
  }

  std::vector<double> vec{1.2,1.1,1.11,1.111};
  for(auto& elem : vec){
    elem *= 3;
  }
  printElements(vec);

  int array[]={1,2,3,4,5};

  long sum=0;
  for(int x : array){
    sum += x;
  }
  for(auto elem : {sum, sum*2, sum *4}){
    std::cout << elem << std::endl;
  }
  std::vector<std::string> vs{"Hello","world","!"};
  //for(const C& elem : vs){//error:no conversion from string to C defined
  //  std::cout << "elem" << std::endl;
  //}

  //5.Move语义和Rvalue Reference
  std::vector<D> dd(5);

  createAndInsert(dd);
  createAndInsert(dd);
  createAndInsert(dd);

  //6.新式的字符串字面常量(String Literal)
  std::cout << R"(\\n)" << std::endl;
  std::cout << "\\\\n" << std::endl;
  std::cout << R"nc(a()\")nc" << std::endl;

  //7.
  E e1;
  E e2;
  swap(e1,e2);

  //8.
  float a3[square(9)];
  std::cout << sizeof(a3)/sizeof(a3[0]) << std::endl;
  std::array<float,std::numeric_limits<short>::max()> a4;
  std::cout << a4.size() << std::endl;

  //9.
  print(7.5, "hello", std::bitset<16>(377), 42);

  Vvec<int> coll;

  //10.
  []{
    std::cout << "Hello lambda" << std::endl;
  };

  []{
    std::cout << "hello lambda" << std::endl;
  }();

  auto l1 = []{
    std::cout << "Hello Lambda" << std::endl;
  };

  l1();

  auto l2=[](const std::string& s){
    std::cout << s << std::endl;
  };

  l2("hello another lambda");

  []{
    return 42;
  };

  auto l4 = []()->double{
    return 42.13;
  };

  std::cout << l4() << std::endl;

  int xa=0;
  int ya=42;
  auto qqq = [xa, &ya]{
    std::cout <<"xa: "<<xa<<std::endl;
    std::cout <<"ya: "<<ya<<std::endl;
    ++ya;
  };
  xa=ya=77;
  qqq();
  qqq();
  std::cout<<"final ya: "<<ya<<std::endl;

  int id=0;
  auto ff1=[id]()mutable{
    std::cout<<"id: " << id << std::endl;
    ++id;
  };
  id = 42;
  ff1();
  ff1();
  ff1();
  std::cout << id << std::endl;

  auto lf=returnLambda();
  std::cout<<lf(60,70)<<std::endl;

  //11.
  









  return 0;
}
