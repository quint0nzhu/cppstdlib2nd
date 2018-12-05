/*
  author: Quinton
  date: 2018-12-4
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 16
*/


#include <iostream>
#include <locale>
#include <exception>


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

  //16.3 细究Locale


  return 0;
}
