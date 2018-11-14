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

bool absLess(int elem1,int elem2)
{
  return abs(elem1)<abs(elem2);
}

//checks whether an element is even or odd
bool checkEven(int elem,bool even)
{
  if(even){
    return elem%2==0;
  }
  else{
    return elem%2==1;
  }
}





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

  //difference_type
  //count(InputIterator beg,InputIterator end,const T& value)
  //difference_type
  //count_if(InputIterator beg,InputIterator end,UnaryPredicate op)
  //第一形式计算区间[beg,end)中“元素值等于value”的元素个数
  //第二形式计算区间[beg,end)中“令unary predicate
  // op(elem)
  //结果为true”的元素个数
  //返回类型difference_type，是用以表现iterator间距的类型：
  // typename iterator_traits<InputIterator>::difference_type
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //Associative和unordered容器提供了一个类似的成员函数count()，用来计算“以某给定值为key”的元素个数
  //复杂度：线性。执行比较动作（或调用op()）共numElems次

  coll.clear();
  int num;
  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //count elements with value 4
  num=count(coll.begin(),coll.end(),//range
            4);//value
  std::cout<<"number of elements equal to 4: "<<num<<std::endl;

  //count elements with even value
  num=count_if(coll.begin(),coll.end(),//range
               [](int elem){//criterion
                 return elem%2==0;
               });
  std::cout<<"number of elements with even value: "<<num<<std::endl;

  //count elements that are greater than value 4
  num=count_if(coll.begin(),coll.end(),//range
               [](int elem){//criterion
                 return elem>4;
               });
  std::cout<<"number of elements greater than 4: "<<num<<std::endl;

  std::cout<<count_if(coll.begin(),coll.end(),
                      std::bind(std::logical_not<bool>(),
                                std::bind(std::modulus<int>(),
                                          std::placeholders::_1,
                                          2)))<<std::endl;
  std::cout<<count_if(coll.begin(),coll.end(),
                      std::not1(std::bind2nd(std::modulus<int>(),2)))<<std::endl;

  //11.5.2 最大值和最小值

  //ForwardIterator
  //min_element(ForwardIterator beg,ForwardIterator end)
  //ForwardIterator
  //min_element(ForwardIterator beg,ForwardIterator end,CompFunc op)
  //ForwardIterator
  //max_element(ForwardIterator beg,ForwardIterator end);
  //ForwardIterator
  //max_element(ForwardIterator beg,ForwardIterator end,CompFunc op)
  //pair<ForwardIterator,ForwardIterator>
  //minmax_element(ForwardIterator beg,ForwardIterator end)
  //pair<ForwardIterator,ForwardIterator>
  //minmax_element(ForwardIterator beg,ForwardIterator end,CompFunc op)
  //所有这些算法分别返回[beg,end)区间中的最小元素位置、最大元素位置，或“最小和最大元素的位置所组成的pair”
  //上述无op实参的各个版本，将以operator<进行元素比较
  //op用来比较两个元素：
  // op(elem1,elem2)
  //如果第一元素小于第二元素，应当返回true
  //如果存在多个最小值或最大值，min_element()和max_element()返回其所找到的第一个目标元素。minmax_element()返回第一个最小元素和最后一个最大元素。所以，max_element()和minmax_element()返回的最大元素不是同一个
  //op不应该改动传入的实参
  //复杂度：线性。min_element()和max_element()的元素比较（或调用op()）执行numElems-1次。minmax_element()的元素比较（或调用op()）执行3*(numElems-1)/2次

  std::deque<int> coll1;

  INSERT_ELEMENTS(coll1,2,6);
  INSERT_ELEMENTS(coll1,-3,6);

  PRINT_ELEMENTS(coll1);

  //process and print minimum and maximum
  std::cout<<"minimum: "
           <<*min_element(coll1.cbegin(),coll1.cend())<<std::endl;
  std::cout<<"maximum: "
           <<*max_element(coll1.cbegin(),coll1.cend())<<std::endl;

  //print min and max and their distance using minmax_element()
  auto mm=minmax_element(coll1.cbegin(),coll1.cend());
  std::cout<<"min: "<<*(mm.first)<<std::endl;//print minimum
  std::cout<<"max: "<<*(mm.second)<<std::endl;//print maximum
  std::cout<<"distance: "<<distance(mm.first,mm.second)<<std::endl;

  //process and print minimum and maximum of absolute values
  std::cout<<"minimum of absolute values: "
           <<*min_element(coll1.cbegin(),coll1.cend(),absLess)<<std::endl;
  std::cout<<"maximum of absolute values: "
           <<*max_element(coll1.cbegin(),coll1.cend(),absLess)<<std::endl;

  //11.5.3 查找元素(Searching Element)

  //InputIterator
  //find(InputIterator beg,InputIterator end,const T& value)
  //InputIterator
  //find_if(InputIterator beg,InputIterator end,UnaryPredicate op)
  //InputIterator
  //find_if_not(InputIterator beg,InputIterator end,UnaryPredicate op)
  //第一形式返回[beg,end)区间中第一个“元素值等于value”的元素位置
  //第二形式返回[beg,end)区间中第一个“造成以下unary predicate结果为true”的元素：
  // op(elem)
  //第三形式（始自C++11）返回[beg,end)区间中第一个“造成以下unary predicate结果为false“的元素：
  // op(elem)
  //如果没有找到匹配元素，它们都返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //如果是已排序区间(sorted range)，应使用lower_bound()、upper_bound()、equal_range()或binary_search()算法以获得更高效能
  //Associative和unordered容器提供一个等效的成员函数find()，拥有较好复杂度（对associative容器而言是对数，对unordered容器而言是常量）
  //复杂度：线性。至多比较（或调用op()）numElems次

  std::list<int> coll2;

  INSERT_ELEMENTS(coll2,1,9);
  INSERT_ELEMENTS(coll2,1,9);

  PRINT_ELEMENTS(coll2,"coll: ");

  //find first element with value 4
  std::list<int>::iterator pos1;
  pos1=find(coll2.begin(),coll2.end(),//range
            4);

  //find second element with value 4
  //-note: continue the search behind the first 4(if any)
  std::list<int>::iterator pos2;
  if(pos1!=coll2.end()){
    pos2=find(++pos1,coll2.end(),//range
              4);//value
  }

  //print all elements from first to second 4(both included)
  //-note: now we need the position of the first 4 again(if any)
  if(pos1!=coll2.end()&&pos2!=coll2.end()){
    copy(--pos1,++pos2,
         std::ostream_iterator<int>(std::cout," "));
    std::cout<<std::endl;
  }

  coll.clear();
  std::vector<int>::iterator pos;

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //find first element greater than 3
  pos=find_if(coll.begin(),coll.end(),//range
              std::bind(std::greater<int>(),
                        std::placeholders::_1,
                        3));//criterion

  //print its position
  std::cout<<"the "
           <<distance(coll.begin(),pos)+1
           <<". element is the first greater than 3"<<std::endl;

  //find first element divisible by 3
  pos=find_if(coll.begin(),coll.end(),
              [](int elem){
                return elem%3==0;
              });

  //print its position
  std::cout<<"the "
           <<distance(coll.begin(),pos)+1
           <<". element is the first divisible by 3"<<std::endl;

  //find first element not <5
  pos=find_if_not(coll.begin(),coll.end(),
                  std::bind(std::less<int>(),
                            std::placeholders::_1,5));
  std::cout<<"first value >=5: "<<*pos<<std::endl;

  //ForwardIterator
  //search_n(ForwardIterator beg,ForwardIterator end,Size count,const T& value)
  //ForwardIterator
  //search_n(ForwardIterator beg,ForwardIterator end,Size count,const T& value,BinaryPredicate op)
  //第一形式返回[beg,end)区间内”连续count个元素值都等于value“中的第一个元素位置
  //第二形式返回[beg,end)区间内”连续count个元素造成以下binary predicate结果为true“中的第一元素位置：
  // op(elem,value)
  //(value is the passed fourth argument)
  //如果没有找到匹配元素，两种形式都返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //这两个算法不在早期的STL规范中，也没有获得谨慎的对待，因此第二形式使用了一个binary predicate而非unary predicate，这破坏了STL的一致性
  //复杂度：线性。至多比较（或调用op()）numElems*count次

  coll1.clear();

  coll1.insert(coll1.begin(),{1,2,7,7,6,3,9,5,7,7,7,3,6});
  PRINT_ELEMENTS(coll1);

  //find three consecutive elements with value 7
  std::deque<int>::iterator pos3;
  pos3=search_n(coll1.begin(),coll1.end(),//range
                3,//count
                7);//value
  //print result
  if(pos3!=coll1.end()){
    std::cout<<"three consecutive elements with value 7 "
             <<"start with "<<distance(coll1.begin(),pos3)+1
             <<". element"<<std::endl;
  }
  else{
    std::cout<<"no four consecutive elements with value 7 found"<<std::endl;
  }

  //find four consecutive odd elements

  pos3=search_n(coll1.begin(),coll1.end(),//range
                4,//count
                0,//value
                [](int elem, int value){//criterion
                  return elem%2==1;
                });

  //print result
  if(pos3!=coll1.end()){
    std::cout<<"first four consecutive odd elements are: ";
    for(int i=0;i<4;++i,++pos3){
      std::cout<<*pos3<<' ';
    }
  }
  else{
    std::cout<<"no four consecutive elements with value > 3 found";
  }
  std::cout<<std::endl;

  //find four consecutive elements with value greater than 3
  pos3=search_n(coll1.begin(),coll1.end(),//range
                4,//count
                3,//value
                std::greater<int>());//criterion
  if(pos3!=coll1.end()){
    for(int i=0;i<4;++i,++pos3){
      std::cout<<*pos3<<' ';
    }
  }
  else{
    std::cout<<"no found!"<<std::endl;
  }
  std::cout<<std::endl;

  //bool binaryIsPrime(int elem1,int){
  //  return isPrime(elem1);
  //}
  // ...
  //pos=search_n(coll.begin(),coll.end(),//range
  //             4,//count
  //             0,//required dummy value
  //             binaryIsPrime);//binary criterion

  //ForwardIterator1
  //search(ForwardIterator1 beg,ForwardIterator1 end,ForwardIterator2 searchBeg,ForwardIterator2 searchEnd)
  //ForwardIterator1
  //search(ForwardIterator1 beg,ForwardIterator1 end,ForwardIterator2 searchBeg,ForwardIterator2 searchEnd,BinaryPredicate op)
  //两个形式都返回[beg,end)区间内”与[searchBeg,searchEnd)区间完全吻合“的第一个子区间内的第一元素位置
  //第一形式中，子区间内的元素必须完全等于[searchBeg,searchEnd)的元素
  //第二形式中，子区间内的元素和[searchBeg,searchEnd)的对应元素必须造成以下binary predicate的结果为true：
  // op(elem,searchElem)
  //如果没有找到匹配元素，两种形式都返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //如果你想查找一个子区间但是”只知其第一元素和最末元素“，请参考以前的例子
  //复杂度：线性。至多比较（或调用op()）共numElems*numSearchElems次

  coll1.clear();
  coll2.clear();

  INSERT_ELEMENTS(coll1,1,7);
  INSERT_ELEMENTS(coll1,1,7);
  INSERT_ELEMENTS(coll2,3,6);

  PRINT_ELEMENTS(coll1,"coll: ");
  PRINT_ELEMENTS(coll2,"subcoll: ");

  //search first occurrence of subcoll in coll
  pos3=search(coll1.begin(),coll1.end(),//range
              coll2.begin(),coll2.end());//subrange

  //loop while subcoll found as subrange of coll
  while(pos3!=coll1.end()){
    //print position of first element
    std::cout<<"subcoll found starting with element "
             <<distance(coll1.begin(),pos3)+1
             <<std::endl;

    //search next occurrence of subcoll
    ++pos3;
    pos3=search(pos3,coll1.end(),//range
                coll2.begin(),coll2.end());//subrange
  }

  coll.clear();
  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //arguments for checkEven()
  //-check for: "even odd even"
  bool checkEvenArgs[3]={true,false,true};

  //search first subrange in coll
  pos=search(coll.begin(),coll.end(),//range
             checkEvenArgs,checkEvenArgs+3,//subrange values
             checkEven);//subrange criterion

  //loop while subrange found
  while(pos!=coll.end()){
    //print position of first element
    std::cout<<"subrange found starting with element "
             <<distance(coll.begin(),pos)+1
             <<std::endl;

    //search next subrange in coll
    pos=search(++pos,coll.end(),//range
               checkEvenArgs,checkEvenArgs+3,//subr.values
               checkEven);//subr.criterion
  }

  //ForwardIterator1
  //find_end(ForwardIterator1 beg,ForwardIterator1 end,ForwardIterator2 searchBeg,ForwardIterator2 searchEnd)
  //ForwardIterator1
  //find_end(ForwardIterator1 beg,ForwardIterator1 end,ForwardIterator2 searchBeg,ForwardIterator2 searchEnd,BinaryPredicate op)




  return 0;
}
