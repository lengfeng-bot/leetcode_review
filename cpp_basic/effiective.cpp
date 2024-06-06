#include <iostream>
#include <string>
#include <list>
using namespace std;

class PhoneNumber
{
    ....
};

// ABEbtry = Adress Book Entry
class ABEbtry
{

public:
    // 赋值初始化
    ABEbtry(const string &name, const string &address, const list<PhoneNumber> &phones)
    {

        theName = name;
        theAddress = address;
        thePhones = phones;
        numTimes = 0;
    }

    // 初始化列表
    ABEbtry(const string &name, const string &address, const list<PhoneNumber> &phones)
        : theNmae(name),
          theAddress(address),
          thePhones(phones),
          numTimes(0)
    {
    }

private:
    string theName;
    string theAddress;
    list<PhoneNumber> thePhones;
    int numTimes;
}

class Empty
{

public:
    Empty(){...} // 默认构造函数
    Empty(const Empty &rhs)
    {
        ...
    } // 拷贝构造函数
    ~Empty(){...} // 析构函数
    Empty &operator=(const Empty & rhs)
    {
        ...
    } // 拷贝操作符重载
};

class Uncopyable
{

protected:
    Uncopyable(/* args */); // 允许继承对象构造和析构
    ~Uncopyable();

private:
    Uncopyable(const Uncopyable &rhs); // 阻止copying
    Uncopyable &operator=(const Uncopyable &rhs);
};

class Hajimi : private Uncopyable
{
};

// class Hajimi
// {
// private:
//     Hajimi(const Hajimi &rhs); // 只有声明，Hajimi只有一个！
//     Hajimi &operator=(const Hajimi &rhs);

// public:
// };

class Base
{
public:
    Base() { sayHello(); }

    virtual void sayHello()
    {
        std::cout << "Hello,Base!" << std::endl;
    }

    virtual void sayBye()
    {
        std::cout << "Bye,Base!" << std::endl;
    }

    virtual ~Base()
    {
        sayBye();
    }
}

class Derived : public Base
{
public:
    Derived() {}

    void sayHello() override
    {
        std::cout << "Hello,Derived!" << std::endl;
    }
    void sayBye() override
    {
        std::cout << "Bye,Derived!" << std::endl;
    }
};
