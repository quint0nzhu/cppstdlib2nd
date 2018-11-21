/*
  author: Quinton
  date: 2018-11-20
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 13
*/



#include <iostream>
#include <string>


void f(const char* s,int n)
{
  std::cout<<s<<std::endl;
  std::cout<<"length: "<<n<<std::endl;
}

int main(int argc, char* argv[])
{
  //第13章 字符串
  //13.1 String Class的目的
  //13.1.1 例一：提炼临时文件名

  std::string filename,basename,extname,tmpname;
  const std::string suffix("tmp");

  //for each command-line argument(which is an ordinary C-string)
  for(int i=1;i<argc;++i){
    //process argument as filename
    filename=argv[i];

    //search period in filename
    std::string::size_type idx=filename.find('.');
    if(idx==std::string::npos){
      //filename does not contain any period
      tmpname=filename+'.'+suffix;
    }
    else{
      //split filename into base name and extension
      //-base name contains all characters before the period
      //-extension contains all characters after the period
      basename=filename.substr(0,idx);
      extname=filename.substr(idx+1);
      if(extname.empty()){
        //contains period but no extension: append tmp
        tmpname=filename;
        tmpname+=suffix;
      }
      else if(extname==suffix){
        //replace extension tmp with xxx
        tmpname=filename;
        tmpname.replace(idx+1,extname.size(),"xxx");
      }
      else{
        //replace any extension with tmp
        tmpname=filename;
        tmpname.replace(idx+1,std::string::npos,suffix);
      }
    }

    //print filename and temporary name
    std::cout<<filename<<"=>"<<tmpname<<std::endl;
  }

  const std::string delims(" \t,.;");
  std::string line;

  //for every line read successfully
  while(getline(std::cin,line)){
    std::string::size_type begIdx,endIdx;

    //search beginning of the first word
    begIdx=line.find_first_not_of(delims);

    //while beginning of a word found
    while(begIdx!=std::string::npos){
      //search end of the actual word
      endIdx=line.find_first_of(delims,begIdx);
      if(endIdx==std::string::npos){
        //end of word is end of line
        endIdx=line.length();
      }

      //print characters in reverse order
      for(int i=endIdx-1;i>=static_cast<int>(begIdx);--i){
        std::cout<<line[i];
      }
      std::cout<<' ';

      //search beginning of the next word
      begIdx=line.find_first_not_of(delims,endIdx);
    }
    std::cout<<std::endl;
  }

  //13.2 String Class细节描述
  //13.2.1 String的各种相关类型
  //13.2.2 操作函数概览

  std::string s1("nico");//initializes s1 with: 'n' 'i' 'c' 'o'
  std::string s2("nico",5);//initializes s2 with: 'n' 'i' 'c' 'o' '\0'
  std::string s3(5,'\0');//initializes s3 with: '\0' '\0' '\0' '\0' '\0'

  std::cout<<s1.length()<<std::endl;//yields 4
  std::cout<<s2.length()<<std::endl;//yields 5
  std::cout<<s3.length()<<std::endl;//yields 5

  //13.2.3 构造函数和析构函数(Constructor and Destructor)

  //std::string s('x');//ERROR
  std::string ss(1,'x');//OK, creates a string that has one character 'x'
  std::string sss({'x'});//OK, ditto(since C++ 11)

  //13.2.4 String和C-String

  std::string s4("12345");

  int a=atoi(s4.c_str());//convert string into integer
  std::cout<<"a: "<<a<<std::endl;
  f(s4.data(),s4.length());//call function for a character array and the number of characters

  char buffer[100];
  s4.copy(buffer,100);//copy at most 100 characters of s4 into buffer
  s4.copy(buffer,100,2);//copy at most 100 characters of s4 into buffer starting with the third character of s4

  std::string s5("abc");

  f(s5.c_str(),s5.length());//s5.c_str() is valid during the whole statement

  const char* p;
  p = s5.c_str();//p refers to the contents of s5 as a C-string
  f(p,s5.length());//OK(p is still valid)
  s5+="ext";//invalidates p
  f(p,s5.length());//ERROR: argument p is not valid, but not done on my computer

  //13.2.5 大小和容量(Size and Capacity)

  std::cout<<s5.max_size()<<std::endl;
  std::string s6;//create empty string
  s6.reserve(80);//reserve memory for 80 characters
  s6.reserve();//"would like to shrink capacity to fit the current size"
  s6.shrink_to_fit();//"would like to shrink capacity to fit the current size"(C++ 11)

  //13.2.6 元素访问(Element Access)







  return 0;
}
