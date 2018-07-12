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



template<typename T>
void printElements(const T& coll)
{
  for(const auto& elem : coll){
    std::cout << elem << std::endl;
  }
}


int main()
{
  //6.
  //6.1 STL
  //6.2 Container
  //6.2.1 Sequence Container
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

  return 0;
}
