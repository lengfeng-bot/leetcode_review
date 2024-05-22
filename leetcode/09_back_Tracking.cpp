#include <iostream>
#include <vector>

using namespace std;

// 回溯法的模板！！重要
//  void backtracking(参数)
//  {
//      if (终止条件)
//      {
//          存放结果;
//          return;
//      }

//     for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）)
//     {
//         处理节点;
//         backtracking(路径，选择列表); // 递归
//         回溯，撤销处理结果
//     }
// }

vector<vector<int>> ans;
vector<int> path;

void backtracking(int n, int k, int start)
{
    if (path.size() == k)
    {
        ans.push_back(path);
        return;
    }

    // for (int i = start; i <= n; i++)
    // 剪枝优化
    for (int i = start; i <= n - (k - path.size()) + 1; i++)
    {
        path.push_back(i);
        backtracking(n, k, i + 1);
        path.pop_back();
    }
}

// 组合
vector<vector<int>> combine(int n, int k)
{

    backtracking(n, k, 1);
    return ans;
}

// int main()
// {
//     vector<vector<int>> ans = combine(4, 2);
//     for (int i = 0; i < ans.size(); i++)
//     {
//         for (auto c : ans[i])
//             cout << c << " ";

//         cout << endl;
//     }
//     system("pause");
//     return 0;
// }

int sum = 0;

void backtracking01(int k, int n, int start)
{
    if (sum > n)
    { // 剪枝操作
        return;
    }
    if (sum == n && path.size() == k)
    {
        ans.push_back(path);
        return;
    }
    if (path.size() == k)
        return;

    for (int i = start; i <= 9; i++)
    {
        path.push_back(i);
        sum += i;
        backtracking01(k, n, i + 1);
        path.pop_back();
        sum -= i;
    }
}

vector<vector<int>> combinationSum3(int k, int n)
{
    ans.clear();
    path.clear();
    backtracking01(k, n, 1);
    return ans;
}

// int main()
// {
//     vector<vector<int>> ans = combinationSum3(2, 18);

//     // print
//     for (int i = 0; i < ans.size(); i++)
//     {
//         for (auto c : ans[i])
//             cout << c << " ";

//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

// 电话号码的字母组合
vector<string> letterCombinations(string digits)
{
    if (digits.size() == 0)
        return {};
    dfs(0, digits);
    return ans;
}
