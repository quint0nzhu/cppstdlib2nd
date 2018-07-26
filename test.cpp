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




  return 0;
}
