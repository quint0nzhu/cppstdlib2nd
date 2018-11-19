/*
  author: Quinton
  date: 2018-11-19
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 12
*/


#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <exception>
#include <queue>
#include <list>



template<typename T>
class Stack{
protected:
  std::deque<T> c;//container for the elements

public:
  //exception class for pop() and top() with empty stack
  class ReadEmptyStack:public std::exception{
  public:
    virtual const char* what()const throw(){
      return "read empty stack";
    }
  };

  //number of elements
  typename std::deque<T>::size_type size()const{
    return c.size();
  }

  //is stack empty?
  bool empty()const{
    return c.empty();
  }

  //push element into the stack
  void push(const T& elem){
    c.push_back(elem);
  }

  //pop element out of the stack and return its value
  T pop(){
    if(c.empty()){
      throw ReadEmptyStack();
    }

    T elem(c.back());
    c.pop_back();
    return elem;
  }

  //return value of next element
  T& top(){
    if(c.empty()){
      throw ReadEmptyStack();
    }
    return c.back();
  }
};





int main()
{
  // 第12章 特殊容器
  //12.1 Stack（堆栈）

  std::stack<int> st;//integer stack

  std::stack<int,std::vector<int>> st1;//integer stack that uses a vector

  //12.2.1 核心接口

  //push()将一个元素放入stack内
  //top()返回stack内的”下一个“元素
  //pop()从stack中移除元素

  //12.1.2 Stack运用实例

  //push three elements into the stack
  st.push(1);
  st.push(2);
  st.push(3);

  //pop and print two elements from the stack
  std::cout<<st.top()<<' ';
  st.pop();
  std::cout<<st.top()<<' ';
  st.pop();

  //modify top element
  st.top()=77;

  //push two new elements
  st.push(4);
  st.push(5);

  //pop one element without processing it
  st.pop();

  //pop and print remaining elements
  while(!st.empty()){
    std::cout<<st.top()<<' ';
    st.pop();
  }
  std::cout<<std::endl;

  std::stack<std::pair<std::string,std::string>> st2;

  auto p=std::make_pair("hello","world");
  st2.push(std::move(p));//OK, if p is not used any more

  st2.emplace("nico","josuttis");

  while(!st2.empty()){
    std::cout<<st2.top().first<<" "<<st2.top().second<<std::endl;
    st2.pop();
  }

  //12.1.3 一个用户自定义的Stack Class

  try{
    Stack<int> myst;

    //push three elements into the stack
    myst.push(1);
    myst.push(2);
    myst.push(3);

    //pop and print two elements from the stack
    std::cout<<myst.pop()<<' ';
    std::cout<<myst.pop()<<' ';

    //modify top element
    myst.top()=77;

    //push two new elements
    myst.push(4);
    myst.push(5);

    //pop one element without processing it
    myst.pop();

    //pop and print three elements
    //-ERROR: one element too many
    std::cout<<myst.pop()<<' ';
    std::cout<<myst.pop()<<std::endl;
    std::cout<<myst.pop()<<std::endl;
  }
  catch(const std::exception& e){
    std::cerr<<"EXCEPTION: "<<e.what()<<std::endl;
  }

  //12.1.4 细究Class stack<>

  //12.2 Queue（队列）

  std::queue<std::string> buffer;//string queue

  std::queue<std::string,std::list<std::string>> buffer1;//string queue that uses a list

  //12.2.1 核心接口

  //push()将一个元素放入queue内
  //front()返回queue内的下一个元素（也就是第一个被放入的元素）
  //back()返回queue内的最后一个元素（也就是第一个被插入的元素）
  //pop()从queue中移除一个元素

  std::queue<std::string> q;

  //insert three elements into the queue
  q.push("These ");
  q.push("are ");
  q.push("more than ");

  //read and print two elements from the queue
  std::cout<<q.front();
  q.pop();
  std::cout<<q.front();
  q.pop();

  //insert two new elements
  q.push("four ");
  q.push("words!");

  //skip one element
  q.pop();

  //read and print two elements
  std::cout<<q.front();
  q.pop();
  std::cout<<q.front()<<std::endl;
  q.pop();

  //print number of elements in the queue
  std::cout<<"number of elements in the queue: "<<q.size()<<std::endl;

  //12.2.3 一个用户自定义的Queue Class
  //12.2.4 细究Class queue<>

  //12.3 Priority Queue（带优先级的队列）










  return 0;
}
