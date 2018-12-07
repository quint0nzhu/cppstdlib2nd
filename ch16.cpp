/*
  author: Quinton
  date: 2018-12-4
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 16
*/


#include <iostream>
#include <locale>
#include <exception>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <typeinfo>
#include <codecvt>


class germanBoolNames:public std::numpunct_byname<char>{
public:
  germanBoolNames(const std::string& name):std::numpunct_byname<char>(name){}

protected:
  virtual std::string do_truename()const{
    return "wahr";
  }
  virtual std::string do_falsename()const{
    return "falsch";
  }
};

//output operator for pos_format() and neg_format():
std::ostream& operator<<(std::ostream& strm,std::moneypunct<char>::pattern p)
{
  for(int i=0;i<4;++i){
    auto f=p.field[i];
    strm<<(f==std::money_base::none?"none":
           f==std::money_base::space?"space":
           f==std::money_base::symbol?"symbol":
           f==std::money_base::sign?"sign":
           f==std::money_base::value?"value":
           "???")<<" ";
  }
  return strm;
}

template<bool intl>
void printMoneyPunct(const std::string& localeName)
{
  std::locale loc(localeName);
  const std::moneypunct<char,intl>& mp
    =std::use_facet<std::moneypunct<char,intl>>(loc);
  std::cout<<"moneypunct in locale \""<<loc.name()<<"\":"<<std::endl;
  std::cout<<" decimal_point: "<<(mp.decimal_point()!='\0'?
                                  mp.decimal_point():' ')<<std::endl;
  std::cout<<" thousands_sep: "<<(mp.thousands_sep()!='\0'?
                                  mp.thousands_sep():' ')<<std::endl;
  std::cout<<" grouping:      ";

  for(int i=0;i<mp.grouping().size();++i){
    std::cout<<static_cast<int>(mp.grouping()[i])<<' ';
  }
  std::cout<<std::endl;
  std::cout<<" curr_symbol:   "<<mp.curr_symbol()<<std::endl;
  std::cout<<" positive_sign: "<<mp.positive_sign()<<std::endl;
  std::cout<<" negative_sign: "<<mp.negative_sign()<<std::endl;
  std::cout<<" frac_digits:   "<<mp.frac_digits()<<std::endl;
  std::cout<<" pos_format:    "<<mp.pos_format()<<std::endl;
  std::cout<<" neg_format:    "<<mp.neg_format()<<std::endl;
}

//convert string to wstring
std::wstring to_wstring(const std::string& str,
                        const std::locale& loc=std::locale())
{
  std::vector<wchar_t> buf(str.size());
  std::use_facet<std::ctype<wchar_t>>(loc).widen(str.data(),
                                                 str.data()+str.size(),
                                                 buf.data());
  return std::wstring(buf.data(),buf.size());
}

//convert wstring to string with '?' as default character
std::string to_string(const std::wstring& str,
                      const std::locale& loc=std::locale())
{
  std::vector<char> buf(str.size());
  std::use_facet<std::ctype<wchar_t>>(loc).narrow(str.data(),
                                                  str.data()+str.size(),
                                                  '?',buf.data());
  return std::string(buf.data(),buf.size());
}

//convert UTF-8 string to wstring
std::wstring utf8_to_wstring(const std::string& str)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
  return myconv.from_bytes(str);
}

//convert wstring to UTF-8 string
std::string wstring_to_utf8(const std::wstring& str)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
  return myconv.to_bytes(str);
}



int main(int argc, char* argv[])
{
  //第16章 国际化
  //16.1 字符编码和字符集
  //16.1.1 多字节(Multibyte)和宽字符(Wide-Character)文本
  //16.1.2 不同的字符集
  //16.1.3 在C++中处理字符集
  //16.1.4 Character Trait
  //16.1.5 特殊字符的国际化

  //strm.widen('\n');//internationalized newline character
  //strm.widen('\0');//internationalized string-termination character
  //std::use_facet<std::ctype<charType>>(loc).widen(c);

  //16.2 Locale（地域）概念
  //16.2.1 使用Locale

  try{
    //use classic C locale to read data from standard input
    std::cin.imbue(std::locale::classic());//OR std::locale("C"), use global locale(classic C locale by default)
    //std::cin.imbue(std::locale(""));//use native locale according to the environment

    //use a German locale to write data to standard output
    //-use different locale names for Windows an POSIX
    #ifdef _MSC_VER
    std::cout.imbue(std::locale("deu_deu.1252"));
    #else
    std::cout.imbue(std::locale("de_DE"));
    #endif

    //read and output floating-point values in a loop
    std::cout<<"input floating-point values(classic notation): "<<std::endl;
    double value;
    while(std::cin>>value){
      std::cout<<value<<std::endl;
    }
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  std::cout.clear();
  std::cin.clear();

  try{
    //create the default locale from the user's environment
    std::locale langLocale("");

    //and assign it to the standard output channel
    std::cout.imbue(langLocale);

    //process the name of the locale to find out whether German is used
    std::cout<<langLocale.name()<<std::endl;
    bool isGerman=(langLocale.name().substr(0,2)=="de"||
                   langLocale.name().substr(0,3)=="ger"||
                   langLocale.name().substr(0,3)=="Ger");

    //read locale for the input
    std::cout<<(isGerman?"Sprachumgebung fuer Eingaben: "
                :"Locale for input: ")<<std::endl;

    std::string s;
    std::cin>>s;
    if(!std::cin){
      if(isGerman){
        std::cerr<<"FEHLER beim Einlesen der Sprachumgebung"<<std::endl;
      }
      else{
        std::cerr<<"ERROR while reading the locale"<<std::endl;
      }
      return EXIT_FAILURE;
    }
    std::locale cinLocale(s);//create locale by string(since C++ 11)
    //std::locale cinLocale(s.c_str());//create locale by string before C++ 11

    //and assign it to the standard input channel
    std::cin.imbue(cinLocale);

    //read and output floating-point values in a loop
    std::cout<<(isGerman?"Gleitkommawerte: "
                :"Floating-point values: ")<<std::endl;
    double value;
    while(std::cin>>value){
      std::cout<<value<<std::endl;
    }
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  //create a locale object depending on the program's environment and
  //set it as the global object
  std::locale::global(std::locale(""));
  std::setlocale(LC_ALL,"");

  //register global locale object for streams
  std::cin.imbue(std::locale());
  std::cout.imbue(std::locale());
  std::cerr.imbue(std::locale());

  //16.2.2 Locale Facet

  std::cout<<std::use_facet<std::numpunct<char>>(std::cout.getloc()).truename()<<std::endl;

  //const std::numpunct<char>& fac=std::use_facet<std::numpunct<char>>(std::locale("de"));
  //std::cout<<"true in German: "<<fac.truename()<<std::endl;//ERROR

  std::locale loc(std::locale(""),new germanBoolNames(""));
  std::cout.imbue(loc);
  std::cout<<std::boolalpha<<true<<std::endl;

  std::cout.clear();

  //16.3 细究Locale

  std::vector<std::string> v={"cd","ab"};

  //sort strings according to the German locale
  std::sort(v.begin(),v.end(),//range
            std::locale("de_DE"));//sorting criterion

  for(const auto& e:v){
    std::cout<<e<<' ';
  }
  std::cout<<std::endl;

  //16.4 细究Facet

  //std::numpunct_byname("de_DE")

  //16.4.1 数值格式化(Numeric Formatting)

  std::cout.clear();

  try{
    //print floating-point value with the global classic locale:
    std::locale locC;
    std::cout.imbue(locC);
    std::use_facet<std::num_put<char>>(locC).put(std::cout,std::cout,' ',
                                                 1234.5678);
    std::cout<<std::endl;

    //print floating-point value with German locale:
    #ifdef _MSC_VER
    std::locale locG("deu_deu.1252");
    #else
    std::locale locG("de_DE");
    #endif
    std::cout.imbue(locG);
    std::use_facet<std::num_put<char>>(locG).put(std::cout,std::cout,' ',
                                                 1234.5678);
    std::cout<<std::endl;
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  // std::locale loc;//locale
  //InIt beg=...;//beginning of input sequence
  //InIt end=...;//end of input sequence
  //std::ios_base& fs=...;//stream that defines input format
  //std::ios_base::iostate err;//state after call
  //T val;//value after successful call

  //get numeric input of facet of the loc locale
  //const std::num_get<charT>& ng=std::use_facet<std::num_get<charT,InIt>>(loc);

  //read value with numeric input facet
  //ng.get(beg,end,fs,err,val);

  //16.4.2 货币符号格式化(Monetary Formatting)

  try{
    printMoneyPunct<false>("C");
    std::cout<<std::endl;
    printMoneyPunct<false>("german");
    std::cout<<std::endl;
    printMoneyPunct<true>("german");
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  try{
    //use German locale:
    #ifdef _MSC_VER
    std::locale locG("deu_deu.1252");
    #else
    std::locale locG("de_DE@euro");
    #endif
    const std::money_put<char>& mpG=std::use_facet<std::money_put<char>>(locG);

    //ensure that the money_put<> facet impacts the output and currency is written:
    std::cout.imbue(locG);
    std::cout<<std::showbase;

    //use double as monetary value(use local symbol)
    mpG.put(std::cout,false,std::cout,' ',12345.678);
    std::cout<<std::endl;

    //use string as monetary value(use international symbol)
    mpG.put(std::cout,true,std::cout,' ',"12345.678");
    std::cout<<std::endl;
  }
  catch(const std::exception& e){
    std::cerr<<"EXCEPTION: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  //get monetary input facet of the loc locale
  //const std::money_get<charT>& mg=std::use_facet<std::money_get<charT>>(loc);

  //read value with monetary input facet
  //long double val;
  //mg.get(beg,end,intl,fs,err,val);

  std::cin.clear();

  try{
    //use German locale:
    #ifdef _MSC_VER
    std::locale locG("deu_deu.1252");
    #else
    std::locale locG("de_DE");
    #endif

    //use German locale and ensure that the currency is written:
    std::cin.imbue(locG);
    std::cout.imbue(locG);
    std::cout<<std::showbase;

    //read monetary value into long double(use international symbol)
    long double val;
    std::cout<<"monetary value: ";
    std::cin>>std::get_money(val,true);

    if(std::cin){
      //write monetary value(use local symbol)
      std::cout<<std::put_money(val,false)<<std::endl;
    }
    else{
      std::cerr<<"invalid format"<<std::endl;
    }
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  //16.4.3 时间和日期格式化(Time and Date Formatting)

  std::cin.clear();
  std::cout.clear();

  try{
    //query local time:
    auto now=std::chrono::system_clock::now();
    std::time_t t=std::chrono::system_clock::to_time_t(now);
    tm* nowTM=std::localtime(&t);

    //print local time with the global classic locale:
    std::locale locC;
    std::cout.imbue(locC);
    const std::time_put<char>& tpC=std::use_facet<std::time_put<char>>(locC);

    //use single conversion specifier
    tpC.put(std::cout,std::cout,' ',nowTM,'x');
    std::cout<<std::endl;

    //use format string:
    std::string format="%A %x %I%p\n";//format:weekday date hour
    tpC.put(std::cout,std::cout,' ',nowTM,
            format.c_str(),format.c_str()+format.size());

    //print local time with German locale:
    #ifdef _MSC_VER
    std::locale locG("deu_deu.1252");
    #else
    std::locale locG("de_DE");
    #endif
    std::cout.imbue(locG);
    const std::time_put<char>& tpG=std::use_facet<std::time_put<char>>(locG);
    tpG.put(std::cout,std::cout,' ',nowTM,'x');
    std::cout<<std::endl;
    tpG.put(std::cout,std::cout,' ',nowTM,
            format.c_str(),format.c_str()+format.size());
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  try{
    //use German locale:
    #ifdef _MSC_VER
    std::locale locG("deu_deu.1252");
    #else
    std::locale locG("de_DE.ISO-8859-1");
    #endif

    std::cin.imbue(locG);
    const std::time_get<char>& tgG=std::use_facet<std::time_get<char>>(locG);

    //print date order of German locale:
    typedef std::time_base TB;
    std::time_get<char>::dateorder d=tgG.date_order();
    std::cout<<"dateorder: "
             <<(d==TB::no_order||d==TB::mdy?"mdy":
                d==TB::dmy?"dmy":
                d==TB::ymd?"ymd":
                d==TB::ydm?"ydm":"unknown")<<std::endl;

    //read weekday(in German) and time(hh:mm)
    std::cout<<"<wochentag><hh>:<mm>: ";
    std::string format="%A %H:%M";
    struct tm val;
    std::ios_base::iostate err=std::ios_base::goodbit;
    tgG.get(std::istreambuf_iterator<char>(std::cin),
            std::istreambuf_iterator<char>(),
            std::cin,err,&val,
            format.c_str(),format.c_str()+format.size());
    if(err!=std::ios_base::goodbit){
      std::cerr<<"invalid format"<<std::endl;
    }
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  //16.4.4 字符的分类和转换

  std::locale loc1;
  std::string s="Fuck YOu!";
  std::cout.imbue(loc1);

  for(char& c:s){
    c=std::use_facet<std::ctype<char>>(loc1).toupper(c);
  }

  std::cout<<s<<std::endl;

  char narrow[]="0123456789";
  wchar_t wide[10];

  std::use_facet<std::ctype<wchar_t>>(loc1).widen(narrow,narrow+10,wide);

  std::wcout<<sizeof(wide)<<std::endl;
  for(int i=0;i<10;++i){
    std::cout<<wide[i]<<' ';
  }
  std::cout<<std::endl;

  std::string s1="hello,world\n";
  std::wstring ws=to_wstring(s1);
  std::wcout<<ws;
  std::cout<<to_string(ws);

  //create and initialize the table
  //std::ctype_base::mask mytable[std::ctype<char>::table_size]={
  //  ...
  //};

  //use the table for the ctype<char> facet ct
  //std::ctype<char> ct(mytable,false);

  std::cout<<std::boolalpha<<std::islower('c',std::locale())<<std::endl;
  std::cout<<std::toupper('c',std::locale())<<std::endl;
  std::cout<<std::use_facet<std::ctype<char>>(std::locale()).is(std::ctype_base::lower,'c')<<std::endl;
  std::cout<<std::isdigit('9')<<std::endl;//C style call, and return int not bool

  //std::codecvt_utf8<wchar_t,
  //                  0x10FFFF,
  //                  std::consume_header
  //                  |std::generate_header
  //                  |std::little_endian>
  //  wchar2utf8facet;

  try{
    #ifdef _MSC_VER
    //string with German umlaut and euro symbol(in Windows encoding):
    std::string s="hello,world\n";

    //convert to wide-character string(using Windows encoding):
    std::wstring ws=to_wstring(s,std::locale("de_DEU.1252"));
    #else
    //string with German umlaut and euro symbol(in ISO Latin-15 encoding):
    std::string s="hello,world\n";

    //convert to wide-character string(using ISO Latin-15 encoding)
    std::wstring ws=to_wstring(s,std::locale("de_DE@euro"));
    #endif

    //print string as UTF-8 sequence:
    std::cout<<wstring_to_utf8(ws)<<std::endl;
  }
  catch(const std::exception& e){
    std::cerr<<"Exception: "<<e.what()<<std::endl;
    return EXIT_FAILURE;
  }

  //create input stream reading UTF-8 sequences:

  std::wbuffer_convert<std::codecvt_utf8<wchar_t>> utf8inBuf(std::cin.rdbuf());
  std::wistream utf8in(&utf8inBuf);

  //create output stream writing UTF-16 sequences:
  std::wbuffer_convert<std::codecvt_utf16<wchar_t,
                                          0xFFFF,
                                          std::generate_header>> utf16outBuf(std::cout.rdbuf());
  std::wostream utf16out(&utf16outBuf);

  //write each character read:
  wchar_t cc;
  while(utf8in.get(cc)){
    utf16out.put(cc);
  }

  //16.4.5 字符串校勘(String Collation)

  std::locale locc;
  std::string s2="abc",s3="abc";

  //get collate facet of the loc locale
  const std::collate<char>& col=std::use_facet<std::collate<char>>(locc);

  //compare strings by using the collate facet
  int result=col.compare(s2.data(),s2.data()+s2.size(),
                         s3.data(),s3.data()+s3.size());
  if(result==0){
    //s1 and s2 are equal
    std::cout<<"s1 and s2 are equal"<<std::endl;
  }

  std::cout<<std::boolalpha<<locc(s2,s3)<<std::endl;//check s1<s2 according to locale loc

  //16.4.6 消息国际化(Internationalized Message)

  return 0;
}
