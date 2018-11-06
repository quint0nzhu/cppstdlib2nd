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

  //container& container::operator=(initializer-list)
  //将initializer-list的所有元素赋值给现有容器，亦即以传入的元素的拷贝替换所有现有元素
  //这个操作符会针对被覆写(overwritten)的元素调用其assignment操作符，针对被附加(appended)的元素调用其copy构造函数，针对被移除(removed)的元素调用其析构函数
  //始自C++11

  //void container::assign(initializer-list)
  //将initializer-list的所有元素赋值给现有容器，亦即以传入的元素的拷贝替换所有现有元素
  //始自C++11

  //void array::fill(const T& value)
  //将value赋值给所有元素，亦即以value的拷贝替换所有现有元素
  //始自C++11

  //void container::assign(size_type num,cont T& value)
  //赋值num个value，亦即以num个value拷贝替换掉所有现有元素
  //T必须是元素类型

  //void container:assign(InputIterator beg,InputIterator end)
  //赋值[beg,end)区间内的所有元素，亦即以[beg,end)内的元素拷贝替换掉所有现有元素
  //此函数为一个member template。因此，只要源区间的元素类型可转换为容器的元素类型，此函数即可派上用场

  //void container::swap(container& c)
  //void swap(container& c1,container& c2)
  //和c交换内容；或是交换c1和c2的内容
  //上述两个操作都互换：
  //-容器的元素
  //-排序准则、相等性准则、hash函数对象——如果有的话
  //所有指向元素的reference、pointer和iterator，都会交换其容器，因为它们此后仍然指向相同（被交换后的）元素
  //Array内部不能够只是交换pointer。因此，swap()带有线性复杂度，而完成之后iterator和reference指向原本的容器，但是不同的元素
  //对于associative容器，只要“比较准则”进行复制或赋值时不抛出异常，本函数就不抛出异常。对于unordered容器，只有当”相等判断式“或hash函数对象抛出异常，本函数才会抛出异常。对于其他所有容器，本函数一律不抛出异常
  //复杂度：一般而言是常量。对array则是线性
  //基于其复杂度，当你不再需要被赋值的对象(assigned object)，你应该宁可使用swap()不使用copy assignment操作

  //8.5 元素直接访问(Direct Element Access)

  //reference container::at(size_type idx)
  //const_reference container::at(size_type idx)const
  //返回索引idx所代表的元素（第一个元素的索引为0）
  //如果传入一个无效索引（小于0或大于等于size()），会导致out_of_range异常
  //后续的改动或内存重分配，可能会导致这里所返回的reference失效
  //如果调用者保证idx合法有效，那么最好使用速度更快的operator[]

  //T& map::operator at(const key_type& key)
  //const T& map::operator at(const key_type& key)const
  //返回map之中key所对应的value
  //如果没有任何元素的key等key，会抛出out_of_range异常
  //始自C++11

  //reference container::operator[](size_type idx)
  //const_reference container::operator[](size_type idx)const
  //两者都返回索引idx所代表的元素（第一个元素的索引为0）
  //如果传入一个无效索引（小于0或大于等于size()），会导致不确定的行为。所以调用者必须确保索引有效，否则应该使用at()
  //后续的改动或内存重新分配，可能会导致这里所返回的reference失效

  //T& map::operator[](const key_type& key)
  //T& map::operator[](key_type&& key)
  //关联式数组(associative array)的operator[]
  //在map中，会返回key所对应的value
  //如果不存在“key为key“的元素，本操作会自动创建一个新元素，其key由key而来（复制或搬移），其value则由value类型之default构造函数给予。不存在所谓的无效索引（只是会带来意外的行为）
  //对于第二形式，key的状态此后变得不确定（这个形式针对”key尚未存在“提供了move语义）
  //上述第一形式相当于：
  //(*((insert(make_pair(key,T()))).first)).second
  //上述第二形式始自C++11

  //reference container::front()
  //const_reference container::front()const
  //两者都返回第一个元素（第一个元素的索引为0）
  //调用者必须确保容器内拥有元素(size()>0)，否则会导致不明确的行为
  //对string的支持始自C++11

  //reference container::back()
  //const_reference container::back()const
  //两者都返回最后一个元素（其索引为size()-1）
  //调用者必须确保容器内拥有元素（size()>0），否则会导致不明确的行为
  //对string的支持始自C++11

  //T* container::data()
  //const T* container:;data()const
  //两者都返回一个带着所有元素的C-style array（或者说一个pointer指向第一个元素）
  //本函数用来将一个标准库array的所有元素传递给一个C-style array
  //String只有第二形式
  //对array和vector的支持始自C++1

  //8.6 "产出迭代器"之各项操作

  //iterator container::begin()
  //const_iterator container::begin()const
  //const_iterator container::cbegin()const
  //返回一个iterator，指向容器起始处（第一个元素的位置）
  //如果容器为空，此操作相当于container::end()或container::cend()
  //Unordered容器也提供带有数值实参的begin()和cbegin()，用以提供bucket接口
  //cbegin()始自C++11

  //iterator container::end()
  //const_iterator container::end()const
  //const_iterator container::cend()const
  //返回一个iterator，指向容器尾端（最后元素的下一个位置）
  //如果容器为空，则此动作相当于container::begin()或container::cbegin()
  //Unordered容器也提供带有数值实参的end()和cend()，用以提供bucket接口
  //cend()始自C++11

  //reverse_iterator container::rbegin()
  //const_reverse_iterator container::rbegin()const
  //const_reverse_iterator container::crbegin()const
  //返回一个反向iterator，指向反向迭代的起点（此起点也就是正向之最末一个元素）
  //如果容器为空，则此动作相当于container::rend()或container::crend()
  //crbegin()始自C++11
  
  //reverse_iterator container::rend()
  //const_reverse_iterator container::rend()const
  //const_reverse_iterator container::crend()const
  //返回一个反向iterator，指向反向迭代的终点（此终点也就是正向之第一元素之更前方）
  //如果容器为空，则此动作相当于container::rbegin()或container::crbegin()
  //crend()始自C++11

  //8.7 安插和移除(Inserting and Removing)元素
  //8.7.1 安插单一元素(Inserting Single Element)

  //iterator container::insert(const T& value)
  //iterator container::insert(T&& value)
  //pair<iterator,bool> container::insert(const T& value)
  //pair<iterator,bool> container::insert(T&& value)
  //在associative或unordered容器中安插value
  //第一和第三形式会复制value
  //第二和第四形式会搬移value放进容器中，所以此后value的值将不再明确(unspecified)
  //容器如果允许元素重复，亦即(unordered)multiset和multimap，采用第一和第二形式。它们返回新元素的位置。自C++11起，新安插的元素保证被放置于既有的等值元素的尾端
  //容器中果不允许元素重复，亦即(unordered)set和map，采用第三和第四形式。如果安插不成功（因为已经存在一个元素有着相同的value或相同的key），它们返回既有元素的位置和false。如果安插成功，它们返回新元素的位置和一个ture
  //T是容器的元素类型，对(unordered)map和multimap而言那是一个key/value pair
  //对于map、multimap、unordered map和unordered multimap，带有move语义的上述形式是个member template。因此，value的类型只要能转换为容器的value类型(key/value pair)就可以。之所以引入这个性质是为了允许你传入两个string使得第一个可被转换为一个constant string（那是key type)
  //函数如果不成功，不会带来任何影响——前提是unordered容器的hash函数不抛出异常
  //对于所有容器，“指向既有元素”的所有reference都仍然有效。对于associative容器，所有“指向既有元素”的iterator都仍然有效。对于unordered容器，所有“指向既有元素”的iterator也都有效的前提是：没有发生rehashing（当最终元素量等于或大于bucket个数乘以最大负载系数，就会发生rehashing）
  //第二和第四形式始自C++11

  //iterator container::emplace(args)
  //pair<iterator,bool> container::emplace(args)
  //在associative或unordered容器中安插新元素，以args为初值
  //容器如果允许元素重复，亦即ordered/unordered的multiset和multimap，采用第一形式。它们返回新元素的位置。新安插的元素保证被放置于既有的等值元素的尾端
  //容器如果不允许元素重复，亦即ordered/unordered的set和map，采用第二形式。如果安插不成功（因为已经存在一个元素有着相同的value或相同的key），它们返回既有元素的位置和false。如果安插成功，它们返回新元素的位置和一个true
  //函数如果不成功，不会带来任何影响——前提是unordered容器的hash函数不抛出异常
  //对于所有容器，“指向既有元素”的所有reference都仍然有效。对于associative容器，所有“指向既有元素”的iterator都仍然有效。对于unordered容器，所有“指向既有元素”的iterator也都有效的前提是：没有发生rehashing（当最终元素量等于或大于bucket个数乘以最大负载系数，就会发生rehashing）
  //注意，对于sequence容器，相同形式也是可能的，其中第一实参被视为新元素的安插位置
  //注意，为了emplace（安放）新的key/value pair进入(unordered)map和multimap中，你必须使用逐块式构建(piecewise construction)
  //始自C++11

  //iterator container::insert(const_iterator pos,const T& value)
  //iterator container::insert(const_iterator pos,T&& value)
  //在iterator pos位置上安插value
  //第一形式会复制value
  //第二形式会搬移value放进容器中，所以此后value的值将不再明确(unspecified)
  //返回新元素的位置
  //容器如果不允许元素重复，例如set、map、unordered set和unordered map，而又已经存在一个元素有着和value相同的key，那么调用将无作用，返回的是即有元素的位置
  //对于associative和unordered容器，pos只作为一个提示，指向“安插时必要的查找动作”的起始建议位置。如果value刚好可安插于pos位置上，则此函数且有“摊提之常量时间”复杂度，否则具有对数复杂度
  //对于vector，这个操作可能导致指向其他元素的iterator和reference失效——如果“重分配”发生的话（当最终的元素数量超过原本容量的话就会发生重分配）
  //对于deque，这个操作会导致指向其他元素的iterator和reference失效
  //T是容器元素的类型，在(unordered)map和multimap中它是一个key/value pair
  //对于map、multimap、unordered map和unordered multimap，带有move语义的第二形式是个member template。因此，value的类型只要能转换为容器的value类型(key/value pair)就可以。之所以引入这个性质是为了允许你传入两个string使得第一个可被转换为一个constant string（那是key type)
  //对于string，value采用pass by value
  //对于vector和deque，如果元素的copy/move操作（构造函数和赋值操作符）不抛出异常，则此函数万一失败也不会带来任何影响。对于unordered容器，如果hash函数不抛出异常，则此函数万一失败也不会带来任何影响。对于所有其他标准容器，此函数万一失败也不会带来任何影响
  //第二形式始自C++11。在此之前用的是iterator类型而不是const_iterator

  //iterator container::emplace(const_iterator pos,args)
  //在容器的iterator位置pos上安插新元素，以args为初值
  //返回新元素的位置
  //对于vector，这个操作可能导致指向其他元素的iterator和reference失效——如果“重分配“发生的话（当最终的元素量超过原本容量的话就会发生重分配）
  //对于deque，这个操作会导致指向其他元素的iterator和reference失效
  //T是容器元素的类型
  //对于vector和deque，只要元素copy操作（构造函数和assignment操作符）不抛出异常，这个函数要么就成功，要么就全无影响。对于其他所有标准容器，这个函数要么就成功，要么就全无影响
  //相同形式也可能存在于associative容器中，新元素将被安插于pos之前一位置
  //这个函数要么就成功，要么就全无影响，前提是unordered容器的hash函数不抛出异常
  //始自C++11

  //iterator container::emplace_hint(const_iterator pos,args)
  //在容器的iterator位置pos上安插新元素，以args为初值
  //返回新元素的位置
  //容器如果不允许元素重复，例如set、map、unordered set和unordered map，而又已经存在一个元素有着和value相同的key，那么调用将无作用，返回的是既有元素的位置
  //位置pos只作为提示使用，指向”安插时必要的查找动作“的起始点。如果新元素刚好可安插于pos位置上，则此函数具有”摊提之常量时间“复杂度，否则具有对数复杂度
  //T是容器元素的类型，在(unordered)map和multimap中它是一个key/value pair
  //此函数万一失败也不会带来任何影响，前提是（对unordered容器而言）hash函数不抛出异常
  //始自C++11

  //void container::push_front(const T& value)
  //void container::push_front(T&& value)
  //安插value使成为第一个元素
  //第一形式会复制value
  //第二形式始自C++11,会搬移value放进容器中，此后value的值不再明确(unspecified)
  //T是容器的元素类型，两个形式都相当于insert(begin(),value)
  //对于deque，此操作会造成”指向其他元素“的iterator失效，而”指向其他元素“的reference仍保持有效
  //此函数若失败不会带来任何影响

  //void container::emplace_front(args)
  //安插一个新的第一元素，由实参列(argument list)args初始化
  //因此，容器的元素类型必须带有一个可被调用的(callable)构造函数接受args
  //对于deque，此操作会造成”指向其他元素“的iterator失效，而“指向其他元素”的reference仍保持有效
  //此函数若失败不会带来任何影响
  //始自C++11

  //void container::push_back(const T& value)
  //void container::push_back(T&& value)
  //追加value，使成为新的最末元素，第一形式会复制value
  //第二形式始自C++11,会搬移value放进容器中，此后value的值不再明确(unspecified)
  //T是容器的元素类型
  //两个形式都相当于insert(end(),value)
  //对于vector，这个操作可能导致“指向其他元素”的iterator和reference失效——如果“重分配”发生的话（当最终的元素数量超过原本容量的话就会发生重分配）
  //对于deque，这个操作会导致”指向其他元素“的iterator失效，”指向其他元素“的reference则仍然有效
  //对string，value采用pass by value
  //对vector和deque，如果元素的copy/move构造函数不抛出异常，则此函数万一失败也不会带来任何影响。对于list，此函数万一失败也不会带来任何影响

  //void container::emplace_back(args)
  //追加一个新的最末元素，它由实参列(argument list)args初始化
  //因此，容器的元素类型必须带有一个可被调用的(callable)构造函数接受args
  //对于vector，这个操作可能导致”指向其他元素“的iterator和reference失效——如果”重分配”发生的话（当最终的元素量超过原本容量的话就会发生重分配）
  //对于deque，这个操作会导致“指向其他元素”的iterator失效，“指向其他元素”的reference则仍然有效
  //此函数要么就成功，要么就无任何影响，前提是，对于vector和deque，其copy/move构造函数不抛出异常
  //始自C++11

  //8.7.2 安插多重元素(Inserting Multiple Elements)

  //void container::insert(initializer-list)
  //将initializer-list内的元素的拷贝插入一个associative容器内
  //对于所有容器，“指向既有元素”的所有reference都仍然有效。对于associative容器，所有“指向既有元素”的iterator都仍然有效。对于unordered容器，所有“指向既有元素”的iterator也都有效的前提是：没有发生rehashing（当最终元素量等于或大于bucket个数乘以最大负载系数，就会发生rehashing)
  //始自C++11

  //iterator container::insert(const_iterator pos,initializer-list)
  //在iterator pos位置上安插initializer-list中的元素的拷贝
  //返回第一个被安插元素的位置，或返回pos——如果initializer-list为空
  //对于vector，这个操作可能导致“指向其他元素”的iterator和reference失效——如果“重分配”发生的话（当最终的元素数量超过原本容量的话就会发生重分配）
  //对于deque，这个操作会导致“指向其他元素”的iterator和reference失效
  //对于list，此函数万一失败也不会带来任何影响
  //始自C++11

  //iterator container::insert(const_iterator pos,size_type num,const T& value)
  //在iterator pos的位置上安插num个value拷贝
  //返回第一个被安插元素的位置，或返回pos——如果num==0（在C++11之前，不返回任何东西）
  //对于vector，这个操作可能导致“指向其他元素”的iterator和reference失效——如果“重分配”发生的话（当最终的元素数量超过原本容量的话就会发生重分配）
  //对于deque，这个操作会导致“指向其他元素”的iterator和reference失效
  //T是容器的元素类型。对于map和multimap而言它是key/value pair
  //对于string，value采用pass by value
  //对于vector和deque，如果元素的copy/move操作（构造函数和assignment操作符）不抛出异常，则此函数万一失败也不会带来任何影响。对于list，此函数万一失败也不会带来任何影响
  //在C++11这前，用的是iterator类型而不是const_iterator，且返回类型为void

  //void container::insert(InputIterator beg,InputIterator end)
  //将区间[beg,end)内所有元素的拷贝安插到associative容器内
  //此函数是个member template，因此，只要源区间的元素可转换为容器元素的类型，本函数就可派上用场
  //对于所有容器，“指向既有元素”的reference仍然有效。对于associative容器，所有“指向既有元素”的iterator都仍然有效。对于unordered容器，所有“指向既有元素”的iterator也都有效的前提是：没有发生rehashing（当最终元素量等于或大于bucket个数乘以最大负载系数，就会发生rehashing）
  //此函数要么就成功，要么就无任何影响，前提是，unordered容器的hash函数不抛出异常

  //iterator container::insert(const_iterator pos,InputIterator beg,InputIterator end)
  //将区间[beg,end)内所有元素的拷贝安插于迭代器pos所指的位置上
  //返回第一个被安插元素的位置，或返回pos——如果beg==end（在C++11之前，不返回任何东西）
  //此函数是个member template，因此，只要源区间的元素可转换为容器元素的类型，本函数就可派上用场
  //对于vector，这个操作可能导致“指向其他元素”的iterator和reference失效——如果“重分配”发生的话（当最终的元素数量超过原本容量的话就会发生重分配）
  //对于vector和deque，这个操作可能导致“指向其他元素”的iterator和reference失效
  //对于list，此函数万一失败也不会带来任何影响
  //在C++11之前，用的是iterator类型而不是const_iterator，且返回类型为void

  //8.7.3 移除元素(Removing Element)

  //size_type container::erase(const T& value)
  //从associative容器中移除所有和value相等的元素
  //返回被移除的元素个数
  //调用被移除元素的析构函数
  //T是被排序值(sorted value)的类型：
  //-在(unordered)set和multiset中，T是元素类型
  //-在(unordered)map和multimap中，T是key的类型
  //此函数不会造成指向其他元素的iterator和reference失效
  //此函数有可能抛出异常，如果比较测试或hash函数抛出异常的话
  //(forward)list的remove()提供相同功能。其他容器可使用remove()算法

  //iterator container::erase(const_iterator pos)
  //将iterator pos所指位置上的元素移除，返回后继元素的位置（或返回end())，调用被移除元素的析构函数
  //注意，调用者必须确保iterator pos有效。例如：
  // coll.erase(coll.end());//ERROR=>undefined behavior
  //对于vector和deque，此操作可能造成“指向其他元素”的iterator和reference无效。对于所有其他容器，“指向其他元素”的iterator和reference永远保持有效
  //对于vector、deque和list，此函数不抛出异常。对于associative和unordered容器，如果hash函数或“比较测试”抛出异常，此函数有可能抛出异常
  //在C++11之前，返回类型是void（对于associative容器）且使用iterator而非const_iterator
  //对于以iterator为元素的set，自C++11起调用erase()有可能形成岐义(ambiguous)。因此C++11修正为：提供重载版本，分别是erase(iterator)和erase(const_iterator)

  //iterator container::erase(const_iterator beg,const_iterator end)
  //移除区间[beg,end)内的所有元素，返回最后一个被移除元素的位置（或返回end()）
  //一如区间惯例，始于beg（含）而终于end（不含）的所有元素都被移除
  //调用被移除元素的析构函数，调用者必须确保beg和end形成一个有效序列，并且该序列是容器的一部分
  //对于vector和deque，此操作可能造成“指向其他元素”的iterator和reference无效。对于所有其他容器，“指向其他元素”的iterator和reference永远保持有效
  //对于vector、deque和list，此函数不抛出异常。对于associative和unordered容器，如果hash函数或“比较测试”抛出异常，此函数有可能抛出异常
  //在C++11之前，返回类型是void（对于associative容器）且使用iterator而非const_iterator

  //void container::pop_front()
  //移除容器的第一元素
  //相当于：
  // container.erase(container.begin())
  //或者对forward list而言相当于：
  // container.erase_after(container.before_begin())
  //如果容器是空的，会导致不明确的行为。因此调用者必须确保容器至少有一个元素，也就是!empty()
  //此函数不抛出异常，“指向其他元素”的iterator和reference都保持有效

  //void container::pop_back()
  //移除容器的最末元素，相当于：
  // container.erase(prev(container.end())
  //如果容器是空的，会导致不明确的行为。因此调用者必须确保容器至少有一个元素，也就是!empty()
  //此函数不抛出异常，“指向其他元素”的iterator和reference都保持有效
  //对string而言，始自C++11

  //void container::clear()
  //移除所有元素，将容器清空，调用被移除元素的析构函数，“指向容器内元素”的所有iterator和reference都失效
  //对于vector、deque和string，它甚至会令任何past-the-end-iterator失效——那是由end()或cend()返回的东西
  //此函数不抛出异常（在C++11之前，对于vector和deque，如果copy构造函数或assignment操作符抛出异常，此函数也会抛出异常）

  //8.7.4 重设大小(Resizing)
  
  //void container::resize(size_type num)
  //void container::resize(size_type num,const T& value)
  //将容器大小改为num，如果size()原本就是num，则两者皆无效
  //如果num大于size()，则在容器尾端附加额外元素。第一形式通过default构造函数来构建新元素，第二形式以value的拷贝作为新元素
  //如果num小于size()，则移除尾端元素，获得新的大小。每个被移除元素的析构函数都会被调用
  //对于vector和deque，这些函数可能造成“指向其他元素”的iterator和reference无效。对于所有其他容器，“指向其他元素”的iterator和reference永远保持有效
  //对于vector和deque，这些函数要么成功，要么无效，前提是元素的构造函数和assignment操作符不抛出异常。对于list和forward list，如果失败不会带来任何影响
  //在C++11之前，value是以by value方式传递
  //对于string，value是以by value方式传递

  //8.8 List和Forward List的特殊成员函数
  //8.8.1 特殊成员函数（针对List和Forward List）

  //void list::remove(const T& value)
  //void list::remove_if(UnaryPredicate op)
  //remove()移除所有带有value值的元素
  //remove_if()移除所有”令单参判断式op(elem)产出true“的元素
  //注意，op不应在函数调用过程中改变状态(state)
  //两个形式都会调用被移除元素的析构函数，留下的元素保持原先次序（stable[稳定的]）
  //这是<algorithm>中remove()算法的特殊版本，T是容器元素的类型
  //只有当元素的比较动作抛出异常，这些函数才可能抛出异常

  //void list::unique()
  //void list::unique(BinaryPredicate op)
  //移除(forward)list内相邻而重复的元素，使每一个元素都不同于下一个元素
  //第一形式会将所有”和前一元素相等“的元素移除
  //第二形式的意义是：任何一个元素elem，如果其前一元素是e，而elem和e造成双参判断式(binary predicate)op(elem,e）获得true，那么就移除elem。换言之，这个判断式并非拿元素和其目前的前一紧临元素比较，而是拿元素和其未被移除的前一元素比较
  //注意，op不应在函数调用过程中改变状态(state)，两个形式都会调用被移除元素的析构函数
  //这是<algorithm>的unique()算法的特别版本，如果”元素比较动作“中不抛出异常，这些函数亦不抛出异常

  //void list::splice(const_iterator pos,list& source)
  //void list::splice(const_iterator pos,list&& source)
  //将source的所有元素搬移到*this，并将它们安插到iterator pos所指位置
  //调用之后，source被清空
  //如果source和*this相同，会导致不明确的行为。所以调用端必须确定source和*this是不同的list。欲移动同一个list内的元素，应该使用稍后提及的其他splice()形式
  //调用者必须确定pos是*this的一个有效位置；否则会导致不明确的行为
  //”指向source的元素“的所有pointer、iterator和reference仍然有效。此后它们属于this
  //此函数不抛出异常
  //第二形式始自C++11。在C++11之前，用的是iterator而非const_iterator

  //void list::splice(const_iterator pos,list& source,const_iterator sourcePos)
  //void list::splice(const_iterator pos,list&& source,const_iterator sourcePos)
  //从source list中，将位于sourcePos位置上的元素搬移至*this，并安插于iterator pos所指位置
  //source和*this可以相同。这种情况下，元素将在list内部被搬移
  //如果source和*this不是同一个list，在此操作之后，其元素个数少1
  //调用者必须确保pos是*this的一个有效位置，且sourcePos是source的一个有效迭代器，而且sourcePos不是source.end()；否则会导致不明确的行为
  //“指向source的元素”的所有pointer、iterator和reference仍然有效。此后它们属于this
  //此函数不抛出异常，第二形式始自C++11。在C++11之前，用的是iterator而非const_iterator

  //void list::splice(const_iterator pos,list& source,const_iterator sourceBeg,const_iterator sourceEnd)
  //void list::splice(const_iterator pos,list&& source,const_iterator sourceBeg,const_iterator sourceEnd)
  //从source list中，将[sourceBeg,sourceEnd)区间内的所有元素搬移到*this，并安插于iterator pos所指的位置
  //source和*this可以相同。这种情况下，pos不得为被移动区间的一部分，而元素将在list内部移动
  //如果source和*this不是同一个list，在此操作之后，其元素个数将减少
  //调用者必须确保pos是*this的一个有效位置，且sourceBeg和sourceEnd形成一个有效区间，该区间是source的一部分；否则会导致不明确的行为
  //“指向source的元素”的所有pointer、iterator和reference仍然有效。此后它们属于this
  //此函数不抛出异常，第二形式始自C++11。在C++11之前，用的是iterator而非const_iterator

  //void list::sort()
  //void list::sort(CompFunc cmpPred)
  //对list内的所有元素排序，第一形式以operator<对list的所有元素进行排序
  //第二形式调用cmpPred比较两元素，以此对list中的所有元素排序：
  // op(elem1,elem2)
  //Value相同的元素，其顺序保持不变（除非有异常抛出）
  //这是<algorithm>中sort()和stable_sort()算法的特殊版本

  //void list::merge(list& source)
  //void list::merge(list&& source)
  //void list::merge(list& source,CompFunc cmpPred)
  //void list::merge(list&& source,CompFunc cmpPred)
  //将(forward)list source内的所有元素并入*this，调用后source变成空
  //前两个形式采用operator<作为排序准则
  //后两个形式采用cmpPred作为可选的排序准则，以此比较两元素的大小：
  // cmpPred(elem,sourceElem)
  //诸元素如果含有相等内容，它们的次序保持不变(stable)
  //如果*this和source在排序准则operator<或cmpPred之下已排好序(sorted)，则新产生的(forward)list也将会是已排好序，而且*this内的相等元素会优先于source内的相等元素。严格地说，C++ standard要求两个(forward)list必须已排好序，但实际上对未排序的list进行merge动作也是可能的，不过使用前最好先确认一下
  //这是<algorithm>中的merge()算法的特殊版本
  //只要元素的比较动作不抛出异常，此函数万一失败也不会造成任何影响

  //void list::reverse()
  //将(forward)list内的元素次序颠倒
  //这是<algorithm>中的reverse()算法的特殊版本
  //此函数不抛出异常

  //8.8.2 特殊成员函数（只针对Forward List)

  //iterator forwardlist::before_begin()
  //const_iterator forwardlist::before_begin()const
  //const_iterator forwardlist::cbefore_begin()const
  //返回一个iterator，指向第一个元素之前一个位置
  //由于在forward list中你无法回向迭代(iterate backward)，这个成员函数允许你获得一个“可用来插入一个新的第一元素，或用来删除第一元素”的位置

  //iterator forwardlist::insert_after(const_iterator pos,const T& value)
  //iterator forwardlist::insert_after(const_iterator pos,T&& value)
  //就在iterator pos所指位置上安插value
  //第一形式会复制value，第二形式会搬移value放进容器内，此后value的状态不再明确
  //返回新元素的位置，函数要么成功，要么无任何影响，
  //传入容器的end()或cend()作为pos，会导致不明确的行为

  //iterator forwardlist::emplace_after(const_iterator pos,args)
  //在iterator pos所指位置上安插一个新元素，以args为初值
  //返回新元素的位置，函数要么成功，要么无任何影响
  //传入容器的end()或cend()作为pos，会导致不明确的行为

  //iterator forwardlist::insert_after(const_iterator pos,size_type num,const T& value)
  //在iterator pos所指位置上安插num个value的拷贝
  //返回最后被安插的那个元素的位置。如果num==0就返回pos
  //函数要么成功，要么无任何影响，传入容器的end()或cend()作为pos，会导致不明确的行为

  //iterator forwardlist::insert_after(const_iterator pos,initializer-list)
  //在iterator pos所指位置上安插initializer-list的元素拷贝
  //返回最后被安插的那个元素的位置。如果initializer-list是空的，就返回pos
  //函数要么成功，要么无任何影响，传入容器的end()或cend()作为pos，会导致不明确的行为

  //iterator forwardlist::insert_after(const_iterator pos,InputIterator beg,InputIterator end)
  //在iterator pos所指位置上安插[beg,end)的所有元素的拷贝
  //返回最后被安插的那个元素的位置。如果beg==end，就返回pos
  //这是一个member template。因此，源区间的元素可以是任何类型，只要能够转换为容器的元素类型就行
  //函数要么成功，要么无任何影响，传入容器的end()或cend()作为pos，会导致不明确的行为

  //iterator forwardlist::erase_after(const_iterator pos)
  //移除iterator pos所指位置之后的所有元素，返回后继元素的位置（或返回end()）
  //调用被移除元素的析构函数，“指向其他元素”的iterator和reference仍然保持有效
  //调用者必须确保iterator pos有效，此函数不抛出异常
  //传入容器的end()或cend()作为pos，会导致不明确的行为

  //void forwardlist::erase_after(const_iterator beg,const_iterator end)
  //移除(beg,end)区间内的元素，注意，这不是个半开区间，因为它排除了beg和end。例如：
  // coll.erase(coll.before_begin(),coll.end());//OK: erases all elements
  //返回end,调用被移除元素的析构函数，调用者必须确保beg和end定义出容器内的一个有效区间(valid range)
  //此函数不抛出异常，指向其他元素的iterator和reference仍然保持有效

  //void forwardlist::splice_after(const_iterator pos,forwardlist& source)
  //void forwardlist::splice_after(const_iterator pos,forwardlist&& source)
  //将source的所有元素搬移至*this,并在iterator pos位置上安插它们
  //在此调用后，source成空。
  //如果source和*this是同一个容器，则行为不明确。因此，调用者必须确保source是另一个list。如果想要在同一个list中搬移元素，必须使用稍后显示的splice_after()形式
  //调用者必须确保pos是*this的一个有效位置；若否，行为将不明确
  //“指向source的成员”的pointer、iterator和reference仍然有效。此后它们属于this
  //此函数不抛出异常，传入容器的end()或cend()作为pos，会导致不明确的行为

  //void forwardlist::splice_after(const_iterator pos,forwardlist& source,const_iterator sourcePos)
  //void forwardlist::splice_after(const_iterator pos,forwardlist&& source,const_iterator sourcePos)
  //将list source的sourcePos位置上的元素搬移到*this,将它安插到iterator pos所指位置
  //source和*this可以是同一个容器。如果这样，元素就是在自家容器内搬移
  //如果source是另一个list，它的元素将在此操作完成后少一个
  //调用者必须确保pos是*this的一个有效位置，sourcePos是source的一个有效iterator，而且sourcePos不是source.end()；否则此操作的行为将不明确
  //“指向source的成员”的pointer、iterator和reference仍然有效。此后它们属于this
  //此函数不抛出异常，传入容器的end()或cend()作为pos，会导致不明确的行为

  //void forwardlist::splice_after(const_iterator pos,forwardlist& source,const_iterator sourceBeg,const_iterator sourceEnd)
  //void forwardlist::splice_after(const_iterator pos,forwardlist&& source,const_iterator sourceBeg,const_iterator sourceEnd)
  //将list source的(sourceBeg,sourceEnd)区间内的元素搬移到*this，将它们安插在iterator pos位置上。注意，最后两个实参不是半开区间，因为它排除了beg也排除了end。以下调用会将coll2的所有元素搬移到coll的起点为：
  // coll.splice_after(coll.before_begin(),coll2,coll2.before_begin(),coll2.end());
  //source和*this可以是同一个容器。这样的话，pos不可以落在被搬移区间内，而元素就在同一个list内被搬移
  //如果source是另一个list，此操作之后它将内含较少元素
  //调用者必须确保pos是*this的一个有效位置，sourceBeg和sourceEnd定义出source内的一个有效区间；否则此操作的行为将不明确
  //“指向source的成员”的pointer、iterator和reference仍然有效。此后它们属于this
  //此函数不抛出异常，传入容器的end()和cend()作为pos，会导致不明确的行为

  //8.9 容器的策略接口(Policy Interface)
  //8.9.1 非更易型策略函数(Nonmodifying Policy Function)

  //size_type container::capacity()const
  //






  return 0;
}
