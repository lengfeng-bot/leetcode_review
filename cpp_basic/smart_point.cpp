#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Boy

{

public:
    Boy(string name, int age) : m_name(name), m_age(age) { cout << "using construction of " << m_name << endl; };
    ~Boy() { cout << "using destruction of " << m_name << endl; };

    void getInfo()
    {
        cout << "name:" << m_name << endl;
        cout << "age:" << m_age << endl;
    };
    void setInfo(string name, int age)
    {
        m_name = name;
        m_age = age;
    };

    string m_name;
    int m_age;
};

void test_raw_ptr()
{
    Boy *p1 = new Boy("qqqq", 1);
    Boy *p2 = p1;
    p2->getInfo();
    p2 = new Boy("www", 2);
    p2->getInfo();
}

// unique_ptr提供了对单一对象的独占所有权语义。这意味着 unique_ptr 实例拥有其指向的对象，并且当 unique_ptr 被销毁时，它指向的对象也会被自动删除。
void test_unique_ptr()
{ // 创建方法1
    unique_ptr<Boy> p1(new Boy("jack", 10));
    p1->getInfo();

    // 创建方法2
    unique_ptr<Boy> p2 = make_unique<Boy>("peiter", 20);
    p2->getInfo();

    // 不支持普通的拷贝和赋值
    // unique ptr( const unique_ptr&)= delete;
    // unique_ptr<Boy> p3(p2);
    // unique_ptr<Boy> p3 = p2;

    // 可以使用move函数将所有权进行转移,此时p2指针为空
    unique_ptr<Boy> p4 = move(p2);
    p4->getInfo();
    if (!p2)
        cout << "you are transformer!!" << endl;
}

// 使用引用计数实现对同一块内存的多个引用。在最后一个引用被释放时，指向的内存才释放，这也是和 unique_ptr 最大的区别。当对象的所有权需要共享(share)时，share_ptr可以进行赋值拷贝。
// 每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，删除所指向的堆内存。
void test_shared_ptr()
{

    shared_ptr<Boy> p1 = make_shared<Boy>("kikki", 20);
    p1->getInfo();

    // 拷贝构造，增加内部计数引用
    shared_ptr<Boy> p2(p1);
    p2->setInfo("mama", 30);

    // 赋值操作，引用计数增加
    shared_ptr<Boy> p3;
    p3 = p1;

    // 使用 use_count 方法来获取当前的引用计数
    cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;

    // 不能将一个原始指针初始化多个shared_ptr
    Boy *ptr = new Boy("aaa", 99);
    shared_ptr<Boy> ptr1(ptr);
    // 报错
    // shared_ptr<Boy> ptr2(ptr);
}

struct Father;
struct Son;
// shared_ptr最大的问题！循环引用
// 解决办法：使用weak_ptr
struct Father
{
    // shared_ptr<Son> son_;
    weak_ptr<Son> son_;
};

struct Son
{
    shared_ptr<Father> father_;
};

void loop()
{
    auto father = make_shared<Father>();
    auto son = make_shared<Son>();
    cout << father.use_count() << " ";
    cout << son.use_count() << endl;

    father->son_ = son;
    son->father_ = father;
    cout << father.use_count() << " ";
    cout << son.use_count() << endl;
}

int main()
{
    // test_raw_ptr();
    // test_unique_ptr();
    // test_shared_ptr();
    // loop();
    shared_ptr<Boy> p1 = make_shared<Boy>("11", 2);
    shared_ptr<Boy> pt1 = make_shared<Boy>("22", 4);
    shared_ptr<Boy> p2(p1);
    shared_ptr<Boy> p3(p1);

    cout << p2.use_count() << endl;
    p2.reset();
    // cout << p1.use_count() << endl;
    // p3.reset();
    // cout << p1.use_count() << endl;
    // p1.reset();
    // cout << p1.use_count() << endl;
    cout << p2.use_count() << endl;

    cout
        << "------------------" << endl;
    system("pause");
    return 0;
}
