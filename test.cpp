/*
  author: Quinton
  date: 2018-12-7
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 17
*/


#include <random>
#include <iostream>
#include <algorithm>
#include <vector>



int main(int argc, char* argv[])
{
  //第17章 数值
  //17.1 随机数及分布(Random Number and Distribution)
  //一个引擎和一个分布的组合

  //17.1.1 第一个例子

  //create default engine as source of randomness
  std::default_random_engine dre;

  //use engine to generate integral numbers between 10 and 20(both included)
  std::uniform_int_distribution<int> di(10,20);
  for(int i=0;i<20;++i){
    std::cout<<di(dre)<<" ";
  }
  std::cout<<std::endl;

  //use engine to generate floating-point numbers between 10.0 and 20.0
  //(10.0 included, 20.0 not included)
  std::uniform_real_distribution<double> dr(10,20);
  for(int i=0;i<8;++i){
    std::cout<<dr(dre)<<" ";
  }
  std::cout<<std::endl;

  //use engine to shuffle elements
  std::vector<int> v={1,2,3,4,5,6,7,8,9};

  std::shuffle(v.begin(),v.end(),//range
               dre);//source of randomness
  for(int i=0;i<v.size();++i){
    std::cout<<v[i]<<" ";
  }
  std::cout<<std::endl;


  return 0;
}
