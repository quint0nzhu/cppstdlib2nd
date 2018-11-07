/*
  author: Quinton
  date: 2018-11-7
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 9
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <list>


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

  //sort, starting with the second element
  //- NONPORTABLE version
  reverse(coll.begin(),coll.end());
  if(coll.size()>1){
    sort(++coll.begin(),coll.end());//if pointer then error.
  }
  for(const auto& elem:coll){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //sort, starting with the second element
  //- PORTABLE version since C++ 11
  reverse(coll.begin(),coll.end());
  if(coll.size()>1){
    sort(next(coll.begin()),coll.end());
  }
  for(const auto& elem:coll){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //sort, starting with the second element
  //- PORTABLE version before C++ 11
  reverse(coll.begin(),coll.end());
  if(coll.size()>1){
    std::vector<int>::iterator beg=coll.begin();
    sort(++beg,coll.end());
  }
  for(const auto& elem:coll){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //9.3 迭代器相关辅助函数
  //9.3.1 advance()

  //void advance(InputIterator& pos,Dist n)
  //令名称为pos的input迭代器前进（或后退）n个元素
  //对bidirectional迭代器和random-access迭代器而言，n可为负值，表示向后退
  //Dist是个template类型。通常它必须是个整数类型，因为会调用诸如<、++、--等操作，还要和0做比较
  //advance()并不检查迭代器是否超过序列的end()（因为迭代器常不知道其所操作的容器，因此无从检查）。所以，调用advance()有可能导致不明确行为——因为“对序列尾端调用operator++”是一种未被定义的行为

  std::list<int> coll1;

  //insert elements from 1 to 9
  for(int i=1;i<=9;++i){
    coll1.push_back(i);
  }

  std::list<int>::iterator pos1=coll1.begin();

  //print actual element
  std::cout<<*pos1<<std::endl;

  //step three elements forward
  advance(pos1,3);

  //print actual element
  std::cout<<*pos1<<std::endl;

  //step one element backward
  advance(pos1,-1);

  //print actual element
  std::cout<<*pos1<<std::endl;

  //9.3.2 next()和prev()

  //ForwardIterator next(ForwardIterator pos)
  //ForwardIterator next(ForwardIterator pos，Dist n)
  //导致forward迭代器pos前进1或n个位置
  //如果处理的是bidirectional和random-access迭代器，n可为负值，导致后退（回头）移动
  //Dist是类型std::iterator_traits<ForwardIterator>::difference_type
  //其内部将对一个临时对象调用advance(pos,n)
  //注意，next()并不检查是否会跨越序列的end()。因此调用者必须自行担保其结果有效

  //BidirectionalIterator prev(BidirectionalIterator pos)
  //BidirectionalIterator prev(BidirectionalIterator pos,Dist n)
  //导致bidirectional迭代器pos后退1或n个位置
  //n可为负值，导致向前移动
  //Dist是类型std::iterator_traits<BidirectionalIterator>::difference_type
  //其内部将对一个临时对象调用advance(pos,-n)
  //注意，prev()并不检查是否会跨越序列的begin()。因此调用者必须自行担保其结果有效

  auto pos2=coll.begin();
  while(pos2!=coll.end()&&next(pos2)!=coll.end()){
    std::cout<<*pos2<<' ';
    ++pos2;
  }
  std::cout<<std::endl;

  auto pos3=coll.begin();
  auto nextPos=pos3;
  ++nextPos;
  while(pos3!=coll.end()&&nextPos!=coll.end()){
    std::cout<<*pos3<<' ';
    ++pos3;
    ++nextPos;
  }
  std::cout<<std::endl;

  auto pos4=coll.begin();
  while(pos4!=coll.end()&&pos4+1!=coll.end()){
    std::cout<<*pos4<<' ';
    ++pos4;
  }
  std::cout<<std::endl;

  //9.3.3 distance()

  //Dist distance(InputIterator pos1,InputIterator pos2)
  //返回两个input迭代器pos1和pos2之间的距离
  //两个迭代器必须指向同一个容器
  //如果不是random-access迭代器，则从pos1开始前进必须能够到达pos2,亦即pos2的位置必须与pos1相同或在其后
  //返回类型Dist是迭代器相应的defference类型：
  // iterator_traits<InputIterator>::difference_type

  std::list<int> coll2;

  //insert elements from -3 to 9
  for(int i=-3;i<=9;++i){
    coll2.push_back(i);
  }

  //search element with value 5
  std::list<int>::iterator pos5;
  pos5=find(coll2.begin(),coll2.end(),//range
            5);//value
  if(pos5!=coll2.end()){
    //process and print difference from the beginning
    std::cout<<"difference between beginning and 5: "
             <<distance(coll2.begin(),pos5)<<std::endl;
  }
  else{
    std::cout<<"5 not found"<<std::endl;
  }

  //9.3.4 iter_swap()

  //void iter_swap(ForwardIterator1 pos1,ForwardIterator2 pos2)
  //交换迭代器pos1和pos2所指的值
  //迭代器的类型不必相同，但其所指的两个值必须可以相互赋值(assignable)

  for(const auto& elem:coll1){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //swap first and second value
  iter_swap(coll1.begin(),next(coll1.begin()));//iter_swap(coll1.begin(),++coll1.begin());//ERROR: might not compile

  for(const auto& elem:coll1){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //swap first and last value
  iter_swap(coll1.begin(),prev(coll1.end()));//iter_swap(coll1.begin(),--coll1.end());//ERROR: might not compile

  for(const auto& elem:coll1){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //9.4 迭代器适配器(Iterator Adapter)
  //9.4.1 Reverse（反向）迭代器

  coll1.sort();

  //print all elements in normal order
  for_each(coll1.begin(),coll1.end(),//range
           [](const decltype(*coll1.begin())& elem){//operation
             std::cout << elem <<' ';
           });
  std::cout<<std::endl;

  //print all elements in reverse order
  for_each(coll1.crbegin(),coll1.crend(),//range
           [](const decltype(*coll1.crbegin())& elem){//operation
             std::cout <<elem<<' ';
           });
  std::cout<<std::endl;









  return 0;
}
