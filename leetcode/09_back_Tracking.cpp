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
// 修改start!
int sum1 = 0;
void backtracking03(vector<int> &candidates, int target, int start)
{
    if (sum1 > target)
        return;

    if (sum1 == target)
    {
        ans.push_back(path);
        return;
    }
    for (int i = start; i < candidates.size(); i++)
    {
        path.push_back(candidates[i]);
        sum1 += candidates[i];
        backtracking03(candidates, target, start);
        path.pop_back();
        sum1 -= candidates[i];
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    ans.clear();
    path.clear();
    backtracking03(candidates, target, 0);
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
int sum2 = 0;
void backtracking04(vector<int> &candidates, int target, int start)
{

    if (sum2 > target)
        return;
    if (sum2 == target)
    {

        ans.push_back(path);
        return;
    }

    for (int i = start; i < candidates.size(); i++)
    {
        // 关键去重，其实i>start不太能够理解
        if (i > start && candidates[i] == candidates[i - 1])
        {
            continue;
        }
        path.push_back(candidates[i]);
        sum2 += candidates[i];
        backtracking04(candidates, target, i + 1);
        sum2 -= candidates[i];
        path.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    ans.clear();
    path.clear();
    sort(candidates.begin(), candidates.end());
    backtracking04(candidates, target, 0);
    return ans;
}

// int main()
// {
//     vector<int> can = {1, 1, 2, 3};
//     vector<vector<int>> ans = combinationSum2(can, 4);

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

vector<vector<string>> res;
vector<string> pth;

bool is_Palindrome(string s)
{
    int n = s.size();
    if (n == 1)
        return true;
    int l = 0, r = n - 1;
    while (l < r)
    {
        if (s[l] == s[r])
        {
            l++;
            r--;
        }
        else
            return false;
    }
    return true;
}

/// @brief 分割回文串

void backtracking10(string s, int begin)
{

    if (begin == s.size())
    {
        res.push_back(pth);
        return;
    }

    for (int i = begin; i < s.size(); i++)
    {
        string c = s.substr(begin, i - begin + 1);
        if (is_Palindrome(c))
        {

            pth.push_back(c);
            backtracking10(s, i + 1);
            pth.pop_back();
        }
        else
            continue;
    }
}

vector<vector<string>> partition(string s)
{
    backtracking10(s, 0);
    return res;
}

// int main()
// {

//     string s = "aab";
//     vector<vector<string>> result = partition(s);

//     for (int i = 0; i < result.size(); i++)
//     {
//         for (auto r : result[i])
//             cout << r << " ";
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

vector<string> result;
string road;

void backtracking10(string s, int start, int sub_size, int num_comma)
{

    if (num_comma == 4)
    {
        string cur = road.substr(road.size() - 1 - sub_size, sub_size);
        if (stoi(cur) > 255 || (cur.size() > 1 && cur[0] == '0') || (road.size() - 4 < s.size()))
            return;
        else
        {
            string r = road;
            r.pop_back();
            result.push_back(r);
            return;
        }
    }

    for (int i = start; i < s.size(); i++)
    {
        string cur = s.substr(start, i - start + 1);
        if (stoi(cur) > 255 || (cur.size() > 1 && cur[0] == '0'))
            break;

        road.append(cur);
        road.append(".");
        num_comma++;
        backtracking10(s, i + 1, cur.size(), num_comma);
        num_comma--;
        road.pop_back();
        road.erase(road.size() - cur.size());
    }
}

/// @brief 复原IP地址
/// @param s
/// @return
vector<string> restoreIpAddresses(string s)
{

    backtracking10(s, 0, 0, 0);
    return result;
}

// int main()
// {

//     string s = "101023";
//     vector<string> result = restoreIpAddresses(s);

//     for (int i = 0; i < result.size(); i++)
//     {
//         for (auto r : result[i])
//             cout << r << " ";
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

vector<vector<int>> ans11;
vector<int> path11;

void backtracking11(vector<int> &nums, int start)
{

    ans11.push_back(path11);

    for (int i = start; i < nums.size(); i++)
    {

        path11.push_back(nums[i]);
        backtracking11(nums, i + 1);
        path11.pop_back();
    }
}

/// @brief 子集问题1
/// @param nums
/// @return
vector<vector<int>> subsets(vector<int> &nums)
{

    backtracking11(nums, 0);
    return ans11;
}

// int main()
// {

//     vector<int> nums = {1, 2, 3};
//     vector<vector<int>> result = subsets(nums);

//     for (int i = 0; i < result.size(); i++)
//     {
//         for (auto r : result[i])
//             cout << r << " ";
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

/// @brief 子集问题2
/// @param nums
/// @return

vector<vector<int>> ans12;
vector<int> path12;

void backtracking12(vector<int> &nums, int start)
{

    ans12.push_back(path12);

    for (int i = start; i < nums.size(); i++)
    {
        if (i != start && nums[i] == nums[i - 1])
            continue;
        path12.push_back(nums[i]);
        backtracking12(nums, i + 1);
        path12.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    backtracking12(nums, 0);
    return ans;
}

vector<vector<int>> ans13;
vector<int> path13;

void backtracking13(vector<int> &nums, vector<bool> used)
{
    if (path13.size() == nums.size())
    {
        ans13.push_back(path13);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {

        if (used[i] == 1)
            continue;
        else
            used[i] = 1;
        path13.push_back(nums[i]);
        backtracking11(nums, used);
        used[i] = 0;
        path11.pop_back();
    }
}

// 全排列
vector<vector<int>> permute(vector<int> &nums)
{
    vector<bool> used(nums.size(), 0);
    backtracking13(nums, used);
    return ans13;
}

// int main()
// {

//     vector<int> nums = {1, 2, 3};
//     vector<vector<int>> result = permute(nums);

//     for (int i = 0; i < result.size(); i++)
//     {
//         for (auto r : result[i])
//             cout << r << " ";
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

vector<vector<int>> ans14;
vector<int> path;

void backtracking14(vector<int> &nums, unordered_map<int, int> &used)
{
    if (path14.size() == nums.size())
    {
        ans14.push_back(path14);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }

        if (used[nums[i]] <= 0)
            continue;

        else
            used[nums[i]]--;

        path14.push_back(nums[i]);
        backtracking11(nums, used);
        used[nums[i]]++;
        path14.pop_back();
    }
}

// 全排列2
vector<vector<int>> permuteUnique(vector<int> &nums)
{
    unordered_map<int, int> used;
    for (auto c : nums)
        used[c]++;
    sort(nums.begin(), nums.end());
    backtracking11(nums, used);
    return ans14;
}

// int main()
// {

//     vector<int> nums = {1, 1, 2};
//     vector<vector<int>> result = permute(nums);

//     for (int i = 0; i < result.size(); i++)
//     {
//         for (auto r : result[i])
//             cout << r << " ";
//         cout << endl;
//     }

//     system("pause");
//     return 0;
// }

vector<vector<string>> ways;
vector<string> way;

void queentracking(int n, vector<int> blackaera)
{

    if (way.size() == n)
    {
        ways.push_back(way);
        return;
    }
}

// N皇后！！
vector<vector<string>> solveNQueens(int n)
{
}