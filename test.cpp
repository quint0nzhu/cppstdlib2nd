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







  return 0;
}
