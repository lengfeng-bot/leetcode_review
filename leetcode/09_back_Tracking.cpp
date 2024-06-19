#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
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
// 这道题我刚开始搞了两层循环，但其实只需要在回溯代码中遍历宽度即可，深度是通过回溯得到的
unordered_map<char, string> phoneMap{
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}};

vector<string> ans02;
string path02;

void backtracking02(int start, string digits)
{
    if (start == digits.size())
    {
        ans02.push_back(path02);
        return;
    }

    for (auto d : phoneMap[digits[start]])
    {
        path02.push_back(d);
        backtracking02(start + 1, digits);
        path02.pop_back();
    }
}

vector<string> letterCombinations(string digits)
{
    if (digits.size() == 0)
        return ans02;

    backtracking02(0, digits);
    return ans02;
}

// int main()
// {
//     vector<string> output = letterCombinations("23");
//     for (auto out : output)
//         cout << out << " ";
//     cout << endl;
//     system("pause");
//     return 0;
// }

// 组合总和1
// 这道题真难，去重复这个问题我不知道修改哪个地方，只能对结果处理了。虽然过了，但时间垫底。。
int sum1 = 0;
void backtracking03(vector<int> &candidates, int target, int start)
{
    if (sum1 > target)
    {
        return;
    }
    if (sum1 == target)
    {
        ans.push_back(path);

        return;
    }
    if (start == target / 2 + 1)
        return;

    for (int i = 0; i < candidates.size(); i++)
    {
        path.push_back(candidates[i]);
        sum1 += candidates[i];
        backtracking03(candidates, target, start + 1);
        path.pop_back();
        sum1 -= candidates[i];
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    ans.clear();
    path.clear();
    backtracking03(candidates, target, 0);
    for (int i = 0; i < ans.size(); i++)
    {
        sort(ans[i].begin(), ans[i].end());
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    return ans;
}

// int main()
// {
//     vector<int> can = {3, 5, 8};
//     vector<vector<int>> ans = combinationSum(can, 11);

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

/// @brief 组合总和2
/// @param candidates
/// @param target
/// @return
vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
}