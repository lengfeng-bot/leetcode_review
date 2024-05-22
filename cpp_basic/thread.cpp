#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h> //sleep

using namespace std;

void t1()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "11111\n";
        _sleep(1);
    }
}

void t2()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "22222\n";
        _sleep(1);
    }
}

// join()调用该函数会阻塞当前线程（主调线程）。阻塞调用者(caller)所在的线程（主调线程）直至被join的std::thread对象标识的线程（被调线程）执行结束。

// detach：将当前线程对象所代表的执行实例与该线程对象分离，使得线程的执行可以单独进行。一旦线程执行完毕，它所分配的资源将会被释放。

// join会使调用它的线程阻塞，直到目标线程完成，而detach会让目标线程在后台运行，不会阻塞调用线程。

// int main()
// {

//     thread th1(t1); // 实例化一个线程对象th1，使用函数t1构造，然后该线程就开始执行了（t1()）
//     thread th2(t2);
//     th1.join();
//     th2.join();
//     // th1.detach();
//     // th2.detach();
//     cout << "here is main\n\n";

//     cout << "-------------------" << endl;
//     system("pause");
//     return 0;
// }

#include <mutex>
// 互斥锁
std::mutex mtx; // 定义一个全局的互斥锁

// std::lock_guard 用于管理互斥锁的加锁和解锁操作。它的主要作用是在构造函数中获取一个互斥锁，然后在析构函数中自动释放该锁，以确保在锁保护区域的结束时正确解锁。
// 简单来说就是使用 std::lock_guard 让开发者使用时不用关心 std::mutex 锁的释放。

int cnt = 20;

void t3()
{
    std::lock_guard<mutex> lock(mtx);
    for (int i = 0; i < 5; i++)
    {
        cnt--;
        cout << cnt << endl;
    }
}

void t4()
{
    std::lock_guard<mutex> lock(mtx);
    for (int i = 0; i < 5; i++)
    {
        cnt++;
        cout << cnt << endl;
    }
}

int main()
{
    thread th1(t3);
    thread th2(t4);

    th1.join();
    th2.join();

    cout << "end of main\n";
    system("pause");
    return 0;
}
