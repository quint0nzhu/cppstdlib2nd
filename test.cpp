/*
  author: Quinton
  date: 2018-7-24
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter7
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>


int main()
{
  //7 STL容器
  //7.1容器的共通能力和共通操作
  //7.1.1容器的共通能力
  //7.1.2容器的共通操作

  //initialize a vector with some specific values (since C++11)
  const std::vector<int> v1 = {1,2,3,5,7,11,13,17,21};
  for(const auto& elem : v1){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //same with different syntax
  const std::vector<int> v2 {1,2,3,5,7,11,13,17,21};
  for(const auto& elem : v2){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //initialize an unordered set with "hello" and two empty strings
  std::unordered_set<std::string> w = {"hello",std::string(),""};
  for(const auto& elem : w){
    std::cout << elem << std::endl;
  }
  std::cout << std::endl;

  




  return 0;
}
