/*
  author: Quinton
  date: 2018-7-6
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter6
*/

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <set>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>



template<typename T>
void printElements(const T& coll)
{
  for(const auto& elem : coll){
    std::cout << elem << std::endl;
  }
}


int main()
{
  //6标准模板库
  //6.1 STL组件(Component)
  //6.2 容器(Container)
  //6.2.1序列式容器(Sequence Container)
  std::vector<int> coll; //vector container for integer elements

  //append elements with values 1 to 6
  for(int i = 1; i <= 6; ++i){
    coll.push_back(i);
  }

  //print all elements followed by a space
  for(int i = 0; i < coll.size(); ++i){
    std::cout << coll[i] << ' ';
  }
  std::cout << std::endl;

  std::deque<float> coll1;//deque container for floating-point elements

  //insert elements from 1.1 to 6.6 each at the front
  for(int i = 1; i <= 6; ++i){
    coll1.push_front(i*1.1);//insert at the front
  }

  //print all elements followed by a space
  for(int i = 0; i < coll1.size(); ++i){
    std::cout << coll1[i] << ' ';
  }
  std::cout << std::endl;

  //array container of 5 string elements:
  std::array<std::string,5> coll2={"hello","world"};

  //print each element with its index on a line
  for(int i = 0; i < coll2.size(); ++i) {
    std::cout << i << ": " << coll2[i]<<std::endl;
  }

  std::list<char> coll3; // list container for character elements

  //append elements from 'a' to 'z'
  for(char c = 'a'; c <= 'z'; ++c){
    coll3.push_back(c);
  }

  //print all elements:
  //-use range-based for loop
  for(auto elem : coll3){
    std::cout << elem << ' ';
  }
  std::cout<<std::endl;

  std::list<char> coll4; //list container for character elements

  //append elements from 'a' to 'z'
  for(char c = 'a'; c <= 'z'; ++c){
    coll4.push_back(c);
  }

  //print all elements
  //- while there are elements
  //- print and remove the first element
  while(!coll4.empty()){
    std::cout << coll4.front() <<' ';
    coll4.pop_front();
  }
  std::cout<<std::endl;

  //create forward-list container for some prime numbers
  std::forward_list<long> coll5={2,3,5,7,11,13,17};

  //resize two times
  //-note: poor performance
  coll5.resize(9);
  coll5.resize(10, 99);

  //print all elements:
  for(auto elem : coll5){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //6.2.2关联式容器(Associative Container)

  std::multiset<std::string> cities{
    "Braunschweig","Hanover","Frankfurt","New York",
      "Chicago","Toronto","Paris","Frankfurt"
      };
  //print each element:
  for(const auto& elem : cities){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  //insert additional values:
  cities.insert({"London","Munich","Hanover","Braunschweig"});

  //print each element:
  for(const auto& elem : cities){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::multimap<int,std::string> coll6;//container for int/string values

  //insert some elements in arbitrary order
  //- a value with key 1 gets inserted twice

  coll6 = {{5,"tagged"},
           {2,"a"},
           {1,"this"},
           {4,"of"},
           {6,"strings"},
           {1,"is"},
           {3,"multimap"}};

  //print all element values
  //- element member second is the value
  for(auto elem : coll6){
    std::cout << elem.second << ' ';
  }
  std::cout << std::endl;

  //6.2.3无序容器(Unordered Container)

  std::unordered_multiset<std::string> cities1{
    "Braunschweig","Hanover","Frankfurt","New York",
      "Chicago","Toronto","Paris","Frankfurt"
      };

  //print each element:
  for(const auto& elem : cities1){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  //insert additional values:
  cities1.insert({"London","Munich","Hanover","Braunschweig"});

  //print each element:
  for(const auto& elem : cities1){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::unordered_map<std::string,double> coll7{
    {"time",9.9},
      {"struppi",11.77}
  };

  //square the value of each element:
  for(std::pair<const std::string,double>& elem : coll7){
    elem.second *= elem.second;
  }

  //print each element (key and value):
  for(const auto& elem : coll7){
    std::cout << elem.first << ": " << elem.second << std::endl;
  }

  //6.2.4(Associative Array)

  //type of the container:
  //-unordered_map: elements are key/value pairs
  //-string: keys have type string
  //-float: values have type float

  std::unordered_map<std::string,float> coll8;

  //insert some elements into the collection
  //-using the syntax of an associative array
  coll8["VAT1"]=0.16;
  coll8["VAT2"]=0.07;
  coll8["Pi"]=3.1415;
  coll8["an arbitrary number"]=4983.223;
  coll8["Null"]=0;

  //change value
  coll8["VAT1"]+=0.03;

  //print difference of VAT values
  std::cout << "VAT difference: " << coll8["VAT1"] - coll8["VAT2"] << std::endl;

  //6.2.5






  return 0;
}
