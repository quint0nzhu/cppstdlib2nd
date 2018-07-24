/*
  author: Quinton
  date: 2018-7-6
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter6
*/

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <set>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <cstdlib> //for abs()
#include <functional>



template<typename T>
void printElements(const T& coll)
{
  for(const auto& elem : coll){
    std::cout << elem << std::endl;
  }
}

//PRINT_ELEMENTS()
//-prints optional string optstr followed by
//-all elements of the collection coll
//-in one line, separated by spaces

template<typename T>
inline void PRINT_ELEMENTS(const T& coll,
                           const std::string& optstr="")
{
  std::cout << optstr;
  for(const auto& elem : coll){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
}

//function that prints the passed argument
void print(int elem)
{
  std::cout << elem << ' ';
}

int square(int value)
{
  return value*value;
}

//predicate, which returns whether an integer is a prime number
bool isPrime(int number)
{
  //ignore negative sign
  number = abs(number);

  //0 and 1 are no prime numbers
  if(number == 0 || number == 1){
    return false;
  }

  //find divisor that divides without a remainder
  int divisor;
  for(divisor = number/2; number%divisor != 0; --divisor){
    ;
  }

  //if no divisor greater than 1 is found, it is a prime number
  return divisor == 1;
}

class Person{
public:
  Person():_firstname(""),_lastname(""){}
  Person(std::string fn,std::string ln)
  {
    _firstname = fn;
    _lastname = ln;
  }

public:
  std::string firstname()const{return _firstname;}
  std::string lastname()const{return _lastname;}

private:
  std::string _firstname;
  std::string _lastname;
};

//binary function predicate:
//-returns whether a person is less than another person
bool personSortCriterion(const Person& p1, const Person& p2)
{
  //a person is less than another person
  //-if the last name is less
  //-if the last name is equal and the first name is less
  return p1.lastname() < p2.lastname() ||
                         (p1.lastname() == p2.lastname() &&
                          p1.firstname() < p2.firstname());
}

class PrintInt{
public:
  void operator()(int elem)const {
    std::cout << elem << ' ';
  }
};

//function object that adds the value with which it is initialized
class AddValue{
private:
  int theValue;//the value to add
public:
  //constructor initializes the value to add
  AddValue(int v):theValue(v){}

  //the "function call" for the element adds the value
  void operator()(int& elem)const{
    elem += theValue;
  }
};







int main()
{
  //6标准模板库
  //6.1 STL组件(Component)
  //6.2 容器(Container)
  //6.2.1序列式容器(Sequence Container)
  std::vector<int> coll; //vector container for integer elements

  //append elements with values 1 to 6
  for(int i = 1; i <= 6; ++i){
    coll.push_back(i);
  }

  //print all elements followed by a space
  for(int i = 0; i < coll.size(); ++i){
    std::cout << coll[i] << ' ';
  }
  std::cout << std::endl;

  std::deque<float> coll1;//deque container for floating-point elements

  //insert elements from 1.1 to 6.6 each at the front
  for(int i = 1; i <= 6; ++i){
    coll1.push_front(i*1.1);//insert at the front
  }

  //print all elements followed by a space
  for(int i = 0; i < coll1.size(); ++i){
    std::cout << coll1[i] << ' ';
  }
  std::cout << std::endl;

  //array container of 5 string elements:
  std::array<std::string,5> coll2={"hello","world"};

  //print each element with its index on a line
  for(int i = 0; i < coll2.size(); ++i) {
    std::cout << i << ": " << coll2[i]<<std::endl;
  }

  std::list<char> coll3; // list container for character elements

  //append elements from 'a' to 'z'
  for(char c = 'a'; c <= 'z'; ++c){
    coll3.push_back(c);
  }

  //print all elements:
  //-use range-based for loop
  for(auto elem : coll3){
    std::cout << elem << ' ';
  }
  std::cout<<std::endl;

  std::list<char> coll4; //list container for character elements

  //append elements from 'a' to 'z'
  for(char c = 'a'; c <= 'z'; ++c){
    coll4.push_back(c);
  }

  //print all elements
  //- while there are elements
  //- print and remove the first element
  while(!coll4.empty()){
    std::cout << coll4.front() <<' ';
    coll4.pop_front();
  }
  std::cout<<std::endl;

  //create forward-list container for some prime numbers
  std::forward_list<long> coll5={2,3,5,7,11,13,17};

  //resize two times
  //-note: poor performance
  coll5.resize(9);
  coll5.resize(10, 99);

  //print all elements:
  for(auto elem : coll5){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //6.2.2关联式容器(Associative Container)

  std::multiset<std::string> cities{
    "Braunschweig","Hanover","Frankfurt","New York",
      "Chicago","Toronto","Paris","Frankfurt"
      };
  //print each element:
  for(const auto& elem : cities){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  //insert additional values:
  cities.insert({"London","Munich","Hanover","Braunschweig"});

  //print each element:
  for(const auto& elem : cities){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::multimap<int,std::string> coll6;//container for int/string values

  //insert some elements in arbitrary order
  //- a value with key 1 gets inserted twice

  coll6 = {{5,"tagged"},
           {2,"a"},
           {1,"this"},
           {4,"of"},
           {6,"strings"},
           {1,"is"},
           {3,"multimap"}};

  //print all element values
  //- element member second is the value
  for(auto elem : coll6){
    std::cout << elem.second << ' ';
  }
  std::cout << std::endl;

  //6.2.3无序容器(Unordered Container)

  std::unordered_multiset<std::string> cities1{
    "Braunschweig","Hanover","Frankfurt","New York",
      "Chicago","Toronto","Paris","Frankfurt"
      };

  //print each element:
  for(const auto& elem : cities1){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  //insert additional values:
  cities1.insert({"London","Munich","Hanover","Braunschweig"});

  //print each element:
  for(const auto& elem : cities1){
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::unordered_map<std::string,double> coll7{
    {"time",9.9},
      {"struppi",11.77}
  };

  //square the value of each element:
  for(std::pair<const std::string,double>& elem : coll7){
    elem.second *= elem.second;
  }

  //print each element (key and value):
  for(const auto& elem : coll7){
    std::cout << elem.first << ": " << elem.second << std::endl;
  }

  //6.2.4关联式数组(Associative Array)

  //type of the container:
  //-unordered_map: elements are key/value pairs
  //-string: keys have type string
  //-float: values have type float

  std::unordered_map<std::string,float> coll8;

  //insert some elements into the collection
  //-using the syntax of an associative array
  coll8["VAT1"]=0.16;
  coll8["VAT2"]=0.07;
  coll8["Pi"]=3.1415;
  coll8["an arbitrary number"]=4983.223;
  coll8["Null"]=0;

  //change value
  coll8["VAT1"]+=0.03;

  //print difference of VAT values
  std::cout << "VAT difference: " << coll8["VAT1"] - coll8["VAT2"] << std::endl;

  //6.2.5其他容器
  //6.2.6容器适配器(Container Adapter)
  //6.3迭代器(Iterator)

  std::list<char> coll9;//list container for character elements

  //append elements from 'a' to 'z'
  for(char c = 'a'; c <= 'z'; ++c){
    coll9.push_back(c);
  }

  //print all elements:
  //-iterator over all elements
  std::list<char>::const_iterator pos;
  for(pos = coll9.begin(); pos != coll9.end(); ++pos){
    std::cout << *pos << ' ';
  }
  std::cout << std::endl;

  //6.3.1关联式(Associative)及无序(Unordered)容器的更多实例

  //type of the collection
  typedef std::set<int> IntSet;

  IntSet coll10;//set container for int values

  //insert elements from 1 to 6 in arbitrary order
  //- note that there are two calls of insert() with value 1

  /*coll10.insert(3);
  coll10.insert(1);
  coll10.insert(5);
  coll10.insert(4);
  coll10.insert(1);
  coll10.insert(6);
  coll10.insert(2);*/

  coll10.insert({3,1,5,4,1,6,2,7});

  //print all elements
  //- iterate over all elements
  IntSet::const_iterator pos1;
  for(pos1 = coll10.begin(); pos1 != coll10.end(); ++pos1){
    std::cout << *pos1 << ' ';
  }
  std::cout << std::endl;

  //unordered multiset container for int values
  std::unordered_set<int> coll11;

  //insert some elements
  coll11.insert({1,3,5,7,11,13,17,19,23,27,1});

  //print all elements
  for(auto elem : coll11){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //insert one more element
  coll11.insert(25);

  //print all elements again
  for(auto elem : coll11){
    std::cout << elem  << ' ';
  }
  std::cout << std::endl;

  //6.3.2迭代器种类(Iterator Category)
  //6.4算法(Algorithm)

  //create vector with elements from 1 to 6 in arbitrary order
  std::vector<int> coll12 = {2,5,4,1,6,3};

  //find and print minimum and maximum elements
  auto minpos = min_element(coll12.cbegin(),coll12.cend());
  std::cout << "min: " << *minpos << std::endl;
  auto maxpos = max_element(coll12.cbegin(),coll12.cend());
  std::cout << "max: " << *maxpos << std::endl;

  //sort all elements
  sort(coll12.begin(),coll12.end());

  //find the first element with value 3
  //-no cbegin()/cend() because later we modify the elements pos3 refers to
  auto pos3 = find(coll12.begin(),coll12.end(),//range
                   3);//value

  //reverse the order of the found element with value 3 and all following elements
  reverse(pos3, coll12.end());

  //print all elements
  for(auto elem : coll12){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //create vector with elements from 1 to 6 in arbitrary order
  std::vector<int> coll13;
  coll13.push_back(2);
  coll13.push_back(5);
  coll13.push_back(4);
  coll13.push_back(1);
  coll13.push_back(6);
  coll13.push_back(3);

  //find and print minimum and maximum elements
  std::vector<int>::const_iterator minpos1 = min_element(coll13.begin(),
                                                         coll13.end());
  std::cout << "min: " << *minpos1 << std::endl;
  std::vector<int>::const_iterator maxpos1 = max_element(coll13.begin(),
                                                         coll13.end());
  std::cout << "max: " << *maxpos1 << std::endl;

  //sort all elements
  sort(coll13.begin(), coll13.end());

  //find the first element with value 3
  std::vector<int>::iterator pos31;
  pos31 = find(coll13.begin(), coll13.end(),//range
               3);//value

  //reverse the order of the found element with value 3 and all following elements
  reverse(pos31, coll13.end());

  //print all elements
  std::vector<int>::const_iterator pos2;
  for(pos2 = coll13.begin(); pos2 != coll13.end(); ++pos2){
    std::cout << *pos2 << ' ';
  }
  std::cout << std::endl;

  //6.4.1区间(Range)

  std::list<int> coll14;

  //insert elements from 20 to 40
  for(int i = 20; i <= 40; ++i){
    coll14.push_back(i);
  }

  //find position of element with value3
  //- there is none, so pos3 get coll.end()
  auto pos32 = find(coll14.begin(),coll14.end(),//range
                    3);//value

  //reverse the order of elements between found element and the end
  //- because pos3 is coll.end() it reverses an empty range
  reverse(pos32, coll14.end());

  //find positions of values 25 and 35
  std::list<int>::iterator pos25,pos35;
  pos25=find(coll14.begin(), coll14.end(),//range
             25);//value
  pos35=find(coll14.begin(), coll14.end(),//range
             35);//value

  //print the maximum of the corresponding range
  //- note: including pos25 but excluding pos35
  std::cout << "max: " << *max_element(pos25, pos35) << std::endl;

  //process the elements including the last position
  std::cout << "max: " << *max_element(pos25, ++pos35) << std::endl;

  //6.4.2处理多重区间(Multiple Ranges)

  std::list<int> coll15={1,2,3,4,5,6,7,8,9};
  std::vector<int> coll16;
  //RUNTIME ERROR:
  //- overwrites nonexisting elements in the destination
  //copy(coll15.cbegin(),coll15.cend(),//source
  //     coll16.begin());//destination

  //resize destination to have enough room for the overwriting algorithm
  coll16.resize(coll15.size());

  //copy elements from first into second collection
  //- overwrites existing elements in destination
  copy(coll15.cbegin(),coll15.cend(),//source
       coll16.begin());//destination

  for(auto& elem : coll16){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //create third collection with enough room
  //- initial size is passed as parameter

  std::deque<int> coll17(coll15.size());

  //copy elements from first into third collection
  copy(coll15.cbegin(),coll15.cend(),//source
       coll17.begin());//destination

  for(auto& elem : coll17){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //6.5迭代器之适配器(Iterator Adapter)
  //6.5.1 Insert Iterator（安插型迭代器）

  std::list<int> coll18={1,2,3,4,5,6,7,8,9};

  //copy the elements of coll18 into coll19 by appending them
  std::vector<int> coll19;
  copy(coll18.cbegin(),coll18.cend(),//source
       back_inserter(coll19));//destination

  for(auto& elem : coll19){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //copy the element of coll118 into coll20 by inserting them at the front
  //- reverses the order of the elements
  std::deque<int> coll20;
  copy(coll18.cbegin(),coll18.cend(),//source
       front_inserter(coll20));//destination

  for(auto& elem : coll20){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //copy elements of coll18 into coll21
  //- only inserter that works for associative collections
  std::set<int> coll21;
  copy(coll18.cbegin(),coll18.cend(),//source
       inserter(coll21,coll21.begin()));

  for(auto& elem : coll21){
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  //6.5.2 Stream Iterator（串流迭代器）
  /*
  std::vector<std::string> coll22;
  //read all words from the standard input
  //- source: all strings until end-of-file(or error)
  //- destination: coll22(inserting)
  copy(std::istream_iterator<std::string>(std::cin),//start of source
       std::istream_iterator<std::string>(),//end of source
       back_inserter(coll22));//destination

  //sort elements
  sort(coll22.begin(),coll22.end());

  //print all elements without duplicates
  //-source: coll22
  //-destination: standard output(with newline between elements)
  unique_copy(coll22.cbegin(),coll22.cend(),//source
              std::ostream_iterator<std::string>(std::cout,"\n"));//destination
  */
  //6.5.3 Reverse Iterator（反向迭代器）
  std::vector<int> coll23;

  //insert elements from 1 to 9
  for(int i = 1; i <= 9; ++i){
    coll23.push_back(i);
  }

  //print all element in reverse order
  copy(coll23.crbegin(),coll23.crend(),//source
       std::ostream_iterator<int>(std::cout, " "));//destination
  std::cout << std::endl;

  //6.5.4 Move Iterator（搬迁迭代器）
  //6.6用户自定义的泛型函数(User-Defined Generic Function)

  PRINT_ELEMENTS(coll23, "all elements: ");

  //6.7更易型算法(Manipulating Algorithm)
  //6.7.1移除(Removing)元素

  std::list<int> coll24;

  //insert elements from 6 to and 1 to 6
  for(int i = 1; i <= 6; ++i){
    coll24.push_front(i);
    coll24.push_back(i);
  }

  //print all elements of the collection
  std::cout << "pre: ";
  copy(coll24.cbegin(),coll24.cend(),//source
       std::ostream_iterator<int>(std::cout, " "));//destination

  std::cout << std::endl;

  //remove all elements with value 3
  remove(coll24.begin(),coll24.end(),//range
         3);//value

  //print all elements of the collection
  std::cout << "post: ";
  copy(coll24.cbegin(),coll24.cend(),//source
       std::ostream_iterator<int>(std::cout, " "));//destination
  std::cout << std::endl;

  std::list<int> coll25;

  //insert elements from 6 to 1 and 1 to 6
  for(int i = 1; i <= 6; ++i){
    coll25.push_front(i);
    coll25.push_back(i);
  }

  //print all elements of the collection
  copy(coll25.cbegin(),coll25.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  //remove all elements with value 3
  //-retain new end

  std::list<int>::iterator end = remove(coll25.begin(),coll25.end(),
                                        3);

  //print resulting elements of the collection
  copy(coll25.begin(),end,
       std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  //print number of removed elements
  std::cout << "number of removed elements: "
            << distance(end, coll25.end()) << std::endl;

  //remove "removed" elements
  coll25.erase(end, coll25.end());

  //print all elements of the modified collection
  copy(coll25.cbegin(),coll25.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  //6.7.2更易Associative（关联式）和Unordered（无序）容器

  //unordered set with elements from 1 to 9
  std::set<int> coll26 = {1,2,3,4,5,6,7,8,9};

  //print all elements of the collection
  copy(coll26.cbegin(),coll26.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  //Remove all elements with value 3
  //-algorithm remove() does not work
  //-instead member function erase() works

  int num = coll26.erase(3);

  //print number of removed elements
  std::cout << "number of removed elements: " << num << std::endl;

  //print all elements of the modified collection
  copy(coll26.cbegin(), coll26.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  //6.7.3算法vs.成员函数
  std::list<int> coll27;

  //insert elements from 6 to 1 and 1 to 6
  for(int i = 1; i <= 6; ++i){
    coll27.push_front(i);
    coll27.push_back(i);
  }

  //remove all elements with value 3 (poor performance)
  coll27.erase(remove(coll27.begin(),coll27.end(),
                      3),
               coll27.end());

  //remove all elements with value 4 (good performance)
  coll27.remove(4);

  copy(coll27.cbegin(),coll27.cend(),
       std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  //6.8以函数作为算法的实参
  //6.8.1以函数作为算法实参的实例示范

  std::vector<int> coll28;

  //insert elements from 1 to 9
  for(int i = 1; i <= 9; ++i){
    coll28.push_back(i);
  }

  for_each(coll28.cbegin(),coll28.cend(),//range
           print);//operation
  std::cout << std::endl;

  std::set<int> coll29;
  std::vector<int> coll30;

  //insert elements from 1 to 9 into coll29
  for(int i = 1; i <= 9; ++i){
    coll29.insert(i);
  }

  PRINT_ELEMENTS(coll29,"initialized: ");

  //transform each element from coll29 to coll30
  //-square transformed values

  std::transform(coll29.cbegin(),coll29.cend(),//source
                 std::back_inserter(coll30),//destination
                 square);//operation
  PRINT_ELEMENTS(coll30, "squared:  ");

  //6.8.2判断式(Predicate)

  std::list<int> coll31;

  //insert elements from 24 to 30
  for(int i = 24; i <= 30; ++i){
    coll31.push_back(i);
  }

  //search for prime number
  auto pos4 = find_if(coll31.cbegin(),coll31.cend(),//range
                      isPrime);//predicate
  if(pos4 != coll31.end()){
    //found
    std::cout << *pos4 << " is first prime number found" << std::endl;
  }
  else {
    //not found
    std::cout << "no prime number found" << std::endl;
  }

  std::deque<Person> coll32;
  coll32.push_back(Person("hello","world"));
  coll32.push_back(Person("kit","him"));
  coll32.push_back(Person("fuck", "template"));
  coll32.push_back(Person("fuck","him"));

  for(const auto& elem : coll32){
    std::cout << elem.firstname() << " " << elem.lastname() << std::endl;
  }

  sort(coll32.begin(),coll32.end(),//range
       personSortCriterion);//sort criterion

  for(const auto& elem : coll32){
    std::cout << elem.firstname() << " " << elem.lastname() << std::endl;
  }

  //6.9使用Lambda

  std::deque<int> coll33 = {1,3,19,5,13,7,11,2,17};
  int x = 4;
  int y = 12;
  auto pos5 = find_if(coll33.cbegin(),coll33.cend(),//range
                      [x,y](int i )-> bool {//search criterion
                        return i > x && i < y;
                      });
  std::cout << "first elem >4 and <12: " << *pos5 << std::endl;

  //sort Persons according to lastname(and firstname):
  sort(coll32.begin(),coll32.end(),//range
       [](const Person& p1, const Person& p2){//sort criterion
         return p1.firstname()<p2.firstname()||
                              (p1.firstname()==p2.firstname() &&
                               p1.lastname()<p2.lastname());
       });

  for(const auto& elem : coll32){
    std::cout << elem.firstname() << " " << elem.lastname() << std::endl;
  }

  //6.10函数对象(Function Object)
  //6.10.1定义一个函数对象

  std::vector<int> coll34;

  //insert elements from 1 to 9
  for(int i = 1; i <= 9; ++i){
    coll34.push_back(i);
  }

  //print all elements
  for_each(coll34.cbegin(),coll34.cend(),//range
           PrintInt());//operation
  std::cout << std::endl;

  std::list<int> coll35;

  //insert elements from 1 to 9
  for(int i = 1; i <= 9; ++i){
    coll35.push_back(i);
  }

  PRINT_ELEMENTS(coll35,"initialized:          ");

  //add value 10 to each element

  for_each(coll35.begin(),coll35.end(),//range
           AddValue(10));//operation

  PRINT_ELEMENTS(coll35,"after adding 10:        ");

  //add value of first element to each element
  for_each(coll35.begin(),coll35.end(),//range
           AddValue(*coll35.begin()));//operation

  PRINT_ELEMENTS(coll35,"after adding first element:    ");

  //6.10.2预定义的函数对象

  std::deque<int> coll36 = {1,2,3,5,7,11,13,17,19};

  PRINT_ELEMENTS(coll36,"initialized:  ");

  //negate all value in coll36
  transform(coll36.cbegin(),coll36.cend(),//source
            coll36.begin(),//destination
            std::negate<int>());//operation
  PRINT_ELEMENTS(coll36,"negated:   ");

  //square all value in coll36
  transform(coll36.cbegin(),coll36.cend(),//first source
            coll36.cbegin(),//second source
            coll36.begin(),//destination
            std::multiplies<int>());//operation
  PRINT_ELEMENTS(coll36,"squared:   ");

  //6.10.3 Binder

  std::set<int,std::greater<int>> coll37={1,2,3,4,5,6,7,8,9};
  std::deque<int> coll38;

  //Note: due to the sorting criterion greater<>() elements have reverse order:
  PRINT_ELEMENTS(coll37,"initialized: ");

  //transform all elements into coll38 by multiplying them with 10
  transform(coll37.cbegin(),coll37.cend(),//source
            std::back_inserter(coll38),//destination
            std::bind(std::multiplies<int>(),std::placeholders::_1,10));//operation
  PRINT_ELEMENTS(coll38,"transformed:  ");

  //replace value equal to 70 with 42
  replace_if(coll38.begin(),coll38.end(),//range
             std::bind(std::equal_to<int>(),std::placeholders::_1,70),//replace criterion
             42);
  PRINT_ELEMENTS(coll38,"replaced:    ");

  //remove all elements with values between 50 and 80
  coll38.erase(remove_if(coll38.begin(),coll38.end(),
                         std::bind(std::logical_and<bool>(),
                                   std::bind(std::greater_equal<int>(),std::placeholders::_1,50),
                                   std::bind(std::less_equal<int>(),std::placeholders::_1,80))),
               coll38.end());
  PRINT_ELEMENTS(coll38,"removed:   ");

  //6.10.4函数对象vs. Lambda
  //6.11容器内的元素
  //6.11.1容器元素的必要条件
  //6.11.2 Value语义vs. Reference 语义
  //6.12 STL内部的错误和异常
  //6.12.1错误处理(Error Handling)
  /*
  std::vector<int> coll39;//empty collection
  std::vector<int> coll40;//empty collection

  //RUNTIME ERROR:
  //-beginning is behind the end of the range
  std::vector<int>::iterator pos6=coll39.begin();
  reverse(++pos6,coll39.end());

  //insert elements from 1 to 9 into coll39
  for(int i = 1; i <= 9; ++i){
    coll39.push_back(i);
  }

  //RUNTIME ERROR:
  //-overwriting nonexisting elements
  copy(coll39.cbegin(),coll39.cend(),//source
       coll40.begin());//destination

  //RUNTIME ERROR:
  //-collections mistaken
  //-cbegin() and cend() refer to different collections
  copy(coll39.cbegin(),coll40.cend(),//source
       coll39.end());//destination
  */

  //6.12.2异常处理(Exception Handling)
  //6.13扩展STL
  //6.13.1整合更多Type
  //6.13.2派生自STL Type

  //7 STL容器
  //7.1容器的共通能力和共通操作
  //7.1.1容器的共通能力
  //7.1.2容器的共通操作












  return 0;
}
