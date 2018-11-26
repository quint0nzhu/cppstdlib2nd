/*
  author: Quinton
  date: 2018-11-25
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter 14
*/


#include <regex>
#include <iostream>
#include <iomanip> //for std::ios::boolalpha
#include <algorithm>


void out(bool b)
{
  std::cout<<(b?"found":"not found")<<std::endl;
}



int main(int argc, char* argv[])
{
  //第14章 正则表达式
  //14.1 Regex的匹配和查找接口(Match and Search Interface)

  //find XML/HTML-tagged value(using default syntax):
  std::regex reg1("<.*>.*</.*>");
  bool found=std::regex_match("<tag>value</tag>",//data
                              reg1);//regular expression

  out(found);

  //find XML/HTML-tagged value(tags before and after the value must match):
  std::regex reg2("<(.*)>.*</\\1>");
  found=std::regex_match("<tag>value</tag>",//data
                         reg2);//regular expression

  out(found);

  //find XML/HTML-tagged value(using grep syntax):
  std::regex reg3("<\\(.*\\)>.*</\\1>",std::regex_constants::grep);
  found=std::regex_match("<tag>value</tag>",//data
                         reg3);//regular expression

  out(found);

  //use C-string as regular expression(needs explicit cast to regex):
  found=std::regex_match("<tag>value</tag>",//data
                         std::regex("<(.*)>.*</\\1>"));//regular expression

  out(found);
  std::cout<<std::endl;

  //regex_match() versus regex_search():
  found=std::regex_match("XML tag: <tag>value</tag>",
                         std::regex("<(.*)>.*</\\1>"));//fails to match

  out(found);
  found=std::regex_match("XML tag: <tag>value</tag>",
                         std::regex(".*<(.*)>.*</\\1>.*"));//matches
  out(found);
  found=std::regex_search("XML tag: <tag>value</tag>",
                          std::regex("<(.*)>.*</\\1>"));//matches
  out(found);
  found=std::regex_search("XML tag: <tag>value</tag>",
                          std::regex(".*<(.*)>.*</\\1>.*"));//matches
  out(found);
  std::cout<<std::endl;

  std::regex reg4(R"(<(.*)>.*</\1>)");
  found=std::regex_match("<tag>value</gat>",//data
                         reg4);//regular expression
  out(found);

  //14.2 处理“次表达式”(Subexpression)

  std::string data="XML tag: <tag-name>the value</tag-name>.";
  std::cout<<"data:                  "<<data<<"\n\n";

  std::smatch m;//for returned details of the match
  found=std::regex_search(data,
                          m,
                          std::regex("<(.*)>(.*)</(\\1)>"));

  //print match details
  std::cout<<"m.empty():             "<<std::boolalpha<<m.empty()<<std::endl;
  std::cout<<"m.size():              "<<m.size()<<std::endl;
  if(found){
    std::cout<<"m.str():               "<<m.str()<<std::endl;
    std::cout<<"m.length():            "<<m.length()<<std::endl;
    std::cout<<"m.position():          "<<m.position()<<std::endl;
    std::cout<<"m.prefix().str():      "<<m.prefix().str()<<std::endl;
    std::cout<<"m.suffix().str():      "<<m.suffix().str()<<std::endl;
    std::cout<<std::endl;

    //iterating over all matches(using the match index):
    for(int i=0;i<m.size();++i){
      std::cout<<"m["<<i<<"].str():    "<<m[i].str()<<std::endl;
      std::cout<<"m.str("<<i<<"):      "<<m.str(i)<<std::endl;
      std::cout<<"m.position("<<i<<"): "<<m.position(i)<<std::endl;
    }
    std::cout<<std::endl;

    //iterating over all matches(using iterators):
    std::cout<<"matches: "<<std::endl;
    for(auto pos=m.begin();pos!=m.end();++pos){
      std::cout<<" "<<*pos<<" ";
      std::cout<<"(length: "<<pos->length()<<")"<<std::endl;
    }
  }

  std::string data1="<person>\n"
    " <first>Nico</first>\n"
    " <last>Josuttis</last>\n"
    "</person>\n";

  std::regex reg("<(.*)>(.*)</(\\1)>");

  //iterator over all matches
  auto pos=data1.cbegin();
  auto end=data1.cend();
  std::smatch m1;
  for(;std::regex_search(pos,end,m1,reg);pos=m1.suffix().first){
    std::cout<<"match:    "<<m1.str()<<std::endl;
    std::cout<<" tag:     "<<m1.str(1)<<std::endl;
    std::cout<<" value:   "<<m1.str(2)<<std::endl;
  }

  std::string data2="<person>"
    "<first>Nico</first>"
    "<last>Josuttis</last>"
    "</person>";

  std::regex reg5("<(.*)>([^>]*)</(\\1)>");

  //iterator over all matches
  auto pos1=data2.cbegin();
  auto end1=data2.cend();
  std::smatch m2;
  for(;std::regex_search(pos1,end1,m2,reg5);pos1=m2.suffix().first){
    std::cout<<"match:    "<<m2.str()<<std::endl;
    std::cout<<" tag:     "<<m2.str(1)<<std::endl;
    std::cout<<" value:   "<<m2.str(2)<<std::endl;
  }

  //14.3 Regex Iterator

  //iterate over all matches(using a regex_iterator):
  std::sregex_iterator pos2(data1.cbegin(),data1.cend(),reg);
  std::sregex_iterator end2;
  for(;pos2!=end2;++pos2){
    std::cout<<"match:   "<<pos2->str()<<std::endl;
    std::cout<<" tag:    "<<pos2->str(1)<<std::endl;
    std::cout<<" value:  "<<pos2->str(2)<<std::endl;
  }

  //use a regex_iterator to process each matched substring as element in an algorithm:
  std::sregex_iterator beg(data1.cbegin(),data1.cend(),reg);
  for_each(beg,end2,[](const std::smatch& m){
      std::cout<<"match:    "<<m.str()<<std::endl;
      std::cout<<" tag:     "<<m.str(1)<<std::endl;
      std::cout<<" value:   "<<m.str(2)<<std::endl;
    });

  //14.4 Regex Token Iterator

  //iterate over all matches(using a regex_token_iterator):
  std::sregex_token_iterator pos3(data1.cbegin(),data1,cend(),//sequence
                                  reg,//token separator
                                  {0,2});//0:full match,2:second substring
  std::sregex_token_iterator end3;
  for(;pos3!=end3;++pos){
    std::cout<<"match:     "<<pos3->str()<<std::endl;
  }
  std::cout<<std::endl;

  std::string names="nico, jim, helmut, paul, tim, john paul, rita";
  std::regex sep("[ \t\n]*[,;.][ \t\n]*");//separated by ,;or. and spaces
  std::sregex_token_iterator p(names.cbegin(),names.cend(),//sequence
                               sep,//separator
                               -1);//-1:values between sparators
  std::sregex_token_iterator e;
  for(;p!=e;++p){
    std::cout<<"name:      "<<*p<<std::endl;
  }




  return 0;
}
