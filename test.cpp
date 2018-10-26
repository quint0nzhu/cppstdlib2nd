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
#include <forward_list>
#include <map>


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

void printLists(const std::list<int>& l1, const std::list<int>& l2)
{
  std::cout << "list1: ";
  copy(l1.cbegin(),l1.cend(),std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl << "list2: ";
  copy(l2.cbegin(),l2.cend(),std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl << std::endl;
}

void printLists(const std::string& s, const std::forward_list<int>& l1,
                const std::forward_list<int>& l2)
{
  std::cout<<s<<std::endl;
  std::cout<<"list1: ";
  copy(l1.cbegin(),l1.cend(),std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl<<"list2: ";
  copy(l2.cbegin(),l2.cend(),std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;
}

template<typename InputIterator, typename Tp>
inline InputIterator
find_before(InputIterator first, InputIterator last, const Tp& val)
{
  if(first == last){
    return first;
  }
  InputIterator next(first);
  ++next;
  while(next!=last && !(*next == val)){
    ++next;
    ++first;
  }
  return first;
}

template<typename InputIterator, typename Pred>
inline InputIterator
find_before_if(InputIterator first, InputIterator last, Pred pred)
{
  if(first == last){
    return first;
  }
  InputIterator next(first);
  ++next;
  while(next!=last && !pred(*next)){
    ++next;
    ++first;
  }
  return first;
}

class RuntimeCmp{
public:
  enum cmp_mode{normal,reverse};
private:
  cmp_mode mode;
public:
  //constructor for sorting criterion
  //-default criterion uses value normal
  RuntimeCmp (cmp_mode m=normal):mode(m){}

  //comparison of elements
  //-member function for any element type
  template<typename T>
  bool operator()(const T& t1, const T& t2)const{
    return mode==normal?t1<t2:t2<t1;
  }

  //comparison of sorting criteria
  bool operator==(const RuntimeCmp& rc)const{
    return mode==rc.mode;
  }
};

//type of a set that uses this sorting criterion
typedef std::set<int,RuntimeCmp> IntSet;


namespace MyLib{
  template<typename Cont>
  inline
  bool replace_key(Cont& c,
                    const typename Cont::key_type& old_key,
                    const typename Cont::key_type& new_key)
  {
    typename Cont::iterator pos;
    pos = c.find(old_key);
    if(pos != c.end()){
      //insert new element with value of old element
      c.insert(typename Cont::value_type(new_key,pos->second));

      //remove old element
      c.erase(pos);
      return true;
    }
    else{
      //key not found
      return false;
    }
  }
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
  //7.4.1 Deque的能力
  //7.4.2 Deque的操作函数
  //7.4.3 Exception Handling
  //7.4.4 Deque运用实例

  //create empty deque of strings
  std::deque<std::string> coll7;

  //insert serveral elements
  coll7.assign(3,std::string("string"));
  coll7.push_back("last string");
  coll7.push_front("first string");

  //print elements separated by newlines
  copy(coll7.cbegin(),coll7.cend(),
       std::ostream_iterator<std::string>(std::cout, "\n"));
  std::cout << std::endl;

  //remove first and last element
  coll7.pop_front();
  coll7.pop_back();

  //insert "another" into every element but the first
  for(unsigned i = 1; i < coll7.size(); ++i){
    coll7[i] = "another" + coll7[i];
  }

  //change size to four elements
  coll7.resize(4,"resized string");

  //print elements separated by newlines
  copy(coll7.cbegin(),coll7.cend(),
       std::ostream_iterator<std::string>(std::cout,"\n"));

  //7.5 List
  //7.5.1 List的能力
  //7.5.2 List的操作

  std::list<int> coll8; //empty!
  //std::cout << coll8.front(); //RUNTIME ERROR => undefined behavior

  if(!coll8.empty()){
    std::cout << coll8.back(); //OK
  }

  std::list<int> coll9={1,3,3,4};

  //remove all elements with value val
  coll9.remove(3);
  copy(coll9.cbegin(),coll9.cend(),
       std::ostream_iterator<int>(std::cout,"\n"));

  //remove all even elements
  coll9.remove_if([](int i){
      return i % 2 == 0;
    });
  PRINT_ELEMENTS(coll9);

  //7.5.3 异常处理(Exception Handling)
  //7.5.4 List运用实例

  //create two empty lists
  std::list<int> list1, list2;

  //fill both lists with elements
  for(int i = 0; i < 6; ++i){
    list1.push_back(i);
    list2.push_front(i);
  }
  printLists(list1, list2);

  //insert all elements of list1 before the first element with value 3 of list2
  //- find() returns an iterator to the first element with value 3
  list2.splice(find(list2.begin(),list2.end(),//destination position
                    3),
               list1);//source list
  printLists(list1,list2);

  //move first element of list2 to the end
  list2.splice(list2.end(),//destination position
               list2,//source list
               list2.begin());//source position
  printLists(list1,list2);

  //sort second list, assign to list1 and remove duplicates
  list2.sort();
  list1=list2;
  list2.unique();
  printLists(list1,list2);

  //merge both sorted lists into the first list
  list1.merge(list2);
  printLists(list1,list2);

  //7.6 Forward List
  //7.6.1 Forward List的能力
  //7.6.2 Forward List的操作
  std::forward_list<int> l3={1,2,3,4};

  std::cout<<"l3.size(): " << std::distance(l3.begin(),l3.end()) << std::endl;
  std::cout<<l3.max_size()<<std::endl;

  std::forward_list<int> fwlist={1,2,3};

  //insert 77, 88, and 99 at the beginning:
  fwlist.insert_after(fwlist.before_begin(),//position
                      {77,88,99});//values
  copy(fwlist.cbegin(),fwlist.cend(),
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;
  //RUNTIME ERROR: appending element after end is undefined behavior
  //fwlist.insert_after(fwlist.end(),9999);

  std::forward_list<int> list={1,2,3,4,5,97,98,99};

  //find the position before the first even element
  auto posBefore=list.before_begin();
  for(auto pos=list.begin();pos!=list.end();++pos,++posBefore){
    if(*pos % 2 == 0){
      break;//element found
    }
  }

  //and insert a new element in front of the first even element
  list.insert_after(posBefore,41);
  PRINT_ELEMENTS(list);

  posBefore=list.before_begin();
  for(;std::next(posBefore)!=list.end();++posBefore){
    if(*std::next(posBefore) % 2 == 0){
      break;//element found
    }
  }

  list.insert_after(posBefore,43);
  PRINT_ELEMENTS(list);

  //find the position before the first even element
  auto posBefore1 = find_before_if(list.before_begin(),list.end(),
                                   [](int i){
                                     return i%5 == 0;
                                   });

  //and insert a new element in front of it
  list.insert_after(posBefore1,44);
  PRINT_ELEMENTS(list);

  std::forward_list<int> l4={1,2,3,4,5};
  std::forward_list<int> l5={97,98,99};

  //find 3 in l4
  auto pos1=l4.before_begin();
  for(auto pb1=l4.begin();pb1!=l4.end();++pb1,++pos1){
    if(*pb1==3){
      break;//found
    }
  }

  //find 99 in l5
  auto pos2=l5.before_begin();
  for(auto pb2=l5.begin();pb2!=l5.end();++pb2,++pos2){
    if(*pb2==99){
      break;//found
    }
  }

  //splice 3 from l4 to l5 before 99
  l5.splice_after(pos2,l4,//destination
                  pos1);//source

  PRINT_ELEMENTS(l4);
  PRINT_ELEMENTS(l5);

  l5.splice_after(find_before(l5.before_begin(),l5.end(),99),l4,//destination
                  find_before(l4.before_begin(),l4.end(),5));//source

  PRINT_ELEMENTS(l4);
  PRINT_ELEMENTS(l5);

  //RUNTIME ERROR: move first element to the end is not possible that way
  //fwlist.splice_after(fwlist.end(),//destination position
  //                   fwlist,//source list
  //                   fwlist.begin());//source position

  //7.6.3 异常处理(Exception Handling)
  //7.6.4 Forward List运用实例

  //create two forward lists
  std::forward_list<int> list3={1,2,3,4};
  std::forward_list<int> list4={77,88,99};
  printLists("initial: ",list3,list4);

  //insert six new element at the beginning of list4
  list4.insert_after(list4.before_begin(),99);
  list4.push_front(10);
  list4.insert_after(list4.before_begin(),{10,11,12,13});
  printLists("6 new elems: ",list3,list4);

  //insert all elements of list4 at the beginning of list3
  list3.insert_after(list3.before_begin(),list4.begin(),list4.end());
  printLists("list4 into list3: ",list3,list4);

  //delete second element and elements after element with value 99
  list4.erase_after(list4.begin());
  list4.erase_after(find(list4.begin(),list4.end(),99),list4.end());
  printLists("delete 2nd and after 99: ",list3,list4);

  //sort list3, assign it to list4, and remove duplicates
  list3.sort();
  list4=list3;
  list4.unique();
  printLists("sorted and unique: ",list3,list4);

  //merge both sorted lists into list3
  list3.merge(list4);
  printLists("merged: ",list3,list4);

  //7.7 Set和Multiset
  //7.7.1 Set和Multiset的能力
  //7.7.2 Set和Multiset的操作函数

  std::set<int> c6;

  c6.insert(1);
  c6.insert(2);
  c6.insert(4);
  c6.insert(5);
  c6.insert(6);

  std::cout<<"lower_bound(3): "<<*c6.lower_bound(3)<<std::endl;
  std::cout<<"upper_bound(3): "<<*c6.upper_bound(3)<<std::endl;
  std::cout<<"equal_range(3): "<<*c6.equal_range(3).first<<" "
           <<*c6.equal_range(3).second<<std::endl;
  std::cout<<std::endl;
  std::cout<<"lower_bound(5): "<<*c6.lower_bound(5)<<std::endl;
  std::cout<<"upper_bound(5): "<<*c6.upper_bound(5)<<std::endl;
  std::cout<<"equal_range(5): "<<*c6.equal_range(5).first<<" "
           <<*c6.equal_range(5).second<<std::endl;

  std::set<double> c7;

  c7.insert(1.1);
  c7.insert(2.2);
  c7.insert(3.3);
  c7.insert(4.4);

  if(c7.insert(3.3).second){
    std::cout<<"3.3 inserted"<<std::endl;
  }
  else{
    std::cout<<"3.3 already exists"<<std::endl;
  }

  //insert value and process return value
  double value = 4.4;
  auto status=c7.insert(value);
  if(status.second){
    std::cout<< value <<" inserted as element ";
  }
  else{
    std::cout<< value <<" already exists as element ";
  }
  std::cout<<std::distance(c7.begin(),status.first)+1<<std::endl;

  std::set<int> coll10;
  coll10.insert(1);
  coll10.insert(3);
  coll10.insert(5);

  //remove all elements with passed value
  std::cout<<coll10.erase(4)<<std::endl;
  PRINT_ELEMENTS(coll10);

  std::multiset<int> coll11={1,2,3,3,3,4,5,4,2};
  PRINT_ELEMENTS(coll11);

  //remove first element with passed value
  std::multiset<int>::iterator pos3;
  pos3=coll11.find(4);//this find() fast
  if(pos3!=coll11.end()){
    coll11.erase(pos3);
  }
  std::cout<<coll11.erase(3)<<std::endl;
  PRINT_ELEMENTS(coll11);

  //7.7.3 异常处理(Exception Handling)
  //7.7.4 Set和Multiset运用实例

  //type of the collection:
  //-no duplicates
  //-elements are integral values
  //-descending order
  std::set<int,std::greater<int>> coll12;

  //insert elements in random order using different member functions
  coll12.insert({4,3,5,1,6,2});
  coll12.insert(5);

  //print all elements
  for(int elem : coll12){
    std::cout<<elem<<' ';
  }
  std::cout<<std::endl;

  //insert 4 again and process return value
  auto status1=coll12.insert(4);
  if(status1.second){
    std::cout<<"4 inserted as element "<<std::distance(coll12.begin(),status1.first)+1<<std::endl;
  }
  else{
    std::cout<<"4 already exists"<<std::endl;
  }

  //assign elements to another set with ascending order
  std::set<int> coll13(coll12.cbegin(),coll12.cend());

  //print all elements of the copy using stream iterators
  copy(coll13.cbegin(),coll13.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout<<std::endl;

  //remove all elements up to element with value 3
  coll13.erase(coll13.begin(),coll13.find(3));

  //remove all elements with value 5
  int num;
  num = coll13.erase(5);
  std::cout<<num<<" element(s) removed"<<std::endl;

  //print all elements
  copy(coll13.cbegin(),coll13.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout<<std::endl;

  //type of the collection:
  //-can duplicates
  //-elements are integral value
  //-descending order
  std::multiset<int,std::greater<int>> coll14;

  //insert elements in random order using different member functions
  coll14.insert({4,3,5,1,6,2});
  coll14.insert(5);

  //print all elements
  for(int elem : coll14){
    std::cout<<elem<<' ';
  }
  std::cout << std::endl;

  //insert 4 again and process return value
  auto ipos=coll14.insert(4);
  std::cout<<"4 inserted as element "<<std::distance(coll14.begin(),ipos)+1<<std::endl;

  //assign elements to another multiset with ascending order
  std::multiset<int> coll15(coll14.cbegin(),coll14.cend());

  //print all elements of the copy using stream iterators
  copy(coll15.cbegin(),coll15.cend(),
       std::ostream_iterator<int>(std::cout," "));
  std::cout<<std::endl;

  //remove all elements up to element with value 3
  coll15.erase(coll15.begin(),coll15.find(3));

  //remove all elements with value 5
  std::cout << coll15.erase(5)<<" element(s) removed"<<std::endl;

  //print all elements
  PRINT_ELEMENTS(coll15);

  //7.7.5 运行期指定排序准则

  //create, fill, and print set with normal element order
  //-uses default sorting criterion
  IntSet coll16={4,7,5,1,6,2,5};
  PRINT_ELEMENTS(coll16);

  //create sorting criterion with reverse element order
  RuntimeCmp reverse_order(RuntimeCmp::reverse);

  //create, fill, and print set with reverse element order
  IntSet coll17(reverse_order);
  coll17={4,7,5,1,6,2,5};
  PRINT_ELEMENTS(coll17);

  //assign elements AND sorting criterion
  coll16=coll17;
  coll16.insert(3);
  PRINT_ELEMENTS(coll16);

  //just to make sure...
  if(coll16.value_comp()==coll17.value_comp()){
    std::cout<<"coll16 and coll17 have the same sorting criterion"<<std::endl;
  }
  else{
    std::cout<<"coll16 and coll17 hava a different sorting criterion"<<std::endl;
  }

  //7.8 Map和Multimap
  //7.8.1 Map和Multimap的能力
  //7.8.2 Map和Multimap的操作函数
  typedef std::map<std::string,float,std::greater<std::string>> StringFloatMap;
  StringFloatMap coll18;

  std::map<float,std::string> c8;//sorting criterion: less<>
  std::map<float,std::string,std::greater<float>> c9;
  //std::cout<<(c8==c9)<<std::endl;//ERROR: different types

  std::multimap<std::string,float> coll19={{"abc",1.1},{"def",2.2},{"ghi",3.3},{"def",4.4}};
  //do something with all elements having a certain value
  std::multimap<std::string,float>::iterator pos4;
  for(pos4=coll19.begin();pos4!=coll19.end();++pos4){
    if(pos4->second <= 5.5){//float can not use ==
      std::cout<<"key: "<<pos4->first<<"\t\t\t"
               <<"value: "<<pos4->second<<std::endl;
    }
  }

  for(auto& elem : coll19){
    std::cout<<"key: "<<elem.first<<"\t"
             <<"value: "<<elem.second<<std::endl;
    elem.second+=5.5;//OK
  }

  //elem.first="hello";//ERROR at compile time
  //pos4->first="hello";//ERROR at compile time
  pos4=coll19.begin();
  pos4->second=13.5;//OK

  for(auto& elem : coll19){
    std::cout<<"key: "<<elem.first<<"\t"
             <<"value: "<<elem.second<<std::endl;
  }

  //add 10 to the value of each element:
  std::for_each(coll19.begin(),coll19.end(),
                [](std::pair<const std::string,float>& elem){
                  elem.second+=10;
                });
  for(auto& elem :coll19){
    std::cout<<"key: "<<elem.first<<"\t"
             <<"value: "<<elem.second<<std::endl;
  }


































  return 0;
}
