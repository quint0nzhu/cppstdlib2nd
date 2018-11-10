/*
  author: Quinton
  date: 2018-11-9
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 10
*/

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <list>
#include <functional> //Predefined Function Object and Binder
#include <locale>


class Person{
private:
  std::string fname;
  std::string lname;
public:
  Person(std::string fn,std::string ln):fname(fn),lname(ln){}
  std::string firstname()const{return fname;}
  std::string lastname()const{return lname;}
};

//class for function predicate
//-operator() returns whether a person is less than another person
class PersonSortCriterion{
public:
  bool operator()(const Person& p1,const Person& p2)const{
    //a person is less than another person
    //-if the last name is less
    //-if the last name is equal and the first name is less
    return p1.lastname()<p2.lastname()||
                         (p1.lastname()==p2.lastname() &&
                          p1.firstname()<p2.firstname());
  }
};

class IntSequence{
private:
  int value;
public:
  IntSequence(int initialValue)//constructor
    :value(initialValue){}

  int operator()(){//"functiona call"
    return ++value;
  }
};

//function object to process the mean value
class MeanValue{
private:
  long num;//number of elements
  long sum;//sum of all element values
public:
  //contructor
  MeanValue():num(0),sum(0){}

  //"function call"
  //-process one more element of the sequence
  void operator()(int elem){
    ++num;//increment count
    sum+=elem;//add value
  }

  //return mean value
  double value(){
    return static_cast<double>(sum)/static_cast<double>(num);
  }
};

class Nth{//function object that returns true for the nth call
private:
  int nth;//call for which to return true
  int count;//call counter
public:
  Nth(int n):nth(n),count(0){}
  bool operator()(int){
    return ++count==nth;
  }
};

char myToupper(char c)
{
  std::locale loc;
  return std::use_facet<std::ctype<char>>(loc).toupper(c);
}

void incr(int& i)
{
  ++i;
}

class Person1{
private:
  std::string name;
public:
  Person1(const std::string& n):name(n){}
  void print()const{
    std::cout<<name<<std::endl;
  }
  void print2(const std::string& prefix)const{
    std::cout<<prefix<<name<<std::endl;
  }
};


int main()
{
  //第10章 STL函数对象及Lambda
  //10.1 Function Object（函数对象）的概念
  //10.1.1 以Function Object排序准则(Sorting Criterion)

  //create a set with special sorting criterion
  std::set<Person,PersonSortCriterion> coll;
  coll.insert({Person("ab","cd"),Person("ab","ac"),Person("aa","ac")});

  for(const auto& elem:coll){
    std::cout<<elem.firstname()<<" "<<elem.lastname()<<std::endl;
  }

  //10.1.2 Function Object拥有内部状态(Internal State)

  std::list<int> coll1;

  //insert values from 1 to 9
  generate_n(std::back_inserter(coll1),//start
             9,//number of elements
             IntSequence(1));//generates values, starting with 1

  for(const auto& elem:coll1){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //replace second to last element but one with values starting a 42
  generate(next(coll1.begin()),//start
           prev(coll1.end()),//end
           IntSequence(42));//generates values, starting with 42

  for(const auto& elem:coll1){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  std::list<int> coll2;
  IntSequence seq(1);//integral sequence starting with 1

  //insert values from 1 to 4
  //-pass function object by reference
  // so that it will continue with 5
  std::generate_n<std::back_insert_iterator<std::list<int>>,
             int,IntSequence&>(back_inserter(coll2),//start
                               4,//number of elements
                               seq);//generates values
  for(const auto& elem:coll2){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //insert values from 42 to 45
  std::generate_n(std::back_inserter(coll2),//start
             4,//number of elements
             IntSequence(42));//generates values

  for(const auto& elem:coll2){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //continue with first sequence
  //-pass function object by value
  // so that it will continue with 5 again
  generate_n(back_inserter(coll2),//start
             4,//number of elements
             seq);//generates values

  for(const auto& elem:coll2){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //continue with first sequence again
  generate_n(back_inserter(coll2),//start
             4,//number of elements
             seq);//generates values

  for(const auto& elem:coll2){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //10.1.3 for_each()返回值

  std::vector<int> coll3={1,2,3,4,5,6,7,8};

  //process and print mean value
  MeanValue mv=for_each(coll3.begin(),coll3.end(),//range
                        MeanValue());//operation
  std::cout<<"mean value: "<<mv.value()<<std::endl;

  //10.1.4 Predicate（判断式）vs. Function Object（函数对象）

  std::list<int> coll4={1,2,3,4,5,6,7,8,9,10};
  for(const auto& elem:coll4){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //remove third element
  std::list<int>::iterator pos;
  pos = remove_if(coll4.begin(),coll4.end(),//range
                  Nth(3));//remove criterion
  coll4.erase(pos,coll4.end());//list要把移除的东西，从尾端删除掉！

  for(const auto& elem:coll4){
    std::cout<<elem<<" ";
  }
  std::cout<<std::endl;

  //10.2 预定义的Function Object和Binder
  //10.2.1 预定义的Function Object
  //10.2.2 Function Adapter和Binder

  auto plus10=std::bind(std::plus<int>(),std::placeholders::_1,10);
  std::cout<<"+10: "<<plus10(7)<<std::endl;

  auto plus10times2=std::bind(std::multiplies<int>(),
                              std::bind(std::plus<int>(),
                                        std::placeholders::_1,
                                        10),
                              2);
  std::cout<<"+10 *2:  "<<plus10times2(7)<<std::endl;

  auto pow3=std::bind(std::multiplies<int>(),std::bind(std::multiplies<int>(),
                                                       std::placeholders::_1,
                                                       std::placeholders::_1),
                      std::placeholders::_1);
  std::cout<<"x*x*x: "<<pow3(7)<<std::endl;

  auto inversDivide=std::bind(std::divides<double>(),
                              std::placeholders::_2,
                              std::placeholders::_1);
  std::cout<<"invdiv: "<<inversDivide(49,7)<<std::endl;

  std::cout<<std::bind(std::plus<int>(),std::placeholders::_1,10)(32)<<std::endl;

  //add 10 to each element
  transform(coll4.begin(),coll4.end(),//source
            coll4.begin(),//destination
            std::bind(std::plus<int>(),std::placeholders::_1,10));//operation
  for(const auto& elem:coll4){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //find first element >12
  auto pos1=std::find_if(coll4.begin(),coll4.end(),
                         std::bind(std::greater<int>(),std::placeholders::_1,12));
  std::cout<<*pos1<<std::endl;

  std::string s("Internationalization");
  std::string sub("Nation");

  //search substring case insensitive
  std::string::iterator pos2;
  pos2=search(s.begin(),s.end(),//string to search in
              sub.begin(),sub.end(),//substring to search
              std::bind(std::equal_to<char>(),//compar.criterion
                        std::bind(myToupper,std::placeholders::_1),
                        std::bind(myToupper,std::placeholders::_2)));
  if(pos2!=s.end()){
    std::cout<<"\""<<sub<<"\" is part of \""<<s<<"\""<<std::endl;
  }

  int i=0;
  std::bind(incr,i)();//increments a copy of i, no effect for i
  std::bind(incr,std::ref(i))();//increments i

  std::vector<Person1> coll5
    ={Person1("Tick"),Person1("Trick"),Person1("Track")};

  //call member function print() for each person
  for_each(coll5.begin(),coll5.end(),
           std::bind(&Person1::print,std::placeholders::_1));
  std::cout<<std::endl;

  //call member function print2() with additional argument for each person
  for_each(coll5.begin(),coll5.end(),
           std::bind(&Person1::print2,std::placeholders::_1,"Person1: "));
  std::cout<<std::endl;

  //call print2() for temporary Person
  std::bind(&Person1::print2,std::placeholders::_1,"This is: ")(Person1("nico"));



  return 0;
}
