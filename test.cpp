/*
  author: Quinton
  date: 2018-11-12
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 11
*/

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <iostream>
#include <string>

//INSERT_ELEMENTS(collection,first,last)
//-fill values from first to last into the collection
//-NOTE: NO half-open range
template<typename T>
inline void INSERT_ELEMENTS(T& coll,int first,int last)
{
  for(int i=first;i<=last;++i){
    coll.insert(coll.end(),i);
  }
}

//PRINT_ELEMENTS()
//-prints optional string optcstr followed by
//-all elements of the collection coll
//-separated by spaces
template<typename T>
inline void PRINT_ELEMENTS(const T& coll,const std::string& optcstr="")
{
  std::cout<<optcstr;
  for(auto elem:coll){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;
}

//PRINT_MAPPED_ELEMENTS()
//-prints optional string optcstr followed by
//-all elements of the key/value collection coll
//-separated by spaces
template<typename T>
inline void PRINT_MAPPED_ELEMENTS(const T& coll,
                                  const std::string& optcstr="")
{
  std::cout<<optcstr;
  for(auto elem:coll){
    std::cout<<'['<<elem.first
             <<','<<elem.second<<"] ";
  }
  std::cout<<std::endl;
}

void print(int elem)
{
  std::cout<<elem<<' ';
}

//function object that adds the value with which it is initialized
template<typename T>
class AddValue{
private:
  T theValue;//value to add
public:
  //constructor initializes the value to add
  AddValue(const T& v):theValue(v){}

  //the function call for the element adds the value
  void operator()(T& elem)const{
    elem+=theValue;
  }
};

//function object to process the mean value
class MeanValue{
private:
  long num;//number of elements
  long sum;//sum of all element values
public:
  //constructor
  MeanValue():num(0),sum(0){}

  //function call
  //-process one more element of the sequence
  void operator()(int elem){
    num++;//increment count
    sum+=elem;//add value
  }

  //return mean value (implicit type conversion)
  operator double(){
    return static_cast<double>(sum)/static_cast<double>(num);
  }
};






int main()
{
  //第11章 STL算法
  //11.1 算法头文件(Header File)
  //11.2 算法概观
  //11.2.1 扼要介绍
  //11.2.2 算法分门别类

  //void square(int& elem)//call-by-reference
  //{
  //  elem=elem*elem;//assign processed value directly
  //}
  //...
  //for_each(coll.begin(),coll.end(),//range
  //         square);//operation modifying algorithm

  //int square(int elem)//call-by-value
  //{
  //  return elem*elem;
  //}
  //...
  //transform(coll.cbegin(),coll.cend(),//source range
  //          coll.begin(),//destination range
  //          square);//operation

  //sort all elements
  //-best n*log(n) complexity on average
  //-n*n complexity in worst case
  //sort(coll.begin(),coll.end());

  //sort all elements
  //-always n*log(n) complexity
  //-but usually twice as long as sort()
  //partial_sort(coll.begin(),coll.end(),coll.end());

  //sort all elements
  //-n*log(n) or n*log(n)*log(n) complexity
  //stable_sort(coll.begin(),coll.end());

  //sort all elements
  //-n+n*log(n) complexity
  //make_heap(coll.begin(),coll.end());
  //sort_heap(coll.begin(),coll.end());

  //move the four lowest elements to the front
  //nth_element(coll.begin(),//beginning of range
  //            coll.begin()+3,//position between first and second part
  //            coll.end());//end of range

  //move all elements less than seven to the front
  //vector<int>::iterator pos;
  //pos=partition(coll1.begin(),coll1.end(),//range
  //              [](int elem){//criterion
  //                return elem<7;
  //              });

  //11.3 辅助函数
  //11.4 for_each()算法

  //UnaryProc
  //for_each(InputIterator beg,InputIterator end,UnaryProc op)
  //对区间[beg,end)中的每一个元素调用：
  // op(elem)
  //返回op（它已在算法内部被改动过）的一个拷贝（副本）。Since C++ 11, the returned op is moved
  //op可以改动元素。然而，请参考与transform()之间的比较，后者具有相同能力，但行事稍有不同
  //op的任何返回值都会被忽略
  //复杂度：线性。调用op()共numElems次

  std::vector<int> coll;

  INSERT_ELEMENTS(coll,1,9);

  //call print() for each element
  for_each(coll.begin(),coll.end(),//range
           [](int elem){//operation
             std::cout<<elem<<' ';
           });
  std::cout<<std::endl;

  for_each(coll.begin(),coll.end(),//range
           print);//operation
  std::cout<<std::endl;

  for(auto elem:coll){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //add 10 to each element
  for_each(coll.begin(),coll.end(),//range
           [](int& elem){//operation
             elem+=10;
           });
  PRINT_ELEMENTS(coll);

  //add value of first element to each element
  for_each(coll.begin(),coll.end(),//range
           [=](int& elem){//operation
             elem+=*coll.begin();
           });
  PRINT_ELEMENTS(coll);

  for_each(coll.begin(),coll.end(),//range
           [&](int& elem){//operation
             elem+=*coll.begin();
           });
  PRINT_ELEMENTS(coll);

  for_each(coll.begin(),coll.end(),//range
           AddValue<int>(10));//operation
  PRINT_ELEMENTS(coll);

  for_each(coll.begin(),coll.end(),//range
           AddValue<int>(*coll.begin()));//operation
  PRINT_ELEMENTS(coll);

  //add 10 to each element
  transform(coll.cbegin(),coll.cend(),//source range
            coll.begin(),//destination range
            [](int elem){//operation
              return elem+10;
            });
  PRINT_ELEMENTS(coll);

  //add value of first element to each element
  transform(coll.cbegin(),coll.cend(),//source range
            coll.begin(),//destination range
            [=](int elem){//operation
              return elem+*coll.begin();
            });
  PRINT_ELEMENTS(coll);

  coll.clear();

  INSERT_ELEMENTS(coll,1,8);

  //process and print mean value
  double mv=for_each(coll.begin(),coll.end(),//range
                     MeanValue());//operation, 返回的函数对象调用成员函数隐式转换成double数值
  std::cout<<"mean value: "<<mv<<std::endl;

  //11.5 非更易型算法(Nonmodifying Algorithm)
  //11.5.1 元素计数
  


  return 0;
}
