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
#include <algorithm>
#include <iterator>



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

  //6.2.4关联式数组(Associative Array)

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

  //6.2.5其他容器
  //6.2.6容器适配器(Container Adapter)
  //6.3迭代器(Iterator)

  std::list<char> coll9;//list container for character elements

  //append elements from 'a' to 'z'
  for(char c = 'a'; c <= 'z'; ++c){
    coll9.push_back(c);
  }

  //print all elements:
  //-iterator over all elements
  std::list<char>::const_iterator pos;
  for(pos = coll9.begin(); pos != coll9.end(); ++pos){
    std::cout << *pos << ' ';
  }
  std::cout << std::endl;

  //6.3.1关联式(Associative)及无序(Unordered)容器的更多实例

  //type of the collection
  typedef std::set<int> IntSet;

  IntSet coll10;//set container for int values

  //insert elements from 1 to 6 in arbitrary order
  //- note that there are two calls of insert() with value 1

  /*coll10.insert(3);
  coll10.insert(1);
  coll10.insert(5);
  coll10.insert(4);
  coll10.insert(1);
  coll10.insert(6);
  coll10.insert(2);*/

  coll10.insert({3,1,5,4,1,6,2,7});

  //print all elements
  //- iterate over all elements
  IntSet::const_iterator pos1;
  for(pos1 = coll10.begin(); pos1 != coll10.end(); ++pos1){
    std::cout << *pos1 << ' ';
  }
  std::cout << std::endl;

  //unordered multiset container for int values
  std::unordered_set<int> coll11;

  //insert some elements
  coll11.insert({1,3,5,7,11,13,17,19,23,27,1});

  //print all elements
  for(auto elem : coll11){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //insert one more element
  coll11.insert(25);

  //print all elements again
  for(auto elem : coll11){
    std::cout << elem  << ' ';
  }
  std::cout << std::endl;

  //6.3.2迭代器种类(Iterator Category)
  //6.4算法(Algorithm)

  //create vector with elements from 1 to 6 in arbitrary order
  std::vector<int> coll12 = {2,5,4,1,6,3};

  //find and print minimum and maximum elements
  auto minpos = min_element(coll12.cbegin(),coll12.cend());
  std::cout << "min: " << *minpos << std::endl;
  auto maxpos = max_element(coll12.cbegin(),coll12.cend());
  std::cout << "max: " << *maxpos << std::endl;

  //sort all elements
  sort(coll12.begin(),coll12.end());

  //find the first element with value 3
  //-no cbegin()/cend() because later we modify the elements pos3 refers to
  auto pos3 = find(coll12.begin(),coll12.end(),//range
                   3);//value

  //reverse the order of the found element with value 3 and all following elements
  reverse(pos3, coll12.end());

  //print all elements
  for(auto elem : coll12){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //create vector with elements from 1 to 6 in arbitrary order
  std::vector<int> coll13;
  coll13.push_back(2);
  coll13.push_back(5);
  coll13.push_back(4);
  coll13.push_back(1);
  coll13.push_back(6);
  coll13.push_back(3);

  //find and print minimum and maximum elements
  std::vector<int>::const_iterator minpos1 = min_element(coll13.begin(),
                                                         coll13.end());
  std::cout << "min: " << *minpos1 << std::endl;
  std::vector<int>::const_iterator maxpos1 = max_element(coll13.begin(),
                                                         coll13.end());
  std::cout << "max: " << *maxpos1 << std::endl;

  //sort all elements
  sort(coll13.begin(), coll13.end());

  //find the first element with value 3
  std::vector<int>::iterator pos31;
  pos31 = find(coll13.begin(), coll13.end(),//range
               3);//value

  //reverse the order of the found element with value 3 and all following elements
  reverse(pos31, coll13.end());

  //print all elements
  std::vector<int>::const_iterator pos2;
  for(pos2 = coll13.begin(); pos2 != coll13.end(); ++pos2){
    std::cout << *pos2 << ' ';
  }
  std::cout << std::endl;

  //6.4.1区间(Range)

  std::list<int> coll14;

  //insert elements from 20 to 40
  for(int i = 20; i <= 40; ++i){
    coll14.push_back(i);
  }

  //find position of element with value3
  //- there is none, so pos3 get coll.end()
  auto pos32 = find(coll14.begin(),coll14.end(),//range
                    3);//value

  //reverse the order of elements between found element and the end
  //- because pos3 is coll.end() it reverses an empty range
  reverse(pos32, coll14.end());

  //find positions of values 25 and 35
  std::list<int>::iterator pos25,pos35;
  pos25=find(coll14.begin(), coll14.end(),//range
             25);//value
  pos35=find(coll14.begin(), coll14.end(),//range
             35);//value

  //print the maximum of the corresponding range
  //- note: including pos25 but excluding pos35
  std::cout << "max: " << *max_element(pos25, pos35) << std::endl;

  //process the elements including the last position
  std::cout << "max: " << *max_element(pos25, ++pos35) << std::endl;

  //6.4.2处理多重区间(Multiple Ranges)

  std::list<int> coll15={1,2,3,4,5,6,7,8,9};
  std::vector<int> coll16;
  //RUNTIME ERROR:
  //- overwrites nonexisting elements in the destination
  //copy(coll15.cbegin(),coll15.cend(),//source
  //     coll16.begin());//destination

  //resize destination to have enough room for the overwriting algorithm
  coll16.resize(coll15.size());

  //copy elements from first into second collection
  //- overwrites existing elements in destination
  copy(coll15.cbegin(),coll15.cend(),//source
       coll16.begin());//destination

  for(auto& elem : coll16){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //create third collection with enough room
  //- initial size is passed as parameter

  std::deque<int> coll17(coll15.size());

  //copy elements from first into third collection
  copy(coll15.cbegin(),coll15.cend(),//source
       coll17.begin());//destination

  for(auto& elem : coll17){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //6.5迭代器之适配器(Iterator Adapter)
  //6.5.1 Insert Iterator（安插型迭代器）

  std::list<int> coll18={1,2,3,4,5,6,7,8,9};

  //copy the elements of coll18 into coll19 by appending them
  std::vector<int> coll19;
  copy(coll18.cbegin(),coll18.cend(),//source
       back_inserter(coll19));//destination

  for(auto& elem : coll19){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //copy the element of coll118 into coll20 by inserting them at the front
  //- reverses the order of the elements
  std::deque<int> coll20;
  copy(coll18.cbegin(),coll18.cend(),//source
       front_inserter(coll20));//destination

  for(auto& elem : coll20){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //copy elements of coll18 into coll21
  //- only inserter that works for associative collections
  std::set<int> coll21;
  copy(coll18.cbegin(),coll18.cend(),//source
       inserter(coll21,coll21.begin()));

  for(auto& elem : coll21){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //6.5.2 Stream Iterator（串流迭代器）

  std::vector<std::string> coll22;
  //read all words from the standard input
  //- source: all strings until end-of-file(or error)
  //- destination: coll22(inserting)
  copy(std::istream_iterator<std::string>(std::cin),//start of source
       std::istream_iterator<std::string>(),//end of source
       back_inserter(coll22));//destination

  //sort elements
  sort(coll22.begin(),coll22.end());

  //print all elements without duplicates
  //-source: coll22
  //-destination: standard output(with newline between elements)
  unique_copy(coll22.cbegin(),coll22.cend(),//source
              std::ostream_iterator<std::string>(std::cout,"\n"));//destination

  //6.5.3 Reverse Iterator（反向迭代器）
  








  return 0;
}
