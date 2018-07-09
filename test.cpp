/*
  author: Quinton
  date: 2018-7-6
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter6
*/

#include <iostream>
#include <vector>
#include <deque>


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


  return 0;
}
