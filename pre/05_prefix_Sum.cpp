#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/// 一维前缀和
///
///
///
///  经典模板
class NumArray
{
public:
    vector<int> sums;

    NumArray(vector<int> &nums)
    {
        int n = nums.size();
        sums.resize(n + 1);
        for (int i = 0; i < n; i++)
        {
            sums[i + 1] = sums[i] + nums[i];
        }
    }

    int sumRange(int i, int j)
    {
        return sums[j + 1] - sums[i];
    }
};

/// <summary>
/// 构建回文串检测
/// </summary>

/// 自己笨戳的解法，还错了！！！
vector<bool> canMakePaliQueries1(string s, vector<vector<int>> &queries)
{
    unordered_map<char, int> map;
    int count = 0;
    int num = 0;
    vector<bool> ans;
    for (int i = 0; i < 25; i++)
    {
        map['a' + i] = 0;
    }
    for (int i = 0; i < queries.size(); i++)
    {
        for (int j = queries[i][0]; j <= queries[i][1]; j++)
        {
            map[s[j]]++;
            if (map[s[j]] % 2 != 0)
                count++;
        }
        num = queries[i][1] - queries[i][0] + 1;
        if (num % 2 == 0)
        {
            if (queries[i][2] >= count / 2)
                ans.push_back(true);
            else
                ans.push_back(false);
        }
        else
        {
            if (queries[i][2] >= (count - 1) / 2)
                ans.push_back(true);
            else
                ans.push_back(false);
        }
    }
    return ans;
}
/// <summary>
/// 完美的解法，前缀和+位运算 ,但是我现在想不到，
/// </summary>
vector<bool> canMakePaliQueries2(string s, vector<vector<int>> &queries)
{
    int n = s.size();
    vector<int> count(n + 1);
    for (int i = 0; i < n; i++)
    {
        count[i + 1] = count[i] ^ (1 << (s[i] - 'a'));
    }
    vector<bool> res;
    for (auto &query : queries)
    {
        int l = query[0], r = query[1], k = query[2];
        int bits = 0, x = count[r + 1] ^ count[l];
        while (x > 0)
        {
            x &= x - 1;
            bits++;
        }
        res.push_back(bits <= k * 2 + 1);
    }
    return res;
}

// int main() {
//     string s = "abcda";
//     vector<vector<int>> queries = {{0,3,2},{0,4,1}};
//     vector<bool> answer = canMakePaliQueries1(s, queries);
//     std::cout << "检测结果：";
//     for (bool result : answer) {
//         std::cout << (result ? "true " : "false ");
//     }
//
//     return 0;
// }

/// <summary>
/// 除自身以外数组的乘积
/// </summary>
/// 先暴力，发现超时了，之后想办法使用O(n)时间求解，也就是说，遍历ans和nums只能使用一个for循环，按照是这个思路，考虑前缀乘积求解。
/// 同时要满足空间复杂度O(1),就通过改变输出数组ans解决问题！
vector<int> productExceptSelf(vector<int> &nums)
{
    int n = nums.size();
    vector<int> result(n, 1);

    // 计算左侧乘积并存储在result中
    int leftProduct = 1;
    for (int i = 0; i < n; i++)
    {
        result[i] *= leftProduct;
        leftProduct *= nums[i];
    }

    // 计算右侧乘积并乘以result中对应位置的值
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }

    return result;
}

// int main() {
//     vector<int> nums = { 1, 2, 3, 4 };
//     vector<int> result = productExceptSelf(nums);
//
//     cout << "除自身以外数组的乘积：";
//     for (int num : result) {
//         cout << num << " ";
//     }
//     cout << endl;
//
//     return 0;
// }

/// <summary>
/// 向下取整数对和
/// </summary>
/// 直接暴力解，很明显是O(n2)超时了，时间复杂度只能为O(n),思路转换：与其算出每一对的结果再相加，不如直接算出某个结果出现了多少次，相乘之后再相加,,后面想不出来了。。
int sumOfFlooredPairs(vector<int> &nums)
{
    vector<long long> arr(200010, 0);
    vector<long long> sum(200010, 0);
    int maxV = 0;
    long long ret = 0;
    for (auto it : nums)
    {
        maxV = max(maxV, it);
        arr[it]++;
    }
    for (int i = 1; i <= maxV * 2; ++i)
    {
        sum[i] = sum[i - 1] + arr[i];
    }
    for (int i = 1; i <= maxV; ++i)
    {
        if (arr[i] > 0)
        {
            for (long long j = 1; j * i <= maxV; ++j)
            {
                // 后面那部分意义是：数字i的出现次数 乘以 整数部分j 乘以 （数组中除以i的整数部分是j的数字的数量）
                ret = (ret + (sum[(j + 1) * i - 1] - sum[j * i - 1]) * j * arr[i]) % 1000000007;
            }
        }
    }
    return ret;
}

// int main() {
//     vector<int> nums = {7,7,7,7,7,7,7 };
//     int result = sumOfFlooredPairs(nums);
//
//     cout << "整数对和的下取整数：" << result << endl;
//
//     return 0;
// }
