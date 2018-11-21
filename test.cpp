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

  const std::string cs("nico");//cs contains: 'n' 'i' 'c' 'o'
  std::string s7("abcde");//s7 contains: 'a' 'b' 'c' 'd' 'e'
  std::string t;//t contains no character(is empty)

  std::cout<<s7[2]<<std::endl;//yeilds 'c' as char&
  std::cout<<s7.at(2)<<std::endl;//yields 'c' as char&
  std::cout<<s7.front()<<std::endl;//yields 'a' as char&
  std::cout<<cs[1]<<std::endl;//yields 'i' as const char&
  std::cout<<cs.back()<<std::endl;//yields 'o' as const char&

  std::cout<<s7[100]<<std::endl;//ERROR: undefined behavior
  //std::cout<<s7.at(100)<<std::endl;//throws out_of_range
  std::cout<<t.front()<<std::endl;//yields '\0'
  std::cout<<t.back()<<std::endl;//ERROR: undefined behavior, BUT IT IS WORK!

  std::cout<<s7[s7.length()]<<std::endl;//yields '\0' (undefined behavior before C++11)
  std::cout<<cs[cs.length()]<<std::endl;//yields '\0'
  //std::cout<<s7.at(s7.length())<<std::endl;//throws out_of_range
  //std::cout<<cs.at(cs.length())<<std::endl;//throws out_of_range

  char& r=s7[2];//reference to third character
  char* p1=&s7[3];//pointer to fourth character

  r='X';//OK, s7 contains: 'a' 'b' 'X' 'd' 'e'
  std::cout<<s7<<std::endl;
  *p1='Y';//OK, s7 contains: 'a' 'b' 'X' 'Y' 'e'
  std::cout<<s7<<std::endl;

  s7="new long value";//reallocation invalidates r and p

  r='X';//ERROR: undefined behavior, BUT IT IS WORK!
  std::cout<<s7<<std::endl;
  *p1='Y';//ERROR: undefined behavior,BUT IT IS WORK!
  std::cout<<s7<<std::endl;

  //13.2.7 比较(Comparison)

  std::string s8,s9;
  std::cout<<(s8==s9)<<std::endl;//returns true if s8 and s9 contain the same characters
  std::cout<<("hello"<s8)<<std::endl;//return whether s8 is less than the C-string "hello"

  std::cout<<(std::string("aaaa")<std::string("bbbb"))<<std::endl;
  std::cout<<(std::string("aaaa")<std::string("abba"))<<std::endl;
  std::cout<<(std::string("aaaa")<std::string("aaaaaa"))<<std::endl;

  std::string s10("abcd");

  std::cout<<s10.compare("abcd")<<std::endl;//returns 0
  std::cout<<s10.compare("dcba")<<std::endl;//returns a value < 0 (s10 is less)
  std::cout<<s10.compare("ab")<<std::endl;//returns a value > 0 (s10 is greater)

  std::cout<<s10.compare(s10)<<std::endl;//returns 0 (s10 is equal to s10)
  std::cout<<s10.compare(0,2,s10,2,2)<<std::endl;//returns a value < 0 ("ab" is less than "cd")
  std::cout<<s10.compare(1,2,"bcx",2)<<std::endl;//returns 0 ("bc" is equal to "bc")

  //13.2.8 更改内容(Modifier)

  const std::string aString("othello");
  std::string s11;

  std::cout<<(s11=aString)<<std::endl;//assign "othello"
  std::cout<<(s11="two\nlines")<<std::endl;//assign a C-string
  std::cout<<(s11=' ')<<std::endl;//assign a single character

  std::cout<<s11.assign(aString)<<std::endl;//assign "othello" (equivalent to operator =)
  std::cout<<s11.assign(aString,1,3)<<std::endl;//assign "the"
  std::cout<<s11.assign(aString,2,std::string::npos)<<std::endl;//assign "hello"

  std::cout<<s11.assign("two\nlines")<<std::endl;//assign a C-string(equivalent to operator =)
  std::cout<<s11.assign("nico",5)<<std::endl;//assign the character array: 'n' 'i' 'c' 'o' '\0'
  std::cout<<s11.assign(5,'x')<<std::endl;//assign five characters: 'x' 'x' 'x' 'x' 'x'

  s11="";//assign the empty string
  s11.clear();//clear contents
  s11.erase();//erase all characters

  std::string s12;
  std::cout<<(s12+=aString)<<std::endl;//append "othello"
  std::cout<<(s12+="two\nlines")<<std::endl;//append C-string
  std::cout<<(s12+='\n')<<std::endl;//append single character
  std::cout<<(s12+={'o','k'})<<std::endl;//append an initializer list of characters (since C++11)


  s12.clear();

  std::cout<<s12.append(aString)<<std::endl;//append "othello" (equivalent to operator +=)
  std::cout<<s12.append(aString,1,3)<<std::endl;//append "the"
  std::cout<<s12.append(aString,2,std::string::npos)<<std::endl;//append "hello"

  std::cout<<s12.append("two\nlines")<<std::endl;//append C-string (equivalent to operator +=)
  std::cout<<s12.append("nico",5)<<std::endl;//append character array: 'n' 'i' 'c' 'o' '\0'
  std::cout<<s12.length()<<std::endl;

  std::cout<<s12.append(5,'x')<<std::endl;//append five characters: 'x' 'x' 'x' 'x' 'x'

 s12.push_back('\n');//append single character (equivalent to operator +=)
 std::cout<<s12<<std::endl;

 const std::string bString("age");
 std::string s13("p");

 std::cout<<s13.insert(1,bString)<<std::endl;//s13: page
 std::cout<<s13.insert(1,"ersifl")<<std::endl;//s13: persiflage

 //std::cout<<s13.insert(0,' ')<<std::endl;//ERROR
 std::cout<<s13.insert(0," ")<<std::endl;//OK
 std::cout<<s13.insert(0,1,' ')<<std::endl;//ERROR: ambiguous,BUT IT IS WORK!

 //insert(size_type idx,size_type num,charT c);//position is index
 //insert(iterator pos,size_type num,charT c);//position is iterator























  return 0;
}
