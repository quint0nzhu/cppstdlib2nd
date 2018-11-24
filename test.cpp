/*
  author: Quinton
  date: 2018-11-20
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 13
*/



#include <iostream>
#include <string>
#include <sstream> //for std::stringstream()
#include <limits>
#include <exception>
#include <algorithm>
#include <cctype> //for toupper()
#include <regex>
#include <locale>



void f(const char* s,int n)
{
  std::cout<<s<<std::endl;
  std::cout<<"length: "<<n<<std::endl;
}

std::string foo()
{
  std::string s1("international");
  std::string s2("ization");

  std::string s=std::move(s1)+std::move(s2);//OK
  //s1 and s2 have valid state with unspecified value

  return s;
}

void process(const std::string& filecontents)
{
  //process first line of passed string:
  std::string firstLine;
  std::getline(std::stringstream(filecontents),//OK since C++11
               firstLine);
  std::cout<<firstLine<<std::endl;
}

//replace functions of the standard char_traits<char>
//so that strings behave in a case-insensitive way
struct ignorecase_traits:public std::char_traits<char>{
  //return whether c1 and c2 are equal
  static bool eq(const char& c1,const char& c2){
    return std::toupper(c1)==std::toupper(c2);
  }
  //return whether c1 is less than c2
  static bool lt(const char& c1,const char& c2){
    return std::toupper(c1)<std::toupper(c2);
  }
  //compare up to n characters of s1 and s2
  static int compare(const char* s1,const char* s2,
                     std::size_t n){
    for(std::size_t i=0;i<n;++i){
      if(!eq(s1[i],s2[i])){
        return lt(s1[i],s2[i])?-1:1;
      }
    }
    return 0;
  }
  //search c in s
  static const char* find(const char* s,std::size_t n,
                          const char& c){
    for(std::size_t i=0;i<n;++i){
      if(eq(s[i],c)){
        return &(s[i]);
      }
    }
    return 0;
  }
};

//define a special type for such strings
typedef std::basic_string<char,ignorecase_traits> icstring;

//define an output operator
//because the traits type is different from that for std::ostream
inline
std::ostream& operator<<(std::ostream& strm,const icstring& s)
{
  //simply convert the icstring into a normal string
  return strm<<std::string(s.data(),s.length());
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
 //s.insert((std::string::size_type)0,1,' ');//OK

 std::string s14="i18n";//s14:i18n
 std::cout<<s14.replace(1,2,"nternationalizatio")<<std::endl;//s14:internationalization
 std::cout<<s14.erase(13)<<std::endl;//s14:international
 std::cout<<s14.erase(7,5)<<std::endl;//s14:internal
 s14.pop_back();//s14:interna(since C++11)
 std::cout<<s14<<std::endl;
 std::cout<<s14.replace(0,2,"ex")<<std::endl;//s14:externa

 //13.2.9 子字符串(Substring)及字符串接合(String Concatenation)

 std::string s15("interchangeability");

 std::cout<<s15.substr()<<std::endl;//returns a copy of s15
 std::cout<<s15.substr(11)<<std::endl;//returns string("ability")
 std::cout<<s15.substr(5,6)<<std::endl;//returns string("change")
 std::cout<<s15.substr(s15.find('c'))<<std::endl;//returns string("changeability")

 std::string s16("enter");
 std::string s17("nation");
 std::string i18n;

 i18n='i'+s16.substr(1)+s17+"aliz"+s17.substr(1);
 std::cout<<"i18n means: "+i18n<<std::endl;

 std::cout<<foo()<<std::endl;

 //13.2.10 I/O操作符

 //while(getline(cin,s))//for each line read from cin
 //while(getline(cin,s,':'))//for each token separated by ':'

 process("first line\nsecond line");

 //13.2.11 搜索和查找(Searching and Finding)

 std::string s18("Hi Bill, I'm ill, so please pay the bill");

 std::cout<<s18.find("il")<<std::endl;//returns 4(first substring "il")
 std::cout<<s18.find("il",10)<<std::endl;//returns 13(first substring "il" starting from s18[10])
 std::cout<<s18.rfind("il")<<std::endl;//returns 37(last substring "il")
 std::cout<<s18.find_first_of("il")<<std::endl;//returns 1(first char 'i' or 'l')
 std::cout<<s18.find_last_of("il")<<std::endl;//returns 39)(last char 'i' or 'l')
 std::cout<<s18.find_first_not_of("il")<<std::endl;//returns 0(first char neither 'i' nor 'l')
 std::cout<<s18.find_last_not_of("il")<<std::endl;//returns 36(last char neither 'i' nor 'l')
 std::cout<<(s18.find("hi")==std::string::npos?true:false)<<std::endl;//returns npos

 //13.2.12 npos的意义

 std::string s19;
 std::string::size_type idx;//be careful: don't use any other type!

 idx=s19.find("substring");
 if(idx==std::string::npos){
   std::cout<<"not found!"<<std::endl;
 }

 //int idx=s.find("not found");//assume it returns npos
 //if(idx==std::string::npos){}//ERROR: comparison might not work

 //const int NPOS=-1;
 //if(idx==NPOS){}//works almost always

 //13.2.13 数值转换(Numeric Conversion)

 try{
   //convert to numeric type
   std::cout<<std::stoi("   77")<<std::endl;
   std::cout<<std::stod("   77.7")<<std::endl;
   std::cout<<std::stoi("-0x77")<<std::endl;

   //use index of characters not processed
   std::size_t idx1;

   std::cout<<std::stoi("  42 is the truth",&idx1)<<std::endl;
   std::cout<<" idx of first unprocessed char: "<<idx1<<std::endl;

   //use bases 16 and 8
   std::cout<<std::stoi("  42",nullptr,16)<<std::endl;
   std::cout<<std::stol("789",&idx1,8)<<std::endl;
   std::cout<<" idx of first unprocessed char: "<<idx1<<std::endl;

   //convert numeric value to string
   long long ll=std::numeric_limits<long long>::max();
   std::string s19=std::to_string(ll);//converts maximum long long to string
   std::cout<<s19<<std::endl;

   //try to convert back
   std::cout<<std::stoi(s19)<<std::endl;//throws out_of_range
 }
 catch(const std::exception& e){
   std::cout<<e.what()<<std::endl;
 }

 //13.2.14 String对迭代器的支持

 //create a string
 std::string s20("The zip code of Braunschweig in Germany is 38100");
 std::cout<<"original: "<<s20<<std::endl;

 //lowercase all characters
 transform(s20.cbegin(),s20.cend(),//source
           s20.begin(),//destination
           [](char c){//operation
             return tolower(c);
           });
 std::cout<<"lowered: "<<s20<<std::endl;

 //uppercase all characters
 transform(s20.cbegin(),s20.cend(),//source
           s20.begin(),//destination
           [](char c){//operation
             return toupper(c);
           });
 std::cout<<"uppered: "<<s20<<std::endl;

 //search case-insensitive for Germany
 std::string g("Germany");
 std::string::const_iterator pos;
 pos=search(s20.cbegin(),s20.cend(),//source string in which to search
            g.cbegin(),g.cend(),//substring to search
            [](char c1,char c2){//comparison criterion
              return toupper(c1)==toupper(c2);
            });
 if(pos!=s20.cend()){
   std::cout<<"substring \""<<g<<"\" found at index "
            <<pos-s20.cbegin()<<std::endl;
 }

 //search case-insensitive for Germany
 std::regex pat("Germany",//expression to search for
                std::regex_constants::icase);//search case-insensitive
 std::smatch m;
 if(regex_search(s20,m,pat)){//search regex pattern in s
   std::cout<<"substring \"Germany\" found at index "
            <<m.position()<<std::endl;
 }

 //create constant string
 const std::string hello("Hello, how are you?");

 //initialize string s21 with all characters of string hello
 std::string s21(hello.cbegin(),hello.cend());

 //ranged-based for loop that iterates through all the characters
 for(char c:s21){
   std::cout<<c;
 }
 std::cout<<std::endl;

 //reverse the order of all characters inside the string
 reverse(s21.begin(),s21.end());
 std::cout<<"reverse:        "<<s21<<std::endl;

 //sort all characters inside the string
 sort(s21.begin(),s21.end());
 std::cout<<"ordered:        "<<s21<<std::endl;

 //remove adjacent duplicates
 //-unique() reorders and returns new end
 //-erase() shrinks accordingly
 s21.erase(unique(s21.begin(),
                  s21.end()),
           s21.end());
 std::cout<<"no duplicates:  "<<s21<<std::endl;

 std::string input;

 //don't skip leading whitespaces
 std::cin.unsetf(std::ios::skipws);

 //read all characters while compressing whitespaces
 const std::locale& loc(std::cin.getloc());//locale
 unique_copy(std::istream_iterator<char>(std::cin),//beginning of source
             std::istream_iterator<char>(),//end of source
             back_inserter(input),//destination
             [=](char c1,char c2){//criterion for adj.duplicates
               return isspace(c1,loc)&&isspace(c2,loc);
             });

 //process input
 //-here: write it to the standard output
 std::cout<<input<<std::endl;

 //13.2.15 国际化(Internationalization)

 icstring s22("hallo");
 icstring s23("otto");
 icstring s24("hAllo");

 std::cout<<std::boolalpha;
 std::cout<<s22<<" == "<<s23<<" : "<<(s22==s23)<<std::endl;
 std::cout<<s22<<" == "<<s24<<" : "<<(s22==s24)<<std::endl;

 icstring::size_type idx2=s22.find("All");
 if(idx2!=icstring::npos){
   std::cout<<"index of \"All\" in \""<<s22<<"\": "
            <<idx2<<std::endl;
 }
 else{
   std::cout<<"\"All\" not found in \""<<s22<<std::endl;
 }

 //13.2.16 效率(Performance)
 //13.2.17 String和Vector

 //13.3 细究String Class
 //13.3.1 类型定义和静态值

 //string::traits_type
 //Character trait的类型
 //basic_string的第二个template参数
 //对类型string而言，这等价于char_traits<char>

 //string::value_type
 //字符类型
 //等价于traits_type::char_type
 //对类型string而言，这等价于char

 //string::size_type
 //未带正负号的整数类型，用来指定大小值和索引
 //等价于allocator_type::size_type
 //对类型string而言，这等价于size_t

 //string::difference_type
 //带正负号的整数类型，用来指定差值（距离）
 //等价于allocator_type::difference_type
 //对类型string而言，这等价于ptrdiff_t

 //string::reference
 //字符的reference类型
 //等价于allocator_type::reference
 //对类型string而言，这等价于char&

 //string::const_reference
 //常量型的字符的reference类型
 //等价于allocator_type::const_reference
 //对类型string而言，这等价于const char&

 //string::pointer
 //字符的pointer类型
 //等价于allocator_type::pointer
 //对类型string而言，这等价于char*

 //string::const_pointer
 //常量型的字符pointer类型
 //等价于allocator_type::const_pointer
 //对类型string而言，这等价于const char*

 //string::iterator
 //Iterator（迭代器）类型
 //确切类型由实现定义
 //对类型string而言通常是char*

 //string::const_iterator
 //常量型iterator(迭代器)类型
 //确切类型由实现定义
 //对类型string而言通常是const char*

 //string::reverse_iterator
 //Reverse iterator（反向迭代器）类型
 //等价于reverse_iterator<iterator>

 //string::const_reverse_iterator
 //Constant reverse iterator（常量型反向迭代器）类型
 //等价于reverse_iterator<const_iterator>

 //static const size_type string::npos
 //这是一个特殊值，表示未找到或所有剩余字符
 //它是个无正负号整数，初值为-1
 //使用npos时要十分小心

 //13.3.2 创建、复制、销毁(Create,Copy,and Destroy)

 //string::string()
 //Default构造函数
 //建立一个空的string

 //string::string(const string& str)
 //Copy（拷贝）构造函数
 //建立一个新的string，是str的拷贝（副本）

 //string::string(string&& str)
 //Move（搬移）构造函数
 //建立一个新的string，以既有的string str的元素为初值
 //执行之后，str的内容不明确
 //始自C++11

 //string::string(const string& str,size_type str_idx)
 //string::string(const string& str,size_type str_idx,size_type str_num)
 //建立一个新string，其初值为“str之内从索引str_idx开始的最多str_num个字符”
 //如果没有指定str_num，则取“从str_idx开始到str末尾”的所有字符
 //如果str_idx>str.size(),抛出out_of_range异常

 //string::string(const char* cstr)
 //建立一个string，以C-string cstr为初值
 //初值为cstr内“以'\0'为结束符（但不包括'\0'）”的所有字符
 //cstr不可以是null pointer(nullptr或NULL)，否则会导致不确定的行为
 //如果所得结果超出最大字符数，抛出length_error异常

 //string::string(const char* chars,size_type chars_len)
 //建立一个string，以字符数组chars内的chars_len个字符为初值
 //chars必须至少包含chars_len个字符。这些字符可以为任意值，'\0'无特殊意义
 //如果chars_len等于string::npos，抛出length_error异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string::string(size_type num,char c)
 //建立一个string，初值为num个字符c
 //如果num等于string::npos，抛出length_error异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string::string(InputIterator beg,InputIterator end)
 //建立一个字符串，以[beg,end)区间内的字符为初值
 //如果所得结果超出最大字符数，抛出length_error异常

 //string::string(initializer-list)
 //建立一个新的string，以initializer-list的字符为初值
 //始自C++11
 //如果所得结果超出最大字符数，抛出length_error异常

 //string::~string()
 //析构函数
 //销毁所有字符并释放内存

 //13.3.3 大小和容量(Size and Capacity)

 //bool string::empty()const
 //判断string是否为空（不含任何字符）
 //等价于string::size()==0，但有可能更快

 //size_type string::size()const
 //size_type string::length()const
 //两个函数都返回现有的字符数
 //两者等价(equivalent)
 //如果想检查string是否为空，应采用速度更快的empty()

 //size_type string::max_size()const
 //返回“字符串可含之最多字符数”
 //任何操作一旦生成的string长度大于max_size()，就会抛出length_error异常

 //size_type string::capacity()const
 //返回重分配之前string所能包含的最多字符数

 //void string::reserve()
 //void string::reserve(size_type num)
 //第一形式是个“非强制性合身缩减”请求(nonbinding shrink-to-fit request)
 //第二形式保留“至少能容纳num个字符”的内存
 //如果num小于当前容量，这一调用相当于一个“非强制性缩减容量”请求(nonbinding request to shrink the capacity)
 //如果num小于当前字符数，这一调用相当于一个“非强制性缩减容量”请求，希望能够令容量吻合当前字符数
 //容量永远不能小于实际字符数
 //这个操作有可能造成“指向string所含字符”之reference、pointer和iterator失效。然而可以保证的是，在调用reserve()之后的安插过程中不会发生重分配，直到某次安插造成大小超过num。因此，我们可事先调用reserve()来加快速度并保持reference、pointer和iterator的有效性

 //void string::shrink_to_fit()
 //降低内部内存，以符合当前字符数
 //其效果相当于reserve(0)
 //这一调用被视为一个非强性请求(nonbinding request)，允许实现方有优化余地
 //这个操作有可能造成“指向string所含字符”的reference、pointer和iterator失效
 //始自C++11

 //13.3.4 比较(Comparison)

 //bool comparison(const string& str1,const string& str2)
 //bool comparison(const string& str,const char* cstr)
 //bool comparison(const char* cstr,const string& str)
 //第一形式返回两个string的比较结果
 //第二形式和第三形式返回string和C-string的比较结果
 //comparison可以是以下任何一种动作：
 // operator ==
 // operator !=
 // operator <
 // operator >
 // operator <=
 // operator >=
 //按字典次序(lexicographically)进行比较

 //int string::compare(const string& str)const
 //把string *this拿来和string str比较
 //返回值：
 //-0，表示两端strings相等
 //-<0，表示*this小于str（按字典次序）
 //->0，表示*this大于str（按字典次序）
 //以traits::compare()为比较准则

 //int string::compare(size_type idx,size_type len,const string& str)const
 //将string *this之内“从idx开始的最多len个字符”拿来和str比较
 //如果idx>size()，抛出out_of_range异常
 //比较动作和前述的compare(str)相同

 //int string::compare(size_type idx,size_type len,const string& str,size_type str_idx,size_type str_len)const
 //将string *this内“从idx开始的最多len个字符”拿来和str之内“从str_idx开始的最多str_len个字符”相较
 //如果idx>size()，抛出out_of_range异常
 //如果str_idx>str.size()，抛出out_of_range异常
 //比较动作和前述的compare(str)相同

 //int string::compare(const char* cstr)const
 //将string *this的字符和C-string cstr的字符进行比较
 //比较动作和前述的compare(str)相同

 //int string::compare(size_type idx,size_type len,const char* cstr)const
 //将string *this内“从idx开始最多len个字符”和C-string cstr的所有字符比较
 //比较动作和前述的compare(str)相同
 //cstr不可以是null pointer（nullptr或NULL），否则会导致不确定的行为

 //int string::compare(size_type idx,size_type len,const char* chars,size_type chars_len)const
 //将string *this内“从idx开始最多len个字符”拿来和字符数组chars内的chars_len个字符相较
 //比较动作和前述的compare(str)相同
 //chars必须至少包含chars_len个字符。这些字符可以为任意值，'\0'无特殊意义
 //如果chars_len等于string::npos，抛出length_error异常

 //13.3.5 字符访问

 //char& string::operator[](size_type idx)
 //const char& string::operator[](size_type idx)const
 //两种形式都返回索引idx所指的字符（首字符索引为0）
 //length()和size()都是有效索引，本操作符会对此返回一个“由字符类型的default构造函数生成”的值（对string而言是'\0'）。在C++11之前，non-const string的length()或size()都是无效索引
 //无效索引会导致不明确的行为
 //操作non-const string时，返回的reference会因为string被改动或重分配而失效
 //如果调用者无法确定索引有否有效，就应该采用at()

 //char& string::at(size_type idx)
 //const char& string::at(size_type idx)const
 //两种形式都返回索引idx所指的字符（首字符索引为0）
 //对于所有string，以length()的结果为索引，都是无效的
 //传递无效索引（小于0或大于等于length()或size()）会导致out_of_range异常
 //操作non-const string时，返回的reference会因为string被改动或重分配而失效
 //如果调用者确定索引是有效的，可改用操作符[]，速度更快

 //char& string::front()
 //const char& string::front()const
 //两种形式都返回第一个字符
 //对string调用front()，会返回一个“由字符类型的default构造函数生成”的值（对string而言是'\0'）
 //操作non-const string时，返回的reference会因为string被改动或重分配而失效

 //char& string::back()
 //const char& string::back()const
 //两种形式都返回最末字符
 //对空string调用back()，会导致不明确的行为
 //操作non-const string时，返回的reference会因为string被改动或重分配而失效

 //13.3.6 产生C-String和字符数组(Character Array)

 //const char* string::c_str()const
 //const char* string::data()const
 //将string的内容以C-string（一个字符数组，尾部添加'\0'）形式返回。因此这可说是string对应的一个有效的C-string
 //返回值隶属于该string，所以调用者不能修改、释放或删除该返回值
 //只有当string尚且存在，并且用来处理该返回值的函数是个“常量型函数”时，这个返回值才保持有效
 //在C++11之前，data()的返回值保证内含string的所有字符但没有结束符'\0'，因此不能说是个有效的C-string

 //size_type string::copy(char* buf,size_type buf_size)const
 //size_type string::copy(char* buf,size_type buf_size,size_type idx)const
 //两种形式都将string *this内从索引idxgavc最多buf_size个字符复制到字符数组buf中
 //返回被复制的字符数
 //不添加null字符。因此函数执行后的buf内容可能不是个有效的C-string
 //调用者必须确保buf有足够内存；否则会导致不明确的行为
 //如果idx>size()，抛出out_of_range异常

 //13.3.7 ”改动“之相关操作(Modifying Operation)

 //string& string::operator=(const string& str)
 //string& string::assign(const string& str)
 //所谓copy assignment（拷贝赋值）操作符
 //以上两种形式都将str的内容赋值给*this
 //都返回*this

 //string& string::operator=(string&& str)
 //string& string::assign(string&& str)
 //所谓的move assignment（搬移赋值）操作符
 //将str的内容搬移至*this
 //完成后，str的内容不可知（不明确）
 //返回*this
 //始自C++11

 //string& string::assign(const string& str,size_type str_idx,size_type str_num)
 //将str内”从索引str_idx开始最多str_num个字符“赋值给*this
 //返回*this
 //如果str_idx>str.size()，抛出out_of_range异常

 //string& string::operator=(const char* cstr)
 //string& string::assign(const char* cstr)
 //两种形式都将C-string cstr的内容赋值给*this
 //它们操作的是以'\0'结尾的cstr所有字符，但不包含'\0'
 //都返回*this
 //cstr不可以是null pointer（nullptr或NULL），否则会导致不确定的行为
 //如果所得结果超出最大字符数，两函数都抛出length_error异常

 //string& string::assign(const char* chars,size_type chars_len)
 //将数组chars内的chars_len个字符赋值给*this
 //返回*this
 //chars必须至少包含chars_len个字符。这些字符可以为任意值，'\0'无特殊意义
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::operator=(char c)
 //将字符c赋值给*this
 //返回*this
 //调用后，*this只含这个单一字符

 //string& string::assign(size_type num,char c)
 //将num个字符c赋值给*this
 //返回*this
 //如果num等于string::npos，抛出length_error异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::assign(InputIterator beg,InputIterator end)
 //赋值的来源是[beg,end)区间内的所有字符
 //返回*this
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::operator=(initializer-list)
 //string& string::assign(initializer-list)
 //赋值的来源是initializer-list内的所有字符
 //都返回*this
 //如果所得结果超出最大字符数，两operations都抛出length_error异常
 //始自C++11

 //void string::swap(string& str)
 //void swap(string& str1,string& str2)
 //两种形式都用来交换string。第一版本（成员函数）交换*this和str的内容。第二版本（全局函数）交换str1和str2的内容
 //应该尽可能使用这些函数取代赋值(assignment)，因为它们更快。它们具有常量复杂度

 //string& string::operator+=(const string& str)
 //string& string::append(const string& str)
 //两种形式都将str的字符添加到*this尾部
 //都返回*this
 //如果所得结果超出最大字符数，两者都抛出length_error异常

 //string& string::append(const string& str,size_type str_idx,size_type str_num)
 //将str内”从str_idx开始最长str_num个字符“添加到*this末尾
 //返回*this
 //如果str_idx>str.size()，抛出out_of_range异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::operator+=(const char* cstr)
 //string& string::append(const char* cstr)
 //都将C-string的字符添加到*this末尾
 //都返回*this
 //cstr不可以是null pointer（nullptr或NULL），否则会导致不确定的行为
 //如果所得结果超出最大字符数，两者都抛出length_error异常

 //string& string::append(const char* chars,size_type chars_len)
 //将字符数组chars内的chars_len个字符添加到*this末尾
 //返回*this
 //chars必须至少包含chars_len个字符。这些字符可以为任意值，'\0'无特殊意义
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::append(size_type num,char c)
 //将num个字符c添加到*this尾部
 //返回*this
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::operator+=(char c)
 //void string::push_back(char c)
 //将字符c添加到*this尾部
 //Operator+=返回*this
 //如果所得结果超出最大字符数，两者都抛出length_error异常

 //string& string::append(InputIterator beg,InputIterator end)
 //将[beg,end)区间内的所有字符添加到*this尾部
 //返回*this
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::operator+=(initializer-list)
 //void string::append(initializer-list)
 //都将initializer-list的字符添加到*this末尾
 //都返回*this
 //如果所得结果超出最大字符数，两者都抛出length_error异常
 //始自C++11

 //string& string::insert(size_type idx,const string& str)
 //将str插入*this内，从索引idx处开始安插新增字符
 //返回*this
 //如果idx>size()，抛出out_of_range异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::insert(size_type idx,const string& str,size_type str_idx,size_type str_num)
 //将str内”从str_idx开始最多str_num个字符“插入*this，从索引idx处开始安插
 //返回*this
 //如果idx>size()，抛出out_of_range异常
 //如果str_idx>str.size()，抛出out_of_range异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::insert(size_type idx,const char* cstr)
 //将C-string cstr插入*this，从索引idx处开始安插新增字符
 //返回*this
 //cstr不可以是null pointer（nullptr或NULL），否则会导致不确定的行为
 //如果idx>size()，抛出out_of_range异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::insert(size_type idx,const char* chars,size_type chars_len)
 //将字符数组chars内的chars_len个字符插入*this，从索引idx处开始安插新增字符
 //返回*this
 //chars必须至少包含chars_len个字符。这些字符可以为任意值，'\0'无特殊意义
 //如果idx>size()，抛出out_of_range异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::insert(size_type idx,size_type num,char c)
 //iterator string::insert(const_iterator pos,size_type num,char c)
 //分别在idx或pos指定的位置上安插num个字符c
 //第一形式将新字符插入str，从索引idx开始
 //第二形式在iterator pos所指字符之前方插入新字符
 //第一形式返回*this
 //第二形式返回被安插的第一个字符的位置，如果没有安插任何字符就返回pos
 //这两个函数构成重载(overloaded)形式，因此可能导致歧义（模棱两可）。如果你以0为第一实参，由于0可被视为索引（通常被转换为unsigned），也可被视为iterator（通常被转换为char*），因而导致岐义。这种情况下你应该明确告知实参是个”索引“。例如
 //std::string s;
 //...;
 //s.insert(0,1,' ');//ERROR: ambiguous
 //s.insert((std::string::size_type)0,1,' ');//OK
 //如果idx>size()，两种形式都抛出out_of_range异常
 //如果最终结果超出最大字符数，抛出length_error异常
 //在C++11之前，pos的类型是iterator，第二形式的返回类型是void

 //iterator string::insert(const_iterator pos,char c)
 //在iterator pos所指字符之前方插入字符c的拷贝（副本）
 //返回新被插入的字符的位置
 //如果所得结果超出最大字符数，抛出length_error异常
 //在C++11之前，pos的类型是iterator

 //iterator string::insert(const_iterator pos,InputIterator beg,InputIterator end)
 //在iterator pos所指字符之前方插入[beg,end)区间的所有字符
 //返回被安插的第一个字符的位置，如果没有安插任何字符就返回pos
 //如果所得结果超出最大字符数，抛出length_error异常
 //在C++11之前，pos的类型是iterator，返回类型是void

 //iterator string::insert(const_interator pos,initializer-list)
 //在iterator pos所指字符之前方插入initializer-list的所有字符
 //返回被安插的第一个字符的位置，如果没有安插任何字任就返回pos
 //如果所得结果超出最大字符数，抛出length_error异常

 //void string::clear()
 //string& string::erase()
 //两个函数都会删除(delete)string内的所有字符，因此调用后string成空
 //erase()返回*this

 //string& string::erase(size_type idx)
 //string& string::erase(size_type idx,size_type len)
 //两种形式都删除*this之内从索引idx开始的最多len个字符
 //都返回*this
 //如果未指定len，则删除idx之后的所有字符
 //如果idx>size()，两种形式都抛出out_of_range异常

 //iterator string::erase(const_iterator pos)
 //iterator string::erase(const_iterator beg,const_iterator end)
 //分别删除pos所指的单一字符或[beg,end)区间内的所有字符
 //都返回最后一个被删除字符的下一字符（因此第二形式返回的是end）
 //在C++11之前，pos、beg和end的类型都是iterator

 //void string::pop_back()
 //删除最末字符
 //对空string调用此函数，会导致不明确的行为
 //始自C++11

 //void string::resize(size_type num)
 //void string::resize(size_type num,char c)
 //两种形式都将*this的字符数改为num。也就是说，如果num不等于目前的size()，则在尾部添加或删除足够字符，使字符数等于新的大小num
 //如果字符数增加，则以c为初值。如果未指定c，则使用“字符类型”的default构造函数为新字符设初值（对string而言将是'\0'）
 //如果num等于string::npos，两者都抛出length_error异常
 //如果最终结果超出最大字符数，抛出length_error异常

 //string& string::replace(size_type idx,size_type len,const string& str)
 //string& string::replace(begin_iterator beg,begin_iterator end,const string& str)
 //第一种形式将*this内"从idx开始，最长为len"的字符替换为str内的所有字符
 //第二种形式将[beg,end)区间内的字符替换为str的所有字符
 //返回*this
 //如果idx>size()，两种形式都抛出out_of_range异常
 //如果最终结果超出最大字符数，抛出length_error异常
 //在C++11之前，beg和end的类型是iterator

 //string& string::replace(size_type idx,size_type len,const string& str,size_type str_idx,size_type str_num)
 //将*this内“从idx开始，最长为len“的字符替换为str内”从str_idx开始，最长为str_num“的所有字符
 //返回*this
 //如果idx>size()，抛出out_of_range异常
 //如果str_idx>str.size()，抛出out_of_range异常
 //如果所得结果超出最大字符数，抛出length_error异常

 //string& string::replace(size_type idx,size_type len,const char* cstr)
 //string& string::replace(const_iterator beg,const_iterator end,const char* cstr)
 //分别将*this中”以idx开始，最长为len“的字符，或[beg,end)区间内的字符替换为C-string cstr的所有字符
 //都返回*this
 //cstr不可以是null pointer（nullptr或NULL），否则会导致不确定的行为
 //如果idx>size()，两种形式都抛出out_of_range异常
 //如果最终结果超出最大字符数，抛出length_error异常
 //在C++11之前，beg和end的类型是iterator

 //string& string::replace(size_type idx,size_type len,const char* chars,size_type chars_len)
 //string& string::replace(const_iterator beg,const_iterator end,const char* chars,size_type chars_len)
 //分别将*this中”以idx开始，最长为len“的字符或[beg,end)区间内的字符，替换为字符数组chars中的chars_len个字符
 //都返回*this
 //chars必须至少包含chars_len个字符。这些字符可以为任意值，'\0'无特殊意义
 //如果idx>size()，两种形式都抛出out_of_range异常
 //如果最终结果超出最大字符数，抛出length_error异常
 //在C++11之前，beg和end的类型是iterator

 //string& string::replace(size_type idx,size_type len,size_type num,char c)
 //string& string::replace(const_iterator beg,const_iterator end,size_type num,char c)
 //分别将*this内”从idx开始，最长为len“的字符，或[beg,end)区间内的字符，替换为num个字符c
 //都返回*this
 //如果idx>size()，两种形式都抛出out_of_range异常
 //如果最终结果超出最大字符数，抛出length_error异常
 //在C++11之前，beg和end的类型是iterator

 //string& string::replace(const_iterator beg,const_iterator end,InputIterator newBeg,InputIterator newEnd)
 //以[newBeg,newEnd)区间内的所有字符替换[beg,end)区间内的所有字符
 //返回*this
 //如果所得结果超出最大字符数，抛出length_error异常
 //在C++11之前，beg和end的类型是iterator

 //string& string::replace(const_iterator beg,const_iterator end,initializer-list)
 //以initializer-list内的所有字符替换[beg,end)区间内的所有字符
 //返回*this
 //如果所得结果超出最大字符数，抛出length_error异常
 //始自C++11

 //13.3.8 查找(Searching and Finding)

 //



 return 0;
}
