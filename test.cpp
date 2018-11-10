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


  return 0;
}
