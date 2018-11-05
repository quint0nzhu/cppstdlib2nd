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
  //void container::push_bakc(T&& value)
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






  return 0;
}
