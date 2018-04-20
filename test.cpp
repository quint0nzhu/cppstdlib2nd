/*
  author: Quinton
  date: 2018-4-19
  This code is the source code of The C++ Standary Library 2nd Edition.
*/




#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <set>






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
  





























  return 0;
}
