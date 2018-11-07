/*
  author: Quinton
  date: 2018-11-7
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 9
*/

#include <vector>
#include <iostream>


int main()
{
  //第9章 STL迭代器
  //9.1 迭代器头文件(Header Files for Iterators)
  //9.2 迭代器种类(Iterator Category)
  //9.2.1 Output迭代器
  //while(...){
  //  *pos=...;//assign a value
  //  ++pos;//advance(prepare for the next assignment)
  //}

  //9.2.2 Input迭代器
  //InputIterator pos,end;

  //while(pos!=end){
  //  ...//read-only access using *pos
  //  ++pos;
  //}
  //++pos; //OK and fast
  //pos++ //OK,but not so fast

  //9.2.3 Forward（前向）迭代器

  //ForwardIterator pos1,pos2;

  //pos1=pos2=begin;//both iterators refer to the same element
  //if(pos1!=end){
  //  ++pos1;//pos1 in one element ahead
  //  while(pos1!=end){
  //    if(*pos1==*pos2){
  //      ...//process adjacent duplicates
  //      ++pos1;
  //      ++pos2;
  //    }
  //  }
  //}

  //9.2.4 Bidirectional（双向）迭代器
  //9.2.5 Random-Access（随机访问）迭代器

  std::vector<int> coll;

  //insert elements from -3 to 9
  for(int i=-3;i<=9;++i){
    coll.push_back(i);
  }

  //print number of elements by processing the distance between beginning and end
  //-NOTE: uses operator - for iterators

  std::cout<<"number/distance: "<<coll.end()-coll.begin()<<std::endl;

  //print all elements
  //-NOTE: uses operator < instead of operator !=
  std::vector<int>::iterator pos;
  for(pos=coll.begin();pos<coll.end();++pos){
    std::cout<<*pos<<' ';
  }
  std::cout<<std::endl;

  //print all elements
  //-NOTE: uses operator [] instead of operator *
  for(int i=0;i<coll.size();++i){
    std::cout<<coll.begin()[i]<<' ';
  }
  std::cout<<std::endl;

  //print every second element
  //-NOTE: uses operator +=
  for(pos=coll.begin();pos<coll.end()-1; pos+=2){//if end() not end()-1 then undefine behavor
    std::cout<<*pos<<' ';
  }
  std::cout<<std::endl;

  //9.2.6 Vector迭代器的递增(Increment)和递减(Decrement)
  






  return 0;
}
