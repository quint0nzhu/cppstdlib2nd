/*
  author: Quinton
  date: 2018-7-24
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter7
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>
#include <deque>
#include <set>
#include <iterator>
#include <array>
#include <algorithm>
#include <cstring> //strcpy()
#include <typeinfo> //typeid()
#include <functional>
#include <numeric>


template<typename T>
void PRINT_ELEMENTS(const T& coll)
{
  for(const auto& elem : coll)
    std::cout << elem << " ";
  std::cout << std::endl;
}

template<typename T>
void shrinkCapacity(std::vector<T>& v)
{
  std::vector<T> tmp(v);//copy elements into a new vector
  v.swap(tmp);//swap internal vector data
}

int main()
{
  //7 STL容器
  //7.1容器的共通能力和共通操作
  //7.1.1容器的共通能力
  //所有容器提供的都是value语义而非reference语义
  //7.1.2容器的共通操作
  //初始化最好统一用{}

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

  std::list<int> l={1,2,3,4,5,6};//l is a linked list of ints

  //copy all elements of the list as floats into a vector
  std::vector<float> c(l.begin(),l.end());

  for(const auto& elem : c){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  std::list<std::string> l1{"hello","world","!"};//l1 is a linked list of strings
  //move all elements of the list into a vector
  std::vector<std::string> c1(std::make_move_iterator(l1.begin()),
                              std::make_move_iterator(l1.end()));

  std::cout << "print moved elements in vector:  " << std::endl;
  for(const auto& elem : c1){
    std::cout << elem << std::endl;
  }


  std::cout << "print origin elements in list:" << std::endl;
  for(const auto& elem : l1){
    std::cout << "elements in list is null" << std::endl;
    std::cout << elem << std::endl;
  }

  int carray[] = {2,3,17,33,45,77};

  //copy all elements of the C-style array into a set
  std::set<int> c2(std::begin(carray),std::end(carray));
  //std::set<int> c2(carray,carray+sizeof(carray)/sizeof(carray[0]));//C++98

  for(const auto& elem : c2){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //read all integer elements of the deque from standard input
  //std::deque<int> c3{std::istream_iterator<int>(std::cin),
  //    std::istream_iterator<int>()};
  std::deque<int> c3((std::istream_iterator<int>(std::cin)),
                     (std::istream_iterator<int>()));

  for(const auto& elem : c3){
    std::cout << elem << std::endl;
  }

  std::vector<int> v3{1,3,5,7,9};

  //move contents of v3 to v4, state of v3 undefined afterward
  std::vector<int> v4=std::move(v3);
  //如果赋值后右侧的内容不再被使用，都建议用上面这种赋值方法
  for(const auto& elem : v4){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  for(const auto& elem : v3){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //尽量用empty(）

  std::cout << v4.size() << " " << v4.max_size() << std::endl;
  //两个容器的所有元素依序相等，那么这两个容器相等
  //cbegin(),cend()只读，begin(),end()可读可写，这些函数与auto配合使用
  //colltype::const_iterator pos;//C++98用法，只读
  //colltype::iterator pos;//C++98用法，可读可写
  //删除元素后vector和deque的迭代器或指向元素的reference可能失效
  //clear()移除所有元素后，对vector,deque,string而言，由end()或cend()返回的逾尾迭代器都可能失效
  //插入元素后，list,forward_list和关联式容器保证原本的迭代器和指向元素的reference继续保持有效，当插入vector且不超出容量时，以上结果也适用于vector，对于无序(unordered)容器，上述保证对于reference一般是成立的，但对于迭代器则只有当不发生rehashing才成立，只要插入后的最终元素总数小于bucket个数乘以最大负载系数，就不会发生rehashing

  //7.1.3容器提供的类型
  //pointer和const_pointer是C++11的新引入的

  //7.2 Array
  //7.2.1 Array的能力
  //Array 初始化基础类型时，初值可能不明确
  std::array<int,4> x;//OOPS: elements of x have undefined value
  std::array<int,4> x1={};//OK: all elements of x have value 0 (int())
  std::array<int,5> coll={42,377,611,21,44};
  std::array<int,10> c4={42};//one element with value 42 followed by 9 elements with value 0
  //std::array<int,5> c5={1,2,3,4,5,6};//ERROR: too many values
  std::array<int,5> a({1,2,3,4,5});//ERROR? but it's OK
  std::vector<int> v5({1,2,3,4,5});//OK
  std::array<std::string, 3> as1, as2;
  std::string* pas1, *pas2;
  as1[0]="hello";
  as1[1]="world";
  pas1=&as1[1];
  as1[2]="!";
  as2[0]="fuck";
  as2[1]="you";
  pas2=&as2[1];
  as2[2]="!";
  std::cout<<*pas1<<std::endl;
  std::cout<<*pas2<<std::endl;
  std::swap(as1,as2);//array的交换结果，使得原指针指向的值发生了变化，这一点和其它容器不同
  std::cout<<*pas1<<std::endl;
  std::cout<<*pas2<<std::endl;
  for(auto & elem : as1)
    std::cout << elem << ' ';
  std::cout<<std::endl;
  for(auto & elem : as2)
    std::cout << elem << ' ';
  std::cout <<std::endl;

  std::array<int,0> coll1;//array with no elements
  std::sort(coll1.begin(),coll1.end());//OK (but has no effect)
  //coll1[5]=10;//RUNTIME ERROR => undefined behavior
  //std::cout<<coll1.front(); //RUNTIME ERROR => undefined behavior

  //7.2.2 Array的操作
  std::array<int,5> a1({1,2,3,4,5});//ERROR? but it's OK
  std::cout << a1.max_size() <<std::endl;
  std::array<int,4> coll2{0}; //only four elements!

  //coll2[5]=100;//RUNTIME ERROR => undefined behavior
  std::cout << coll2.front()<<std::endl;//OK(coll2 has 4 element after construction)
  std::array<int,0> coll3;//always empty
  //std::cout << coll3.front();//RUNTIME ERROR => undefined behavior
  if(coll2.size() > 5){
    coll2[5]=12;//OK
  }
  try{
    coll2.at(5)=12;//throws out_of_range exception
  }
  catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }
  //7.2.3把array当成C-Style Array
  std::array<char,41> a2;//create static array of 41 chars

  strcpy(&a2[0],"hello, world");//copy a C-string into array
  printf("%s\n",&a2[0]);
  strcpy(a2.data(),"hello, fucking world");
  printf("%s\n",a2.data());
  //printf("%s\n",a2.begin());//ERROR(might work, but not protable)

  //7.2.4异常处理(Exception Handling)
  //swap()有可能抛出异常，因为它执行的是“元素逐次”的置换动作

  //7.2.5 Tuple接口
  typedef std::array<std::string, 5> FiveStrings;

  FiveStrings a3={"hello","nico","how","are","you"};

  std::cout<<std::tuple_size<FiveStrings>::value<<std::endl; //yields 5
  std::cout<<typeid(std::tuple_element<1,FiveStrings>::type).name()<<std::endl;//yields std::string
  std::cout<<std::get<1>(a3)<<std::endl;//yields std::string("nico")

  //7.2.6 Array运用实例

  //create array with 10 ints
  std::array<int,10> a4={11,22,33,44};

  PRINT_ELEMENTS(a4);

  //modify last two elements
  a4.back()=9999999;
  a4[a4.size()-2]=42;
  PRINT_ELEMENTS(a4);

  //process sum of all elements
  std::cout<<"sum: "<< std::accumulate(a4.begin(),a4.end(),0)<<std::endl;

  //negate all elements
  std::transform(a4.begin(),a4.end(),//source
            a4.begin(),//destination
                 std::negate<int>());
  PRINT_ELEMENTS(a4);

  //7.3 Vector
  //7.3.1 Vector的能力
  //1.一旦vector重新分配内存，vector元素相关的所有reference,pointer,iterator都会失效
  //2.内存重新分配很耗时间

  std::vector<int> v6;//create an empty vector

  v6.reserve(80);//reserve memory for 80 elements
  v6.push_back(323);
  std::cout<<v6.size()<<std::endl;
  std::cout<<v6.capacity()<<std::endl;
  std::cout<<v6.max_size()<<std::endl;
  //std::vector<T> v7(5);//creates a vector and initializes it with five values
  //(calls five times the default constructor of type T)
  //如果想保留足够的内存，还是用reserve()

  //reserve()不能缩减容量，调用了不会引发任何效果
  //既然vector的容量不会缩减，所以删除元素不会使reference,pointer和iterator不会失效，继续指向动作发生前的位置
  //插入元素有可能使reference,pointer和iterator失效，因为插入可能导致vector重新分配内存

  v6.shrink_to_fit();//request to shrink memory(since C++11)
  //但是调用shrink_to_fit()之后并不能保证v6.capacity==v6.size()获得true
  //也会让指向元素的reference,point和iterator失效

  //shrink capacity of vector v for type T
  //std::vector<T>(v).swap(v);
  //7.3.2 Vector的操作
  std::list<int> l2;
  std::vector<int> coll4;

  l2={1,2,3,4,5};
  //make coll4 be a copy of the contents of l1
  coll4.assign(l2.begin(),l2.end());
  PRINT_ELEMENTS(coll4);

  std::vector<int> coll5;//empty!

  //coll5[5]=23;//RUNTIME ERROR => undefined behavior
  //std::cout << coll5.front(); //RUNTIME ERROR => undefined behavior

  if(coll5.size()>5){
    coll5[5]=11;//OK
  }
  if(!coll5.empty()){
    std::cout<<coll5.front();//OK
  }
  /*try{
    coll5.at(5)=23; //throws out_of_range exception 
  }
  catch(std::exception* e){
    std::cout << e->what() << std::endl;
  }*/
  //vector迭代器持续有效，除非发生两种情况：
  //1.在一个较小索引位置上安插或移动元素
  //2.由于容量变化而引起内存重新分配

  //Inserting and Removing时迭代器必须指向一个合法位置，且区间起始位置不能在结束位置之后

  std::vector<int> coll6; //empty!

  coll6.pop_back();//RUNTIME ERROR => undefined behavior
  if(!coll6.empty()){
    coll6.pop_back();//OK
  }

  coll6={2,4,6,4,10};

  //remove all elements with value val
  coll6.erase(std::remove(coll6.begin(),coll6.end(),4),coll6.end());

  PRINT_ELEMENTS(coll6);

  //remove first element with value val
  std::vector<int>::iterator pos;
  pos = std::find(coll6.begin(),coll6.end(),6);
  if(pos!=coll6.end()){
    coll6.erase(pos);
  }
  PRINT_ELEMENTS(coll6);

  //7.3.3将Vector当作C-Style Array使用
  std::cout << (&coll6[1] == &coll6[0] + 1) << std::endl;

  std::vector<char> v7; //create vector as dynamic array of chars

  v7.resize(41);//make room for 41 characters(including '\0')
  strcpy(&v7[0],"hello, word");//copy a C-string into the vector
  printf("%s\n",&v7[0]);//print contents of the vector as C-string
  std::cout << v7.size() <<std::endl;


  std::vector<char> v8(45);//create static array of 45 chars

  strcpy(v8.data(),"hello, the fucking word");
  printf("%s\n",v8.data());
  std::cout << v8.size() <<std::endl;

  printf("%s\n",v8.begin());//ERROR (might work, but not portable)
  printf("%s\n",v8.data());//OK(since C++11)
  printf("%s\n",&v8[0]);//OK, but data() is better

  //7.3.4 异常处理(Exception Handling)
  //7.3.5 Vector使用实例

  //create empty vector for strings
  std::vector<std::string> sentence;

  //reserve memory for five elements to avoid reallocation
  sentence.reserve(5);

  //append some elements
  sentence.push_back("Hello,");
  sentence.insert(sentence.end(),{"how","are","you","?"});

  //print elements separated with spaces
  copy(sentence.cbegin(),sentence.cend(),std::ostream_iterator<std::string>(std::cout," "));
  std::cout << std::endl;

  //print "technical data"
  std::cout << " max_size(): " << sentence.max_size() << std::endl;
  std::cout << " size(): " << sentence.size() << std::endl;
  std::cout << " capacity(): " << sentence.capacity() << std::endl;

  //swap second and fourth element
  swap(sentence[1], sentence[3]);

  //insert element "always" before element "?"
  sentence.insert(find(sentence.begin(),sentence.end(),"?"),
                  "always");

  //assign "!" to the last element
  sentence.back() = "!";

  //print elements sparated with spaces
  copy(sentence.cbegin(),sentence.cend(),
       std::ostream_iterator<std::string>(std::cout," "));
  std::cout << std::endl;

  //print some "technical data" again
  std::cout << " size(): " << sentence.size() << std::endl;
  std::cout << " capacity(): " << sentence.capacity() << std::endl;

  //delete last two elements
  sentence.pop_back();
  sentence.pop_back();

  //shrink capacity (since C++11)
  sentence.shrink_to_fit();

  //print some "technical data" again
  std::cout << " size(): " << sentence.size() << std::endl;
  std::cout << " capacity(): " << sentence.capacity() << std::endl;

  //7.3.6 Class vector<bool>
  std::vector<bool> c5={true,false,true,false,true,false,true,false,true,false};
  PRINT_ELEMENTS(c5);
  c5.front().flip();//negate first Boolean element
  c5[5]=c5.back();//assign last element to element with index 5;
  PRINT_ELEMENTS(c5);

  //7.4 Deque
  

































  return 0;
}
