/*
  author: Quinton
  date: 2018-12-19
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 19
*/


#include <iostream>
#include <vector>
#include <map>


template<typename T>
class MyAlloc{
public:
  //type definitions
  typedef T value_type;

  //constructors
  //-nothing to do because the allocator has no state
  MyAlloc()noexcept{}
  template<typename U>
  MyAlloc(const MyAlloc<U>&)noexcept{
    //no state to copy
  }

  //allocate but don't initialize num elements of type T
  T* allocate(std::size_t num){
    //allocate memory with global new
    return static_cast<T*>(::operator new(num*sizeof(T)));
  }

  //deallocate storage p of deleted elements
  void deallocate(T* p,std::size_t num){
    //deallocate memory with global delete
    ::operator delete(p);
  }
};

//return that all specializations of this allocator are interchangeable
template<typename T1,typename T2>
bool operator==(const MyAlloc<T1>&,
                const MyAlloc<T2>&)noexcept{
  return true;
}

template<typename T1,typename T2>
bool operator!=(const MyAlloc<T1>&,
                const MyAlloc<T2>&)noexcept{
  return false;
}

template<typename T>
using Vec=std::vector<T,MyAlloc<T>>;//vector using own allocator



int main(int argc, char* argv[])
{
  //第19章 分配器
  //19.1 以应用程序开发者的角度使用Allocator

  //a vector with special allocator
  std::vector<int,MyAlloc<int>> v;

  //a int/float map with special allocator
  std::map<int,float,std::less<int>,
           MyAlloc<std::pair<const int,float>>> m;

  //a string with special allocator
  std::basic_string<char,std::char_traits<char>,
                    MyAlloc<char>> s;

  //special string type that uses special allocator
  typedef std::basic_string<char,std::char_traits<char>,
                            MyAlloc<char>> MyString;

  //special string/string map type that uses special allocator
  typedef std::map<MyString,MyString,std::less<MyString>,
                   MyAlloc<std::pair<const MyString,MyString>>> MyMap;

  //create object of this type
  MyMap mymap;

  Vec<int> coll;//equivalent to: std::vector<int,MyAlloc<int>>

  if(mymap.get_allocator()==s.get_allocator()){
    //OK,mymap and s use the same or interchangeable allocators
    std::cout<<"mymap and s are using the same allocator"<<std::endl;
  }

  //std::uses_allocator<T,Alloc>::value;//true if Alloc is convertible into T::allocator_type

  //19.2 用户自定义的Allocator
  //19.3 以程序库开发者的角度使用Allocator

  //copy(x.begin(),x.end(),//source
  //     raw_storage_iterator<T*,T>(elems));//destination

  //void f()
  //{
    //allocate memory for num elements of type MyType
  //  pair<MyType*,std::ptrdiff_t> p
  //    =get_temporary_buffer<MyType>(num);
  //  if(p.second==0){
      //could not allocate any memory for elements
      //...
  //  }
  //  else if(p.second<num){
      //could not allocate enough memory for num elements
      //however,don't forget to deallocate it
      //...
  //  }

    //do your processing
    //...

    //free temporarily allocated memory, if any
  //  if(p.first!=0){
  //    return_temporary_buffer(p.first);
  //  }
  //}

  return 0;
}
