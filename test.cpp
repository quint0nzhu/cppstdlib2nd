/*
  author: Quinton
  date: 2018-11-7
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 9
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <deque>
#include <set>
#include <iterator> //for ostream_iterator<>



template<typename ForwardIterator>
void shift_left(ForwardIterator beg,ForwardIterator end)
{
  //temporary variable for first element
  typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;

  if(beg!=end){
    value_type tmp(*beg);
    std::cout<<tmp<<std::endl;
  }
}

//foo() for bidirectional iterators
template<typename BiIterator>
void foo(BiIterator beg,BiIterator end,std::bidirectional_iterator_tag)
{
  std::cout<<"biIterator: "<<*beg<<std::endl;
}

//foo() for random-access iterators
template<typename RaIterator>
void foo(RaIterator beg,RaIterator end,std::random_access_iterator_tag)
{
  std::cout<<"raIterator: "<<*beg<<std::endl;
}

template<typename Iterator>
inline void foo(Iterator beg,Iterator end)
{
  foo(beg,end,typename std::iterator_traits<Iterator>::iterator_category());
}

namespace mydistance{

//distance() for random-access iterators
template<typename RaIterator>
typename std::iterator_traits<RaIterator>::difference_type
distance(RaIterator pos1,RaIterator pos2,std::random_access_iterator_tag)
{
  return pos2-pos1;
}

//distance() for input,forward,and bidirectional iterators
template<typename InIterator>
typename std::iterator_traits<InIterator>::difference_type
distance(InIterator pos1,InIterator pos2,std::input_iterator_tag)
{
  typename std::iterator_traits<InIterator>::difference_type d;
  for(d=0;pos1!=pos2;++pos1,++d){
    ;
  }
  return d;
}

//general distance()
template<typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
distance(Iterator pos1,Iterator pos2)
{
  return distance(pos1,pos2,typename std::iterator_traits<Iterator>::iterator_category());
}

}



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

  //create list with elements from 1 to 9
  std::vector<int> coll3={1,2,3,4,5,6,7,8,9};

  //find position of element with value 5
  std::vector<int>::const_iterator pos6;
  pos6=find(coll3.cbegin(),coll3.cend(),
            5);

  //print value to which iterator pos refers
  std::cout<<"pos: "<<*pos6<<std::endl;

  //convert iterator to reverse iterator rpos
  std::vector<int>::const_reverse_iterator rpos(pos6);

  //print value to which reverse iterator rpos refers
  std::cout<<"rpos: "<<*rpos<<std::endl;

  //create deque with elements from 1 to 9
  std::deque<int> coll4={1,2,3,4,5,6,7,8,9};

  //find position of element with value 2
  std::deque<int>::const_iterator pos7;
  pos7=find(coll4.cbegin(),coll4.cend(),//range
            2);//value

  //find position of element with value 7
  std::deque<int>::const_iterator pos8;
  pos8=find(coll4.cbegin(),coll4.cend(),//range
            7);//value

  //print all elements in range [pos7,pos8)
  for_each(pos7,pos8,//range
           [](const decltype(*coll4.cbegin())& elem){
             std::cout<<elem<<' ';
           });//operation
  std::cout<<std::endl;

  //convert iterators to reverse iterators
  std::deque<int>::const_reverse_iterator rpos1(pos7);
  std::deque<int>::const_reverse_iterator rpos2(pos8);

  //print all elements in range[pos7,pos8] in reverse order
  for_each(rpos2,rpos1,//range
           [](const decltype(*coll4.crbegin())& elem){
             std::cout<<elem<<' ';
           });//operation
  std::cout<<std::endl;

  //create list with elements from 1 to 9
  std::list<int> coll5={1,2,3,4,5,6,7,8,9};

  //find position of element with value 5
  std::list<int>::const_iterator pos9;
  pos9=find(coll5.cbegin(),coll5.cend(),//range
            5);//value

  //print value of the element
  std::cout<<"pos: "<<*pos9<<std::endl;

  //convert iterator to reverse iterator
  std::list<int>::const_reverse_iterator rpos3(pos9);

  //print value of the element to which the reverse iterator refers
  std::cout<<"rpos: "<<*rpos3<<std::endl;

  //convert reverse iterator back to normal iterator
  std::list<int>::const_iterator rrpos;
  rrpos=rpos3.base();

  //print value of the element to which the normal iterator refers
  std::cout<<"rrpos: "<<*rrpos<<std::endl;

  //9.4.2 Insert（安插型）迭代器

  std::vector<int> coll6;

  //create back inserter for coll6
  //-inconvenient way
  std::back_insert_iterator<std::vector<int>> iter(coll6);

  //insert elements with the usual iterator interface
  *iter=1;
  iter++;
  *iter=2;
  iter++;
  *iter=3;

  for_each(coll6.cbegin(),coll6.cend(),[](const decltype(*coll6.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //create back inserter and insert elements
  //-convenient way
  back_inserter(coll6)=44;
  back_inserter(coll6)=55;
  for_each(coll6.cbegin(),coll6.cend(),[](const decltype(*coll6.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //use back inserter to append all elements again
  //-reserve enough memory to avoid reallocation
  coll6.reserve(2*coll6.size());
  copy(coll6.cbegin(),coll6.cend(),//source
       back_inserter(coll6));//destination
  for_each(coll6.cbegin(),coll6.cend(),[](const decltype(*coll6.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  std::list<int> coll7;

  //create front inserter for coll7
  //-inconvenient way
  std::front_insert_iterator<std::list<int>> iter1(coll7);

  //insert elements with the usual iterator interface
  *iter1=1;
  iter1++;
  *iter1=2;
  iter1++;
  *iter1=3;

  for_each(coll7.cbegin(),coll7.cend(),[](const decltype(*coll7.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //create front inserter and insert elements
  //-convenient way
  front_inserter(coll7)=44;
  front_inserter(coll7)=55;

  for_each(coll7.cbegin(),coll7.cend(),[](const decltype(*coll7.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //use front inserter to insert all elements again
  copy(coll7.begin(),coll7.end(),//source
       front_inserter(coll7));//destination

  for_each(coll7.cbegin(),coll7.cend(),[](const decltype(*coll7.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  std::set<int> coll8;
  //create insert iterator for coll8
  //-inconvenient way
  std::insert_iterator<std::set<int>> iter2(coll8,coll8.begin());

  //insert elements with the usual iterator interface
  *iter2=1;
  iter2++;
  *iter2=2;
  iter2++;
  *iter2=3;

  for_each(coll8.cbegin(),coll8.cend(),[](const decltype(*coll8.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //create inserter and insert elements
  //-convenient way
  inserter(coll8,coll8.end())=44;
  inserter(coll8,coll8.end())=55;

  for_each(coll8.cbegin(),coll8.cend(),[](const decltype(*coll8.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //use inserter to insert all elements into a list
  std::list<int> coll9;
  copy(coll8.cbegin(),coll8.cend(),//source
       inserter(coll9,coll9.begin()));//destination

  for_each(coll9.cbegin(),coll9.cend(),[](const decltype(*coll9.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //use inserter to reinsert all elements into the list before the second element
  copy(coll8.cbegin(),coll8.cend(),//source
       inserter(coll9,++coll9.begin()));//destination

  for_each(coll9.cbegin(),coll9.cend(),[](const decltype(*coll9.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //9.4.3 Stream（串流）迭代器

  //create ostream iterator for stream cout
  //-vlaues are separated by a newline character
  std::ostream_iterator<int> intWriter(std::cout,"\n");

  //write elements with the usual iterator interface
  *intWriter=42;
  intWriter++;
  *intWriter=77;
  intWriter++;
  *intWriter=-5;

  //create collection with elements from 1 to 9
  std::vector<int> coll10={1,2,3,4,5,6,7,8,9};

  //write all elements without any delimiter
  copy(coll10.cbegin(),coll10.cend(),std::ostream_iterator<int>(std::cout));
  std::cout<<std::endl;

  //write all elements with " < " as delimiter
  std::string delim=" < ";
  copy(coll10.cbegin(),coll10.cend(),std::ostream_iterator<int>(std::cout,delim.c_str()));
  std::cout<<std::endl;

  //create istream iterator that reads integers from cin
  std::istream_iterator<int> intReader(std::cin);

  //create end-of-stream iterator
  std::istream_iterator<int> intReaderEOF;

  //while able to read tokens with istream iterator
  //-write them twice
  while(intReader!=intReaderEOF){
    std::cout<<"once:        "<<*intReader<<std::endl;
    std::cout<<"once again: "<<*intReader<<std::endl;
    ++intReader;
  }

  std::istream_iterator<std::string> cinPos(std::cin);
  std::ostream_iterator<std::string> coutPos(std::cout," ");

  //while input is not at the end of the file
  //-write every third string
  while(cinPos!=std::istream_iterator<std::string>()){
    //ignore the following two strings
    advance(cinPos,2);

    //read and write the third string
    if(cinPos!=std::istream_iterator<std::string>()){
      *coutPos++=*cinPos++;
    }
    std::cout<<std::endl;
  }

  //9.4.4 Move（搬移）迭代器

  std::list<std::string> s{"a","b","c"};
  std::vector<std::string> v1(s.begin(),s.end());//copy strings into v1
  std::vector<std::string> v2(make_move_iterator(v1.begin()),//move strings into v2
                              make_move_iterator(v1.end()));
  for_each(v2.cbegin(),v2.cend(),[](const decltype(*v2.cbegin())& elem){
      std::cout<<elem<<' ';
    });
  std::cout<<std::endl;

  //9.5 Iterator Trait（迭代器特性）
  //9.5.1 为迭代器编写泛型函数(Generic Function)

  shift_left(v2.begin(),v2.end());

  foo(s.begin(),s.end());

  foo(++v2.begin(),v2.end());

  std::cout<<mydistance::distance(s.begin(),s.end())<<std::endl;

  std::cout<<mydistance::distance(++v2.begin(),v2.end())<<std::endl;

  //9.6 用户自定义(User-Defined)迭代器
  





  return 0;
}
