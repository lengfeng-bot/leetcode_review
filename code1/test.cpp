#include <iostream>
// Ctrl+Shift+B 编译
// shift+Alt+F 自动对齐代码
// Ctrl+Shift+P 打开命令面板
#include <limits> // Add missing include directive
using namespace std;
int main()
{

    int num1 = 0;
    int num2 = 0;
    while (!(std::cin >> num1 >> num2))
    {
        std::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter two integers: ";
    }

    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += num1 + num2;
    }

    std::cout << "The sum is: " << sum << std::endl;
    system("pause");
    return 0;
}