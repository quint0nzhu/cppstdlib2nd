/*
  author: Quinton
  date: 2018-11-2
  This code is the source code of The C++ Standary Library 2nd Edition.Chapter8
*/


int main()
{
  //8细探STL容器成员
  //8.1容器内的类型
  //container::value_type
  //元素类型
  //用于(unordered)set和multiset时是常量
  //用于(unordered)map和multimap时是pair<const key-type,mapped-type>

  //container::reference
  //元素的引用类型(reference type)
  //典型定义：container::value_type&
  //在vector<bool>中其实是个辅助类

  //container::const_reference
  //只读元素(read-only element)的引用类型(reference type)
  //典型定义：const container::value_type&
  //在vector<boo>中是bool

  //container::iterator
  ///迭代器类型

  //container::const_iterator
  //只读(read-only)迭代器的类型

  //container::reverse_iterator
  //反向迭代器类型

  //container::const_reverse_iterator
  //只读(read-only)反向迭代器的类型

  //container::pointer
  //指针（用以指向元素）的类型

  //container::const_pointer
  //只读(read-only)指针（用以指向元素）的类型

  //container::size_type
  //无正负号整数类型，用于表示容器大小

  //container::difference_type
  //带正负号的整数类型，用以定义距离

  //container::key_type
  //用以定义关联式容器和无序(associative and unordered)容器的元素的key类型
  //用于(unordered)set和multiset时，相当于value_tye

  //container::mapped_type
  //用以定义关联式和无序(associative and unordered)容器的元素的value类型

  //container::key_compare
  //关联式(associative)容器内的“比较准则”的类型

  //container::value_compare
  //整个元素之“比较准则”(comparison criterion)的类型
  //用于set和multiset时，相当于key_compare
  //在map和multimap中，它是“比较准则”的辅助类，仅比较两元素的key

  //container::hasher
  //无序(unordered)容器内的hashing函数的类型

  //container::key_equal
  //无序(unordered)容器内的“相等判断式”(equality predicate)的类型

  //container::local_iterator
  //无序(unordered)容器内的bucket迭代器的类型
  //始自C++11

  //container::const_local_iterator
  //无序(unordered)容器内的bucket只读迭代器的类型
  //始自C++11

  //8.2创建、复制和销毁(Create, Copy, and Destroy)

  //container::container()
  //Default构造函数，建立一个新的空容器

  //explicit container::container(const CompFunc& cmpPred)
  //以cmpPred为排序准则建立一个空容器，排序准则必须定义一个strict weak ordering

  //explicit container::container(size_type bnum)
  //explicit container::container(size_type bnum, const Hasher& hasher)
  //explicit container::container(size_type bnum, const Hasher& hasher,
  //                              const KeyEqual& eqPred)
  //建立一个新的空容器，带有至少bnum个bucket, hasher用作hashing函数，eqPred用作“鉴定数值相等”的准则(criterion to identify equal value)
  //如果没有传入eqPred，就使用容器类型默认的“等值准则”(equivalence criterion)
  //如果没有传入hasher，就使用容器类型默认的hashing函数

  //container::container(initializer-list)
  //建立一个新容器，以initializer-list内的元素为初值
  //对于array，这个操作是隐式定义的
  //始自C++11

  //container::container(initializer-list,const CompFunc& cmpPred)
  //建立一个容器，排序准则为cmpPred，以initializer-list内的元素为初值
  //排序准则必须定义一个strict weak ordering
  //始自C++11

  //container::container(initializer-list,size_type bnum)
  //container::container(initializer-list,size_type bnum,
  //                     const Hasher& hasher)
  //container::container(initializer-list,size_type bnum,
  //                     const Hasher& hasher,const KeyEqual& eqPred)
  //建立一个容器，带有至少bnum个bucket, hasher用作hashing函数，eqPred用作“鉴定数值相等“的准则，以initializer-list内的元素为初值
  //如果没有传入eqPred，就使用容器类型默认的”等值准则"(equivalence criterion)
  //如果没有传入hasher，就使用容器类型默认的hashing函数

  //container::container(const container& c)
  //Copy构造函数，建立既有容器c的一个新拷贝，针对c中的每一个元素调用copy构造函数
  //对于array，这个操作是隐式定义的

  //container::container(container&& c)
  //Move构造函数，建立一个新容器，以既有容器c的元素为初值
  //经此调用后，c仍然有效，但其内含却“不确定”(unspecified)
  //对于array，这个操作是隐式定义的，始自C++11

  //explicit container::container(size_type num)
  //建立一个容器，可含num个元素，元素由其default构造函数创建

  //container::container(size_type num,const T& value)
  //建立一个容器，可念num个元素，所有元素都是value的拷贝，T是元素类型
  //对于string, value并非pass by reference

  //container::container(InputIterator beg,InputIterator end)
  //建立一个容器，以区间[beg,end)内的所有元素为初值
  //此函数是个member template。因此，只要源区间的元素类型可转换为容器元素类型，此函数即可派上用场
  //注意“由于它是个member template”而带来的问题

  //container::container(InputIterator beg,InputIterator end,
  //                     const CompFunc& cmpPred)
  //产生一个排序准则为cmpPred的容器，并以区间[beg,end)内的所有元素为初值
  //此函数是个member template。因此，只要源区间的元素类型可转换为容器元素类型，此函数即可派上用场
  //排序准则必须定义一个strict weak ordering

  //container::container(InputIterator beg,InputIterator end,size_type bnum)
  //container::container(InputIterator beg,Inputiterator end,size_type bnum,
  //                     const Hasher& hasher)
  //container::container(InputIterator beg,InputIterator end,size_type bnum,
  //                     const Hasher& hasher,const KeyEqual& eqPred)
  //建立一个容器，带有至少bnum个bucket, hasher用作hashing函数，eqPred用作“鉴定数值相等”的准则，以区间[beg,end)内的所有元素为初值
  //如果没有传入eqPred，就使用容器类型默认的“等值准则”(equivalence criterion)
  //如果没有传入hasher，就使用容器类型默认的hashing函数

  //container::~container()
  //析构函数，移除所有元素，并释放内存，对每个元素调用其析构函数

  //8.3 非更易型操作(Nonmodifying Operation)
  //8.3.1 大小相关操作(Size Operation)

  //bool container::empty()const
  //检验容器是否为空（空表示没有元素），相当于begin()==end()，但可能更快，复杂度：常量时间

  //size_type container::size()const
  //返回现有元素的数量，欲检查容器是否为空（即不含元素）应使用empty()，因为empty()可能更快
  //复杂度：常量时间

  //size_type container::max_size()const
  //返回容器可内含的最大元素个数
  //这是一个与实现技术相关的值，可能取决于容器的内存模型。更明确地说，由于vector通常使用单一内存区段(memory segment)，所以vector的这个值往往小于其他容器，复杂度：常量时间

  //8.3.2 元素比较(Comparison Operation)
  //bool operator==(const container& c1,const container& c2)
  //bool operator!=(const container& c1,const container& c2)
  //返回两个容器相等或不等
  //两个容器如果拥有相同数量的元素，且元素内容相同（亦即对应之两两元素施以operator==都导致true）便是相等。但unordered容器还包括必须“相等的元素有着相同的次序”
  //复杂度：一般而言是线性(linear)。但unordered容器有可能最坏情况下是二次(quadratic)

  //bool operator<(const container& c1,const container& c2)
  //bool operator<=(const container& c1,const container& c2)
  //bool operator>(const container& c1,const container& c2)
  //bool operator>=(const container& c1,const container& c2)
  //返回两个容器的比较结果，检验某容器是否小于另一容器，用的是字典顺序式的比较，复杂度：线性(linear)

  //8.3.3 Associative和Unordered容器特有的非更易型操作

  //size_type container::count(const T& value)const
  //返回与value相等的元素个数
  //T是被排序值的类型：
  //-在set和multiset中，T是元素类型
  //-在map和multimap中，T是key的类型
  //复杂度：线性
  //这是相对于<algorithm>中count()算法的特殊版本

  //iterator container::find(const T& value)
  //const_iterator container::find(const T& value)const
  //返回第一个“其值等于value”的元素的位置
  //如果找不到这样的元素就返回end()
  //这是相对于<alogrithm>中find()算法的特殊版本
  //复杂度：对associative容器而言是对数(logarithmic)，对unordered容器而言是常量——前提是用上了一个良好的hash函数

  //iterator container::lower_bound(const T& value)
  //const_iterator container::lower_bound(const T& value)const
  //返回一个iterator指向“根据排序准则，可安插value拷贝“的第一个位置
  //如果找不到这样的元素就返回end()
  //返回之iterator指向”其值大于等于value“之第一个元素（有可能是end()）
  //这是相对于<algorithm>中lower_bound()算法的特殊版本
  //T是被排序值的类型：
  //-在set和multiset中，T是元素类型
  //-在map和multimap中，T是key的类型
  //复杂度：对数(logarithmic)

  //iterator container::upper_bound(const T& value)
  //const iterator container::upper_bound(const T& value)const
  //返回一个iterator，指向”根据排序准则，可安插value拷贝“的最后一个位置
  //如果找不到这样的元素就返回end()
  //返回之iterator指向”其值大于value“之第一个元素（有可能是end()）
  //这是相对于<algorithm>中upper_bound()算法的特殊版本
  //T是被排序值的类型：
  //-在set中multiset中，T是元素类型
  //-在map和multimap中，T是key的类型
  //复杂度：对数(logarithmic)

  //pair<iterator,iterator> container::equal_range(const T& value)
  //pair<const_iterator,const_iterator> container::equal_range(const T& value)const
  //返回一对iterator，指向”根据排序准则，可安插value拷贝“之第一个位置和最后一个位置
  //返回的区间内的元素，其值皆等于value
  //相当于：
  //  make_pair(lower_bound(value),upper_bound(value))
  //这是相对于<algorithm>中equal_range()算法的特殊版本
  //T是被排序值的类型：
  //-在set和multiset中，T是元素类型
  //-在map和multimap中，T是key的类型
  //复杂度：对数(logarithmic)

  //8.4 赋值(Assignment)

  //container& container::operator=(const container& c)
  //这是一个copy assignment操作符
  //将c的所有元素赋值给现有容器，亦即以c的元素替换所有现有元素
  //这个操作符会针对被覆写(overwritten)的元素调用其assignment操作符，针对被附加(appended)的元素调用其copy构造函数，针对被移除(removed)的元素调用其析构函数

  //container& container::opertor=(container&& c)
  //这是一个move assignment操作符
  //将c的所有元素搬移给*this，亦即以c的元素替换所有现有元素
  //调用之后，c仍然有效，但内容不明确（不保证）
  //始自C++11

  //








  return 0;
}
