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
#include <random> //for std::default_random_engine


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

//return whether the second object has double the value of the first
bool doubled(int elem1,int elem2)
{
  return elem1*2==elem2;
}

bool bothEvenOrOdd(int elem1,int elem2)
{
  return elem1%2==elem2%2;
}

void printCollection(const std::list<int>& l)
{
  PRINT_ELEMENTS(l);
}

bool lessForCollection(const std::list<int>& l1,const std::list<int>& l2)
{
  return lexicographical_compare(l1.cbegin(),l1.cend(),//first range
                                 l2.cbegin(),l2.cend());//second range
}

bool differenceOne(int elem1,int elem2)
{
  return elem1+1==elem2||elem1-1==elem2;
}

bool bothSpaces(char elem1,char elem2)
{
  return elem1==' '&&elem2==' ';
}

class MyRandom{
public:
std::ptrdiff_t operator()(std::ptrdiff_t max){
    double tmp;
    tmp=static_cast<double>(rand())
      /static_cast<double>(RAND_MAX);
return static_cast<std::ptrdiff_t>(tmp*max);
  }
};

bool lessLength(const std::string& s1,const std::string& s2)
{
  return s1.length()<s2.length();
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
  //两种形式都返回[beg,end)区间之中“和区间[searchBeg,searchEnd)完全吻合”的最后一个子区间内的第一个元素位置
  //第一形式中，子区间的元素必须完全等于[searchBeg,searchEnd)的元素
  //第二形式中，子区间的元素和[searchBeg,searchEnd)的对应元素必须造成以下binary predicate的结果为true：
  // op(elem,searchElem)
  //如果没有找到匹配元素，两种形式都返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //如果你想查找某个子区间但是“只知道其第一元素和最末元素”，请参考前面的例子
  //这些算法并不是早期STL的一部分。很不幸它们被命名为find_end()而不是search_end()，后者较具一致性，因为用来查找第一个子区间的算法名为search()
  //复杂度：线性。至多比较（或调用op()）共numElems*numSearchElems次

  coll1.clear();
  coll2.clear();

  INSERT_ELEMENTS(coll1,1,7);
  INSERT_ELEMENTS(coll1,1,7);
  INSERT_ELEMENTS(coll2,3,6);

  PRINT_ELEMENTS(coll1,"coll: ");
  PRINT_ELEMENTS(coll2,"subcoll: ");

  //search last occurrence of subcoll in coll
  pos3=find_end(coll1.begin(),coll1.end(),//range
                coll2.begin(),coll2.end());//subrange

  //loop while subcoll found as subrange of coll
  std::deque<int>::iterator end(coll1.end());
  while(pos3!=end){
    //print position of first element
    std::cout<<"subcoll found starting with element "
             <<distance(coll1.begin(),pos3)+1
             <<std::endl;

    //search next occurrence of subcoll
    end=pos3;
    pos3=find_end(coll1.begin(),end,//range
                  coll2.begin(),coll2.end());//subrange
  }

  //InputIterator
  //find_first_of(InputIterator beg,InputIterator end,ForwardIterator searchBeg,ForwardIterator searchEnd)
  //InputIterator
  //find_first_of(InputIterator beg,InputIterator end,ForwardIterator searchBeg,ForwardIterator searchEnd,BinaryPredicate op)
  //第一形式返回第一个“既出现于[beg,end)区间也出现于[searchBeg,searchEnd)区间”的元素的位置
  //第二形式返回[beg,end)区间内第一个满足以下条件的元素：它和区间[searchBeg,searchEnd)内每一个元素进行以下动作的结果都是true
  // op(elem,searchElem)
  //如果没有找到匹配元素，两种形式都返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //你可以使用reverse iterator查找最后一个符合条件的元素
  //这几个算法并不在早期STL规范中
  //在C++11之前，这些算法面对[beg,end)区间所需要的是forward iterator而不是input iterator
  //复杂度：线性。至多比较（或调用op()）共numElems*numSearchElems次

  coll.clear();
  coll2.clear();

  INSERT_ELEMENTS(coll,1,11);
  INSERT_ELEMENTS(coll2,3,5);

  PRINT_ELEMENTS(coll,"coll: ");
  PRINT_ELEMENTS(coll2,"searchcoll: ");

  //search first occurrence of an element of searchcoll in coll
  pos=find_first_of(coll.begin(),coll.end(),//range
                    coll2.begin(),//beginning of search set
                    coll2.end());//end of search set
  std::cout<<"first element of searchcoll in coll is element "
           <<distance(coll.begin(),pos)+1
           <<std::endl;

  //search last occurrence of an element of searchcoll in coll
  std::vector<int>::reverse_iterator rpos;
  rpos=find_first_of(coll.rbegin(),coll.rend(),//range
                     coll2.begin(),//beginning of search set
                     coll2.end());//end of search set
  std::cout<<"last element of searchcoll in coll is element "
           <<distance(coll.begin(),rpos.base())
           <<std::endl;

  //ForwardIterator
  //adjacent_find(ForwardIterator beg,ForwardIterator end)
  //ForwardIterator
  //adjacent_find(ForwardIterator beg,ForwardIterator end,BinaryPredicate op)
  //第一形式返回[beg,end)区间内第一对“连续两个相等元素”中的第一元素位置
  //第二形式返回[beg,end)区间内第一对“连续两个元素均造成以下binary predicate结果为true”的其中第一元素位置：
  // op(elem,nextElem)
  //如果没有找到匹配元素，两种形式都返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //复杂度：线性。至多比较（或调用op()）共numElems次

  coll.clear();
  coll.insert(coll.begin(),{1,3,2,4,5,5,0});

  PRINT_ELEMENTS(coll,"coll: ");

  //search first two elements with equal value
  pos=adjacent_find(coll.begin(),coll.end());

  if(pos!=coll.end()){
    std::cout<<"first two elements with equal value have position "
             <<distance(coll.begin(),pos)+1
             <<std::endl;
  }

  //search first two elements for which the second has double the value of the first
  pos=adjacent_find(coll.begin(),coll.end(),//range
                    doubled);//criterion

  if(pos!=coll.end()){
    std::cout<<"first two elements with second value twice the "
             <<"first have pos. "
             <<distance(coll.begin(),pos)+1
             <<std::endl;
  }

  //11.5.4 区间的比较

  //bool
  //equal(InputIterator1 beg,InputIterator1 end,InputIterator2 cmpBeg)
  //bool
  //equal(InputIterator1 beg,InputIterator1 end,InputIterator2 cmpBeg,BinaryPredicate op)
  //第一形式判断[beg,end)区间内的元素是否都和"以cmpBeg开头的区间"内的元素相等
  //第二形式判断[beg,end)区间内的元素和”以cmpBeg开头的区间“内的对应元素是否都能够造成以下binary predicate产出true：
  // op(elem,cmpElem)
  //注意，op不应在函数调用过程中改变状态(state)，op不应改动传入的实参
  //调用者必须确保”以cmpBeg开头“的区间内含足够元素
  //当序列不相等时，如果想要了解其间的不同，应使用mismatch()算法
  //自C++11起提供了is_permutation()算法，用来判断是否两个序列内含的元素数值相同但次序不同
  //复杂度：线性。至多比较（或调用op()）共numElems次

  coll.clear();
  coll2.clear();

  INSERT_ELEMENTS(coll,1,7);
  INSERT_ELEMENTS(coll2,3,9);

  PRINT_ELEMENTS(coll,"coll: ");
  PRINT_ELEMENTS(coll2,"coll2: ");

  //check whether both collections are equal
  if(equal(coll.begin(),coll.end(),//first range
           coll2.begin())){//second range
    std::cout<<"coll==coll2"<<std::endl;
  }
  else{
    std::cout<<"coll!=coll2"<<std::endl;
  }

  //check for corresponding even and odd elements
  if(equal(coll.begin(),coll.end(),//first range
           coll2.begin(),//second range
           bothEvenOrOdd)){//comparison criterion
    std::cout<<"even and odd elements correspond"<<std::endl;
  }
  else{
    std::cout<<"even and odd elements do not correspond"<<std::endl;
  }

  //bool
  //is_permutation(ForwardIterator1 beg1,ForwardIterator1 end1,ForwardIterator2 beg2)
  //bool
  //is_permutation(ForwardIterator1 beg1,ForwardIterator1 end1,ForwardIterator2 beg2,CompFunc op)
  //两个形式都检测[beg1,end1)区间内的元素是否为beg2起始之区间元素的一个排列组合(a permutation)；也就是说，”顺序无所谓“的情况下两区间的元素是否相等
  //第一形式以operator==比较元素
  //第二形式使用binary predicate op(elem1,elem2)比较元素，它应该在”elem1等于elem2“时返回true
  //注意，op不应在函数调用过程中改变状态(state)，op不应改动传入的实参
  //所有iterator必须有相同的value type（即所指向的元素的类型）
  //这些算法都始自C++11
  //复杂度：最糟情况下是二次（quadratic；共numElems1次比较或调用op()，前提是所有对应元素相等且有相同次序）

  coll.clear();
  coll1.clear();
  coll2.clear();

  coll={1,1,2,3,4,5,6,7,8,9};
  coll2={1,9,8,7,6,5,4,3,2,1};
  coll1={11,12,13,19,18,17,16,15,14,11};

  PRINT_ELEMENTS(coll,"coll: ");
  PRINT_ELEMENTS(coll2,"coll2: ");
  PRINT_ELEMENTS(coll1,"coll1: ");

  //check whether both collections have equal elements in any order
  if(is_permutation(coll.cbegin(),coll.cend(),//first range
                    coll2.cbegin())){//second range
    std::cout<<"coll and coll2 have equal elements"<<std::endl;
  }
  else{
    std::cout<<"coll and coll2 don't have equal elements"<<std::endl;
  }

  //check for corresponding number of even and odd elements
  if(is_permutation(coll.cbegin(),coll.cend(),//first range
                    coll1.cbegin(),//second range
                    bothEvenOrOdd)){//comparison criterion
    std::cout<<"numbers of even and odd elements match"<<std::endl;
  }
  else{
    std::cout<<"numbers of even and odd elements don't match"<<std::endl;
  }

  //pair<InputIterator1,InputIterator2>
  //mismatch(InputIterator1 beg,InputIterator1 end,InputIterator2 cmpBeg)
  //pair<InputIterator1,InputIterator2>
  //mismatch(InputIterator1 beg,InputIterator1 end,InputIterator2 cmpBeg,BinaryPredicate op)
  //第一形式返回[beg,end)区间和”以cmpBeg起始的区间“内第一组两两相异的对应元素
  //第二形式返回[beg,end)区间和”以cmpBeg起始的区间“内第一组”造成以下binaray predicate结果为false“的对应元素：
  // op(elem,cmpElem)
  //如果没有找到相异点，就返回”以end和第二序列的对应元素组成“的pair<>。这并不意味着两序列相等，因为第二序列有可能内含较多元素
  //注意，op不应在函数调用过程中改变状态(state)，op不应改动传入的实参
  //调用者必须确保”以cmpBeg开头“的区间内含足够元素
  //如果想知道两个序列是否相等，应当使用equal()算法
  //复杂度：线性。至多比较（或调用op()）共numElems次

  coll.clear();
  coll={1,2,3,4,5,6};
  coll2.clear();
  coll2={1,2,4,8,16,3};

  PRINT_ELEMENTS(coll,"coll: ");
  PRINT_ELEMENTS(coll2,"coll2: ");

  //find first mismatch
  auto values=mismatch(coll.cbegin(),coll.cend(),//first range
                       coll2.cbegin());//second range
  if(values.first==coll.end()){
    std::cout<<"no mismatch"<<std::endl;
  }
  else{
    std::cout<<"first mismatch: "
             <<*values.first<<" and "
             <<*values.second<<std::endl;
  }

  //find first position where the element of coll is not
  //less than the corresponding element of coll2
  values=mismatch(coll.cbegin(),coll.cend(),//first range
                  coll2.cbegin(),//second range
                  std::less_equal<int>());//criterion
  if(values.first==coll.end()){
    std::cout<<"always less-or-equal"<<std::endl;
  }
  else{
    std::cout<<"not less-or-equal: "
             <<*values.first<<" and "
             <<*values.second<<std::endl;
  }

  //bool
  //lexicographical_compare(InputIterator1 beg1,InputIterator1 end1,InputIterator2 beg2,InputIterator2 end2)
  //bool
  //lexicographical_compare(InputIterator1 beg1,InputIterator1 end1,InputIterator2 beg2,InputIterator2 end2,CompFunc op)
  //两个形式都用来判断[beg1,end1)区间内的元素是否小于[beg2,end2)的元素。所谓”小于“是指就”字典(lexicographical)次序“意义而言
  //第一形式以operator<比较元素
  //第二形式以binary predicate
  // op(elem1,elem2)
  //比较元素。如果elem1小于elem2，应当返回true
  //所谓字典次序的排序意味着两序列中的元素一一比较，直到以下情况发生：
  //-如果两元素不相等，则这两个元素的比较结果就是整个两序列的比较结果
  //-如果两序列的元素数量不同，则元素较少的序列小于另一序列。所以如果第一序列的元素数量较少，比较结果是true
  //如果两序列都没有更多的元素可进行比较，则这两个序列相等，整个比较结果是false
  //注意，op不应在函数调用过程中改变状态(state)，op不应改动传入的实参
  //复杂度：线性。至多比较（或调用op()）min(numElems1,numElems2)次

  std::list<int> c1,c2,c3,c4;

  //fill all collections with the same starting values
  INSERT_ELEMENTS(c1,1,5);
  c4=c3=c2=c1;

  //and now some differences
  c1.push_back(7);
  c3.push_back(2);
  c3.push_back(0);
  c4.push_back(2);

  //create collection of collections
  std::vector<std::list<int>> cc;
  cc.insert(cc.begin(),{c1,c2,c3,c4,c3,c1,c4,c2});

  //print all collections
  for_each(cc.cbegin(),cc.cend(),
           printCollection);
  std::cout<<std::endl;

  //sort collection lexicographically
  sort(cc.begin(),cc.end(),//range
       lessForCollection);//sorting criterion

  //print all collections again
  for_each(cc.cbegin(),cc.cend(),
           printCollection);

  //11.5.5 Predicate用以检验区间

  //bool
  //is_sorted(ForwardIterator beg,ForwardIterator end)
  //bool
  //is_sorted(ForwardIterator beg,ForwardIterator end,BinaryPredicate op)
  //bool
  //ForwardIterator
  //is_sorted_until(ForwardIterator beg,ForwardIterator end)
  //ForwardIterator
  //is_sorted_until(ForwardIterator beg,ForwardIterator end,BinaryPredicate op)
  //is_sorted()检验[beg,end)区间内的元素是否已经排序
  //is_sorted_until()返回[beg,end)区间内元素第一个破坏排序的元素。如果没有这样的元素，返回end
  //第一和第三形式使用operator<比较元素。第二和第四形式使用binary predicate op(elem1,elem2)比较元素——如果elem1”小于“elem2它就该返回true
  //如果区间为空，这些算法返回true，如果只有一个元素则返回end
  //注意，op不应在函数调用过程中改变状态(state),op不应改动传入的实参，这些算法全部始自C++11
  //复杂度：线性。至多调用<或op()共numElems-1次

  coll.clear();
  coll={1,1,2,3,4,5,6,7,8,9};

  PRINT_ELEMENTS(coll,"coll: ");

  //check whether coll is sorted
  if(is_sorted(coll.begin(),coll.end())){
    std::cout<<"coll is sorted"<<std::endl;
  }
  else{
    std::cout<<"coll is not sorted"<<std::endl;
  }

  std::map<int,std::string> collmap;
  collmap={{1,"Bill"},{2,"Jim"},{3,"Nico"},{4,"Liu"},{5,"Ai"}};
  PRINT_MAPPED_ELEMENTS(collmap,"collmap: ");

  //define predicate to compare names
  auto compareName=[](const std::pair<int,std::string>& e1,
                      const std::pair<int,std::string>& e2){
    return e1.second<e2.second;
  };

  //check whether the names in collmap are sorted
  if(is_sorted(collmap.cbegin(),collmap.cend(),compareName)){
    std::cout<<"names in collmap are sorted"<<std::endl;
  }
  else{
    std::cout<<"names in collmap are not sorted"<<std::endl;
  }

  //print first unsorted name
  auto posmap=is_sorted_until(collmap.cbegin(),collmap.cend(),compareName);
  if(posmap!=collmap.end()){
    std::cout<<"first unsorted name: "<<posmap->second<<std::endl;
  }

  //bool
  //is_partitioned(InputIterator beg,InputIterator end,UnaryPredicate op)
  //ForwardIterator
  //partition_point(ForwardIterator beg,ForwardIterator end,BinaryPredicate op)
  //is_partitioned()判断[beg,end)区间内的元素是否被分割(are partitions)，也就是所有符合predicate op()的元素都被置于所有不符合的元素之前（较早出现）
  //partition_point()返回[beg,end)区间中的第一个元素的位置。因此，对于[beg,end)，is_partitioned()必定产出true on entry
  //这些算法使用binary predicate
  // op(elem1,elem2)
  //它应该在elem1“小于”elem2时返回true
  //如果区间为空，partition_point()返回end
  //注意，op不应在函数调用过程中改变状态(state)
  //op不应改动传入的实参
  //这些算法都始自C++11
  //复杂度：
  //-is_partitioned()：线性（至多numElems次调用op()）
  //-partition_point()：如果收到的是random-access iterator则为对数(logarithmic)，否则是线性（无论如何至多log(numElems)次调用op()）

  coll.clear();
  coll={5,3,9,1,3,4,8,2,6};
  PRINT_ELEMENTS(coll,"coll: ");

  //define predicate: check whether element is odd:
  auto isOdd=[](int elem){
    return elem%2==1;
  };

  //check whether coll is partitioned in odd and even elements
  if(is_partitioned(coll.cbegin(),coll.cend(),//range
                    isOdd)){//predicate
    std::cout<<"coll is partitioned"<<std::endl;

    //find first even element:
    auto pos=partition_point(coll.cbegin(),coll.cend(),
                             isOdd);
    std::cout<<"first even element: "<<*pos<<std::endl;
  }
  else{
    std::cout<<"coll is not partitioned"<<std::endl;
  }

  //bool
  //is_heap(RandomAccessIterator beg,RandomAccessIterator end)
  //bool
  //is_heap(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //RandomAccessIterator
  //is_heap_until(RandomAccessIterator beg,RandomAccessIterator end)
  //RandomAccessIterator
  //is_heap_until(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //is_heap()判断[beg,end)区间内的元素是否形成一个heap，那意味着beg是最大值元素（之一）
  //is_heap_until()返回[beg,end)区间内第一个“破坏排序使无法成为heap“的元素位置（该元素将会比第一元素更大）。如果没有这样的元素就返回end
  //第一和第三形式使用operator<比较元素，第二和第四形式使用binary predicate op(elem1,elem2)完成比较，后者应该在elem1”小于“elem2的情况下返回true
  //如果区间为空，这些算法返回true，如果只有一个元素则返回end
  //注意，op不应在函数调用过程中改变状态(state)，op不应改动传入的实参
  //这些算法都始自C++11
  //复杂度：线性。至多调用<或op()共numElems-1次

  coll.clear();
  coll={9,8,7,7,7,5,4,2,1};
  std::vector<int> coll3={5,3,2,1,4,7,9,8,6};
  PRINT_ELEMENTS(coll,"coll: ");
  PRINT_ELEMENTS(coll3,"coll3: ");

  //check whether the collections are heaps
  std::cout<<std::boolalpha<<"coll is heap: "
           <<is_heap(coll.cbegin(),coll.cend())<<std::endl;
  std::cout<<"coll3 is heap: "
           <<is_heap(coll3.cbegin(),coll3.cend())<<std::endl;

  //print the first element that is not a heap in coll3
  auto pos4=is_heap_until(coll3.cbegin(),coll3.cend());
  if(pos4!=coll3.end()){
    std::cout<<"first non-heap element: "<<*pos4<<std::endl;
  }

  //bool
  //all_of(InputIterator beg,InputIterator end,UnaryPredicate op)
  //bool
  //any_of(InputIterator beg,InputIterator end,UnaryPredicate op)
  //bool
  //none_of(InputIterator beg,InputIterator end,UnaryPredicate op)
  //这些算法将判断，[beg,end)区间内是否全部，或至少一个，或没有任何元素造成unary predicate op(elem)产出true
  //如果区间为空，all_of()和none_of()返回true，而any_of()返回false
  //注意，op不应在函数调用过程中改变状态(state)，op不应改动传入的实参
  //这些算法都始自C++11
  //复杂度：线性。至多调用op()numElems次

  coll.clear();
  std::vector<int>::iterator pos5;

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //define an object for the predicate(using a lambda)
  auto isEven=[](int elem){
    return elem%2==0;
  };

  //print whether all,any, or none of the elements are/is even
  std::cout<<std::boolalpha<<"all even?: "
           <<all_of(coll.cbegin(),coll.cend(),isEven)<<std::endl;
  std::cout<<"any even?: "
           <<any_of(coll.cbegin(),coll.cend(),isEven)<<std::endl;
  std::cout<<"none even?: "
           <<none_of(coll.cbegin(),coll.cend(),isEven)<<std::endl;

  //11.6 更易型算法(Modifying Algorithm)
  //11.6.1 复制元素(Copying Element)

  //OutputIterator
  //copy(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg)
  //OutputIterator
  //copy_if(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,UnaryPredicate op)
  //OutputIterator
  //copy_n(InputIterator sourceBeg,Size num,OutputIterator destBeg)
  //BidirectionalIterator2
  //copy_backward(BidirectionalIterator1 sourceBeg,BidirectionalIterator1 sourceEnd,BidirectionalIterator2 destEnd)
  //上述四个算法都将源区间[sourceBeg,sourceEnd)中的所有元素复制到以destBeg为起点或以destEnd为终点的目标区间
  //它们都返回目标区间内最后一个被复制元素的下一位置，也就是第一个未被覆盖(overwritten)的元素的位置
  //关于copy()，destBeg不可处于[sourceBeg,sourceEnd)区间内。关于copy_if()，源区间和目标区间不可重叠。关于copy_backward()，destEnd不可处于(sourceBeg,sourceEnd]区间内
  //copy()正向遍历(forward)，而copy_backward()反向遍历(backward)。只有当源区间和目标区间重叠时，这个不同点才会导致一些问题：
  //-若要把一个子区间复制到前端，应使用copy()。因此对copy()而言，destBeg的位置应该在sourceBeg之前。
  //-若要把一个子区间复制到后端，应使用copy_backward()。因此对copy_backward()而言，destEnd的位置应该在sourceEnd之后
  //所以，只要第三实参位于”前两个实参所指出的源区间”中，你就应该使用另一算法。注意，如果转而使用另一形式，意味着原本应传入目标区间的起点，现在要改而传入终点了。
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //自C++11起，如果源端元素不再被使用，你应该以move()取代copy()，以move_backward()取代copy_backward()
  //C++11之前并未提供copy_if()和copy_n()算法，因此若要复制“符合某给定准则”之元素，必须选择remove_copy_if()并搭配一个negated predicate
  //如果希望在复制过程中反转元素次序，应使用reverse_copy()。该算法比起"copy()算法搭配reverse iterator"略快些
  //如果想把容器内的所有元素赋值(assign)给另一个容器，应当使用assignment操作符（当两个容器的类型相同时才能这么做）或使用容器的assign()成员函数（当两个容器的类型不同时就采用此法）
  //如果希望在复制的同时移除元素，应使用算法remove_copy()和remove_copy_if()
  //如果希望在复制过程中改动元素，请使用transform()或replace_copy()
  //可使用partition_copy()将元素复制到两个目标区间：其中一组满足predicate而另一组不满足
  //复杂度：线性，执行numElems次赋值

  std::vector<std::string> coll4={"Hello","this","is","an","example"};
  std::list<std::string> coll5;

  //copy elements of coll4 into coll5
  //-use back inserter to insert instead of overwrite
  copy(coll4.cbegin(),coll4.cend(),//source range
       back_inserter(coll5));//destination range

  //print elements of coll5
  //-copy elements to cout using an ostream iterator
  copy(coll5.cbegin(),coll5.cend(),//source range
       std::ostream_iterator<std::string>(std::cout," "));//destination range
  std::cout<<std::endl;

  //copy elements of coll4 into coll5 in reverse order
  //-now overwriting
  copy(coll4.crbegin(),coll4.crend(),//source range
       coll5.begin());//destination range

  //print elements of coll5 again
  copy(coll5.cbegin(),coll5.cend(),//source range
       std::ostream_iterator<std::string>(std::cout," "));//destination range
  std::cout<<std::endl;

  //initialize source collection with "..........abcdef.........."
  std::vector<char> source(10,'.');
  for(int c='a';c<='f';c++){
    source.push_back(c);
  }
  source.insert(source.end(),10,'.');
  PRINT_ELEMENTS(source,"source: ");

  //copy all letters three elements in front of the 'a'
  std::vector<char> c5(source.cbegin(),source.cend());
  copy(c5.cbegin()+10,c5.cbegin()+16,//source range
       c5.begin()+7);//destination range
  PRINT_ELEMENTS(c5,"c5:     ");

  //copy all letters three elements behind the 'f'
  std::vector<char> c6(source.cbegin(),source.cend());
  copy_backward(c6.cbegin()+10,c6.cbegin()+16,//source range
                c6.begin()+19);//destination range
  PRINT_ELEMENTS(c6,"c6:     ");

  //copy(std::istream_iterator<std::string>(std::cin),//beginning of source
  //     std::istream_iterator<std::string>(),//end of source
  //     std::ostream_iterator<std::string>(std::cout,"\n"));//destination

  //11.6.2 搬移元素(Moving Element)
  //OutputIterator
  //move(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg)
  //BidirectionalIterator2
  //move_backward(BidirectionalIterator1 sourceBeg,BidirectionalIterator1 sourceEnd,BidirectionalIterator2 destEnd)
  //上述两个算法将源区间[sourceBeg,sourceEnd)中的所有元素搬移至以destBeg为起点或以destEnd为终点的目标区间
  //它们会针对每一个元素调用
  // *destElem=std::move(*sourceElem)
  //因此，如果元素类型提供有move语义，源端元素从此不再明确，它们也就不该再被使用，除非重新初始化或被赋予新值。如果元素类型未提供move语义，元素会被copy，就像copy()或copy_backward()的行为一样
  //它们会返回目标区间内最后一个被复制元素的下一位置，也就是第一个未被覆盖(overwritten)的元素的位置
  //move()的destBeg不可处于[sourceBeg,sourceEnd)区间内。move_backward()的destEnd不可处于(sourceBeg,sourceEnd]区间内
  //move()正向遍历(forward)，而move_backward()反向遍历(backward)。只有当源区间和目标区间重叠时，这个不同点才会导致一些问题：
  //-若要把一个子区间搬移到前端，应使用move()。因此对move()而言，destBeg的位置应该在sourceBeg之前
  //-若要把一个子区间复制到后端，应使用move_backward()。因此对move_backward()而言，destEnd的位置应该在sourceEnd之后
  //所以，只要第三实参位于“前两个实参所指出的源区间”中，你就应该使用另一算法。注意，如果转而使用另一形式，意味着原本应传入目标区间的起点，现在要改而传入终点了。
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //这些算法都始自C++11
  //复杂度：线性，执行numElems次“搬移赋值”(move assignment)

  coll5.clear();

  //copy elements of coll4 into coll5
  //-use back inserter to insert instead of overwrite
  //-use copy() because the elements in coll4 are used again
  copy(coll4.cbegin(),coll4.cend(),//source range
       back_inserter(coll5));//destination range

  //print elements of coll5
  //-copy elements to cout using an ostream iterator
  //-use move() because these elements in coll5 are not used again
  move(coll5.cbegin(),coll5.cend(),//source range
       std::ostream_iterator<std::string>(std::cout," "));//destination range
  std::cout<<std::endl;

  //copy elements of coll4 into coll5 in reverse order
  //-now overwriting(coll5.size() still fits)
  //-use move() because the elements in coll4 are not used again
  move(coll4.crbegin(),coll4.crend(),//source range
       coll5.begin());//destination

  //print elements of coll5 again
  //-use move() because the elements in coll5 are not used again
  move(coll5.cbegin(),coll5.cend(),//source range
       std::ostream_iterator<std::string>(std::cout," "));//destination range
  std::cout<<std::endl;

  //11.6.3 转换和结合元素(Transforming and Combining Element)
  //OutputIterator
  //transform(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,UnaryFunc op)
  //针对源区间[sourceBeg,sourceEnd)中的每一个元素调用：
  // op(elem)并将结果写到以destBeg起始的目标区间内
  //返回目标区间内“最后一个被转换元素”的下一位置，也就是第一个未被覆盖(overwritten)的元素的位置
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //sourceBeg与destBeg可以完全相同，所以，和for_each()算法一样，你可以使用这个算法来改动“序列内”的元素。
  //如果想以某值替换掉“符合给定准则”的元素，应使用replace()
  //复杂度：线性，对op()执行numElems次调用

  coll.clear();
  coll2.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //negate all elements in coll
  transform(coll.cbegin(),coll.cend(),//source range
            coll.begin(),//destination range
            std::negate<int>());
  PRINT_ELEMENTS(coll,"negated: ");

  //transform elements of coll into coll2 with ten times their value
  transform(coll.cbegin(),coll.cend(),//source range
            back_inserter(coll2),//destination range
            std::bind(std::multiplies<int>(),
                      std::placeholders::_1,
                      10));//operation
  PRINT_ELEMENTS(coll2,"coll2: ");

  //print coll2 negatively and in reverse order
  transform(coll2.crbegin(),coll2.crend(),//source range
            std::ostream_iterator<int>(std::cout," "),//destination range
            [](int elem){//operation
              return -elem;
            });
  std::cout<<std::endl;

  //OutputIterator
  //transform(InputIterator1 source1Beg,InputIterator1 source1End,InputIterator2 source2Beg,OutputIterator destBeg,BinaryFunc op)
  //针对第一源区间[source1Beg,source1End)以及“从source2Beg开始的第二源区间”的对应元素，调用
  // op(source1Elem,source2Elem)
  //并将结果写入以destBeg起始的目标区内
  //返回目标区间内“最后一个被转换元素”的下一位置，就是第一个未被覆盖(overwritten)的元素的位置
  //调用者必须保证第二源区间有足够空间（至少拥有和第一源区间相同的大小）
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //source1Beg、source2Beg和destBeg可相同。因此，你可以让元素自己和自己结合，然后将结果覆盖(overwrite)自己
  //复杂度：线性，对op()执行numElems次调用

  coll.clear();
  coll2.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //square each element
  transform(coll.cbegin(),coll.cend(),//first source range
            coll.cbegin(),//second source range
            coll.begin(),//destination range
            std::multiplies<int>());
  PRINT_ELEMENTS(coll,"squared: ");

  //add each element traversed forward with each element traversed backward
  //and insert result into coll2
  transform(coll.cbegin(),coll.cend(),//first source range
            coll.crbegin(),//second source range
            back_inserter(coll2),//destination range
            std::plus<int>());//operation
  PRINT_ELEMENTS(coll2,"coll2: ");

  //print differences of two corresponding elements
  std::cout<<"diff: ";
  transform(coll.cbegin(),coll.cend(),//first source range
            coll2.cbegin(),//second source range
            std::ostream_iterator<int>(std::cout," "),//destination range
            std::minus<int>());//operation
  std::cout<<std::endl;

  //11.6.4 互换元素(Swapping Elements)

  //ForwardIterator2
  //swap_ranges(ForwardIterator1 beg1,ForwardIterator1 end1,ForwardIterator2 beg2)
  //将区间[beg1,end1)内的元素和“从beg2开始的区间”内的对应元素互换
  //返回第二区间中“最后一个被交换元素”的下一位置
  //调用者必须确保目标区间有足够空间，两区间不得重叠
  //如果要将相同类型的两个容器内的所有元素都互换，应使用swap()成员函数，因为该成员函数通常具备常量复杂度
  //复杂度：线性，执行numElems次交换动作

  coll.clear();
  coll1.clear();

  INSERT_ELEMENTS(coll,1,9);
  INSERT_ELEMENTS(coll1,11,23);

  PRINT_ELEMENTS(coll,"coll: ");
  PRINT_ELEMENTS(coll1,"coll1: ");

  //swap elements of coll with corresponding elements of coll1
  std::deque<int>::iterator pos6;
  pos6=swap_ranges(coll.begin(),coll.end(),//first range
                   coll1.begin());//second range

  PRINT_ELEMENTS(coll,"\ncoll: ");
  PRINT_ELEMENTS(coll1,"coll1: ");
  if(pos6!=coll1.end()){
    std::cout<<"first element not modified: "
             <<*pos6<<std::endl;
  }

  //mirror first three with last three elements in coll1
  swap_ranges(coll1.begin(),coll1.begin()+3,//first range
              coll1.rbegin());//second range
  PRINT_ELEMENTS(coll1,"\ncoll1: ");

  //11.6.5 赋值(Assigning New Value)

  //void
  //fill(ForwardIterator beg,ForwardIterator end,const T& newValue)
  //void
  //fill_n(OutputIterator beg,Size num,const T& newValue)
  //fill()将区间[beg,end)内的每一个元素都赋予新值newValue
  //fill_n()将“从beg开始的前num个元素”赋予新值newValue。如果num为负值则不做任何事（始自C++11）
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //自C++11起，fill_n()返回最后被改动的元素的下一位置(beg+num)，如果num是负值则返回beg（在C++11之前，fill_n()的返回类型是void）
  //复杂度：线性（执行numElems次或num次或0次赋值）

  //print ten times 7.7
  fill_n(std::ostream_iterator<float>(std::cout," "),//beginning of destination
         10,//count
         7.7);//new value
  std::cout<<std::endl;

  coll5.clear();

  //insert "hello" nine times
  fill_n(back_inserter(coll5),//beginning of destination
         9,//count
         "hello");//new value
  PRINT_ELEMENTS(coll5,"coll5: ");

  //overwrite all elements with "again"
  fill(coll5.begin(),coll5.end(),//destination
       "again");//new value
  PRINT_ELEMENTS(coll5,"coll5: ");

  //replace all but two elements with "hi"
  fill_n(coll5.begin(),//beginning of destination
         coll5.size()-2,//count
         "hi");//new value
  PRINT_ELEMENTS(coll5,"coll5: ");

  //replace the second and up to the last element but one with "hmmm"
  std::list<std::string>::iterator pos7,pos8;
  pos7=coll5.begin();
  pos8=coll5.end();
  fill(++pos7,--pos8,//destination
       "hmmm");//new value
  PRINT_ELEMENTS(coll5,"coll5: ");

  //void
  //generate(ForwardIterator beg,ForwardIterator end,Func op)
  //void
  //generate_n(OutputIterator beg,Size num,Func op)
  //generate()会调用op()产生新值，并将它赋值给区间[beg,end)内的每个元素
  //generate_n()会调用op()产生新值，并将它赋值给“以beg起始的区间”内的前num个元素。如果num为负值则不做任何事（始自C++11）
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //自C++11起，generate_n()返回最后被改动的元素的下一位置(beg+num)，如果num是负值则返回beg（在C++11之前，generate_n()的返回类型是void）
  //复杂度：线性（op()动作和赋值，执行numElems次或num次或0次）

  coll2.clear();

  //insert five random numbers
  generate_n(back_inserter(coll2),//beginning of destination range
             5,//count
             rand);//new value generator
  PRINT_ELEMENTS(coll2);

  //overwrite with five new random numbers
  generate(coll2.begin(),coll2.end(),//destination range
           rand);//new value generator
  PRINT_ELEMENTS(coll2);

  //void
  //iota(ForwardIterator beg,ForwardIterator end,T startValue)
  //依序赋值startValue、startValue+1、startValue+2......
  //始自C++11
  //复杂度：线性（执行numElems次赋值和累加）

  std::array<int,10> coll6;

  std::iota(coll6.begin(),coll6.end(),//destination range
       42);//start value

  PRINT_ELEMENTS(coll6,"coll6: ");

  //11.6.6替换元素(Replacing Element)

  //void
  //replace(ForwardIterator beg,ForwardIterator end,const T& oldValue,const T&newValue)
  //void
  //replace_if(ForwardIterator beg,ForwardIterator end,UnaryPredicate op,const T& newValue)
  //replace()将[beg,end)区间内每一个“与oldValue相等”的元素替换为newValue
  //replace_if()将[beg,end)区间内每一个令以下unary predicate：
  // op(elem)
  //产生true的元素替换为newValue
  //注意，op不应在函数调用过程中改变状态(state)
  //复杂度：线性（执行比较动作或调用op()，numElems次）

  coll2.clear();

  INSERT_ELEMENTS(coll2,2,7);
  INSERT_ELEMENTS(coll2,4,9);
  PRINT_ELEMENTS(coll2,"coll2: ");

  //replace all elements with value 6 with 42
  replace(coll2.begin(),coll2.end(),//range
          6,//old value
          42);//new value
  PRINT_ELEMENTS(coll2,"coll2: ");

  //replace all elements with value less than 5 with 0
  replace_if(coll2.begin(),coll2.end(),//range
             [](int elem){//criterion for replacement
               return elem<5;
             },
             0);//new value
  PRINT_ELEMENTS(coll2,"coll2: ");

  //OurputIterator
  //replace_copy(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,const T& oldValue,const T& newValue)
  //OutputIterator
  //replace_copy_if(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,UnaryPredicate op,const T& newValue)
  //replace_copy()是copy()和replace()的组合。它将源区间[sourceBeg,sourceEnd)中的元素复制到“以destBeg为起点”的目标区，同时将其中“与oldValue相等”的所有元素替换为newValue
  //replace_copy_if()是copy()和replace_if()的组合。[sourceBeg,sourceEnd)中的元素被复制到“以destBeg为起点”的目标区，同时将其中“令unary predicate op(elem)结果为true”的所有元素替换为newValue
  //两个算法都返回目标区间中“最后一个被复制元素”的下一位置，也就是第一个未被覆盖(overwritten)的元素的位置
  //注意，op不应在函数调用过程中改变状态(state)
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //复杂度：线性，执行比较动作（或调用op()）numElems次

  coll2.clear();

  INSERT_ELEMENTS(coll2,2,6);
  INSERT_ELEMENTS(coll2,4,9);
  PRINT_ELEMENTS(coll2);

  //print all elements with value 5 replace with 55
  replace_copy(coll2.cbegin(),coll2.cend(),//source
               std::ostream_iterator<int>(std::cout," "),//destination
               5,//old value
               55);//new value
  std::cout<<std::endl;

  //print all elements with a value less than 5 replaced with 42
  replace_copy_if(coll2.cbegin(),coll2.cend(),//source
                  std::ostream_iterator<int>(std::cout," "),//destination
                  std::bind(std::less<int>(),
                            std::placeholders::_1,5),//replacement criterion
                  42);//new value
  std::cout<<std::endl;

  //print each element while each odd element is replace with 0
  replace_copy_if(coll2.cbegin(),coll2.cend(),//source
                  std::ostream_iterator<int>(std::cout," "),//destination
                  [](int elem){//replacement criterion
                    return elem%2==1;
                  },
                  0);//new value
  std::cout<<std::endl;

  //11.7 移除型算法(Removing Algorithm)
  //11.7.1 移除某些元素

  //ForwardIterator
  //remove(ForwardIterator beg,ForwardIterator end,const T& value)
  //ForwardIterator
  //remove_if(ForwardIterator beg,ForwardIterator end,UnaryPredicate op)
  //remove()会移除[beg,end)区间中每一个“与value相等”的元素
  //remove_if()会移除[beg,end)区间中每一个“令unary predicate op(elem)结果为true”的元素
  //两个算法都返回被改动的序列的新逻辑终点（也就是最后一个未被移除元素的下一位置）
  //这些算法会把原本置于后面的未移除元素向前移动，覆盖被移除元素
  //未被移除的元素在相对次序上保持不变
  //调用者在调用此算法之后，应保证从此采用其所返回的新逻辑终点，不再使用原始终点end
  //注意，op不应在函数调用过程中改变状态(state)
  //注意，remove_if()通常会在内部复制它所获得的那个unary predicate，然后两次运用它。如果该unary predicate在函数调用过程中改变状态，就可能导致问题
  //由于元素会被改动，所以这些算法不可用于associative或unordered容器。然而这些容器提供了功能类似的成员函数erase()
  //List提供了一个效果相同的成员函数remove()，效能较高，原因是它不重新赋值，而是重新链接pointer
  //复杂度：线性，执行比较动作（或调用op()）numElems次

  coll.clear();

  INSERT_ELEMENTS(coll,2,6);
  INSERT_ELEMENTS(coll,4,9);
  INSERT_ELEMENTS(coll,1,7);
  PRINT_ELEMENTS(coll,"coll:             ");

  //remove all elements with value 5
  pos=remove(coll.begin(),coll.end(),//range
             5);//value to remove

  PRINT_ELEMENTS(coll,"size not changed: ");

  //erase the "removed" elements in the container
  coll.erase(pos,coll.end());
  PRINT_ELEMENTS(coll,"size changed:     ");

  //remove all elements less than 4
  coll.erase(remove_if(coll.begin(),coll.end(),//range
                       [](int elem){//remove criterion
                         return elem<4;
                       }),
             coll.end());
  PRINT_ELEMENTS(coll,"<4 removed:       ");

  //OutputIterator
  //remove_copy(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,const T& value)
  //OutputIterator
  //remove_copy_if(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,UnaryPredicate op)
  //remove_copy()是copy()和remove()的组合。它将源区间[sourceBeg,sourceEnd)内的所有元素复制到“以destBeg为起点”的目标区间去，并在复制过程中移除“与value相等”的所有元素
  //remove_copy_if()是copy()和remove_if()的组合。它将源区间[sourceBeg,sourceEnd)内的元素复制到“以destBeg为起点”的目标区间去，并在复制过程中移除“造成unary predicate op(elem)结果为true”的所有元素
  //两个算法都返回目标区间中最后一个被复制元素的下一位置（也就是第一个未被覆盖的元素）
  //注意，op不应在函数调用过程中改变状态(state)
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //partition_copy()会把元素复制到两个目标区间：其中一个满足某个predicate而另一个不满足（始自C++11）
  //复杂度：线性，执行比较动作（或调用op()）以及赋值numElems次

  coll2.clear();

  INSERT_ELEMENTS(coll2,1,6);
  INSERT_ELEMENTS(coll2,1,9);
  PRINT_ELEMENTS(coll2);

  //print elements without those having the value 3
  remove_copy(coll2.cbegin(),coll2.cend(),//source
              std::ostream_iterator<int>(std::cout," "),//destination
              3);//remove value
  std::cout<<std::endl;

  //print elements without those having a value greater than 4
  remove_copy_if(coll2.cbegin(),coll2.cend(),//source
                 std::ostream_iterator<int>(std::cout," "),//destination
                 [](int elem){//criterion for elements NOT copied
                   return elem>4;
                 });
  std::cout<<std::endl;

  //copy all elements not less than 4 into a multiset
  std::multiset<int> collmset;
  remove_copy_if(coll2.cbegin(),coll2.cend(),//source
                 inserter(collmset,collmset.end()),//destination
                 std::bind(std::less<int>(),
                           std::placeholders::_1,4));//elements NOT copied
  PRINT_ELEMENTS(collmset);

  PRINT_ELEMENTS(coll2);

  //11.7.2 移除重复元素

  //ForwardIterator
  //unique(ForwardIterator beg,ForwardIterator end)
  //ForwardIterator
  //unique(ForwardIterator beg,ForwardIterator end,BinaryPredicate op)
  //以上两种形式都会移除连续重复元素中的多余元素
  //第一形式将[beg,end)区间内所有“与前一元素相等“的元素移除。因此源序列必须先经过排序，才能使用这个算法移除所有重复元素
  //第二形式将每一个”位于元素e之后并造成binary predicate op(e,elem)结果为true“的所有elem元素移除。换言之，上述predicate并非拿元素和其原本的前一元素比较，而是拿它和”经过处理后仍健在”的前一元素比较，参见以下实例。（换言之，如果序列A，B，C，D，E，A不符合移除条件，B符合，轮到C时，C将被拿来和A比较，而不是和原本的前一元素（但已被移除的）B比较。）
  //两个形式都返回被改动的序列的新逻辑终点（也就是最后一个未被移除元素的下一位置）
  //这两个算法将“原本位置在后”的未移除元素向前移动，覆盖掉(overwrite)被移除元素
  //未被移除的元素在相对次序上保持不变
  //调用者在调用这些算法之后，应保证从此使用返回的新逻辑终点，不再使用原始终点end
  //注意，op不应在函数调用过程中改变状态(state)
  //由于会造成元素被改动，所以这些算法不可用于associative或unordered容器
  //List提供了一个效果相同的成员函数unique()，原因是它不重新赋值，而是重新链接pointer
  //复杂度：线性，执行比较动作（或调用op()）numElems次

  //source data
  int sourcedata[]={1,4,4,6,1,2,2,3,1,6,6,6,5,7,5,4,4};
  coll2.clear();

  //initialize coll2 with elements from sourcedata
  copy(std::begin(sourcedata),std::end(sourcedata),//source
       back_inserter(coll2));//destination
  PRINT_ELEMENTS(coll2);

  //remove consecutive duplicates
  pos1=unique(coll2.begin(),coll2.end());

  //print elements not removed
  //-use new logical end
  copy(coll2.begin(),pos1,//source
       std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl<<std::endl;

  //reinitialize coll2 with elements from sourcedata
  copy(std::begin(sourcedata),std::end(sourcedata),//source
       coll2.begin());//destination
  PRINT_ELEMENTS(coll2);

  //remove elements if there was a previous greater element
  coll2.erase(unique(coll2.begin(),coll2.end(),
                     std::greater<int>()),
              coll2.end());
  PRINT_ELEMENTS(coll2);

  //OutputIterator
  //unique_copy(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg)
  //OutputIterator
  //unique_copy(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,BinaryPredicate op)
  //两种形式都是copy()和unique()的组合
  //两者都将源区间[sourceBeg,sourceEnd)内的元素复制到“以destBeg起始的目标区间”，并移除重复元素
  //两个算法都返回目标区间内“最后一个被复制元素”的下一位置（也就是第一个未被覆盖的元素）
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //复杂度：线性，执行比较动作（或调用op()）numElems次

  coll2.clear();

  //initialize coll2 with elements from sourcedata
  copy(std::begin(sourcedata),std::end(sourcedata),//source
       back_inserter(coll2));//destination
  PRINT_ELEMENTS(coll2);

  //print elements with consecutive duplicates removed
  unique_copy(coll2.cbegin(),coll2.cend(),//source
              std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //print elements without consecutive entries that differ by one
  unique_copy(coll2.cbegin(),coll2.cend(),//source
              std::ostream_iterator<int>(std::cout," "),//destination
              differenceOne);//duplicates criterion
  std::cout<<std::endl;

  //don't skip leading whitespaces by default
  // std::cin.unsetf(std::ios::skipws);

  //copy standard input to standard output
  //-while compressing spaces
  //unique_copy(std::istream_iterator<char>(std::cin),//beginning of source:cin
  //            std::istream_iterator<char>(),//end of source:end-of-file
  //            std::ostream_iterator<char>(std::cout),//destination:cout
  //            bothSpaces);

  //11.8 变序型算法(Mutating Algorithm)
  //11.8.1 反转元素次序(Reversing the Order of Elements)

  //void
  //reverse(BidirectionalIterator beg,BidirectionalIterator end)
  //OutputIterator
  //reverse_copy(BidirectionalIterator sourceBeg,BidirectionalIterator sourceEnd,OutputIterator destBeg)
  //reverse()会将[beg,end)区间内的元素全部反转次序
  //reverse_copy()会将源区间[sourceBeg,sourceEnd)内的元素复制到“以destBeg起始的目标区间”，并在复制过程中颠倒次序
  //reverse_copy()返回目标区间内“最后一个被复制元素”的下一位置，也就是第一个未被覆盖(overwritten)的元素
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //List提供了一个效果相同的成员函数reverse()，但它并非重新赋值，而是重新链接pointer，因此具有更佳效能
  //复杂度：线性，分别进行numElems/2次交换，或numElems次赋值

  coll.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll: ");

  //reverse order of elements
  reverse(coll.begin(),coll.end());
  PRINT_ELEMENTS(coll,"coll: ");

  //reverse order from second to last element but one
  reverse(coll.begin()+1,coll.end()-1);
  PRINT_ELEMENTS(coll,"coll: ");

  //print all of them in reverse order
  reverse_copy(coll.cbegin(),coll.cend(),//source
               std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //11.8.2 旋转元素(Rotating Elements)

  //ForwardIterator
  //rotate(ForwardIterator beg,ForwardIterator newBeg,ForwardIterator end)
  //将[beg,end)区间内的元素旋转，执行后，*newBeg成为新的第一元素
  //自C++11起，它返回beg+(end-newbeg)，那是原本的第一元素经旋转后的新位置。C++11之前的返回类型是void
  //调用者必须确保newBeg是[beg,end)区间内的一个有效位置，否则会引发不确定的行为
  //复杂度：线性，最多进行numElems次交换

  coll.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll:       ");

  //rotate one element to the left
  rotate(coll.begin(),//beginning of range
         coll.begin()+1,//new first element
         coll.end());//end of range
  PRINT_ELEMENTS(coll,"one left:   ");

  //rotate two elements to the right
  rotate(coll.begin(),//beginning of range
         coll.end()-2,//new first element
         coll.end());//end of range
  PRINT_ELEMENTS(coll,"two right:  ");

  //rotate so that element with value 4 is the beginning
  rotate(coll.begin(),//beginning of range
         find(coll.begin(),coll.end(),4),//new first element
         coll.end());//end of range
  PRINT_ELEMENTS(coll,"4 first:    ");

  //OutputIterator
  //rotate_copy(ForwardIterator sourceBeg,ForwardIterator newBeg,ForwardIterator sourceEnd,OutputIterator destBeg)
  //它是copy()和rotate()的组合
  //将源区间[sourceBeg,sourceEnd)内的元素复制到“以destBeg起始”之目标区间内，同时旋转元素，使*newBeg成为新的第一元素
  //返回目标区间内“最后一个被复制元素”的下一位置destBeg+(sourceEnd-sourceBeg)
  //调用者必须确保newBeg是[beg,end)区间内的一个有效位置，否则会引发不确定行为
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //源区间和目标区间两者不可重叠
  //复杂度：线性，执行numElems次赋值

  std::set<int> collset;

  INSERT_ELEMENTS(collset,1,9);
  PRINT_ELEMENTS(collset);

  //print elements rotated one element to the left
  std::set<int>::const_iterator posset=next(collset.cbegin());
  rotate_copy(collset.cbegin(),//beginning of source
              posset,//new first element
              collset.cend(),//end of source
              std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //print elements rotated two elements to the right
  posset=collset.cend();
  advance(posset,-2);
  rotate_copy(collset.cbegin(),//beginning of source
              posset,//new first element
              collset.cend(),//end of source
              std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //print elements rotated so that element with value 4 is the beginning
  rotate_copy(collset.cbegin(),//beginning of source
              collset.find(4),//new first element
              collset.cend(),//end of source
              std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //11.8.3 排列元素(Permuting Elements)

  //bool
  //next_permutation(BidirectionalIterator beg,BidirectionalIterator end)
  //bool
  //next_permutation(BidirectionalIterator beg,BidirectionalIterator end,BinaryPredicate op)
  //bool
  //prev_permutation(BidirectionalIterator beg,BidirectionalIterator end)
  //bool
  //prev_permutation(BidirectionalIterator beg,BidirectionalIterator end,BinaryPredicate op)
  //next_permutation()会改变[beg,end)区间内的元素次序，使它们符合“下一排列次序”
  //prev_permutation()会改变[beg,end)区间内的元素次序，使它们符合“上一排列次序”
  //第一形式使用operator<比较元素
  //第二形式使用binary predicate
  // op(elem1,elem2)
  //比较元素，如果“elem1小于elem2”它应该返回true
  //如果元素得以排列成正规次序（normal order，意指字典序），则两个算法都返回false。所谓正规次序，对next_permutation()而言是升序，对prev_permutation()而言是降序。因此，如果要遍历所有排列，你必须首先将所有元素（按升序或降序）排序，然后逐次调用next_permutation()或 prev_permutation()，直到算法返回true
  //复杂度：线性，最多执行numElems/2次交换

  coll.clear();
  INSERT_ELEMENTS(coll,1,3);
  PRINT_ELEMENTS(coll,"on entry:   ");

  //permute elements until they are sorted
  //-runs through all permutations because the elements are sorted now
  while(next_permutation(coll.begin(),coll.end())){
    PRINT_ELEMENTS(coll," ");
  }
  PRINT_ELEMENTS(coll,"afterward:  ");

  //permute until descending sorted
  //-this is the next permutation after ascending sorting
  //-so the loop ends immediately
  while(prev_permutation(coll.begin(),coll.end())){
    PRINT_ELEMENTS(coll," ");
  }
  PRINT_ELEMENTS(coll,"now:        ");

  //permute elements until they are sorted in descending order
  //-runs through all permutations because the elements are sorted in descending order now
  while(prev_permutation(coll.begin(),coll.end())){
    PRINT_ELEMENTS(coll," ");
  }
  PRINT_ELEMENTS(coll,"afterward:  ");

  //11.8.4 对元素重新洗牌(Shuffling Elements)

  //void
  //shuffle(RandomAccessIterator beg,RandomAccessIterator end,UniformRandomNumberGenerator&& eng)
  //void
  //random_shuffle(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //random_shuffle(RandomAccessIterator beg,RandomAccessIterator end,RandomFunc&& op)
  //第一形式始自C++11,将[beg,end)区间内的元素打乱次序重新洗牌，使用你所给定的随机数引擎eng
  //第二形式使用一个均匀分布随机数产生器(uniform distribution random number generator)打乱[beg,end)区间内的元素次序
  //第三形式使用op打乱[beg,end)区间内的元素次序。算法内部使用一个整数值（其类型为“迭代器所提供之difference_type"）来调用op：
  // op(max)
  //这个操作应该返回一个”大于0，小于max“的随机数，不包括max自身
  //对于shuffle()，你不该传入一个只是临时创建出来的引擎。
  //在C++11之前，op被声明为RandomFunc&，所以你不能够对此传入一个临时对象或一个寻常函数
  //复杂度：线性，执行numElems-1次交换

  coll.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll:     ");

  //shuffle all elements randomly
  random_shuffle(coll.begin(),coll.end());

  PRINT_ELEMENTS(coll,"shuffled: ");

  //sort them again
  sort(coll.begin(),coll.end());
  PRINT_ELEMENTS(coll,"sorted:   ");

  //shuffle elements with default engine
  std::default_random_engine dre;
  shuffle(coll.begin(),coll.end(),//range
          dre);//random-number generator

  PRINT_ELEMENTS(coll,"shuffled: ");

  coll.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll,"coll:      ");

  //shuffle elements with self-written random-number generator
  MyRandom rd;
  random_shuffle(coll.begin(),coll.end(),//range
                 rd);//random-number generator

  PRINT_ELEMENTS(coll,"shuffled:  ");

  //random_shuffle(coll.begin(),coll.end(),MyRandom());//ERROR before C++11

  //11.8.5 将元素向前搬(Moving Elements to the Front)

  //ForwardIterator
  //partition(ForwardIterator beg,ForwardIterator end,UnaryPredicate op)
  //BidirectionalIterator
  //stable_partition(BidirectionalIterator beg,BidirectionalIterator end,UnaryPredicate op)
  //这两个算法将[beg,end)区间内造成以下unary predicate op(elem)结果为true的元素向前端移动(to the front)
  //这两个算法都返回“令op()结果为false”的第一个元素位置
  //两都的差别是，无论元素是否满足给定准则，stable_partition()会保持它们之间的相对次序
  //你可以运用此算法，根据排序准则，将所有元素分割为两部分。nth_element()具有类似能力。至于这些算法和nth_element()之间的区别，请看前面的例子
  //注意，op不应在函数调用过程中改变状态(state)
  //在C++11之前，partition()要求的是bidirectional iterator而不是forward iterator，并保证至多执行numElems/2次交换
  //可使用partition_copy()将满足某个predicate的元素复制到一个目标区间内，将不满足的元素复制到另一个目标区间（始自C++11）
  //复杂度：
  //-对于partition()：线性，共执行op()numElems次，以及最多numElems/2次交换
  //-对于stable_partition()：如果系统拥有足够内存，那么就是线性复杂度，执行op()及交换共numElems次；如果没有足够内存，则是n-log-n复杂度，执行op()动作numElems*log(numElems)次

  std::vector<int> coll7;
  std::vector<int> coll8;

  INSERT_ELEMENTS(coll7,1,9);
  INSERT_ELEMENTS(coll8,1,9);
  PRINT_ELEMENTS(coll7,"coll7:    ");
  PRINT_ELEMENTS(coll8,"coll8:    ");
  std::cout<<std::endl;

  //move all even elements to the front
  std::vector<int>::iterator pos9,pos10;
  pos9=partition(coll7.begin(),coll7.end(),//range
                 [](int elem){//criterion
                   return elem%2==0;
                 });
  pos10=stable_partition(coll8.begin(),coll8.end(),//range
                         [](int elem){//criterion
                           return elem%2==0;
                         });

  //print collections and first odd element
  PRINT_ELEMENTS(coll7,"coll7:    ");
  std::cout<<"first odd element: "<<*pos9<<std::endl;
  PRINT_ELEMENTS(coll8,"coll8:    ");
  std::cout<<"first odd element: "<<*pos10<<std::endl;

  //11.8.6 划分为两个子区间(Partition into Two Subranges)

  //pair<OutputIterator1,OutputIterator2>
  //partition_copy(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator1 destTrueBeg,OutputIterator2 destFalseBeg,UnaryPredicate op)
  //以predicate op()为依据，拆分[beg,end)区间内的所有元素成为两个子区间
  //所有“造成unary predicate op(elem)产生true”的元素都被复制到始于destTrueBeg的区间内。所有“造成该predicate产生false”的元素都被复制到始于destFalseBeg的区间内
  //返回一个pair，其内是两个iterator，分别指向destTrueBeg区间和destFalseBeg区间内之最末元素的下一位置
  //注意，op不应在函数调用过程中改变状态(state)，始自C++11
  //如果你只是需要“满足（或不满足）predicate”的元素，可使用copy_if()或remove_copy_if()
  //复杂度：线性（至多numElems次调用op()）

  coll.clear();
  coll={1,6,33,7,22,4,11,33,2,7,0,42,5};
  PRINT_ELEMENTS(coll,"coll: ");

  //destination collections
  std::vector<int> evenColl;
  std::vector<int> oddColl;

  //copy all elements partitioned accordingly into even and odd elements
  partition_copy(coll.cbegin(),coll.cend(),//source range
                 back_inserter(evenColl),//destination for even elements
                 back_inserter(oddColl),//destination for odd elements
                 [](int elem){//predicate:check for even elements
                   return elem%2==0;
                 });
  PRINT_ELEMENTS(evenColl,"evenColl: ");
  PRINT_ELEMENTS(oddColl,"oddColl: ");

  //11.9 排序算法(Sorting Algorithm)
  //11.9.1 对所有元素排序

  //void
  //sort(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //sort(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //void
  //stable_sort(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //stable_sort(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //sort()和stable_sort()的第一形式使用operator<对区间[beg,end)内的所有元素排序
  //sort()和stable_sort()的第二形式使用binary predicate op(elem1,elem2)作为排序准则，对区间[beg,end)内的所有元素排序
  //注意，op必须针对元素值定义出strict weak ordering
  //注意，op不应在函数调用过程中改变状态(state)
  //sort()和stable_sort()的区别是，后者保证相等之各元素的相对次序在排序后保持不变
  //不可以对list或forward list调用这些算法，因为两者都不提供random-access iterator。不过它们提供了成员函数sort()可用来对其自身元素排序
  //sort()保证了很不错的平均效能n-log-n。然而如果你需要极力避免可能出现的最差状况，就该使用partial_sort()或stable_sort()
  //复杂度：
  //-sort()：平均n-log-n（平均大约执行numElems*log(numElems)次比较）
  //-stable_sort()：如果系统拥有足够内存，那么就是n-log-n，也就是执行numElems*log(numElems)次比较；如果没有足够内存，则复杂度是n-log-n*log-n，亦即执行numElems*log(numElems)*log(numElems)次比较

  coll1.clear();

  INSERT_ELEMENTS(coll1,1,9);
  INSERT_ELEMENTS(coll1,1,9);

  PRINT_ELEMENTS(coll1,"on entry: ");

  //sort elements
  sort(coll1.begin(),coll1.end());

  PRINT_ELEMENTS(coll1,"sorted: ");

  //sorted reverse
  sort(coll1.begin(),coll1.end(),//range
       std::greater<int>());//sorting criterion

  PRINT_ELEMENTS(coll1,"sorted >: ");

  //fill two collections with the same elements
  std::vector<std::string> coll9={"1xxx","2x","3x","4x","5xx","6xxxx","7xx","8xxx","9xx","10xxx","11","12","13","14xx","15","16","17"};
  std::vector<std::string> coll10(coll9);

  PRINT_ELEMENTS(coll9,"on entry:\n ");

  //sort(according to the length of the strings)
  sort(coll9.begin(),coll9.end(),//range
       lessLength);//criterion
  stable_sort(coll10.begin(),coll10.end(),//range
              lessLength);//criterion

  PRINT_ELEMENTS(coll9,"\nwith sort():\n");
  PRINT_ELEMENTS(coll10,"\nwith stable_sort():\n");

  //11.9.2 局部排序(Partial Sorting)

  //void
  //partial_sort(RandomAccessIterator beg,RandomAccessIterator sortEnd,RandomAccessIterator end)
  //void
  //partial_sort(RandomAccessIterator beg,RandomAccessIterator sortEnd,RandomAccessIterator end,BinaryPredicate op)
  //第一形式以operator<对[beg,end)区间内的元素排序，使[beg,sortEnd)区间内的元素处于已序状态(sorted order)
  //第二形式使用binary predicate op(elem1,elem2)作为排序准则，使[beg,sortEnd)区间内的元素处于已序状态(sorted order)
  //注意，op必须针对元素值定义出strict weak ordering
  //注意，op不应在函数调用过程中改变状态(state)
  //和sort()不同的是，partial_sort()并不对全部元素排序：一旦第一个元素至sortEnd之间的所有元素都排妥次序，就立刻停止。所以，如果你只需要前3个排好序的元素，可使用partial_sort()来节省时间，它不会对剩余的元素进行非必要的排序
  //如果sortEnd等end，那么partial_sort()会对整个序列排序。平均而言其效能不及sort()，不过以最差情况而论则优于sort()
  //复杂度：在线性和n-log-n之间，大约执行numElems*log(numSortedElems)次比较

  coll1.clear();

  INSERT_ELEMENTS(coll1,3,7);
  INSERT_ELEMENTS(coll1,2,6);
  INSERT_ELEMENTS(coll1,1,5);
  PRINT_ELEMENTS(coll1);

  //sort until the first five elements are sorted
  partial_sort(coll1.begin(),//beginning of the range
               coll1.begin()+5,//end of sorted range
               coll1.end());//end of full range
  PRINT_ELEMENTS(coll1);

  //sort inversely until the first five elements are sorted
  partial_sort(coll1.begin(),//beginning of the range
               coll1.begin()+5,//end of sorted range
               coll1.end(),//end of full range
               std::greater<int>());//sorting criterion
  PRINT_ELEMENTS(coll1);

  //sort all elements
  partial_sort(coll1.begin(),//beginning of the range
               coll1.end(),//end of sorted range
               coll1.end());//end of full range
  PRINT_ELEMENTS(coll1);

  //RandomAccessIterator
  //partial_sort_copy(InputIterator sourceBeg,InputIterator sourceEnd,RandomAccessIterator destBeg,RandomAccessIterator destEnd)
  //RandomAccessIterator
  //partial_sort_copy(InputIterator sourceBeg,InputIterator sourceEnd,RandomAccessIterator destBeg,RandomAccessIterator destEnd,BinaryPredicate op)
  //两者都是copy()和partial_sort()的组合
  //它们将元素从源区间[sourceBeg,sourceEnd)复制到目标区间[destBeg,destEnd)并且进行排序
  //“被排序（被复制）的元素量”是源区间和目标区间两者所含元素量的较小值
  //两者都返回目标区间内“最后一个被复制元素”的下一位置（也就是第一个未被覆盖的元素）
  //如果源区间[sourceBeg,sourceEnd)内的元素量小于目标区间[destBeg,destEnd)内的元素量，所有元素都会被排序并复制，整个行为相当于copy()和sort()的组合
  //注意，op必须针对元素值定义出strict weak ordering
  //复杂度：在线性和n-log-n之间，大约执行numElems*log(numSortedElems)次比较

  coll1.clear();
  std::vector<int> coll11(6);//initialize with 6 elements
  std::vector<int> coll30(30);//initialize with 30 elements

  INSERT_ELEMENTS(coll1,3,7);
  INSERT_ELEMENTS(coll1,2,6);
  INSERT_ELEMENTS(coll1,1,5);
  PRINT_ELEMENTS(coll1);

  //copy elements of coll1 sorted into coll11
  std::vector<int>::const_iterator pos11;
  pos11=partial_sort_copy(coll1.cbegin(),coll1.cend(),
                          coll11.begin(),coll11.end());

  //print all copied elements
  copy(coll11.cbegin(),pos11,
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //copy elements of coll1 sorted into coll30
  std::vector<int>::const_iterator pos30;
  pos30=partial_sort_copy(coll1.cbegin(),coll1.cend(),
                          coll30.begin(),coll30.end(),
                          std::greater<int>());

  //print all copied elements
  copy(coll30.cbegin(),pos30,
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //11.9.3 根据第n个元素排序

  //void
  //nth_element(RandomAccessIterator beg,RandomAccessIterator nth,RandomAccessIterator end)
  //void
  //nth_element(RandomAccessIterator beg,RandomAccessIterator nth,RandomAccessIterator end,BinaryPredicate op)
  //两种形式都对[beg,end)区间内的元素排序，使第n个位置上的元素就位，也就是说所有在位置n之前的元素都小于等于它，所有在位置n之后的元素都大于等于它。这样，你就得到了“根据n位置上的元素”分割开来的两个子序列，第一子序列的元素统统小于第二子序列的元素。如果你只需要n个最大或最小元素，但不要求它们必须处于排序状态(sorted)，这个算法就很有用
  //第一形式使用operator<作为排序准则，第二形式使用binary predicate op(elem1,elem2)作为排序准则
  //注意，op必须针对元素值定义出strict weak ordering
  //注意，op不应在函数调用过程中改变状态(state)
  //partition()算法也可以根据某个排序准则将序列中的元素分割成两部分。
  //复杂度：平均为线性

  coll1.clear();

  INSERT_ELEMENTS(coll1,3,7);
  INSERT_ELEMENTS(coll1,2,6);
  INSERT_ELEMENTS(coll1,1,5);
  PRINT_ELEMENTS(coll1);

  //extract the four lowest elements
  nth_element(coll1.begin(),//beginning of range
              coll1.begin()+3,//element that should be sorted correctly
              coll1.end());//end of range

  //print them
  std::cout<<"the four lowest elements are: ";
  copy(coll1.cbegin(),coll1.cbegin()+4,
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //extract the four highest elements
  nth_element(coll1.begin(),//beginning of range
              coll1.end()-4,//element that should be sorted correctly
              coll1.end());//end of range

  //print them
  std::cout<<"the four highest elements are: ";
  copy(coll1.cend()-4,coll1.cend(),
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //extract the four highest elements(second version)
  nth_element(coll1.begin(),//beginning of range
              coll1.begin()+3,//element that should be sorted correctly
              coll1.end(),//end of range
              std::greater<int>());//sorting criterion

  //print them
  std::cout<<"the four highest elements are: ";
  copy(coll1.cbegin(),coll1.cbegin()+4,
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //11.9.4 Heap算法

  //void
  //make_heap(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //make_heap(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //两种形式都将[beg,end)区间内的元素转化为heap
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //只有在多于一个元素的情况下，才有必要使用这些函数处理heap，如果只有单一元素，那么它自动形成一个heap
  //复杂度：线性，至多执行3*numElems次比较

  //void
  //push_heap(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //push_heap(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //两种形式都将end之前的最后一个元素加入原本就是heap的[beg,end-1)区间内，使整个[beg,end)区间成为一个heap
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //调用者必保证，进入函数时，[beg,end-1)区间内的元素原本便已形成一个heap（在相同的排序准则下），而新元素紧跟其后
  //复杂度：对数，至多执行log(numElems)次比较

  //void
  //pop_heap(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //pop_heap(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //以上两种形式都将heap[beg,end)内的最高元素（也就是第一个元素）移到最后位置，并将剩余区间[beg,end-1]内的元素组织起来，成为一个新的heap
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //调用者必须保证，进入函数时，[beg,end)区间内的元素原本便已形成一个heap（在相同的排序准则下）
  //复杂度：对数，至多执行2*log(numElems)次比较

  //void
  //sort_heap(RandomAccessIterator beg,RandomAccessIterator end)
  //void
  //sort_heap(RandomAccessIterator beg,RandomAccessIterator end,BinaryPredicate op)
  //以上两种形式都可以将heap[beg,end)转换为一个已排序(sorted)序列
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //注意，此算法一旦结束，该区间就不再是个heap了
  //调用者必须保证，进入函数时，区间[beg,end)内的元素原本已形成一个heap（在相同的排序准则下）
  //复杂度：n-log-n，最多执行numElems*log(numElems)次比较动作

  coll.clear();

  INSERT_ELEMENTS(coll,3,7);
  INSERT_ELEMENTS(coll,5,9);
  INSERT_ELEMENTS(coll,1,4);

  PRINT_ELEMENTS(coll,"on entry:           ");

  //convert collection into a heap
  make_heap(coll.begin(),coll.end());

  PRINT_ELEMENTS(coll,"after make_heap():  ");

  //pop next element out of the heap
  pop_heap(coll.begin(),coll.end());
  coll.pop_back();

  PRINT_ELEMENTS(coll,"after pop_heap():   ");

  //push new element into the heap
  coll.push_back(17);
  push_heap(coll.begin(),coll.end());

  PRINT_ELEMENTS(coll,"after push_heap():  ");

  //convert heap into a sorted collection
  //-NOTE: after the call it is no longer a heap
  sort_heap(coll.begin(),coll.end());

  PRINT_ELEMENTS(coll,"after sort_heap():  ");

  //11.10 已排序区间算法(Sorted-Range Algorithm)
  //11.10.1 查找元素(Searching Element)

  //bool
  //binary_search(ForwardIterator beg,ForwardIterator end,const T& value)
  //bool
  //binary_search(ForwardIterator beg,ForwardIterator end,const T& value,BinaryPredicate op)
  //两种形式都用来判断已排序区间[beg,end)中是否包含“和value等值”的元素
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //如果想要获得你所查找的元素的位置，应该使用lower_bound()、upper_bound()或equal_range()
  //调用者必须确保，进入算法之际，工作区间已排序（在指定的排序准则下）
  //复杂度：如果搭配random-access iterator将是对数复杂度，否则为线性复杂度（这些算法至多执行log(numElems)+2次比较，但若搭配的不是random-access iterator，遍历元素的操作复杂度是线性，于是整体复杂度就是线性了）

  coll2.clear();

  INSERT_ELEMENTS(coll2,1,9);
  PRINT_ELEMENTS(coll2);

  //check existence of element with value 5
  if(binary_search(coll2.cbegin(),coll2.cend(),5)){
    std::cout<<"5 is present"<<std::endl;
  }
  else{
    std::cout<<"5 is not present"<<std::endl;
  }

  //check existence of element with value 42
  if(binary_search(coll2.cbegin(),coll2.cend(),42)){
    std::cout<<"42 is present"<<std::endl;
  }
  else{
    std::cout<<"42 is not present"<<std::endl;
  }

  //bool
  //includes(InputIterator1 beg,InputIterator1 end,InputIterator2 searchBeg,InputIterator2 searchEnd)
  //bool
  //includes(InputIterator1 beg,InputIterator1 end,InputIterator2 searchBeg,InputIterator2 searchEnd,BinaryPredicate op)
  //两种形式都用来判断已排序区间[beg,end)是否包含另一个已排序区间[searchBeg,searchEnd)的全部元素。也就是说，对于[searchBeg,searchEnd)中的每一个元素，如果[beg,end)必有一个对应的相等元素，那么[searchBeg,searchEnd)肯定是[beg,end)的子集
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //调用者必须确保在进入算法之际，两区间都已根据同一个排序准则排好序了
  //复杂度：线性，至多执行2*(numElems+numSearchElems)-1次比较动作

  coll2.clear();
  coll.clear();

  INSERT_ELEMENTS(coll2,1,9);
  PRINT_ELEMENTS(coll2,"coll:     ");

  coll.push_back(3);
  coll.push_back(4);
  coll.push_back(7);
  PRINT_ELEMENTS(coll,"search:    ");

  //check whether all elements in search are also in coll
  if(includes(coll2.cbegin(),coll2.cend(),
              coll.cbegin(),coll.cend())){
    std::cout<<"all elements of search are also in coll"<<std::endl;
  }
  else{
    std::cout<<"not all elements of search are also in coll"<<std::endl;
  }

  //ForwardIterator
  //lower_bound(ForwardIterator beg,ForwardIterator end,const T& value)
  //ForwardIterator
  //lower_bound(ForwardIterator beg,ForwardIterator end,const T& value,BinaryPredicate op)
  //ForwardIterator
  //upper_bound(ForwardIterator beg,ForwardIterator end,const T& value)
  //ForwardIterator
  //upper_bound(ForwardIterator beg,ForwardIterator end,const T& value,BinaryPredicate op)
  //lower_bound()返回第一个“大于等于value”的元素位置。这是可插入“元素值为value”且“不破坏区间[beg,end)之已排序性”的第一个位置
  //upper_bound()返回第一个“大于value”的元素位置。这是可插入“元素值为value”且“不破坏区间[beg,end)已排序性”的最后一个位置
  //如果不存在“其值为value”的元素，上述所有算法都返回end
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //调用者必须确保进入算法之际，所有区间都已根据排序准则排好序了
  //若要同时获得lower_bound()和upper_bound()的结果，请使用equal_range()
  //Associative容器提供等效的成员函数，且效能更佳
  //复杂度：如果搭配random-access iterator将是对数复杂度，否则为线性复杂度（这些算法至多执行log(numElems)+1次比较，但若搭配的不是random-access iterator，遍历元素的操作复杂度是线性，于是整体复杂度就是线性了）

  coll2.clear();

  INSERT_ELEMENTS(coll2,1,9);
  INSERT_ELEMENTS(coll2,1,9);
  coll2.sort();
  PRINT_ELEMENTS(coll2);

  //print first and last position 5 could get inserted
  auto pos12=lower_bound(coll2.cbegin(),coll2.cend(),5);
  auto pos13=upper_bound(coll2.cbegin(),coll2.cend(),5);

  std::cout<<"5 could get position "
           <<distance(coll2.cbegin(),pos12)+1
           <<" up to "
           <<distance(coll2.cbegin(),pos13)+1
           <<" without breaking the sorting"<<std::endl;

  //insert 3 at the first possible position without breaking the sorting
  coll2.insert(lower_bound(coll2.begin(),coll2.end(),
                           3),
               3);

  //insert 7 at the last possible position without breaking the sorting
  coll2.insert(upper_bound(coll2.begin(),coll2.end(),
                           7),
               7);

  PRINT_ELEMENTS(coll2);

  //pair<ForwardIterator,ForwardIterator>
  //equal_range(ForwardIterator beg,ForwardIterator end,const T& value)
  //pair<ForwardIterator,ForwardIterator>
  //equal_range(ForwardIterator beg,ForwardIterator end,const T& value,BinaryPredicate op)
  //两种形式都返回“与value相等”的元素所形成的区间。在此区间内插入“其值为value”的元素，并不会破坏[beg,end)区间的已排序性
  //和下式等效：
  // make_pair(lower_bound(...),upper_bound(...))
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //调用者必须确保在进入算法之际，区间已按照排序准则排好序了
  //Associative和unordered容器都提供有等效的成员函数，且效能更佳
  //复杂度：如果搭配random-access iterator将是对数复杂度，否则为线性复杂度（这些算法至多执行2*log(numElems)+1次比较，但搭配的不是random-access iterator，遍历元素的操作复杂度是线性，于是整体复杂度就是线性了）

  coll2.clear();

  INSERT_ELEMENTS(coll2,1,9);
  INSERT_ELEMENTS(coll2,1,9);
  coll2.sort();
  PRINT_ELEMENTS(coll2);

  //print first and last position 5 could get inserted
  std::pair<std::list<int>::const_iterator,std::list<int>::const_iterator> range;
  range=equal_range(coll2.cbegin(),coll2.cend(),5);

  std::cout<<"5 could get position "
           <<distance(coll2.cbegin(),range.first)+1
           <<" up to "
           <<distance(coll2.cbegin(),range.second)+1
           <<" without breaking the sorting"<<std::endl;

  //11.10.2 合并元素(Merging Elements)

  //OutputIterator
  //merge(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg)
  //OutputIterator
  //merge(InputIterator source1beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg,BinaryPredicate op)
  //两者都是将源区间[source1Beg,source1End)和[source2Beg,source2End)内的元素合并，使得“以destBeg起始之目标区间”内含两个源区间的所有元素
  //目标区间内的所有元素都将处于排序状态下
  //两者都返回目标区间内“最后一个被复制元素”的下一位置（也就是第一个未被覆盖的元素位置）
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //源区间不会有任何变化
  //根据C++ standard的说法，调用者应当确保两个源区间一开始都已排序。然而在大部分实现中，上述算法可以将两个未排序的源区间内的元素合并到一个未排序的目标区间中。不过，如果考量移植性，这种情况下你应该改而调用copy()两次，而不是使用merge()
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //源区间和目标区间两者不可重叠
  //List和forward list都提供一个特殊成员函数merge()，用来合并两个list
  //如果你要确保“两个源区间中都出现的元素”在目标区间中只出现一次，请使用set_union()
  //如果你只想获得“同时存在于两个源区间内”的元素，请使用set_intersection()
  //复杂度：线性，至多执行numElems1+numElems2-1次比较

  coll2.clear();
  collset.clear();

  //fill both collections with some sorted elements
  INSERT_ELEMENTS(coll2,1,6);
  INSERT_ELEMENTS(collset,3,8);

  PRINT_ELEMENTS(coll2,"coll1:     ");
  PRINT_ELEMENTS(collset,"coll2:     ");

  //print merged sequence
  std::cout<<"merged:  ";
  merge(coll2.cbegin(),coll2.cend(),collset.cbegin(),collset.cend(),
        std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //OutputIterator
  //set_union(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg)
  //OutputIterator
  //set_union(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg,BinaryPredicate op)
  //两者都是将已排序的源区间[source1Beg,source1End)和[source2Beg,source2End)内的元素合并，得到“以destBeg起始”之目标区间，后者内含的元素要么来自第一源区间，要么来自第二源区间，抑或同时来自两者
  //目标区间内的所有元素都处于排序状态
  //同时出现于两个源区间内的元素，在并集区间(union range)中将只出现一次。不过如果原来的某个源区间内原本就存在重复元素，则目标区间内也会有重复元素——重复的次数是两个源区间内的重复次数的较大值
  //两者都返回目标区间内“最后一个被复制元素”的下一位置（也就是第一个未被覆盖的元素的位置）//op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //源区间不会有任何变化，调用者应当确保两个源区间一开始都已根据排序准则排好序
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //源区间和目标区间两者不可重叠，如果你想得到两个源区间内的全部元素，请用merge()
  //复杂度：线性，至多执行2*(numElems1+numElems2)-1次比较

  //OutputIterator
  //set_intersection(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg)
  //OutputIterator
  //set_intersection(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg,BinaryPredicate op)
  //两者都是将已排序之源区间[source1Beg,source1End)和[source2Beg,source2end)的元素合并，得到“以destBeg起始”之目标区间，后者内含的元素不但存在于第一源区间，也存在于第二源区间
  //目标区间内的所有元素都处于排序状态
  //如果某个源区间内原就存在有重复元素，则目标区间内也会有重复元素——重复的次数是两个源区间内的重复次数的较小值
  //两者都返回目标区间内“最后一个被合并元素”的下一位置
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //源区间不会有任何变化，调用者应当确保两个源区间一开始都已根据排序准则排好序
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //源区间和目标区间两者不可重叠
  //复杂度：线性，至多执行2*(numElems1+numElems2)-1次比较

  //OutputIterator
  //set_difference(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg)
  //OutputIterator
  //set_difference(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg,BinaryPredicate op)
  //两者都是将已排序之源区间[source1Beg,source1End)和[source2Beg,source2End)的元素合并，得到“以destBeg起始”之目标区间，后者内含的元素只存在于第一源区间，不存在于第二源区间
  //目标区间内的所有元素都处于排序状态
  //如果某个源区间内原就存在有重复元素，则目标区间内也会有重复元素——重复次数是第一源区间内的重复次数减去第二源区间内的相应重复次数，如果第二源区间内的重复次数大于第一源区间内的相应重复次数，目标区间内的对应重复次数将会是0
  //两者都返回目标区间内“最后一个被合并元素”的下一位置
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //源区间不会有任何变化，调用者应当确保两个源区间一开始都已根据排序准则排好序
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //源区间和目标区间两者不可重叠
  //复杂度：线性，至多执行2*(numElems1+numElems2)-1次比较

  //OutputIterator
  //set_symmetric_difference(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg)
  //OutputIterator
  //set_symmetric_difference(InputIterator source1Beg,InputIterator source1End,InputIterator source2Beg,InputIterator source2End,OutputIterator destBeg,BinaryPredicate op)
  //两者都是将已排序之源区间[source1Beg,source1end)和[source2Beg,source2End)的元素合并，得到”以destBeg起始“之目标区间，后者内含的元素或存在于第一源区间，或存在于第二源区间，但不同时存在于两个源区间内。
  //目标区间内的所有元素都处于排序状态
  //如果某个源区间内原就存在有重复元素，则目标区间内也会有重复元素——重复的次数是两个源区间内的对应重复元素的个数差值
  //两者都返回目标区间内“最后一个被合并元素”的下一位置
  //op是个可有可无的（可选的）binary predicate，被视为排序准则：
  // op(elem1,elem2)
  //源区间不会有任何变化，调用者应当确保两个源区间一开始都已根据排序准则排好序
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //源区间和目标区间两者不可重叠
  //复杂度：线性，至多执行2*(numElems1+numElem2)-1次比较

  coll.clear();
  coll={1,2,2,4,6,7,7,9};
  coll1.clear();
  coll1={2,2,2,3,6,6,8,9};

  //print source ranges
  std::cout<<"c1:                               ";
  copy(coll.cbegin(),coll.cend(),
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;
  std::cout<<"c2:                               ";
  copy(coll1.cbegin(),coll1.cend(),
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl<<std::endl;

  //sum the ranges by using merge()
  std::cout<<"merge():                          ";
  merge(coll.cbegin(),coll.cend(),
        coll1.cbegin(),coll1.cend(),
        std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //unite the ranges by using set_union()
  std::cout<<"set_union():                      ";
  set_union(coll.cbegin(),coll.cend(),
            coll1.cbegin(),coll1.cend(),
            std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //intersect the ranges by using set_intersection
  std::cout<<"set_intersection():               ";
  set_intersection(coll.cbegin(),coll.cend(),
                   coll1.cbegin(),coll1.cend(),
                   std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //determine elements of first range without elements of second range
  //by using set_difference()
  std::cout<<"set_difference():                 ";
  set_difference(coll.cbegin(),coll.cend(),
                 coll1.cbegin(),coll1.cend(),
                 std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //determine difference the ranges with set_symmetric_difference()
  std::cout<<"set_symmetric_difference():       ";
  set_symmetric_difference(coll.cbegin(),coll.cend(),
                           coll1.cbegin(),coll1.cend(),
                           std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //void
  //inplace_merge(BidirectionalIterator beg1,BidirectionalIterator end1beg2,BidirectionalIterator end2)
  //void
  //inplace_merge(BidirectionalIterator beg1,BidirectionalIterator end1beg2,BidirectionalIterator end2,BinaryPredicate op)
  //两者都是将已排序源区间[beg1,end1beg2)和[end1beg2,end2)的元素合并，使区间[beg1,end2)成为两者之总和（且形成已排序状态）
  //复杂度：若有足够内存则为线性，执行numElems-1次比较，否则为n-log-n，执行numElems*log(numElems)次比较

  coll2.clear();

  //insert two sorted sequences
  INSERT_ELEMENTS(coll2,1,7);
  INSERT_ELEMENTS(coll2,1,8);
  PRINT_ELEMENTS(coll2);

  //find beginning of second part(element after 7)
  std::list<int>::iterator pos14;
  pos14=find(coll2.begin(),coll2.end(),//range
             7);//value
  ++pos14;

  //merge into one sorted range
  inplace_merge(coll2.begin(),pos14,coll2.end());

  PRINT_ELEMENTS(coll2);

  //11.11 数值算法(Numeric Algorithm)
  //11.11.1 运算后产生结果

  //T
  //accumulate(InputIterator beg,InputIterator end, T initValue)
  //T
  //accumulate(InputIterator beg,InputIterator end, T initValue,BinaryFunc op)
  //第一形式计算initValue和区间[beg,end)内每个元素的总和，更具体地说，它针对每一个元素调用以下运算：
  // initValue=initValue+elem
  //第二形式计算initValue和区间[beg,end)内每一个元素进行op运算的结果，更具体地说，它针对每一个元素调用以下表达式：
  // initValue=op(initValue,elem)
  //如果数列为空(beg==end)，两者都返回initValue
  //op不可以改动其所接获的实参
  //复杂度：线性，上述两式分别调用operator+或op()各numElems次

  coll.clear();

  INSERT_ELEMENTS(coll,1,9);
  PRINT_ELEMENTS(coll);

  //process sum of elements
  std::cout<<"sum: "
           <<accumulate(coll.cbegin(),coll.cend(),//range
                        0)//initial value
           <<std::endl;

  //process sum of elements less 100
  std::cout<<"sum: "
           <<accumulate(coll.cbegin(),coll.cend(),//range
                        -100)//initial value
           <<std::endl;

  //process product of elements
  std::cout<<"product: "
           <<accumulate(coll.cbegin(),coll.cend(),//range
                        1,//initial value
                        std::multiplies<int>())//operation
           <<std::endl;

  //process product of elements(use 0 as initial value)
  std::cout<<"product: "
           <<accumulate(coll.cbegin(),coll.cend(),//range
                        0,//initial value
                        std::multiplies<int>())//operation
           <<std::endl;

  //T
  //inner_product(InputIterator1 beg1,InputIterator1 end1,InputIterator2 beg2,T initValue)
  //T
  //inner_product(InputIterator1 beg1,InputIterator1 end1,InputIterator2 beg2,T initValue,BinaryFunc op1,BinaryFunc op2)
  //第一形式计算并返回[beg,end)区间和“以beg2为起始的区间”的对应元素组的内积，并为每次的内积值加上initValue。具体地说，也就是针对“两区间内的每一组对应元素”调用以下表达式：
  // initValue=initValue+elem1*elem2
  //第二形式将[beg,end)区间和“以beg2为起始的区间”内的对应元素组进行op2运算，然后再和initValue进行op1运算，并将结果返回。具体地说，也就是针对“两区间内的每一组对应元素”调用以下表达式：
  // initValue=op1(initValue,op2(elem1,elem2))
  //如果第一区间为空(beg1==end1)，则两者都返回initValue
  //调用者必须确保“以beg2为起始的区间”内含足够的元素空间
  //op1和op2都不可以改动其所接获的实参
  //复杂度：线性，调用operators+和operators*各numElems次，或是调用op1()和op2()各numElems次

  coll2.clear();

  INSERT_ELEMENTS(coll2,1,6);
  PRINT_ELEMENTS(coll2);

  //process sum of all products
  //(0+1*1+2*2+3*3+4*4+5*5+6*6)
  std::cout<<"inner product: "
           <<inner_product(coll2.cbegin(),coll2.cend(),//first range
                           coll2.cbegin(),//second range
                           0)//initial value
           <<std::endl;

  //process sum of 1*6...6*1
  //(0+1*6+2*5+3*4+4*3+5*2+6*1)
  std::cout<<"inner reverse product: "
           <<inner_product(coll2.cbegin(),coll2.cend(),//first range
                           coll2.crbegin(),//second range
                           0)//initial value
           <<std::endl;

  //process product of all sums
  //(1*1+1*2+2*3+3*4+4*5+5*6+6)
  std::cout<<"product of sums: "
           <<inner_product(coll2.cbegin(),coll2.cend(),//first range
                           coll2.cbegin(),//second range
                           1,//initial value
                           std::multiplies<int>(),//outer operation
                           std::plus<int>())//inner operation
           <<std::endl;

  //11.11.2 相对数列和绝对数列之间的转换

  //OutputIterator
  //partial_sum(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg)
  //OutputIterator
  //partial_sum(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,BinaryPredicate op)
  //第一形式计算源区间[sourceBeg,sourceEnd)中每个元素的部分和(partial sum)，然后将结果写入以destBeg为起点的目标区间
  //第二形式将源区间[sourceBeg,sourceEnd)中的每个元素和其先前所有元素进行op运算，并将结果写入以destBeg为起点的目标区间
  //两种形式都返回目标区间内“最后一个被写入的值”的下一位置（也就是第一个未被覆盖的元素的位置）
  //第一形式相当于把一个相对数列转换为一个绝对数列。就此而言，partial_sum()正好和adjacent_difference()互补
  //源区间和目标区间可以完全相同
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //op不应改动传入的实参
  //复杂度：线性，分别调用operator+或op()numElems次

  coll.clear();

  INSERT_ELEMENTS(coll,1,6);
  PRINT_ELEMENTS(coll);

  //print all partial sums
  partial_sum(coll.cbegin(),coll.cend(),//source range
              std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //print all partial products
  partial_sum(coll.cbegin(),coll.cend(),//source range
              std::ostream_iterator<int>(std::cout," "),//destination
              std::multiplies<int>());//operation
  std::cout<<std::endl;

  //OutputIterator
  //adjacent_difference(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg)
  //OutputIterator
  //adjacent_difference(InputIterator sourceBeg,InputIterator sourceEnd,OutputIterator destBeg,BinaryFunc op)
  //第一形式计算[sourceBeg,sourceEnd)区间内每个元素和其紧临的前一元素的差额，并将结果写入以destBeg为起点的目标区间
  //第二形式针对[sourceBeg,sourceEnd)区间内的每个元素和其紧临的前一元素调用op操作，并将结果写入以destBeg为起点的目标区间
  //第一个元素只是被很单纯地复制
  //两个形式都返回目标区间内“最后一个被写入值”的下一位置（也就是第一个未被覆盖的元素的位置）
  //第一形式相当于把一个绝对数列转换为一个相对数列。就此而言，adjacent_difference()正好与partial_sum()互补
  //源区间和目标区间可以完全相同
  //调用者必须确保目标区间有足够空间，要不就得使用insert iterator
  //op不应改动传入的实参
  //复杂度：线性，分别调用operator-或op()共numElems-1次

  coll1.clear();

  INSERT_ELEMENTS(coll1,1,6);
  PRINT_ELEMENTS(coll1);

  //print all differences between elements
  adjacent_difference(coll1.cbegin(),coll1.cend(),//source
                      std::ostream_iterator<int>(std::cout," "));//destination
  std::cout<<std::endl;

  //print all sums with the predecessors
  adjacent_difference(coll1.cbegin(),coll1.cend(),//source
                      std::ostream_iterator<int>(std::cout," "),//destination
                      std::plus<int>());//operation
  std::cout<<std::endl;

  //print all products between elements
  adjacent_difference(coll1.cbegin(),coll1.cend(),//source
                      std::ostream_iterator<int>(std::cout," "),//destination
                      std::multiplies<int>());//operation
  std::cout<<std::endl;

  coll.clear();
  coll={17,-3,22,13,13,-9};
  PRINT_ELEMENTS(coll,"coll:     ");

  //convert into relative values
  adjacent_difference(coll.cbegin(),coll.cend(),//source
                      coll.begin());//destination
  PRINT_ELEMENTS(coll,"relative: ");

  //convert into absolute values
  partial_sum(coll.cbegin(),coll.cend(),//source
              coll.begin());//destination
  PRINT_ELEMENTS(coll,"absolute: ");

  return 0;
}
