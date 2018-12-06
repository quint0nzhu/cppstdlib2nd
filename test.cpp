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





  return 0;
}
