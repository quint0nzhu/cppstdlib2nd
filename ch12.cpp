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
#include <bitset>
#include <limits> //for std::numeric_limits<>



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

  std::priority_queue<float> pbuffer;//priority queue for floats

  std::priority_queue<float,std::vector<float>,std::greater<float>> pbuffer1;

  //12.3.1 核心接口

  //push()将一个元素放入priority queue中
  //top()返回priority queue内的“下一个元素”
  //pop()从priority queue内移除一个元素

  //12.3.2 Priority Queue运用实例

  std::priority_queue<float> pq;

  //insert three elements into the priority queue
  pq.push(66.6);
  pq.push(22.2);
  pq.push(44.4);

  //read and print two elements
  std::cout<<pq.top()<<' ';
  pq.pop();
  std::cout<<pq.top()<<std::endl;
  pq.pop();

  //insert three more elements
  pq.push(11.1);
  pq.push(55.5);
  pq.push(33.3);

  //skip one element
  pq.pop();

  //pop and print remaining elements
  while(!pq.empty()){
    std::cout<<pq.top()<<' ';
    pq.pop();
  }
  std::cout<<std::endl;

  //12.3.3 细究Class priority_queue<>

  //12.4 细究Container Adapter
  //12.4.1 类型定义

  //contadapt::value_type
  //元素的类型
  //和container::value_type相当

  //contadapt::reference
  //“用以指向元素”之reference的类型
  //和container::reference相当
  //始自C++11

  //contadapt::const_reference
  //"用以指向只读元素(read-only element)"之reference的类型
  //和container::const_reference相当
  //始自C++11

  //contadapt::size_type
  //不带正负号的整数类型，用来表现大小
  //和container::size_type相当

  //contadapt::container_type
  //内部容器的类型

  //12.4.2 构造函数(Constructor)

  //contadapt::contadapt()
  //Default构造函数
  //创建一个空的stack或(priority)queue

  //explicit contadapt::contadapt(const Container& cont)
  //explicit contadapt::contadapt(Container&& cont)
  //创建一个stack或queue，以容器cont的元素为初值，后者必须是container adapter的container_type之下的一个对象
  //第一形式中，cont内的所有元素均被复制
  //第二形式中，cont内的所有元素均被搬移(moved)——前提是被传入之容器提供有move语义，否则元素仍然是被复制
  //两种形式都不存在于priority_queue<>中

  //12.4.3 Priority Queue额外提供的构造函数

  //explicit priority_queue::priority_queue(const CompFunc& op)
  //创建一个空的priority queue，以op为排序准则
  //如何将排序准则当作实参传入，见前面的例子

  //priority_queue::priority_queue(const CompFunc& op,const Container& cont)
  //创建一个priority queue,以op为排序准则，以容器cont内的元素为初值
  //cont的所有元素都被复制过来

  //priority_queue::priority_queue(InputIterator beg,InputIterator end)
  //创建一个priority queue,以[beg,end)区间内的元素为初值
  //这是一个template memeber，所以只要源区间内的元素类型可以转化为本容器内的元素类型，此构造函数即可运作

  //priority_queue::priority_queue(InputIterator beg,InputIterator end,const CompFunc& op)
  //创建一个priority queue，以op为排序准则，并以[beg,end)区间内的元素为初值
  //这是一个template member，所以只要源区间内的元素类型可以转化为本容器内的元素类型，此构造函数即可运作
  //如何将排序准则当作实参传入，见前面的例子

  //priority_queue::priority_queue(InputIterator beg,InputIterator end,const CompFunc& op,const Container& cont)
  //创建一个priority queue,以op为排序准则，以[beg,end)区间内的元素加上cont容器内的元素为初值
  //这是一个template member，所以只要源区间内的元素类型可以转化为本容器内的元素类型，此构造函数即可运作

  //12.4.4 各项操作(Operation)

  //bool contadapt::empty()const
  //判断container adapter是否为空（不含任何元素）
  //与contadapt::size()==0等效，但速度可能更快

  //size_type contadapt::size()const
  //返回当前的元素个数
  //若要检验容器是否为空（不含任何元素），应使用empty()，因为后者可能更快

  //void contadapt::push(const value_type& elem)
  //void contadapt::push(value_type&& elem)
  //第一形式安插elem的一份拷贝（副本）
  //第二形式始自C++11，elem将被搬移（如果元素类型提供move语义的话），否则elem将被复制

  //void contadapt::emplace(args)
  //安插一个新元素，它将被args初始化
  //始自C++11

  //reference contadapt::top()
  //const_reference contadapt::top()const
  //reference contadapt::front()
  //const_reference contadapt::front()const
  //上述任何形式，只要container adapter提供了它们，都会返回下一元素
  //-Stack提供两个形式的top()，返回最后一个安插元素
  //-Queue提供两个形式的front()，返回第一个安插元素
  //-Priority queue只提供第二形式的top，获得的是带有最大值的元素。如果候选多于1,究竟返回哪个元素并不明确
  //调用者必须确保container adapter不为空(size()>0)，否则可能导致不明确的行为
  //上述形式中“返回non-const reference”者允许你改动下一元素（当它还在stack/queue内）。这样做合宜与否，由你自己决定
  //在C++11之前，返回类型是(const)value_type&，通常那是相同的

  //void contadapt::pop()
  //移除container adapter内的下一个元素
  //-对于stack而言，所谓“下一元素”是指“最后一个被安插元素”
  //-对于queue而言，所谓“下一元素”是指“第一个被安插元素”
  //-对于priority queue而言，所谓“下一元素”是指“带有最大值的元素”。如果候选多于1,究竟移除哪个元素并不明确
  //此函数无返回值。如果想处理被移除的那个元素，你必须先调用top()才能取得它
  //调用者必须确保stack不为空(size()>0)，否则可能导致不明确的行为

  //reference queue::back()
  //const_reference quque::back()const
  //两种形式都返回queue的最终元素。所谓“最终元素”是指最后一个被插入的元素
  //调用者必须确保queue不为空(size()>0)，否则可能导致不明确的行为
  //第一形式是针对non-const queue而设计，返回一个reference。所以你可以改动最终元素（当它还在queue内）。这样做合宜与否，由你自己决定
  //在C++11之前，返回类型是(const)value_type&，通常那是相同的
  //只有queue<>提供

  //bool comparison(const contadapt& stack1,const contadapt& stack2)
  //返回两个相同类型的stack或queue的比较结果
  //comparison可以是下面任何运算：
  // operators==和!=
  // operators<、>、<=和>=
  //如果两个stack（或两个queue）的元素个数相等，且相同次序上的元素值也相等（也就是所有对应元素之间的比较都得到true），则这两个容器相等
  //Stack中queue之间的大小比较是以“字典顺序”来决定(lexicographically)
  //priority_queue<>不提供这个操作

  //void contadapt::swap(contadapt& c)
  //void swap(contadapt& c1,contadapt& c2)
  //交换*this和c的内容，或交换c1和c2的内容。对于priority queue，还交换排序准则
  //调用相应容器之swap()
  //始自C++11

  //12.5 Bitset
  //12.5.1 Bitset运用实例

  //enumeration type for the bits
  //-each bit represents a color
  enum Color{red,yellow,green,blue,white,black};

  //create bitset for all bits/colors
  std::bitset<6> usedColors;

  //set bits for two colors
  usedColors.set(red);
  usedColors.set(blue);

  //print some bitset data
  std::cout<<"bitfield of used colors:     "<<usedColors<<std::endl;
  std::cout<<"number   of used colors:     "<<usedColors.count()<<std::endl;
  std::cout<<"bitfield of unused colors:   "<<~usedColors<<std::endl;

  //if any color is used
  if(usedColors.any()){
    //loop over all colors
    for(int c=0;c<6;++c){
      //if the actual color is used
      if(usedColors[(Color)c]){
        std::cout<<c<<" is used!"<<std::endl;
      }
    }
  }

  //print some numbers in binary representation
  std::cout<<"267 as binary short:      "
           <<std::bitset<std::numeric_limits<unsigned short>::digits>(267)
           <<std::endl;

  std::cout<<"267 as binary long:       "
           <<std::bitset<std::numeric_limits<unsigned long>::digits>(267)
           <<std::endl;

  std::cout<<"10,000,000 with 24 bits:  "
           <<std::bitset<24>(1e7)<<std::endl;

  //write binary representation into string
  std::string s=std::bitset<42>(12345678).to_string();
  std::cout<<"12,345,678 with 42 bits:  "<<s<<std::endl;

  //transform binary representation into integral number
  std::cout<<"\"1000101011\" as number: "
           <<std::bitset<100>("1000101011").to_ullong()<<std::endl;

  //12.5.2 细究Class bitset

  return 0;
}
